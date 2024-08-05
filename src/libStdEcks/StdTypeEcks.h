#ifndef STDTYPEECKS_H_
#define STDTYPEECKS_H_

/* NOTE(Ecks): static Name Conventions */
#define internal static
#define persist static
#define global static



/* NOTE(Ecks): Memory Sizes */
#define kilobytes(value) ((value)*1024LL) 
#define megabytes(value) (kilobytes(value)*1024LL)
#define gigabytes(value) (megabytes(value)*1024LL)
#define terabytes(value) (gigabytes(value)*1024LL)



/* NOTE(Ecks): Integers */
#undef U8_MAX
#define U8_MAX 255

#undef U16_MAX
#define U16_MAX 65535

#undef U32_MAX
#define U32_MAX 4294967295

#undef U64_MAX
#define U64_MAX 18446744073709551615

#undef I8_MIN
#undef I8_MAX
#define I8_MIN -128
#define I8_MAX 127

#undef I16_MIN
#undef I16_MAX
#define I16_MIN -32768
#define I16_MAX 32767

#undef I32_MIN
#undef I32_MAX
#define I32_MIN -2147483648
#define I32_MAX 2147483647

#undef I64_MIN
#undef I64_MAX
#define I64_MIN -9223372036854775808
#define I64_MAX 9223372036854775807

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long int lu32;
typedef unsigned long long lu64;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long int l32;
typedef signed long long int l64;

#if __amd64__
typedef lu64 u64;
typedef l64 i64;
#else
typedef lu32 u64;
typedef l32 i64;
#endif

// TODO(Ecks): Probably varies in signedness between different platforms.
typedef u16 wchar;
#if UNICODE
typedef wchar tchar;
#else
typedef char tchar;
#endif

/* NOTE(Ecks): Booleans */
#define true 1
#define false 0
typedef int b32;



/* NOTE(Ecks): Precision Floating Points. */
#undef R32_MIN
#undef R32_MAX
#define R32_MIN 1.17549435082228750796873653722224568e-38F32
#define R32_MAX 3.40282346638528859811704183484516925e+38F32

#undef R64_MIN
#undef R64_MAX
#define R64_MIN ((double)2.22507385850720138309023271733240406e-308L)
#define R64_MAX ((double)1.79769313486231570814527423731704357e+308L)

#undef LR64_MIN
#undef LR64_MAX
#define LR64_MIN 3.36210314311209350626267781732175260e-4932L
#define LR64_MAX 1.18973149535723176502126385303097021e+4932L

typedef float r32;
typedef double r64;
typedef long double lr64;



/* Low/High bit macros */
#define iLo4(i) ((i8)(i) & 0xFF)
#define iHi4(i) ((signed)(i) >> 4)
#define uLo4(i) ((u8)(i) & 0xFF)
#define uHi4(i) ((unsigned)(i) >> 4)

#define iLo8(i) ((i8)(i) & 0xFFFF)
#define iHi8(i) ((signed)(i) >> 8)
#define uLo8(i) ((u8)(i) & 0xFFFF)
#define uHi8(i) ((unsigned)(i) >> 8)

#define iLo16(i) ((i16)(i) & 0xFFFFFF)
#define iHi16(i) ((signed)(i) >> 16)
#define uLo16(i) ((u16)(i) & 0xFFFFFF)
#define uHi16(i) ((unsigned)(i) >> 16)

#define iLo32(i) ((i32)(i) & 0xFFFFFFFF)
#define iHi32(i) ((signed)(i) >> 32)
#define uLo32(i) ((u32)(i) & 0xFFFFFFFF)
#define uHi32(i) ((unsigned)(i) >> 32)



/* Color */
#define rgb(r, g, b) (((r) << 16)|((g) << 8)|(b))
#define argb(a, r, g, b) (((a) << 24)|((r) << 16)|((g) << 8)|(b))
#define rgba(r, g, b, a) (((r) << 24)|((g) << 16)|((b) << 8)|(a))
#endif
