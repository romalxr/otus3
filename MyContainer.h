#pragma once

template<typename T, typename A=std::allocator<T> >
class MyContainer
{
public:
    struct Node
    {
        T data;
        Node* next;
    };
private:
    Node* p = nullptr;
    Node* head = nullptr;
    std::size_t size=0;
    using Allocator = typename A::template rebind<Node>::other;
    Allocator allocator;

public:
    class iterator
    {
    public:
        iterator(Node* _ptr = nullptr) : ptr(_ptr) {}

        iterator operator++()
        {
            ptr = ptr->next;
            return *this;
        }
        T& operator*()
        {
            return ptr->data;
        }

        bool operator!=(const iterator& rhs)
        {
            return ptr != rhs.ptr;
        }
    private:
        Node* ptr;
    };

    ~MyContainer()
    {
        while(size!=0)
        {
            p = head;
            for (int i = size-1; i > 0; --i) {
                p = p->next;
            }
            allocator.destroy(p);
            allocator.deallocate(p,1);
            --size;
        }
    }

    void push_back(T data)
    {
        if(p == nullptr) {
            p = allocator.allocate(1);
            p->next= nullptr;
            allocator.construct(&(p->data), data);
            head = p;
        }
        else
        {
            (p->next) = allocator.allocate(1);
            p = p->next;
            p->next = nullptr;
            allocator.construct(&(p->data), data);
        }
        ++size;
    }

    iterator begin()
    {
        return iterator(head);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

};