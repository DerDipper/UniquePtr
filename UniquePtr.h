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

    template<class... Args> static UniquePtr<T> make( Args&&... args )
    {
        return UniquePtr<T>(new T(args...));
    }
};


