#pragma once

using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long;
using InputTy = unsigned char;

#define likely(x) __builtin_expect((x), 1)
#define unlikely(x) __builtin_expect((x), 0)

enum impl_var_t {
    IMPL_SLOW_VARIANT = 1,
    IMPL_FAST_VARIANT = 2,
};

#define AC_MAGIC_NUM 0x5a
struct buf_header_t {
    unsigned char magic_num;
    unsigned char impl_variant;
};
