#pragma once

#include <cstdlib>

#include "utildefines.h"

namespace bas {

class RawAllocator {
  public:
    void *allocate(size_t size, size_t alignment) const
    {
        assert(size % alignment == 0);
        return aligned_alloc(alignment, size);
    }

    template<size_t Alignment> void *allocate(size_t size) const
    {
        return this->allocate(size, Alignment);
    }

    template<size_t Size, size_t Alignment> void *allocate() const
    {
        return this->allocate(Size, Alignment);
    }

    void free(void *ptr) const
    {
        free(ptr);
    }
};

}  // namespace bas
