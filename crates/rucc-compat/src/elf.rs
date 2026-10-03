//! Just enough of ELF64 to compare two relocatable objects the way the `kernel-asm` corpus needs.
//!
//! Two assemblers given the same text should write the same object. Not the same file byte for
//! byte, since nothing makes them lay out the string tables or order the symbol table the same
//! way, but the same sections with the same flags and contents, the same symbols and the same
//! relocations. That is what the linker reads, so that is what [`compare`] looks at.
//!
//! One choice is allowed to differ. A relocation against a local label can name the label, or
//! name its section with the label's offset added to the addend, and gas nearly always does the
//! second. The two mean the same thing to the linker, so every relocation against a local symbol
//! is read as one against its section before anything is compared. The contents of `.comment` and
//! `.note.gnu.property` are not compared either, since they say which tool wrote the file.

use std::collections::BTreeMap;
use std::fmt;

const SHT_SYMTAB: u32 = 2;
const SHT_STRTAB: u32 = 3;
const SHT_RELA: u32 = 4;
const SHT_NOBITS: u32 = 8;
const SHT_REL: u32 = 9;
const SHT_GROUP: u32 = 17;
const SHT_SYMTAB_SHNDX: u32 = 18;

const SHF_INFO_LINK: u64 = 0x40;
const SHF_LINK_ORDER: u64 = 0x80;

const STB_LOCAL: u8 = 0;
const STT_SECTION: u8 = 3;
const STT_FILE: u8 = 4;

const SHN_UNDEF: u16 = 0;
const SHN_ABS: u16 = 0xfff1;
const SHN_COMMON: u16 = 0xfff2;

/// Sections whose contents are a note about the tool that wrote them rather than about the code.
const TOOL_NOTES: &[&str] = &[".comment", ".note.gnu.property"];

/// One section, with its relocations folded in and every index in it turned into a name.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Section {
    /// The name, as in `.text` or `.altinstructions`.
    pub name: String,
    /// `sh_type`.
    pub kind: u32,
    /// `sh_flags`, without `SHF_INFO_LINK`, which only says how `sh_info` is spelled.
    pub flags: u64,
    /// `sh_size`.
    pub size: u64,
    /// `sh_addralign`.
    pub align: u64,
    /// `sh_entsize`.
    pub entsize: u64,
    /// The section a `SHF_LINK_ORDER` section is ordered by, by name.
    pub link: Option<String>,
    /// The contents, empty for `SHT_NOBITS`. A group's contents are its flag word and its member
    /// sections by name, one per line.
    pub bytes: Vec<u8>,
    /// The relocations against it, in offset order.
    pub relocs: Vec<Reloc>,
}

/// One symbol, with its section by name.
#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord)]
pub struct Symbol {
    /// The name.
    pub name: String,
    /// The section it is defined in, or `UND`, `ABS` or `COM`.
    pub section: String,
    /// `st_value`.
    pub value: u64,
    /// `st_size`.
    pub size: u64,
    /// The binding, the high four bits of `st_info`.
    pub bind: u8,
    /// The type, the low four bits of `st_info`.
    pub kind: u8,
    /// `st_other`, which holds the visibility.
    pub other: u8,
}

/// One relocation, with what it points at by name.
#[derive(Debug, Clone, PartialEq, Eq, PartialOrd, Ord)]
pub struct Reloc {
    /// `r_offset`.
    pub offset: u64,
    /// The relocation type.
    pub kind: u32,
    /// The symbol, or `[section]` for a section symbol or a local one read as its section.
    pub target: String,
    /// The addend, from the entry for `RELA` and zero for `REL`.
    pub addend: i64,
}

/// A relocatable object, read.
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct Object {
    /// Every section but the null one, the symbol and string tables and the relocation sections,
    /// in file order.
    pub sections: Vec<Section>,
    /// Every symbol but the null one, section symbols and file symbols, sorted.
    pub symbols: Vec<Symbol>,
}

struct Header {
    name: u32,
    kind: u32,
    flags: u64,
    offset: u64,
    size: u64,
    link: u32,
    info: u32,
    align: u64,
    entsize: u64,
}

struct Raw {
    name: String,
    section: u16,
    value: u64,
    size: u64,
    info: u8,
    other: u8,
}

fn slice(data: &[u8], at: u64, len: u64) -> Result<&[u8], String> {
    let at = usize::try_from(at).map_err(|_| "an offset past the end".to_owned())?;
    let len = usize::try_from(len).map_err(|_| "a size past the end".to_owned())?;
    data.get(at..at.checked_add(len).ok_or("a size past the end")?)
        .ok_or_else(|| format!("{len} bytes at {at} run past the end of the file"))
}

fn u16_at(data: &[u8], at: usize) -> u16 {
    u16::from_le_bytes([data[at], data[at + 1]])
}

fn u32_at(data: &[u8], at: usize) -> u32 {
    u32::from_le_bytes(data[at..at + 4].try_into().expect("four bytes"))
}

fn u64_at(data: &[u8], at: usize) -> u64 {
    u64::from_le_bytes(data[at..at + 8].try_into().expect("eight bytes"))
}

fn string(table: &[u8], at: u32) -> String {
    let at = at as usize;
    let rest = table.get(at..).unwrap_or_default();
    let end = rest.iter().position(|b| *b == 0).unwrap_or(rest.len());
    String::from_utf8_lossy(&rest[..end]).into_owned()
}

/// Where the fields of an ELF file are, which is all that differs between ELF32 and ELF64 here.
struct Class {
    /// Whether it is ELF64.
    wide: bool,
}

impl Class {
    /// A word, which is an address, an offset or a size.
    fn word(&self, data: &[u8], at: usize) -> u64 {
        if self.wide { u64_at(data, at) } else { u64::from(u32_at(data, at)) }
    }

    /// Where a field of the file header, a section header or a symbol is, by its ELF64 offset.
    fn file(&self, at64: usize) -> usize {
        if self.wide {
            return at64;
        }
        match at64 {
            40 => 32,
            58 => 46,
            60 => 48,
            62 => 50,
            _ => at64,
        }
    }

    fn section(&self, at64: usize) -> usize {
        if self.wide {
            return at64;
        }
        match at64 {
            24 => 16,
            32 => 20,
            40 => 24,
            44 => 28,
            48 => 32,
            56 => 36,
            _ => at64,
        }
    }

    fn header_size(&self) -> u64 {
        if self.wide { 64 } else { 40 }
    }

    fn symbol_size(&self) -> usize {
        if self.wide { 24 } else { 16 }
    }

    /// The size of a relocation, with or without its addend.
    fn reloc_size(&self, rela: bool) -> usize {
        match (self.wide, rela) {
            (true, true) => 24,
            (true, false) => 16,
            (false, true) => 12,
            (false, false) => 8,
        }
    }

    /// The symbol and the type a relocation's info word holds.
    fn info(&self, info: u64) -> (u32, u32) {
        if self.wide {
            ((info >> 32) as u32, (info & 0xffff_ffff) as u32)
        } else {
            ((info >> 8) as u32, (info & 0xff) as u32)
        }
    }
}

/// Reads a little endian ELF64 or ELF32 relocatable object.
///
/// ELF32 is what the kernel's 16-bit and 32-bit boot code is built as. Its relocations are
/// `SHT_REL`, which keep the addend in the bytes they patch, so comparing the bytes compares it.
///
/// # Errors
///
/// When it is not one, or it points past its own end.
pub fn read(data: &[u8]) -> Result<Object, String> {
    if data.len() < 52 || &data[..4] != b"\x7fELF" {
        return Err("not an ELF file".to_owned());
    }
    if !matches!(data[4], 1 | 2) || data[5] != 1 || (data[4] == 2 && data.len() < 64) {
        return Err("not a little endian ELF32 or ELF64 file".to_owned());
    }
    let class = Class { wide: data[4] == 2 };
    if u16_at(data, 16) != 1 {
        return Err("not a relocatable object".to_owned());
    }
    let shoff = class.word(data, class.file(40));
    let shentsize = u64::from(u16_at(data, class.file(58)));
    let mut shnum = u64::from(u16_at(data, class.file(60)));
    let mut shstrndx = u32::from(u16_at(data, class.file(62)));
    if shentsize < class.header_size() {
        return Err("section headers are too small".to_owned());
    }
    // Past 0xff00 sections the counts live in the first section header, which the kernel's
    // biggest objects need.
    if shoff != 0 {
        let first = slice(data, shoff, class.header_size())?;
        if shnum == 0 {
            shnum = class.word(first, class.section(32));
        }
        if shstrndx == 0xffff {
            shstrndx = u32_at(first, class.section(40));
        }
    }
    let table = slice(data, shoff, shnum * shentsize)?;
    let headers: Vec<Header> = (0..shnum as usize)
        .map(|n| {
            let h = &table[n * shentsize as usize..];
            Header {
                name: u32_at(h, 0),
                kind: u32_at(h, 4),
                flags: class.word(h, 8),
                offset: class.word(h, class.section(24)),
                size: class.word(h, class.section(32)),
                link: u32_at(h, class.section(40)),
                info: u32_at(h, class.section(44)),
                align: class.word(h, class.section(48)),
                entsize: class.word(h, class.section(56)),
            }
        })
        .collect();
    let contents = |h: &Header| -> Result<&[u8], String> {
        if h.kind == SHT_NOBITS { Ok(&[]) } else { slice(data, h.offset, h.size) }
    };
    let names = headers.get(shstrndx as usize).map(&contents).transpose()?.unwrap_or_default();
    let name_of = |n: usize| headers.get(n).map(|h| string(names, h.name)).unwrap_or_default();

    let mut raw = Vec::new();
    if let Some(symtab) = headers.iter().find(|h| h.kind == SHT_SYMTAB) {
        let strings = headers.get(symtab.link as usize).map(&contents).transpose()?;
        let strings = strings.unwrap_or_default();
        let wide =
            headers.iter().find(|h| h.kind == SHT_SYMTAB_SHNDX).map(&contents).transpose()?;
        let body = contents(symtab)?;
        for (n, s) in body.chunks_exact(class.symbol_size()).enumerate() {
            // ELF32 puts the value and size before the info, other and section fields.
            let (value, size, info, other, at) = if class.wide {
                (u64_at(s, 8), u64_at(s, 16), s[4], s[5], 6)
            } else {
                (u64::from(u32_at(s, 4)), u64::from(u32_at(s, 8)), s[12], s[13], 14)
            };
            let mut section = u16_at(s, at);
            if section == 0xffff {
                if let Some(wide) = wide.filter(|w| w.len() >= n * 4 + 4) {
                    section = u16::try_from(u32_at(wide, n * 4)).unwrap_or(u16::MAX);
                }
            }
            raw.push(Raw {
                name: string(strings, u32_at(s, 0)),
                section,
                value,
                size,
                info,
                other,
            });
        }
    }
    let place = |section: u16| match section {
        SHN_UNDEF => "UND".to_owned(),
        SHN_ABS => "ABS".to_owned(),
        SHN_COMMON => "COM".to_owned(),
        n => name_of(n as usize),
    };
    // What a relocation points at, with a local symbol read as its section plus its value.
    let target = |index: u32| -> (String, i64) {
        let Some(sym) = raw.get(index as usize) else { return (format!("#{index}"), 0) };
        let (bind, kind) = (sym.info >> 4, sym.info & 0xf);
        let defined = !matches!(sym.section, SHN_UNDEF | SHN_ABS | SHN_COMMON);
        if kind == STT_SECTION || (bind == STB_LOCAL && defined && index != 0) {
            let offset = if kind == STT_SECTION { 0 } else { sym.value as i64 };
            (format!("[{}]", place(sym.section)), offset)
        } else {
            (sym.name.clone(), 0)
        }
    };

    let mut relocs: BTreeMap<usize, Vec<Reloc>> = BTreeMap::new();
    for h in headers.iter().filter(|h| h.kind == SHT_RELA || h.kind == SHT_REL) {
        let rela = h.kind == SHT_RELA;
        let list = relocs.entry(h.info as usize).or_default();
        let step = if class.wide { 8 } else { 4 };
        for r in contents(h)?.chunks_exact(class.reloc_size(rela)) {
            let (symbol, kind) = class.info(class.word(r, step));
            let (name, offset) = target(symbol);
            let addend = match (rela, class.wide) {
                (false, _) => 0,
                (true, true) => u64_at(r, 16) as i64,
                (true, false) => i64::from(u32_at(r, 8) as i32),
            };
            list.push(Reloc {
                offset: class.word(r, 0),
                kind,
                target: name,
                addend: addend.wrapping_add(offset),
            });
        }
    }

    let mut sections = Vec::new();
    for (n, h) in headers.iter().enumerate().skip(1) {
        if matches!(h.kind, SHT_SYMTAB | SHT_STRTAB | SHT_RELA | SHT_REL | SHT_SYMTAB_SHNDX) {
            continue;
        }
        let name = name_of(n);
        let mut bytes = contents(h)?.to_vec();
        if h.kind == SHT_GROUP {
            let signature = raw.get(h.info as usize).map(|s| s.name.clone()).unwrap_or_default();
            let mut text = format!("signature {signature}\n");
            for (at, word) in bytes.chunks_exact(4).enumerate() {
                let word = u32_at(word, 0);
                if at == 0 {
                    text.push_str(&format!("flags {word}\n"));
                } else {
                    text.push_str(&name_of(word as usize));
                    text.push('\n');
                }
            }
            bytes = text.into_bytes();
        }
        let mut relocs = relocs.remove(&n).unwrap_or_default();
        relocs.sort();
        sections.push(Section {
            link: (h.flags & SHF_LINK_ORDER != 0).then(|| name_of(h.link as usize)),
            name,
            kind: h.kind,
            flags: h.flags & !SHF_INFO_LINK,
            size: h.size,
            align: h.align,
            entsize: h.entsize,
            bytes,
            relocs,
        });
    }

    let mut symbols: Vec<Symbol> = raw
        .iter()
        .skip(1)
        .filter(|s| !matches!(s.info & 0xf, STT_SECTION | STT_FILE))
        .map(|s| Symbol {
            name: s.name.clone(),
            section: place(s.section),
            value: s.value,
            size: s.size,
            bind: s.info >> 4,
            kind: s.info & 0xf,
            other: s.other,
        })
        .collect();
    symbols.sort();
    Ok(Object { sections, symbols })
}

/// One way two objects disagree.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Difference {
    /// What kind of difference it is, with the section it is in when there is one, for grouping.
    pub bucket: String,
    /// What exactly, for the report.
    pub detail: String,
}

impl fmt::Display for Difference {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{}: {}", self.bucket, self.detail)
    }
}

/// A section name with a per function or per variable suffix taken off, so that a difference in
/// `.text.foo` and one in `.text.bar` land in the same bucket.
#[must_use]
pub fn family(name: &str) -> &str {
    for prefix in [".text.", ".data.", ".rodata.", ".bss.", ".rela."] {
        if name.starts_with(prefix) && name.len() > prefix.len() {
            return &prefix[..prefix.len() - 1];
        }
    }
    name
}

fn differ(bucket: String, detail: String) -> Difference {
    Difference { bucket, detail }
}

/// Every way `ours` differs from `theirs`, the reference, in the order a person would want to
/// read them: missing and extra sections, then each section's header, contents and relocations,
/// then the symbols, then the order of the sections.
#[must_use]
pub fn compare(theirs: &Object, ours: &Object) -> Vec<Difference> {
    let mut out = Vec::new();
    // Sections are matched by name and by which one of that name they are, since a group can
    // hold a `.text.foo` and so can the next group.
    let keyed = |o: &Object| -> BTreeMap<(String, usize), usize> {
        let mut seen: BTreeMap<&str, usize> = BTreeMap::new();
        o.sections
            .iter()
            .enumerate()
            .map(|(at, s)| {
                let n = seen.entry(&s.name).or_default();
                *n += 1;
                ((s.name.clone(), *n), at)
            })
            .collect()
    };
    let (mine, yours) = (keyed(theirs), keyed(ours));
    for (key, _) in mine.iter().filter(|(k, _)| !yours.contains_key(*k)) {
        out.push(differ(
            format!("section missing: {}", family(&key.0)),
            format!("{} is in the reference and not in rucc's object", key.0),
        ));
    }
    for (key, _) in yours.iter().filter(|(k, _)| !mine.contains_key(*k)) {
        out.push(differ(
            format!("extra section: {}", family(&key.0)),
            format!("{} is in rucc's object and not in the reference", key.0),
        ));
    }
    for (key, &a) in &mine {
        let Some(&b) = yours.get(key) else { continue };
        section(&theirs.sections[a], &ours.sections[b], &mut out);
    }
    symbols(&theirs.symbols, &ours.symbols, &mut out);
    if out.is_empty() {
        let order = |o: &Object| o.sections.iter().map(|s| s.name.clone()).collect::<Vec<_>>();
        if order(theirs) != order(ours) {
            out.push(differ(
                "section order".to_owned(),
                format!("{} against {}", order(theirs).join(" "), order(ours).join(" ")),
            ));
        }
    }
    out
}

fn section(a: &Section, b: &Section, out: &mut Vec<Difference>) {
    let name = &a.name;
    let here = family(name);
    let mut header = |what: &str, x: String, y: String| {
        if x != y {
            out.push(differ(format!("section {what}: {here}"), format!("{name}: {x} against {y}")));
        }
    };
    header("type", a.kind.to_string(), b.kind.to_string());
    header("flags", format!("{:#x}", a.flags), format!("{:#x}", b.flags));
    header("alignment", a.align.to_string(), b.align.to_string());
    header("entry size", a.entsize.to_string(), b.entsize.to_string());
    header("link", format!("{:?}", a.link), format!("{:?}", b.link));
    if TOOL_NOTES.contains(&name.as_str()) {
        return;
    }
    if a.size != b.size {
        out.push(differ(
            format!("section size: {here}"),
            format!("{name}: {} bytes against {}", a.size, b.size),
        ));
    } else if a.bytes != b.bytes {
        let at = a.bytes.iter().zip(&b.bytes).position(|(x, y)| x != y).unwrap_or(0);
        let show = |bytes: &[u8]| {
            bytes[at..bytes.len().min(at + 8)]
                .iter()
                .map(|b| format!("{b:02x}"))
                .collect::<Vec<_>>()
                .join(" ")
        };
        out.push(differ(
            format!("section bytes: {here}"),
            format!("{name} at {at:#x}: {} against {}", show(&a.bytes), show(&b.bytes)),
        ));
    }
    if a.relocs != b.relocs {
        let first = a.relocs.iter().zip(&b.relocs).find(|(x, y)| x != y);
        let detail = match first {
            Some((x, y)) => format!("{name}: {} against {}", reloc(x), reloc(y)),
            None => format!("{name}: {} relocations against {}", a.relocs.len(), b.relocs.len()),
        };
        out.push(differ(format!("relocations: {here}"), detail));
    }
}

fn reloc(r: &Reloc) -> String {
    format!("{:#x} type {} {}{:+}", r.offset, r.kind, r.target, r.addend)
}

fn symbols(a: &[Symbol], b: &[Symbol], out: &mut Vec<Difference>) {
    let by_name = |list: &[Symbol]| {
        let mut map: BTreeMap<String, Vec<Symbol>> = BTreeMap::new();
        for s in list {
            map.entry(s.name.clone()).or_default().push(s.clone());
        }
        map
    };
    let (mine, yours) = (by_name(a), by_name(b));
    for (name, list) in &mine {
        match yours.get(name) {
            None => out.push(differ(
                "symbol missing".to_owned(),
                format!("{name} is in the reference and not in rucc's object"),
            )),
            Some(other) if other != list => out.push(differ(
                "symbol differs".to_owned(),
                format!("{name}: {} against {}", symbol(&list[0]), symbol(&other[0])),
            )),
            Some(_) => {}
        }
    }
    for name in yours.keys().filter(|n| !mine.contains_key(*n)) {
        out.push(differ(
            "extra symbol".to_owned(),
            format!("{name} is in rucc's object and not in the reference"),
        ));
    }
}

fn symbol(s: &Symbol) -> String {
    format!(
        "{} {:#x} size {} bind {} type {} other {}",
        s.section, s.value, s.size, s.bind, s.kind, s.other
    )
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Name, type, flags, contents, link, info and entry size of one section.
    type Body<'a> = (&'a str, u32, u64, Vec<u8>, u32, u32, u64);

    /// Builds a small object by hand: a `.text` with the bytes given, a `.data`, a symbol table
    /// with the symbols given, and a `.rela.text` with the relocations given.
    struct Builder {
        text: Vec<u8>,
        /// Name, section index (0 undefined, 1 .text, 2 .data), value, info.
        symbols: Vec<(&'static str, u16, u64, u8)>,
        /// Offset, type, symbol index, addend.
        relocs: Vec<(u64, u32, u32, i64)>,
        comment: &'static str,
    }

    impl Builder {
        fn new() -> Builder {
            Builder {
                text: vec![0xe8, 0, 0, 0, 0, 0xc3],
                symbols: vec![("", 1, 0, STT_SECTION), ("f", 1, 0, 0x12), ("g", 0, 0, 0x10)],
                relocs: vec![(1, 4, 3, -4)],
                comment: "GCC",
            }
        }

        fn build(&self) -> Vec<u8> {
            let names = b"\0.text\0.data\0.symtab\0.strtab\0.rela.text\0.shstrtab\0.comment\0";
            let name = |n: &str| {
                let at = names
                    .windows(n.len() + 1)
                    .position(|w| &w[..n.len()] == n.as_bytes() && w[n.len()] == 0);
                at.unwrap() as u32
            };
            let mut strtab = vec![0u8];
            let mut symtab = vec![0u8; 24];
            for (sym, section, value, info) in &self.symbols {
                let at = strtab.len() as u32;
                strtab.extend_from_slice(sym.as_bytes());
                strtab.push(0);
                symtab.extend_from_slice(&(if sym.is_empty() { 0 } else { at }).to_le_bytes());
                symtab.push(*info);
                symtab.push(0);
                symtab.extend_from_slice(&section.to_le_bytes());
                symtab.extend_from_slice(&value.to_le_bytes());
                symtab.extend_from_slice(&0u64.to_le_bytes());
            }
            let mut rela = Vec::new();
            for (offset, kind, sym, addend) in &self.relocs {
                rela.extend_from_slice(&offset.to_le_bytes());
                rela.extend_from_slice(&((u64::from(*sym) << 32) | u64::from(*kind)).to_le_bytes());
                rela.extend_from_slice(&addend.to_le_bytes());
            }
            let data = [1u8, 2, 3, 4];
            // index: 0 null, 1 .text, 2 .data, 3 .symtab, 4 .strtab, 5 .rela.text, 6 .shstrtab, 7 .comment
            let bodies: Vec<Body<'_>> = vec![
                (".text", 1, 6, self.text.clone(), 0, 0, 0),
                (".data", 1, 3, data.to_vec(), 0, 0, 0),
                (".symtab", SHT_SYMTAB, 0, symtab, 4, 2, 24),
                (".strtab", SHT_STRTAB, 0, strtab, 0, 0, 0),
                (".rela.text", SHT_RELA, 0x40, rela, 3, 1, 24),
                (".shstrtab", SHT_STRTAB, 0, names.to_vec(), 0, 0, 0),
                (".comment", 1, 0x30, self.comment.as_bytes().to_vec(), 0, 0, 1),
            ];
            let mut file = vec![0u8; 64];
            let mut headers = vec![0u8; 64];
            for (n, kind, flags, body, link, info, entsize) in bodies {
                let offset = file.len() as u64;
                file.extend_from_slice(&body);
                let mut h = Vec::new();
                h.extend_from_slice(&name(n).to_le_bytes());
                h.extend_from_slice(&kind.to_le_bytes());
                h.extend_from_slice(&flags.to_le_bytes());
                h.extend_from_slice(&0u64.to_le_bytes());
                h.extend_from_slice(&offset.to_le_bytes());
                h.extend_from_slice(&(body.len() as u64).to_le_bytes());
                h.extend_from_slice(&link.to_le_bytes());
                h.extend_from_slice(&info.to_le_bytes());
                h.extend_from_slice(&1u64.to_le_bytes());
                h.extend_from_slice(&entsize.to_le_bytes());
                headers.extend_from_slice(&h);
            }
            let shoff = file.len() as u64;
            file.extend_from_slice(&headers);
            file[..4].copy_from_slice(b"\x7fELF");
            file[4] = 2;
            file[5] = 1;
            file[6] = 1;
            file[16..18].copy_from_slice(&1u16.to_le_bytes());
            file[18..20].copy_from_slice(&62u16.to_le_bytes());
            file[40..48].copy_from_slice(&shoff.to_le_bytes());
            file[52..54].copy_from_slice(&64u16.to_le_bytes());
            file[58..60].copy_from_slice(&64u16.to_le_bytes());
            file[60..62].copy_from_slice(&8u16.to_le_bytes());
            file[62..64].copy_from_slice(&6u16.to_le_bytes());
            file
        }

        fn object(&self) -> Object {
            read(&self.build()).unwrap()
        }
    }

    #[test]
    fn an_object_is_read_into_sections_symbols_and_relocations() {
        let o = Builder::new().object();
        let names: Vec<&str> = o.sections.iter().map(|s| s.name.as_str()).collect();
        assert_eq!(names, [".text", ".data", ".comment"]);
        let text = &o.sections[0];
        assert_eq!(text.flags, 6);
        assert_eq!(text.bytes, [0xe8, 0, 0, 0, 0, 0xc3]);
        assert_eq!(text.relocs, [Reloc { offset: 1, kind: 4, target: "g".into(), addend: -4 }]);
        let names: Vec<&str> = o.symbols.iter().map(|s| s.name.as_str()).collect();
        assert_eq!(names, ["f", "g"], "the section symbol is left out");
        assert_eq!(o.symbols[1].section, "UND");
        assert_eq!(o.symbols[0].bind, 1);
    }

    #[test]
    fn the_same_object_compares_clean() {
        assert_eq!(compare(&Builder::new().object(), &Builder::new().object()), []);
    }

    #[test]
    fn a_local_label_and_its_section_plus_offset_are_the_same_relocation() {
        // A static function at offset 4, called through its section by one and by its own name
        // by the other.
        let mut gas = Builder::new();
        gas.symbols.push(("s", 1, 4, 0x02));
        gas.relocs = vec![(1, 2, 1, 4)];
        let mut other = Builder::new();
        other.symbols.push(("s", 1, 4, 0x02));
        other.relocs = vec![(1, 2, 4, 0)];
        let (a, b) = (gas.object(), other.object());
        assert_eq!(a.sections[0].relocs[0].target, "[.text]");
        assert_eq!(compare(&a, &b), [], "{:?}", b.sections[0].relocs);
    }

    #[test]
    fn the_comment_is_not_compared() {
        let mut other = Builder::new();
        other.comment = "rucc 0.9 and more";
        assert_eq!(compare(&Builder::new().object(), &other.object()), []);
    }

    #[test]
    fn differences_are_found_and_bucketed() {
        let mut other = Builder::new();
        other.text = vec![0xe8, 0, 0, 0, 0, 0xc2];
        other.relocs = vec![(1, 2, 3, -4)];
        other.symbols.push(("h", 2, 0, 0x11));
        let found = compare(&Builder::new().object(), &other.object());
        let buckets: Vec<&str> = found.iter().map(|d| d.bucket.as_str()).collect();
        assert_eq!(buckets, ["section bytes: .text", "relocations: .text", "extra symbol"]);
        assert_eq!(found[0].detail, ".text at 0x5: c3 against c2");
        assert_eq!(found[1].detail, ".text: 0x1 type 4 g-4 against 0x1 type 2 g-4");
    }

    #[test]
    fn a_function_section_lands_in_the_bucket_of_its_family() {
        assert_eq!(family(".text.do_fork"), ".text");
        assert_eq!(family(".rodata.str1.1"), ".rodata");
        assert_eq!(family(".altinstructions"), ".altinstructions");
        assert_eq!(family(".text"), ".text");
    }

    #[test]
    fn something_that_is_not_an_object_is_refused() {
        assert!(read(b"#!/bin/sh\n").is_err());
        let mut short = Builder::new().build();
        short.truncate(200);
        assert!(read(&short).is_err());
    }

    /// Name, type, contents, link, info and entry size of one ELF32 section.
    type Body32<'a> = (u32, u32, &'a [u8], u32, u32, u32);

    /// An ELF32 object as gas writes one for `-m16` code: `.text` holding `e8 fc ff ff ff`, a
    /// global `start` at 0, and an `R_386_PC32` against an undefined `far` at 1.
    fn elf32() -> Vec<u8> {
        let shstrtab = b"\0.text\0.symtab\0.strtab\0.rel.text\0.shstrtab\0".to_vec();
        let strtab = b"\0start\0far\0".to_vec();
        let text = vec![0xe8, 0xfc, 0xff, 0xff, 0xff];
        let symbol = |name: u32, value: u32, info: u8, section: u16| {
            let mut s = Vec::new();
            s.extend_from_slice(&name.to_le_bytes());
            s.extend_from_slice(&value.to_le_bytes());
            s.extend_from_slice(&0u32.to_le_bytes());
            s.extend_from_slice(&[info, 0]);
            s.extend_from_slice(&section.to_le_bytes());
            s
        };
        let mut symtab = vec![0; 16];
        symtab.extend(symbol(1, 0, 0x10, 1));
        symtab.extend(symbol(7, 0, 0x10, 0));
        let mut rel = Vec::new();
        rel.extend_from_slice(&1u32.to_le_bytes());
        rel.extend_from_slice(&((2u32 << 8) | 2).to_le_bytes());
        let bodies: [Body32<'_>; 5] = [
            (1, 1, &text, 0, 0, 0),
            (7, SHT_SYMTAB, &symtab, 3, 1, 16),
            (15, 3, &strtab, 0, 0, 0),
            (23, SHT_REL, &rel, 2, 1, 8),
            (33, 3, &shstrtab, 0, 0, 0),
        ];
        let mut file = vec![0u8; 52];
        file[..7].copy_from_slice(b"\x7fELF\x01\x01\x01");
        file[16..18].copy_from_slice(&1u16.to_le_bytes());
        file[18..20].copy_from_slice(&3u16.to_le_bytes());
        let mut headers = vec![0u8; 40];
        for (name, kind, body, link, info, entsize) in bodies {
            let offset = file.len() as u32;
            file.extend_from_slice(body);
            let mut h = Vec::new();
            for word in [name, kind, 0, 0, offset, body.len() as u32, link, info, 1, entsize] {
                h.extend_from_slice(&word.to_le_bytes());
            }
            headers.extend(h);
        }
        let shoff = file.len() as u32;
        file.extend(headers);
        file[32..36].copy_from_slice(&shoff.to_le_bytes());
        file[46..48].copy_from_slice(&40u16.to_le_bytes());
        file[48..50].copy_from_slice(&6u16.to_le_bytes());
        file[50..52].copy_from_slice(&5u16.to_le_bytes());
        file
    }

    #[test]
    fn an_elf32_object_is_read_like_an_elf64_one() {
        let object = read(&elf32()).unwrap();
        let text = object.sections.iter().find(|s| s.name == ".text").unwrap();
        assert_eq!(text.bytes, [0xe8, 0xfc, 0xff, 0xff, 0xff]);
        assert_eq!(
            text.relocs,
            [Reloc { offset: 1, kind: 2, target: "far".to_owned(), addend: 0 }]
        );
        let names: Vec<&str> = object.symbols.iter().map(|s| s.name.as_str()).collect();
        assert_eq!(names, ["far", "start"]);
        let start = object.symbols.iter().find(|s| s.name == "start").unwrap();
        assert_eq!((start.section.as_str(), start.bind), (".text", 1));
        assert!(compare(&object, &read(&elf32()).unwrap()).is_empty());
    }
}
