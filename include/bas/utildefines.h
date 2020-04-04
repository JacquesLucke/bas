#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace bas {

#if defined(__GNUC__)
#    define BAS_NOINLINE __attribute__((noinline))
#else
#    define BAS_NOINLINE
#endif

#ifdef __GNUC__
#    define BAS_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#    define BAS_UNLIKELY(x) (x)
#endif

using std::size_t;
using ssize_t = std::make_signed_t<size_t>;

using std::int32_t;
using std::uint32_t;

/* True is returned for powers of two and zero. */
inline bool is_power_of_2(size_t x)
{
    return (x & (x - 1)) == 0;
}

inline uint32_t ceil_power_of_2(uint32_t x)
{
    x -= 1;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return x + 1;
}

inline uint64_t ceil_power_of_2(uint64_t x)
{
    x -= 1;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);
    return x + 1;
}

template<typename T> inline uintptr_t ptr_to_int(T *ptr)
{
    return (uintptr_t)ptr;
}

template<typename T> inline T *int_to_ptr(uintptr_t ptr)
{
    return (T *)ptr;
}

template<typename T> inline bool is_aligned(T *ptr, size_t alignment)
{
    assert(is_power_of_2(alignment));
    return (ptr_to_int(ptr) & (alignment - 1)) == 0;
}

}  // namespace bas
