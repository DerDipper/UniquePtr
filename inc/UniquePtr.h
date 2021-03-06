#pragma once
/*** Includes ***************************************************************/
#include <cstddef>

/*** Class ******************************************************************/
template<typename T, size_t N = 0> class UniquePtr
{

private:
    T* ptr;

public:
    /* Constructors */
    UniquePtr()
    {
        this->ptr = nullptr;
    }

    explicit UniquePtr(nullptr_t)
    {
        ptr = nullptr;
    }

    UniquePtr(UniquePtr&& p)
    {
        this->ptr = p.ptr;
        p.ptr = nullptr;
    }

    UniquePtr(T* ptr)
    {
        this->ptr = ptr;
    }

    UniquePtr(UniquePtr const& p) = delete;

    /* Destructors */
    ~UniquePtr()
    {
        delete ptr;
    }

    /* Operators */
    T& operator*() const
    {
        return *ptr;
    }

    T* operator->() const
    {
        return ptr;
    }

    UniquePtr& operator=(UniquePtr&& rhs)
    {
        delete ptr;

        ptr = rhs.ptr;
        rhs.ptr = nullptr;
        return *this;
    }

    UniquePtr& operator=(nullptr_t)
    {
        delete ptr;

        ptr = nullptr;
        return *this;
    }

    UniquePtr& operator=(const UniquePtr&) = delete;

    explicit operator bool() const
    {
        return (nullptr != ptr);
    }

    T& operator[](size_t index)
    {
        return ptr[index];
    }

    /* Getters */
    T* get(void)
    {
        return ptr;
    }

    /* Methods */
    T* release(void)
    {
        T* retPtr = ptr;
        ptr = nullptr;
        return retPtr;
    }

    void swap(UniquePtr& rhs)
    {
        T* temp = this->ptr;
        this->ptr = rhs.ptr;
        rhs.ptr = temp;
    }

    /* Static Methods */
    template<class... Args> static UniquePtr<T> make( Args&&... args )
    {
        return UniquePtr<T>(new T(args...));
    }
};

/*** External Functions *****************************************************/
template<typename T> void swap(UniquePtr<T>& lhs, UniquePtr<T>& rhs)
{
    lhs.swap(rhs);
}

/*** External Operators *****************************************************/
template<typename TLHS, typename TRHS> bool operator==(UniquePtr<TLHS>& lhs, UniquePtr<TRHS>& rhs)
{
    return (lhs.get() == rhs.get());
}

template<typename TLHS> bool operator==(UniquePtr<TLHS>& lhs, nullptr_t)
{
    return (lhs.get() == nullptr);
}

template<typename TRHS> bool operator==(nullptr_t, UniquePtr<TRHS>& rhs)
{
    return (nullptr == rhs.get());
}

template<typename TLHS, typename TRHS> bool operator!=(UniquePtr<TLHS>& lhs, UniquePtr<TRHS>& rhs)
{
    return (lhs.get() != rhs.get());
}

template<typename TLHS> bool operator!=(UniquePtr<TLHS>& lhs, nullptr_t)
{
    return (lhs.get() != nullptr);
}

template<typename TRHS> bool operator!=(nullptr_t, UniquePtr<TRHS>& rhs)
{
    return (nullptr != rhs.get());
}

template<typename TLHS, typename TRHS> bool operator>(UniquePtr<TLHS>& lhs, UniquePtr<TRHS>& rhs)
{
    return (lhs.get() > rhs.get());
}

template<typename TLHS, typename TRHS> bool operator>=(UniquePtr<TLHS>& lhs, UniquePtr<TRHS>& rhs)
{
    return (lhs.get() >= rhs.get());
}

template<typename TLHS, typename TRHS> bool operator<(UniquePtr<TLHS>& lhs, UniquePtr<TRHS>& rhs)
{
    return (lhs.get() < rhs.get());
}

template<typename TLHS, typename TRHS> bool operator<=(UniquePtr<TLHS>& lhs, UniquePtr<TRHS>& rhs)
{
    return (lhs.get() <= rhs.get());
}


