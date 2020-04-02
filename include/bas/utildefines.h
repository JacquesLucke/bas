#pragma once

#include <cassert>
#include <cstddef>
#include <cstdint>

namespace bas {

using std::size_t;

inline bool is_power_of_2(size_t x)
{
    return (x & (x - 1)) == 0;
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
