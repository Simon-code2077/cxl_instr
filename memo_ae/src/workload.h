/*
 * Developed by FAST Lab @ ECE-UIUC -- 2022-2023
 *  Some part of this file follows the methodology of FAST-20 Yang's resporitory
 *  @ https://github.com/NVSL/OptaneStudy/tree/master
 */
#ifndef WORKLOAD_H
#define WORKLOAD_H

#include <stdint.h>
#include <stdbool.h>

/*
#define BLOCK_xN 1
#define LD_xN_RAND_AVX512   LD_x1_RAND_AVX512 
#define STWB_xN_RAND_AVX512 STWB_x1_RAND_AVX512 
#define NTLD_xN_RAND_AVX512 NTLD_x1_RAND_AVX512 
#define NTST_xN_RAND_AVX512 NTST_x1_RAND_AVX512 
*/

/*
#define BLOCK_xN 8
#define LD_xN_RAND_AVX512   LD_x8_RAND_AVX512 
#define STWB_xN_RAND_AVX512 STWB_x8_RAND_AVX512 
#define NTLD_xN_RAND_AVX512 NTLD_x8_RAND_AVX512 
#define NTST_xN_RAND_AVX512 NTST_x8_RAND_AVX512 
*/

#define BLOCK_xN 16
#define LD_xN_RAND_AVX512   LD_x16_RAND_AVX512 
#define STWB_xN_RAND_AVX512 STWB_x16_RAND_AVX512 
#define NTLD_xN_RAND_AVX512 NTLD_x16_RAND_AVX512 
#define NTST_xN_RAND_AVX512 NTST_x16_RAND_AVX512 
//#define LD_xN_RAND_AVX512   LD_LFENCE_x16_RAND_AVX512 
//#define STWB_xN_RAND_AVX512 STWB_SFENCE_x16_RAND_AVX512 
//#define NTLD_xN_RAND_AVX512 NTLD_LFENCE_x16_RAND_AVX512 
//#define NTST_xN_RAND_AVX512 NTST_SFENCE_x16_RAND_AVX512 

/*
#define BLOCK_xN 32
#define LD_xN_RAND_AVX512   LD_x32_RAND_AVX512 
#define STWB_xN_RAND_AVX512 STWB_x32_RAND_AVX512 
#define NTLD_xN_RAND_AVX512 NTLD_x32_RAND_AVX512 
#define NTST_xN_RAND_AVX512 NTST_x32_RAND_AVX512 
*/

void op_ntld(char* addr, long size);

void op_ld(char* addr, long size);

void op_ntst(char* addr, long size);

void op_st(char* addr, long size);

void op_stall();

void op_movdir64B(char* src_addr, char* dst_addr, long size);

void op_mixed(char* addr, long size, int ratio);

uint64_t op_ntld_32B_lat(char* addr);

uint64_t op_ntld_64B_lat(char* addr);

uint64_t op_ntst_64B_lat(char* addr);

uint64_t op_ld_64B_lat(char* addr);

uint64_t op_st_64B_lat(char* addr);

uint64_t op_st_cl_flush_64B_lat(char* addr);

uint64_t op_st_32B_lat(char* addr);

uint64_t op_ptr_chase(char* addr, uint64_t num_chase_block);

uint64_t op_ld_block_lat(char* addr, bool flush_block, long num_clear_pipe);

uint64_t op_ntld_block_lat(char* addr, bool flush_block, long num_clear_pipe);

uint64_t op_stwb_block_lat(char* addr, bool flush_block, long num_clear_pipe);

uint64_t op_ntst_block_lat(char* addr, bool flush_block, long num_clear_pipe);

void set_all_zmm(char* addr);

void dump_zmm(char* dst, uint64_t size);

/* Assembly to perform non-temporal load */
#define SIZENTLD_64_AVX512	\
					"ldnp  z0, z1, [x9, x10] \n" \
					"add  x10, x10, #0x40 \n"

#define SIZENTLD_128_AVX512	\
					"ldnp  z0, z1, [x9, x10] \n" \
					"ldnp  z2, z3, [x9, x10, #0x40] \n" \
					"add  x10, x10, #0x80 \n"

#define SIZENTLD_256_AVX512	\
					"ldnp  z0, z1, [x9, x10] \n" \
					"ldnp  z2, z3, [x9, x10, #0x40] \n" \
					"ldnp  z4, z5, [x9, x10, #0x80] \n" \
					"ldnp  z6, z7, [x9, x10, #0xc0] \n" \
					"add  x10, x10, #0x100 \n"

#define SIZENTLD_512_AVX512	\
					"ldnp  z0, z1, [x9, x10] \n" \
					"ldnp  z2, z3, [x9, x10, #0x40] \n" \
					"ldnp  z4, z5, [x9, x10, #0x80] \n" \
					"ldnp  z6, z7, [x9, x10, #0xc0] \n" \
					"ldnp  z8, z9, [x9, x10, #0x100] \n" \
					"ldnp  z10, z11, [x9, x10, #0x140] \n" \
					"ldnp  z12, z13, [x9, x10, #0x180] \n" \
					"ldnp  z14, z15, [x9, x10, #0x1c0] \n" \
					"add  x10, x10, #0x200 \n"

#define SIZENTLD_1024_AVX512	\
					"ldnp  z0, z1, [x9, x10] \n" \
					"ldnp  z2, z3, [x9, x10, #0x40] \n" \
					"ldnp  z4, z5, [x9, x10, #0x80] \n" \
					"ldnp  z6, z7, [x9, x10, #0xc0] \n" \
					"ldnp  z8, z9, [x9, x10, #0x100] \n" \
					"ldnp  z10, z11, [x9, x10, #0x140] \n" \
					"ldnp  z12, z13, [x9, x10, #0x180] \n" \
					"ldnp  z14, z15, [x9, x10, #0x1c0] \n" \
					"ldnp  z16, z17, [x9, x10, #0x200] \n" \
					"ldnp  z18, z19, [x9, x10, #0x240] \n" \
					"ldnp  z20, z21, [x9, x10, #0x280] \n" \
					"ldnp  z22, z23, [x9, x10, #0x2c0] \n" \
					"ldnp  z24, z25, [x9, x10, #0x300] \n" \
					"ldnp  z26, z27, [x9, x10, #0x340] \n" \
					"ldnp  z28, z29, [x9, x10, #0x380] \n" \
					"ldnp  z30, z31, [x9, x10, #0x3c0] \n" \
					"add  x10, x10, #0x400 \n"

#define NTLD_x1_RAND_AVX512 \
                "ld1r {v0.2d}, [x9, x10] \n"

#define NTLD_x8_RAND_AVX512 \
                "ld1r {v0.2d}, [x9, x10] \n" \
                "ld1r {v1.2d}, [x9, x10, #16] \n" \
                "ld1r {v2.2d}, [x9, x10, #32] \n" \
                "ld1r {v3.2d}, [x9, x10, #48] \n" \
                "ld1r {v4.2d}, [x9, x10, #64] \n" \
                "ld1r {v5.2d}, [x9, x10, #80] \n" \
                "ld1r {v6.2d}, [x9, x10, #96] \n" \
                "ld1r {v7.2d}, [x9, x10, #112] \n"

#define NTLD_x16_RAND_AVX512 \
                "ld1r {v0.2d}, [x9, x10] \n" \
                "ld1r {v1.2d}, [x9, x10, #16] \n" \
                "ld1r {v2.2d}, [x9, x10, #32] \n" \
                "ld1r {v3.2d}, [x9, x10, #48] \n" \
                "ld1r {v4.2d}, [x9, x10, #64] \n" \
                "ld1r {v5.2d}, [x9, x10, #80] \n" \
                "ld1r {v6.2d}, [x9, x10, #96] \n" \
                "ld1r {v7.2d}, [x9, x10, #112] \n" \
                "ld1r {v8.2d}, [x9, x10, #128] \n" \
                "ld1r {v9.2d}, [x9, x10, #144] \n" \
                "ld1r {v10.2d}, [x9, x10, #160] \n" \
                "ld1r {v11.2d}, [x9, x10, #176] \n" \
                "ld1r {v12.2d}, [x9, x10, #192] \n" \
                "ld1r {v13.2d}, [x9, x10, #208] \n" \
                "ld1r {v14.2d}, [x9, x10, #224] \n" \
                "ld1r {v15.2d}, [x9, x10, #240] \n"

/* Assembly to perform non-temporal store */
#define SIZENTST_64_AVX512			\
					"stnp  z0, z1, [x9, x10] \n" \
					"add  x10, x10, #0x40 \n"

#define SIZENTST_128_AVX512		\
					"stnp  z0, z1, [x9, x10] \n" \
					"stnp  z2, z3, [x9, x10, #0x40] \n" \
					"add  x10, x10, #0x80 \n"

#define SIZENTST_256_AVX512		\
					"stnp  z0, z1, [x9, x10] \n" \
					"stnp  z2, z3, [x9, x10, #0x40] \n" \
					"stnp  z4, z5, [x9, x10, #0x80] \n" \
					"stnp  z6, z7, [x9, x10, #0xc0] \n" \
					"add  x10, x10, #0x100 \n"

#define SIZENTST_512_AVX512		\
					"stnp  z0, z1, [x9, x10] \n" \
					"stnp  z2, z3, [x9, x10, #0x40] \n" \
					"stnp  z4, z5, [x9, x10, #0x80] \n" \
					"stnp  z6, z7, [x9, x10, #0xc0] \n" \
					"stnp  z8, z9, [x9, x10, #0x100] \n" \
					"stnp  z10, z11, [x9, x10, #0x140] \n" \
					"stnp  z12, z13, [x9, x10, #0x180] \n" \
					"stnp  z14, z15, [x9, x10, #0x1c0] \n" \
					"add  x10, x10, #0x200 \n"

#define SIZENTST_1024_AVX512	\
					"stnp  z0, z1, [x9, x10] \n" \
					"stnp  z2, z3, [x9, x10, #0x40] \n" \
					"stnp  z4, z5, [x9, x10, #0x80] \n" \
					"stnp  z6, z7, [x9, x10, #0xc0] \n" \
					"stnp  z8, z9, [x9, x10, #0x100] \n" \
					"stnp  z10, z11, [x9, x10, #0x140] \n" \
					"stnp  z12, z13, [x9, x10, #0x180] \n" \
					"stnp  z14, z15, [x9, x10, #0x1c0] \n" \
					"stnp  z16, z17, [x9, x10, #0x200] \n" \
					"stnp  z18, z19, [x9, x10, #0x240] \n" \
					"stnp  z20, z21, [x9, x10, #0x280] \n" \
					"stnp  z22, z23, [x9, x10, #0x2c0] \n" \
					"stnp  z24, z25, [x9, x10, #0x300] \n" \
					"stnp  z26, z27, [x9, x10, #0x340] \n" \
					"stnp  z28, z29, [x9, x10, #0x380] \n" \
					"stnp  z30, z31, [x9, x10, #0x3c0] \n" \
					"add  x10, x10, #0x400 \n"

#define NTST_x1_RAND_AVX512 \
                "st1 {v0.2d}, [x9, x10] \n"

#define NTST_x8_RAND_AVX512 \
                "st1 {v0.2d}, [x9, x10] \n" \
                "st1 {v1.2d}, [x9, x10, #16] \n" \
                "st1 {v2.2d}, [x9, x10, #32] \n" \
                "st1 {v3.2d}, [x9, x10, #48] \n" \
                "st1 {v4.2d}, [x9, x10, #64] \n" \
                "st1 {v5.2d}, [x9, x10, #80] \n" \
                "st1 {v6.2d}, [x9, x10, #96] \n" \
                "st1 {v7.2d}, [x9, x10, #112] \n"

#define NTST_x16_RAND_AVX512 \
                "st1 {v0.2d}, [x9, x10] \n" \
                "st1 {v1.2d}, [x9, x10, #16] \n" \
                "st1 {v2.2d}, [x9, x10, #32] \n" \
                "st1 {v3.2d}, [x9, x10, #48] \n" \
                "st1 {v4.2d}, [x9, x10, #64] \n" \
                "st1 {v5.2d}, [x9, x10, #80] \n" \
                "st1 {v6.2d}, [x9, x10, #96] \n" \
                "st1 {v7.2d}, [x9, x10, #112] \n" \
                "st1 {v8.2d}, [x9, x10, #128] \n" \
                "st1 {v9.2d}, [x9, x10, #144] \n" \
                "st1 {v10.2d}, [x9, x10, #160] \n" \
                "st1 {v11.2d}, [x9, x10, #176] \n" \
                "st1 {v12.2d}, [x9, x10, #192] \n" \
                "st1 {v13.2d}, [x9, x10, #208] \n" \
                "st1 {v14.2d}, [x9, x10, #224] \n" \
                "st1 {v15.2d}, [x9, x10, #240] \n"

/* temporal load */
#define SIZELD_1024_AVX512	\
					"ldp  z0, z1, [x9, x10] \n" \
					"ldp  z2, z3, [x9, x10, #0x40] \n" \
					"ldp  z4, z5, [x9, x10, #0x80] \n" \
					"ldp  z6, z7, [x9, x10, #0xc0] \n" \
					"ldp  z8, z9, [x9, x10, #0x100] \n" \
					"ldp  z10, z11, [x9, x10, #0x140] \n" \
					"ldp  z12, z13, [x9, x10, #0x180] \n" \
					"ldp  z14, z15, [x9, x10, #0x1c0] \n" \
					"ldp  z16, z17, [x9, x10, #0x200] \n" \
					"ldp  z18, z19, [x9, x10, #0x240] \n" \
					"ldp  z20, z21, [x9, x10, #0x280] \n" \
					"ldp  z22, z23, [x9, x10, #0x2c0] \n" \
					"ldp  z24, z25, [x9, x10, #0x300] \n" \
					"ldp  z26, z27, [x9, x10, #0x340] \n" \
					"ldp  z28, z29, [x9, x10, #0x380] \n" \
					"ldp  z30, z31, [x9, x10, #0x3c0] \n" \
					"add  x10, x10, #0x400 \n"

#define LD_x1_RAND_AVX512 \
                "ldr q0, [x9, x10] \n"

#define LD_x8_RAND_AVX512 \
                "ldr q0, [x9, x10] \n" \
                "ldr q1, [x9, x10, #16] \n" \
                "ldr q2, [x9, x10, #32] \n" \
                "ldr q3, [x9, x10, #48] \n" \
                "ldr q4, [x9, x10, #64] \n" \
                "ldr q5, [x9, x10, #80] \n" \
                "ldr q6, [x9, x10, #96] \n" \
                "ldr q7, [x9, x10, #112] \n"

#define LD_LFENCE_x16_RAND_AVX512 \
                "vmovdqa64 0x2a80(%%r11, %%r10), %%zmm0 \n lfence \n" \
                "vmovdqa64 0x680(%%r11, %%r10), %%zmm1 \n lfence \n" \
                "vmovdqa64 0x8500(%%r11, %%r10), %%zmm2 \n lfence \n" \
                "vmovdqa64 0x8980(%%r11, %%r10), %%zmm3 \n lfence \n" \
                "vmovdqa64 0x6d40(%%r11, %%r10), %%zmm4 \n lfence \n" \
                "vmovdqa64 0xf7c0(%%r11, %%r10), %%zmm5 \n lfence \n" \
                "vmovdqa64 0x4640(%%r11, %%r10), %%zmm6 \n lfence \n" \
                "vmovdqa64 0x1480(%%r11, %%r10), %%zmm7 \n lfence \n" \
                "vmovdqa64 0x2f00(%%r11, %%r10), %%zmm8 \n lfence \n" \
                "vmovdqa64 0x15c0(%%r11, %%r10), %%zmm9 \n lfence \n" \
                "vmovdqa64 0xf100(%%r11, %%r10), %%zmm10 \n lfence \n" \
                "vmovdqa64 0x66c0(%%r11, %%r10), %%zmm11 \n lfence \n" \
                "vmovdqa64 0xe240(%%r11, %%r10), %%zmm12 \n lfence \n" \
                "vmovdqa64 0xf480(%%r11, %%r10), %%zmm13 \n lfence \n" \
                "vmovdqa64 0x84c0(%%r11, %%r10), %%zmm14 \n lfence \n" \
                "vmovdqa64 0xe480(%%r11, %%r10), %%zmm15 \n lfence \n"

#define LD_x16_RAND_AVX512 \
                "ldr q0, [x9, x10] \n" \
                "ldr q1, [x9, x10, #16] \n" \
                "ldr q2, [x9, x10, #32] \n" \
                "ldr q3, [x9, x10, #48] \n" \
                "ldr q4, [x9, x10, #64] \n" \
                "ldr q5, [x9, x10, #80] \n" \
                "ldr q6, [x9, x10, #96] \n" \
                "ldr q7, [x9, x10, #112] \n" \
                "ldr q8, [x9, x10, #128] \n" \
                "ldr q9, [x9, x10, #144] \n" \
                "ldr q10, [x9, x10, #160] \n" \
                "ldr q11, [x9, x10, #176] \n" \
                "ldr q12, [x9, x10, #192] \n" \
                "ldr q13, [x9, x10, #208] \n" \
                "ldr q14, [x9, x10, #224] \n" \
                "ldr q15, [x9, x10, #240] \n"


#define LD_x32_RAND_AVX512 \
                "vmovdqa64 0x7b40(%%r11, %%r10), %%zmm0 \n" \
                "vmovdqa64 0x7640(%%r11, %%r10), %%zmm1 \n" \
                "vmovdqa64 0xdf00(%%r11, %%r10), %%zmm2 \n" \
                "vmovdqa64 0xdb40(%%r11, %%r10), %%zmm3 \n" \
                "vmovdqa64 0xb6c0(%%r11, %%r10), %%zmm4 \n" \
                "vmovdqa64 0x6980(%%r11, %%r10), %%zmm5 \n" \
                "vmovdqa64 0xf280(%%r11, %%r10), %%zmm6 \n" \
                "vmovdqa64 0x3dc0(%%r11, %%r10), %%zmm7 \n" \
                "vmovdqa64 0x6d80(%%r11, %%r10), %%zmm8 \n" \
                "vmovdqa64 0xf580(%%r11, %%r10), %%zmm9 \n" \
                "vmovdqa64 0xf300(%%r11, %%r10), %%zmm10 \n" \
                "vmovdqa64 0x3140(%%r11, %%r10), %%zmm11 \n" \
                "vmovdqa64 0x8980(%%r11, %%r10), %%zmm12 \n" \
                "vmovdqa64 0xecc0(%%r11, %%r10), %%zmm13 \n" \
                "vmovdqa64 0xc5c0(%%r11, %%r10), %%zmm14 \n" \
                "vmovdqa64 0x1e40(%%r11, %%r10), %%zmm15 \n" \
                "vmovdqa64 0xf3c0(%%r11, %%r10), %%zmm16 \n" \
                "vmovdqa64 0xe800(%%r11, %%r10), %%zmm17 \n" \
                "vmovdqa64 0x2200(%%r11, %%r10), %%zmm18 \n" \
                "vmovdqa64 0x66c0(%%r11, %%r10), %%zmm19 \n" \
                "vmovdqa64 0xc00(%%r11, %%r10), %%zmm20 \n" \
                "vmovdqa64 0x2bc0(%%r11, %%r10), %%zmm21 \n" \
                "vmovdqa64 0x6a80(%%r11, %%r10), %%zmm22 \n" \
                "vmovdqa64 0x94c0(%%r11, %%r10), %%zmm23 \n" \
                "vmovdqa64 0xbec0(%%r11, %%r10), %%zmm24 \n" \
                "vmovdqa64 0xcdc0(%%r11, %%r10), %%zmm25 \n" \
                "vmovdqa64 0xf80(%%r11, %%r10), %%zmm26 \n" \
                "vmovdqa64 0xc000(%%r11, %%r10), %%zmm27 \n" \
                "vmovdqa64 0x4340(%%r11, %%r10), %%zmm28 \n" \
                "vmovdqa64 0x4640(%%r11, %%r10), %%zmm29 \n" \
                "vmovdqa64 0xcc0(%%r11, %%r10), %%zmm30 \n" \
                "vmovdqa64 0x6b40(%%r11, %%r10), %%zmm31 \n"

#define LD_x32_RAND_AARCH64 \
                "ld1 {v0.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v1.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v2.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v3.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v4.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v5.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v6.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v7.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v8.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v9.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v10.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v11.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v12.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v13.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v14.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v15.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v16.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v17.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v18.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v19.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v20.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v21.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v22.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v23.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v24.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v25.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v26.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v27.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v28.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v29.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v30.2d}, [x11, x10, lsl #3] \n" \
                "ld1 {v31.2d}, [x11, x10, lsl #3] \n"

#define STWB_x1_RAND_AVX512 \
                "vmovdqa64  %%zmm0,  0xe80(%%r11, %%r10) \n clwb 0xe80(%%r11, %%r10) \n"

#define STWB_x1_RAND_AARCH64 \
                "st1 {v0.2d}, [x11, x10, lsl #3] \n dc cvac, [x11, x10, lsl #3] \n"

#define STWB_x8_RAND_AVX512 \
                "vmovdqa64  %%zmm0,  0xe80(%%r11, %%r10) \n clwb 0xe80(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm1,  0xe4c0(%%r11, %%r10) \n clwb 0xe4c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm2,  0x4780(%%r11, %%r10) \n clwb 0x4780(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm3,  0xc240(%%r11, %%r10) \n clwb 0xc240(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm4,  0x2e00(%%r11, %%r10) \n clwb 0x2e00(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm5,  0xf4c0(%%r11, %%r10) \n clwb 0xf4c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm6,  0xe5c0(%%r11, %%r10) \n clwb 0xe5c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm7,  0x7040(%%r11, %%r10) \n clwb 0x7040(%%r11, %%r10) \n"

#define STWB_x8_RAND_AARCH64 \
                "st1 {v0.2d}, [x11, x10, lsl #3] \n dc cvac, [x11, x10, lsl #3] \n" \
                "st1 {v1.2d}, [x11, x10, lsl #3] \n dc cvac, [x11, x10, lsl #3] \n" \
                "st1 {v2.2d}, [x11, x10, lsl #3] \n dc cvac, [x11, x10, lsl #3] \n" \
                "st1 {v3.2d}, [x11, x10, lsl #3] \n dc cvac, [x11, x10, lsl #3] \n" \
                "st1 {v4.2d}, [x11, x10, lsl #3] \n dc cvac, [x11, x10, lsl #3] \n" \
                "st1 {v5.2d}, [x11, x10, lsl #3] \n dc cvac, [x11, x10, lsl #3] \n" \
                "st1 {v6.2d}, [x11, x10, lsl #3] \n dc cvac, [x11, x10, lsl #3] \n" \
                "st1 {v7.2d}, [x11, x10, lsl #3] \n dc cvac, [x11, x10, lsl #3] \n"

//#define STWB_SFENCE_x16_RAND_AVX512

#define STWB_x16_RAND_AVX512 \
                "vmovdqa64  %%zmm0,  0x28c0(%%r11, %%r10) \n clwb 0x28c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm1,  0xc880(%%r11, %%r10) \n clwb 0xc880(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm2,  0x3cc0(%%r11, %%r10) \n clwb 0x3cc0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm3,  0xdd40(%%r11, %%r10) \n clwb 0xdd40(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm4,  0x6bc0(%%r11, %%r10) \n clwb 0x6bc0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm5,  0xe600(%%r11, %%r10) \n clwb 0xe600(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm6,  0x1c0(%%r11, %%r10) \n clwb 0x1c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm7,  0xf540(%%r11, %%r10) \n clwb 0xf540(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm8,  0x11c0(%%r11, %%r10) \n clwb 0x11c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm9,  0xb000(%%r11, %%r10) \n clwb 0xb000(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm10,  0x3f80(%%r11, %%r10) \n clwb 0x3f80(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm11,  0x5c40(%%r11, %%r10) \n clwb 0x5c40(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm12,  0xed00(%%r11, %%r10) \n clwb 0xed00(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm13,  0xd600(%%r11, %%r10) \n clwb 0xd600(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm14,  0x4c80(%%r11, %%r10) \n clwb 0x4c80(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm15,  0xb280(%%r11, %%r10) \n clwb 0xb280(%%r11, %%r10) \n"

/* temporal store */
#define STWB_x32_RAND_AVX512 \
                "vmovdqa64  %%zmm0,  0x9c0(%%r11, %%r10) \n clwb 0x9c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm1,  0x3b40(%%r11, %%r10) \n clwb 0x3b40(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm2,  0xe540(%%r11, %%r10) \n clwb 0xe540(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm3,  0xe180(%%r11, %%r10) \n clwb 0xe180(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm4,  0x2b80(%%r11, %%r10) \n clwb 0x2b80(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm5,  0xa380(%%r11, %%r10) \n clwb 0xa380(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm6,  0x9ac0(%%r11, %%r10) \n clwb 0x9ac0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm7,  0xd500(%%r11, %%r10) \n clwb 0xd500(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm8,  0x51c0(%%r11, %%r10) \n clwb 0x51c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm9,  0x99c0(%%r11, %%r10) \n clwb 0x99c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm10,  0xacc0(%%r11, %%r10) \n clwb 0xacc0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm11,  0x4900(%%r11, %%r10) \n clwb 0x4900(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm12,  0x3540(%%r11, %%r10) \n clwb 0x3540(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm13,  0x8ac0(%%r11, %%r10) \n clwb 0x8ac0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm14,  0x2580(%%r11, %%r10) \n clwb 0x2580(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm15,  0xc5c0(%%r11, %%r10) \n clwb 0xc5c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm16,  0xfd40(%%r11, %%r10) \n clwb 0xfd40(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm17,  0xac40(%%r11, %%r10) \n clwb 0xac40(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm18,  0x1240(%%r11, %%r10) \n clwb 0x1240(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm19,  0xa00(%%r11, %%r10) \n clwb 0xa00(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm20,  0x53c0(%%r11, %%r10) \n clwb 0x53c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm21,  0xcd00(%%r11, %%r10) \n clwb 0xcd00(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm22,  0xbac0(%%r11, %%r10) \n clwb 0xbac0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm23,  0x2500(%%r11, %%r10) \n clwb 0x2500(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm24,  0xd300(%%r11, %%r10) \n clwb 0xd300(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm25,  0xba40(%%r11, %%r10) \n clwb 0xba40(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm26,  0xf500(%%r11, %%r10) \n clwb 0xf500(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm27,  0x2080(%%r11, %%r10) \n clwb 0x2080(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm28,  0xf2c0(%%r11, %%r10) \n clwb 0xf2c0(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm29,  0xa980(%%r11, %%r10) \n clwb 0xa980(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm30,  0x8880(%%r11, %%r10) \n clwb 0x8880(%%r11, %%r10) \n" \
                "vmovdqa64  %%zmm31,  0x54c0(%%r11, %%r10) \n clwb 0x54c0(%%r11, %%r10) \n"

#define SIZESTWB_1024_AVX512	\
				"vmovdqa64  %%zmm0,  0x0(%%r9, %%r10) \n" \
                "clwb  0x0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x40(%%r9, %%r10) \n" \
                "clwb  0x40(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x80(%%r9, %%r10) \n" \
                "clwb  0x80(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0xc0(%%r9, %%r10) \n" \
                "clwb  0xc0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x100(%%r9, %%r10) \n" \
                "clwb  0x100(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x140(%%r9, %%r10) \n" \
                "clwb  0x140(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x180(%%r9, %%r10) \n" \
                "clwb  0x180(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x1c0(%%r9, %%r10) \n" \
                "clwb  0x1c0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x200(%%r9, %%r10) \n" \
                "clwb  0x200(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x240(%%r9, %%r10) \n" \
                "clwb  0x240(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x280(%%r9, %%r10) \n" \
                "clwb  0x280(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x2c0(%%r9, %%r10) \n" \
                "clwb  0x2c0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x300(%%r9, %%r10) \n" \
                "clwb  0x300(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x340(%%r9, %%r10) \n" \
                "clwb  0x340(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x380(%%r9, %%r10) \n" \
                "clwb  0x380(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x3c0(%%r9, %%r10) \n" \
                "clwb  0x3c0(%%r9, %%r10) \n" \
				"add $0x400, %%r10 \n"

#define SIZESTWB_1024_AARCH64 \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "add x10, x10, #0x400 \n"

#define SIZEST_1024_AVX512	\
				"vmovdqa64  %%zmm0,  0x0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm1,  0x40(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm2,  0x80(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm3,  0xc0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm4,  0x100(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm5,  0x140(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm6,  0x180(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm7,  0x1c0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm8,  0x200(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm9,  0x240(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm10,  0x280(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm11,  0x2c0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm12,  0x300(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm13,  0x340(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm14,  0x380(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm15,  0x3c0(%%r9, %%r10) \n" \
				"add $0x400, %%r10 \n"

/* perform movdir64B */
#define SIZEMOV_1024 \
                "movdir64b 0x0(%%r9, %%r10), %%r12 \n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x40(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x80(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0xc0(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x100(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x140(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x180(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x1c0(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x200(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x240(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x280(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x2c0(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x300(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x340(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x380(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
                "movdir64b 0x3c0(%%r9, %%r10), %%r12\n" \
                "add $0x40, %%r12 \n" \
				"add $0x400, %%r10 \n" \

#define SIZEMOV_1024_AARCH64 \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "mov x12, x9 \n" \
                "add x10, x10, #0x400 \n"

/* Mixed read and write */
/* try using the same dest reg. Assign some value to zmm0 for storing. */
#define SIZE_R1W1_512 \
				"vmovdqa64  0x0(%%r9, %%r10), %%zmm0 \n" \
				"vmovdqa64  0x40(%%r9, %%r10), %%zmm1 \n" \
				"vmovdqa64  0x80(%%r9, %%r10), %%zmm2 \n" \
				"vmovdqa64  0xc0(%%r9, %%r10), %%zmm3 \n" \
				"" \
				"vmovq		%1, %%xmm0 \n" \
				"vmovdqa64  %%zmm0,  0x0(%%r9, %%r10) \n" \
				"clwb  0x0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x40(%%r9, %%r10) \n" \
				"clwb  0x40(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x80(%%r9, %%r10) \n" \
				"clwb  0x80(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0xc0(%%r9, %%r10) \n" \
				"clwb  0xc0(%%r9, %%r10) \n" \
				"add $0x200, %%r10 \n" \

#define SIZE_R1W1_512_AARCH64 \
                "ld1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "ld1 {v1.2d}, [x9, x10, lsl #3] \n" \
                "ld1 {v2.2d}, [x9, x10, lsl #3] \n" \
                "ld1 {v3.2d}, [x9, x10, lsl #3] \n" \
                "mov v0.d[0], %1 \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "st1 {v0.2d}, [x9, x10, lsl #3] \n" \
                "dc cvac, [x9, x10, lsl #3] \n" \
                "add x10, x10, #0x200 \n"

#define SIZE_R2W1_576 \
				"vmovdqa64  0x0(%%r9, %%r10), %%zmm0 \n" \
				"vmovdqa64  0x40(%%r9, %%r10), %%zmm0 \n" \
				"vmovdqa64  0x80(%%r9, %%r10), %%zmm0 \n" \
				"vmovdqa64  0xc0(%%r9, %%r10), %%zmm0 \n" \
				"vmovdqa64  0x100(%%r9, %%r10), %%zmm0 \n" \
				"vmovdqa64  0x140(%%r9, %%r10), %%zmm0 \n" \
				"vmovq	%1, %%xmm1 \n" \
				"vmovdqa64  %%zmm1,  0x0(%%r9, %%r10) \n" \
				"clwb  0x0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm1,  0x40(%%r9, %%r10) \n" \
				"clwb  0x40(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm1,  0x80(%%r9, %%r10) \n" \
				"clwb  0x80(%%r9, %%r10) \n" \
				"add $0x180, %%r10 \n" \

#define SIZE_R2W1_384 \
				"vmovdqa64  0x0(%%r9, %%r10), %%zmm0 \n" \
				"vmovdqa64  0x40(%%r9, %%r10), %%zmm1 \n" \
				"vmovdqa64  0x80(%%r9, %%r10), %%zmm2 \n" \
				"vmovdqa64  0xc0(%%r9, %%r10), %%zmm3 \n" \
				"vmovq	%1, %%xmm0 \n" \
				"vmovdqa64  %%zmm0,  0x0(%%r9, %%r10) \n" \
				"clwb  0x0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x40(%%r9, %%r10) \n" \
				"clwb  0x40(%%r9, %%r10) \n" \
				"add $0x180, %%r10 \n" \

#define SIZE_R3W1_512 \
				"vmovdqa64  0x0(%%r9, %%r10), %%zmm0 \n" \
				"vmovdqa64  0x40(%%r9, %%r10), %%zmm1 \n" \
				"vmovdqa64  0x80(%%r9, %%r10), %%zmm2 \n" \
				"vmovdqa64  0xc0(%%r9, %%r10), %%zmm3 \n" \
				"vmovdqa64  0x100(%%r9, %%r10), %%zmm4 \n" \
				"vmovdqa64  0x140(%%r9, %%r10), %%zmm5 \n" \
				"" \
				"vmovq		%1, %%xmm0 \n" \
				"vmovdqa64  %%zmm0,  0x0(%%r9, %%r10) \n" \
				"clwb  0x0(%%r9, %%r10) \n" \
				"vmovdqa64  %%zmm0,  0x40(%%r9, %%r10) \n" \
				"clwb  0x40(%%r9, %%r10) \n" \
				"add $0x200, %%r10 \n" \

/* snippets for latency measuring */

/* Assembly instructions utilize the following registers:
 * rsi: memory address
 * rax, rdx, rcx, r8d and r9d: timing
 * rdx: populating cache-lines
 * ymm0: streaming instructions
 */
#define REGISTERS "rsi", "rax", "rdx", "rcx", "r8", "r9", "ymm0"

#define REGISTERS_AND_ZMM "rsi", "rax", "rdx", "rcx", "r8", "r9", \

#define REGISTERS_AARCH64 "x9", "x10", "x11", "x12", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31"

#define ZMM_0_15 "zmm0", "zmm1", "zmm2", "zmm3", "zmm4", "zmm5", "zmm6", "zmm7", "zmm8", "zmm9", "zmm10", "zmm11", "zmm12", "zmm13", "zmm14", "zmm15"

/* rdtscp: reads current timestamp to EDX:EAX and also sets ECX
 * 		   higher 32-bits of RAX, RDX and RCX are cleared
 *
 * r9d = old EDX
 * r8d = old EAX
 * Here is what we do to compute t_start and t_end:
 * - RDX holds t_end
 * - RAX holds t_start
 */

/** Douglas: read this blog for more info about timing 
 * 	http://sites.utexas.edu/jdm4372/2018/07/23/comments-on-timing-short-code-sections-on-intel-processors/
*/
#define TIMING_BEGIN      	"rdtscp \n" \
							"lfence \n" \
							"mov %%edx, %%r9d \n" \
							"mov %%eax, %%r8d \n"

#define TIMING_BEGIN_AARCH64 \
                "mrs x9, cntvct_el0 \n" \
                "isb \n"

#define TIMING_END      	"mfence \n" \
							"rdtscp \n" \
							"lfence \n" \
							"shl $32, %%rdx \n" \
							"or  %%rax, %%rdx \n" \
							"mov %%r9d, %%eax \n" \
							"shl $32, %%rax \n" \
							"or  %%r8, %%rax \n" \
							"mov %%rax, %[t_start] \n" \
							"mov %%rdx, %[t_end] \n"

#define TIMING_END_AARCH64 \
                "mrs x10, cntvct_el0 \n" \
                "isb \n" \
                "sub %[t_start], x10, x9 \n" \
                "mov %[t_end], x10 \n"

#define FLUSH_64K_BLOCK \
                            "LOOP_64K_BLOCK_FLUSH: \n" \
                                "clflush (%%r11, %%r10) \n" \
                                "add $0x40, %%r10 \n" \
                                "cmp $0x10000, %%r10 \n" \
                                "jl LOOP_64K_BLOCK_FLUSH\n" \
                            "xor %%r10, %%r10 \n" \
							"mfence \n"

#define FLUSH_64K_BLOCK_AARCH64 \
                "LOOP_64K_BLOCK_FLUSH: \n" \
                "dc cvac, [x11, x10, lsl #3] \n" \
                "add x10, x10, #0x40 \n" \
                "cmp x10, #0x10000 \n" \
                "b.lt LOOP_64K_BLOCK_FLUSH \n" \
                "mov x10, #0 \n" \
                "dsb sy \n"

#define FLUSH_CACHE_LINE    "clflush 0*32(%%rsi) \n" \
							"clflush 2*32(%%rsi) \n" \
							"clflush 4*32(%%rsi) \n" \
							"clflush 6*32(%%rsi) \n" \
							"mfence \n"

#define FLUSH_CACHE_LINE_AARCH64 \
                "dc cvac, [x9, #0] \n" \
                "dc cvac, [x9, #64] \n" \
                "dc cvac, [x9, #128] \n" \
                "dc cvac, [x9, #192] \n" \
                "dsb sy \n"

#define CLEAR_PIPELINE      "nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" \
							"nop \nnop \nnop \nnop \nnop \nnop \n" 

#define CLEAR_PIPELINE_AARCH64 \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n" \
                "nop \n nop \n nop \n nop \n nop \n nop \n"

#define CLEAR_PIPELINE_x16  CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE \
            CLEAR_PIPELINE

#define CLEAR_PIPELINE_x16_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64 \
                CLEAR_PIPELINE_AARCH64

#endif // WORKLOAD_H
