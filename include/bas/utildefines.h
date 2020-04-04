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

using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::int8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::uint8_t;

/* True is returned for powers of two and zero. */
inline bool is_power_of_2(size_t x)
{
    return (x & (x - 1)) == 0;
}

template<typename T> T ceil_power_of_2(T x)
{
    x -= 1;
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);

    if constexpr (sizeof(T) >= 2) {
        x |= (x >> 8);
    }
    if constexpr (sizeof(T) >= 4) {
        x |= (x >> 16);
    }
    if constexpr (sizeof(T) >= 8) {
        x |= (x >> 32);
    }

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
