#include <cstddef>


template<typename T> class UniquePtr
{
private:
    T* ptr;

    UniquePtr(T* ptr)
    {
        this->ptr = ptr;
    }

public:
    ~UniquePtr()
    {
        delete ptr;
    }
    
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

    T& operator*() const
    {
        return *ptr;
    }

    T* operator->() const
    {
        return ptr;
    }

    UniquePtr(UniquePtr const& p) = delete;

    UniquePtr& operator=(const UniquePtr&) = delete;

    operator bool() const
    {
        return (nullptr != ptr);
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

    template<class... Args> static UniquePtr<T> make( Args&&... args )
    {
        return UniquePtr<T>(new T(args...));
    }
};


