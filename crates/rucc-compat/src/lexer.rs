//! Splitting preprocessed output back into preprocessing tokens.
//!
//! The comparison the harness is making is over tokens, not over text, and the difference
//! matters in both directions. Two outputs that differ only in where the spaces are hold the
//! same tokens and the compiler behind them will do the same thing. Two outputs that differ
//! by one space between `int` and `x` do not, and text with the whitespace taken out of it
//! cannot tell those apart.
//!
//! This is the phase 3 lexer from the standard and nothing more: identifiers, preprocessing
//! numbers, character constants, string literals and punctuators. It never has to decide what
//! a token means, only where it ends.

/// The punctuators, longest first, so that the first one that matches is the right one.
const PUNCTUATORS: &[&str] = &[
    "%:%:", "...", "<<=", ">>=", "->", "++", "--", "<<", ">>", "<=", ">=", "==", "!=", "&&", "||",
    "*=", "/=", "%=", "+=", "-=", "&=", "^=", "|=", "##", "<:", ":>", "<%", "%>", "%:", "[", "]",
    "(", ")", "{", "}", ".", "&", "*", "+", "-", "~", "!", "/", "%", "<", ">", "^", "|", "?", ":",
    ";", "=", ",", "#",
];

/// The tokens in `text`, as they were spelled.
///
/// Whitespace and newlines separate tokens and are not tokens. A literal that is never closed
/// ends at the newline, because the alternative is one token that swallows the rest of the
/// file and a difference report that says nothing.
#[must_use]
pub fn tokens(text: &str) -> Vec<String> {
    let bytes = text.as_bytes();
    let mut out = Vec::new();
    let mut at = 0;
    while at < bytes.len() {
        let byte = bytes[at];
        if byte.is_ascii_whitespace() {
            at += 1;
            continue;
        }
        let end = if starts_identifier(byte) {
            identifier(bytes, at)
        } else if byte.is_ascii_digit()
            || (byte == b'.' && at + 1 < bytes.len() && bytes[at + 1].is_ascii_digit())
        {
            number(bytes, at)
        } else if byte == b'"' || byte == b'\'' {
            literal(bytes, at)
        } else {
            punctuator(text, at)
        };
        out.push(text[at..end].to_owned());
        at = end;
    }
    out
}

/// An identifier can start with a letter, an underscore, a dollar as an extension, or a
/// byte of something outside ASCII, which is how a UTF-8 identifier reaches us.
fn starts_identifier(byte: u8) -> bool {
    byte.is_ascii_alphabetic() || byte == b'_' || byte == b'$' || byte >= 0x80
}

fn identifier(bytes: &[u8], from: usize) -> usize {
    let mut at = from + 1;
    while at < bytes.len() {
        let byte = bytes[at];
        if starts_identifier(byte) || byte.is_ascii_digit() {
            at += 1;
        } else {
            break;
        }
    }
    at
}

/// A preprocessing number, which is looser than any number the language has: a digit or a dot
/// followed by digits, letters, dots and the sign after an exponent.
fn number(bytes: &[u8], from: usize) -> usize {
    let mut at = from + 1;
    while at < bytes.len() {
        let byte = bytes[at];
        if matches!(byte, b'e' | b'E' | b'p' | b'P')
            && at + 1 < bytes.len()
            && matches!(bytes[at + 1], b'+' | b'-')
        {
            at += 2;
            continue;
        }
        if byte.is_ascii_alphanumeric() || byte == b'_' || byte == b'.' || byte >= 0x80 {
            at += 1;
            continue;
        }
        break;
    }
    at
}

/// A string or character literal, ending at its quote or at the newline.
fn literal(bytes: &[u8], from: usize) -> usize {
    let quote = bytes[from];
    let mut at = from + 1;
    while at < bytes.len() {
        match bytes[at] {
            b'\n' => return at,
            b'\\' if at + 1 < bytes.len() && bytes[at + 1] != b'\n' => at += 2,
            byte if byte == quote => return at + 1,
            _ => at += 1,
        }
    }
    at
}

fn punctuator(text: &str, from: usize) -> usize {
    let rest = &text[from..];
    for punctuator in PUNCTUATORS {
        if rest.starts_with(punctuator) {
            return from + punctuator.len();
        }
    }
    // Something that is not a token at all, such as a stray backslash. One byte at a time, so
    // that it shows up in the report rather than stopping the run.
    from + text[from..].chars().next().map_or(1, char::len_utf8)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn spacing_does_not_change_the_tokens_but_pasting_does() {
        assert_eq!(tokens("int  x ;"), tokens("int x;"));
        assert_ne!(tokens("int x;"), tokens("intx;"));
    }

    #[test]
    fn a_punctuator_is_the_longest_one_that_matches() {
        assert_eq!(tokens("a>>=b"), ["a", ">>=", "b"]);
        assert_eq!(tokens("a > > = b"), ["a", ">", ">", "=", "b"]);
        assert_eq!(tokens("x?y:z"), ["x", "?", "y", ":", "z"]);
    }

    #[test]
    fn a_preprocessing_number_holds_its_exponent_sign() {
        assert_eq!(tokens("1e+5"), ["1e+5"]);
        assert_eq!(tokens("1e +5"), ["1e", "+", "5"]);
        assert_eq!(tokens("0x1p-3f"), ["0x1p-3f"]);
        assert_eq!(tokens(".5"), [".5"]);
        assert_eq!(tokens("x.5"), ["x", ".5"]);
    }

    #[test]
    fn a_number_next_to_a_plus_is_two_tokens_either_way() {
        // GCC prints `41 +1` where we would print `41+1`, and both are the same two tokens.
        // That difference belongs to the spacing rule, not to this one.
        assert_eq!(tokens("41 +1"), tokens("41+1"));
    }

    #[test]
    fn a_string_keeps_its_spaces_and_its_escapes() {
        assert_eq!(tokens("\"a  b\" \"c\""), ["\"a  b\"", "\"c\""]);
        assert_eq!(tokens("\"a\\\"b\""), ["\"a\\\"b\""]);
        assert_eq!(tokens("'\\''"), ["'\\''"]);
        assert_eq!(tokens("L\"wide\""), ["L", "\"wide\""]);
    }

    #[test]
    fn an_unclosed_literal_ends_at_the_line_rather_than_eating_the_file() {
        assert_eq!(tokens("'a\nint x;"), ["'a", "int", "x", ";"]);
    }

    #[test]
    fn an_identifier_can_hold_a_dollar_and_a_utf8_letter() {
        assert_eq!(tokens("$name x"), ["$name", "x"]);
        assert_eq!(tokens("\u{00e9}t\u{00e9} = 1"), ["\u{00e9}t\u{00e9}", "=", "1"]);
    }
}
