#pragma once

#include "allocator.h"
#include "vector_base.h"

namespace bas {

template<typename T, size_t N = 0, typename AllocatorT = RawAllocator>
class Vector {
  private:
    VectorBase<T, AllocatorT> m_base;
    AllocatorT m_allocator;
    AlignedBuffer<sizeof(T) * N, alignof(T)> m_inline_buffer;

    template<typename OtherT, size_t OtherN, typename OtherAllocator>
    friend class Vector;

  public:
    Vector()
    {
        m_base.set_pointers(this->inline_buffer(), 0, N);
    }

    ~Vector()
    {
        destruct_n(m_base.m_begin, m_base.size());
        if (!this->is_inline()) {
            m_allocator.free(m_base.m_begin);
        }
    }

    explicit Vector(size_t size) : Vector()
    {
        m_base.reserve(size, m_allocator);
        construct_default_n(m_base.m_begin, size);
        m_base.set_pointers(m_base.m_begin, size, m_base.capacity());
    }

    Vector(size_t size, const T &value) : Vector()
    {
        m_base.reserve(size, m_allocator);
        std::fill_n(m_base.m_begin, size, value);
        m_base.set_pointers(m_base.m_begin, size, m_base.capacity());
    }

    Vector(const std::initializer_list<T> &values)
        : Vector(ArrayRef<T>(values))
    {
    }

    Vector(ArrayRef<T> values) : Vector()
    {
        m_base.extend(values, m_allocator);
    }

    template<typename SequenceT>
    static Vector FromSequence(const SequenceT &sequence)
    {
        Vector vector;
        for (const auto &value : sequence) {
            vector.append(value);
        }
        return vector;
    }

    Vector(const Vector &other) : m_allocator(other.m_allocator)
    {
        this->init_copy_from_other_vector(other);
    }

    template<size_t OtherN>
    Vector(const Vector<T, OtherN, AllocatorT> &other)
        : m_allocator(other.m_allocator)
    {
        this->init_copy_from_other_vector(other);
    }

    template<size_t OtherN>
    Vector(Vector<T, OtherN, AllocatorT> &&other) noexcept
        : m_allocator(other.m_allocator)
    {
        size_t size = other.size();

        if (other.is_inline()) {
            if (size <= N) {
                /* Copy between inline buffers. */
                m_base.set_pointers(this->inline_buffer(), size, N);
                uninitialized_relocate_n(
                    other.m_base.m_begin, size, m_base.m_begin);
            }
            else {
                /* Copy from inline buffer to newly allocated buffer. */
                uint capacity = size;
                m_base.set_pointers((T *)m_allocator.allocate(
                                        sizeof(T) * capacity, alignof(T)),
                                    size,
                                    capacity);
                uninitialized_relocate_n(
                    other.m_base.m_begin, size, m_base.m_begin);
            }
        }
        else {
            /* Steal the pointer. */
            m_base = other.m_base;
        }

        other.m_base.set_pointers(other.inline_buffer(), 0, OtherN);
    }

    Vector &operator=(const Vector &other)
    {
        if (this == &other) {
            return *this;
        }

        this->~Vector();
        new (this) Vector(other);

        return *this;
    }

    Vector &operator=(Vector &&other)
    {
        if (this == &other) {
            return *this;
        }

        /* This can fail, when the vector is used to build a recursive data
           structure. See https://youtu.be/7Qgd9B1KuMQ?t=840. */
        this->~Vector();
        new (this) Vector(std::move(other));

        return *this;
    }

    T &operator[](size_t index)
    {
        return m_base[index];
    }

    const T &operator[](size_t index) const
    {
        return m_base[index];
    }

    operator ArrayRef<T>() const
    {
        return m_base;
    }

    operator MutableArrayRef<T>()
    {
        return m_base;
    }

    ArrayRef<T> as_ref() const
    {
        return m_base;
    }

    MutableArrayRef<T> as_mutable_ref()
    {
        return m_base;
    }

    size_t size() const
    {
        return m_base.size();
    }

    void append(const T &value)
    {
        m_base.append(value, m_allocator);
    }

    void append(T &&value)
    {
        m_base.append(std::move(value), m_allocator);
    }

    size_t append_and_get_index(const T &value)
    {
        return m_base.append_and_get_index(value, m_allocator);
    }

    bool contains(const T &value)
    {
        return m_base.contains(value);
    }

    void append_n_times(const T &value, size_t n)
    {
        m_base.append_n_times(value, n, m_allocator);
    }

    void append_non_duplicates(const T &value)
    {
        m_base.append_non_duplicates(value, m_allocator);
    }

    void extend(ArrayRef<T> array)
    {
        m_base.extend(array, m_allocator);
    }

    void extend(T *start, size_t n)
    {
        m_base.extend(start, n, m_allocator);
    }

    void extend_non_duplicates(ArrayRef<T> array)
    {
        m_base.extend_non_duplicates(array, m_allocator);
    }

    const T &last() const
    {
        return m_base.last();
    }

    T &last()
    {
        return m_base.last();
    }

    void fill(const T &value)
    {
        m_base.fill(value);
    }

    void fill_indices(ArrayRef<size_t> indices, const T &value)
    {
        m_base.fill_indices(indices, value);
    }

    bool is_empty() const
    {
        return m_base.is_empty();
    }

    void remove_last()
    {
        m_base.remove_last();
    }

    T pop_last()
    {
        return m_base.pop_last();
    }

    void remove_and_reorder(size_t index)
    {
        m_base.remove_and_reorder(index);
    }

    void remove_first_occurrence_and_reorder(const T &value)
    {
        m_base.remove_first_occurrence_and_reorder(value);
    }

    ssize_t index_try(const T &value) const
    {
        return m_base.index_try(value);
    }

    size_t index(const T &value) const
    {
        ssize_t index = this->index_try(value);
        assert(index >= 0);
        return (size_t)index;
    }

    void reserve(size_t capacity)
    {
        m_base.reserve(capacity, m_allocator);
    }

    bool is_inline() const
    {
        return m_base.m_begin == this->inline_buffer();
    }

    void clear()
    {
        m_base.clear();
    }

    T *begin()
    {
        return m_base.m_begin;
    }

    T *end()
    {
        return m_base.m_end;
    }

    const T *begin() const
    {
        return m_base.m_begin;
    }

    const T *end() const
    {
        return m_base.m_end;
    }

  private:
    T *inline_buffer()
    {
        return nullptr;
        // return (T *)m_inline_buffer.ptr();
    }

    const T *inline_buffer() const
    {
        return nullptr;
        // return (T *)m_inline_buffer.ptr();
    }

    template<size_t OtherN>
    void init_copy_from_other_vector(const Vector<T, OtherN> &other)
    {
        size_t size = other.size();

        if (size <= N) {
            m_base.set_pointers(this->inline_buffer(), size, N);
        }
        else {
            m_base.set_pointers(
                (T *)m_allocator.allocate(sizeof(T) * size, alignof(T)),
                size,
                size);
        }

        uninitialized_copy(
            other.m_base.m_begin, other.m_base.m_end, m_base.m_begin);
    }
};

}  // namespace bas
