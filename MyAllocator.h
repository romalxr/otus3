#pragma once

template<typename T, uint num_elems>
class MyAlloc
{
private:
    T* p = nullptr;
    int total = 0;
    void* head = nullptr;
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const pointer;
    using reference = T&;
    using const_reference = const reference;
    MyAlloc()
    {
        p = (T*)std::malloc(num_elems * sizeof(T));
        head = p;
        if (!p)
            throw std::bad_alloc();
    }

    ~MyAlloc()
    {
        std::free(head);
    }

    T* allocate(std::size_t n)
    {
        ++total;
        if(total>num_elems)
        {
            throw std::bad_alloc();
        }
        return p++;
    }

    void deallocate(T* p, std::size_t n)
    {
        --total;
    }

    template<typename U, typename... Args>
    void construct(U* p, Args&&... args)
    {
        new((void*)p) U(std::forward<Args...>(args...));
    }

    template<typename U>
    void destroy(U* p)
    {
        p->~U();
    }

    template< typename U >
    struct rebind
    {
        typedef MyAlloc<U, num_elems> other;
    };
};