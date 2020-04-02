#pragma once

#include <cstdlib>

#include "aligned_allocation.h"

namespace bas {

class RawAllocator {
  public:
    void *allocate(size_t size, size_t alignment) const
    {
        return aligned_malloc(size, alignment);
    }

    template<size_t Alignment> void *allocate(size_t size) const
    {
        return this->allocate(size, Alignment);
    }

    template<size_t Size, size_t Alignment> void *allocate() const
    {
        return this->allocate(Size, Alignment);
    }

    void free(void *pointer) const
    {
        aligned_free(pointer);
    }
};

}  // namespace bas
