#include <arm_neon.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
static float F(uint32_t b) { float f; memcpy(&f, &b, 4); return f; }
static uint32_t B(float f) { uint32_t b; memcpy(&b, &f, 4); return b; }
static float32x2_t P(uint32_t x, uint32_t y) { float32x2_t v = {F(x), F(y)}; return v; }
static void show(const char *what, float32x2_t v) { printf("%-40s %08x %08x\n", what, B(v[0]), B(v[1])); }
#define NQ 0x7fc00001u
#define NN 0xffc00002u
#define SN 0x7f800003u
#define ONE 0x3f800000u
#define NZ 0x80000000u
int main(void)
{
    show("vabs_f32(-0, -qnan2)", vabs_f32(P(NZ, NN)));
    show("vabs_f32(-1, sNaN3)", vabs_f32(P(0xbf800000u, SN)));
    show("vabd_f32((qnan1,1),(1,-qnan2))", vabd_f32(P(NQ, ONE), P(ONE, NN)));
    show("vabd_f32((-qnan2,1),(1,1))", vabd_f32(P(NN, ONE), P(ONE, ONE)));
    show("vmax_f32((+0,-0),(-0,+0))", vmax_f32(P(0, NZ), P(NZ, 0)));
    show("vmax_f32((qnan1,1),(1,qnan1))", vmax_f32(P(NQ, ONE), P(ONE, NQ)));
    show("vmin_f32((+0,-0),(-0,+0))", vmin_f32(P(0, NZ), P(NZ, 0)));
    show("vmin_f32((qnan1,1),(1,qnan1))", vmin_f32(P(NQ, ONE), P(ONE, NQ)));
    printf("%-40s %08x %08x\n", "vmaxv_f32 (1,qnan1) (qnan1,1)", B(vmaxv_f32(P(ONE, NQ))), B(vmaxv_f32(P(NQ, ONE))));
    printf("%-40s %08x %08x\n", "vmaxv_f32 (-0,+0) (+0,-0)", B(vmaxv_f32(P(NZ, 0))), B(vmaxv_f32(P(0, NZ))));
    printf("%-40s %08x %08x\n", "vminv_f32 (1,qnan1) (-0,+0)", B(vminv_f32(P(ONE, NQ))), B(vminv_f32(P(0, NZ))));
    printf("%-40s %08x %08x\n", "vaddv_f32 (-0,-0) (1,2)", B(vaddv_f32(P(NZ, NZ))), B(vaddv_f32(P(ONE, 0x40000000u))));
    float32x4_t q = {1e8f, 1.0f, -1e8f, 1.0f};
    float32x4_t z = {-0.0f, -0.0f, -0.0f, -0.0f};
    printf("%-40s %08x %08x\n", "vaddvq_f32 (1e8,1,-1e8,1) (-0 x4)", B(vaddvq_f32(q)), B(vaddvq_f32(z)));
    show("vmul_n_f32((qnan1,sNaN3), -qnan2)", vmul_n_f32(P(NQ, SN), F(NN)));
    show("vmul_n_f32((1,2), sNaN3)", vmul_n_f32(P(ONE, 0x40000000u), F(SN)));
    show("vmul_n_f32((3,-0), 2)", vmul_n_f32(P(0x40400000u, NZ), F(0x40000000u)));
    int64x1_t a = {0x1111111111111111}, b = {0x2222222222222222};
    printf("%-40s %016llx\n", "vsli_n_s64(a,b,0)", (unsigned long long)vsli_n_s64(a, b, 0)[0]);
    printf("%-40s %016llx\n", "vsli_n_s64(a,b,1)", (unsigned long long)vsli_n_s64(a, b, 1)[0]);
    printf("%-40s %016llx\n", "vsri_n_s64(a,b,64)", (unsigned long long)vsri_n_s64(a, b, 64)[0]);
    printf("%-40s %016llx\n", "vsri_n_s64(a,b,1)", (unsigned long long)vsri_n_s64(a, b, 1)[0]);
    return 0;
}
