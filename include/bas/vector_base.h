#pragma once

#include "array_ref.h"
#include "index_range.h"
#include "memory_utils.h"

namespace bas {

template<typename T, typename AllocatorT> struct VectorBase {
    T *m_begin;
    T *m_end;
    T *m_capacity_end;

#ifdef DEBUG
    size_t m_debug_size;
#    define VECTOR_BASE_UPDATE_DEBUG_SIZE(ptr) \
        (ptr)->m_debug_size = (ptr)->size()
#else
#    define VECTOR_BASE_UPDATE_DEBUG_SIZE(ptr) ((void)0)
#endif

    VectorBase() = default;
    ~VectorBase() = default;

    void set_pointers(T *begin, size_t size, size_t capacity)
    {
        m_begin = begin;
        m_end = begin + size;
        m_capacity_end = begin + capacity;
        VECTOR_BASE_UPDATE_DEBUG_SIZE(this);
    }

    size_t size() const
    {
        return m_end - m_begin;
    }

    size_t capacity() const
    {
        return m_capacity_end - m_begin;
    }

    operator ArrayRef<T>() const
    {
        return this->as_ref();
    }

    operator MutableArrayRef<T>()
    {
        return this->as_mutable_ref();
    }

    ArrayRef<T> as_ref() const
    {
        return ArrayRef<T>(m_begin, this->size());
    }

    MutableArrayRef<T> as_mutable_ref()
    {
        return MutableArrayRef<T>(m_begin, this->size());
    }

    void append(const T &value, AllocatorT &allocator)
    {
        if (m_end == m_capacity_end) {
            this->grow(this->size() + 1, allocator);
        }
        this->append_unchecked(value);
    }

    void append(T &&value, AllocatorT &allocator)
    {
        if (m_end == m_capacity_end) {
            this->grow(this->size() + 1, allocator);
        }
        this->append_unchecked(std::move(value));
    }

    void append_unchecked(const T &value)
    {
        assert(m_end < m_capacity_end);
        new (m_end) T(value);
        m_end++;
        VECTOR_BASE_UPDATE_DEBUG_SIZE(this);
    }

    void append_unchecked(T &&value)
    {
        assert(m_end < m_capacity_end);
        new (m_end) T(std::move(value));
        m_end++;
        VECTOR_BASE_UPDATE_DEBUG_SIZE(this);
    }

    size_t append_and_get_index(const T &value, AllocatorT &allocator)
    {
        size_t index = this->size();
        this->append(value, allocator);
        return index;
    }

    void append_non_duplicates(const T &value, AllocatorT &allocator)
    {
        if (!this->contains(value)) {
            this->append(value, allocator);
        }
    }

    bool contains(const T &value)
    {
        for (const T &elem : *this) {
            if (elem == value) {
                return true;
            }
        }
        return false;
    }

    void append_n_times(const T &value, size_t n, AllocatorT &allocator)
    {
        this->reserve(this->size() + n, allocator);
        uninitialized_fill_n(m_end, n, value);
        m_end += n;
        VECTOR_BASE_UPDATE_DEBUG_SIZE(this);
    }

    void extend(ArrayRef<T> array, AllocatorT &allocator)
    {
        this->extend(array.begin(), array.size(), allocator);
    }

    void extend(const T *start, size_t n, AllocatorT &allocator)
    {
        this->reserve(this->size() + n, allocator);
        this->extend_unchecked(start, n);
    }

    void extend_unchecked(const T *start, size_t n)
    {
        uninitialized_copy_n(start, n, m_end);
        m_end += n;
        VECTOR_BASE_UPDATE_DEBUG_SIZE(this);
    }

    void extend_non_duplicates(ArrayRef<T> array, AllocatorT &allocator)
    {
        for (const T &value : array) {
            this->append_non_duplicates(value, allocator);
        }
    }

    void reserve(size_t capacity, AllocatorT &allocator)
    {
        if (capacity > this->capacity()) {
            this->grow(capacity, allocator);
        }
    }

    const T &last() const
    {
        assert(this->size() > 0);
        return *(m_end - 1);
    }

    T &last()
    {
        assert(this->size() > 0);
        return *(m_end - 1);
    }

    void fill(const T &value)
    {
        std::fill(m_begin, m_end, value);
    }

    void fill_indices(ArrayRef<size_t> indices, const T &value)
    {
        MutableArrayRef<T>(*this).fill_indices(indices, value);
    }

    bool is_empty() const
    {
        return m_begin == m_end;
    }

    void clear()
    {
        destruct_n(m_begin, this->size());
        m_end = m_begin;
        VECTOR_BASE_UPDATE_DEBUG_SIZE(this);
    }

    void clear_and_free(AllocatorT &allocator)
    {
        if (m_begin != nullptr) {
            destruct_n(m_begin, this->size());
            allocator.free(m_begin);
            m_begin = nullptr;
            m_end = nullptr;
            m_capacity_end = nullptr;
        }
    }

    IndexRange index_range() const
    {
        return IndexRange(this->size());
    }

    /**
     * Deconstructs the last element and decreases the size by one.
     * This will assert when the vector is empty.
     */
    void remove_last()
    {
        assert(!this->is_empty());
        m_end--;
        destruct(m_end);
        VECTOR_BASE_UPDATE_DEBUG_SIZE(this);
    }

    /**
     * Remove the last element from the vector and return it.
     */
    T pop_last()
    {
        assert(!this->is_empty());
        m_end--;
        T value = std::move(*m_end);
        destruct(m_end);
        VECTOR_BASE_UPDATE_DEBUG_SIZE(this);
        return value;
    }

    /**
     * Delete any element in the vector.
     * The empty space will be filled by the previously last element.
     */
    void remove_and_reorder(size_t index)
    {
        assert(index < this->size());
        T *element_to_remove = m_begin + index;
        m_end--;
        if (element_to_remove < m_end) {
            *element_to_remove = std::move(*m_end);
        }
        destruct(m_end);
        VECTOR_BASE_UPDATE_DEBUG_SIZE(this);
    }

    void remove_first_occurrence_and_reorder(const T &value)
    {
        size_t index = this->index(value);
        this->remove_and_reorder((uint)index);
    }

    /**
     * Do a linear search to find the value in the vector.
     * When found, return the first index, otherwise return -1.
     */
    ssize_t index_try(const T &value) const
    {
        for (T *current = m_begin; current != m_end; current++) {
            if (*current == value) {
                return current - m_begin;
            }
        }
        return -1;
    }

    /**
     * Do a linear search to find the value in the vector.
     * When found, return the first index, otherwise fail.
     */
    size_t index(const T &value) const
    {
        ssize_t index = this->index_try(value);
        assert(index >= 0);
        return (size_t)index;
    }

    T &operator[](size_t index)
    {
        assert(index < this->size());
        return m_begin[index];
    }

    const T &operator[](size_t index) const
    {
        assert(index < this->size());
        return m_begin[index];
    }

    T *begin()
    {
        return m_begin;
    }

    T *end()
    {
        return m_end;
    }

    const T *begin() const
    {
        return m_begin;
    }

    const T *end() const
    {
        return m_end;
    }

  private:
    BAS_NOINLINE void grow(size_t min_capacity, AllocatorT &allocator)
    {
        if (min_capacity <= this->capacity()) {
            return;
        }

        size_t size = this->size();
        min_capacity = ceil_power_of_2(min_capacity);

        T *new_begin = (T *)allocator.allocate(sizeof(T) * min_capacity,
                                               alignof(T));
        uninitialized_relocate_n(m_begin, size, new_begin);
        allocator.free(m_begin);

        m_begin = new_begin;
        m_end = new_begin + size;
        m_capacity_end = new_begin + min_capacity;
    }
};

}  // namespace bas
