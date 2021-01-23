#include <cstddef>


template<typename T> class UniquePtr
{

private:
    T* ptr;

public:
    UniquePtr()
    {
        this->ptr = nullptr;
    }

    UniquePtr(nullptr_t)
    {
        delete ptr;
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

    ~UniquePtr()
    {
        delete ptr;
    }

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

    T* get(void)
    {
        return ptr;
    }

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

    template<class... Args> static UniquePtr<T> make( Args&&... args )
    {
        return UniquePtr<T>(new T(args...));
    }
};

template<typename T> void swap(UniquePtr<T>& lhs, UniquePtr<T>& rhs)
{
    lhs.swap(rhs);
}


