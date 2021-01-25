#include "UniquePtr.h"
#include <utility>
#include <cassert>

class MyClass
{
    int value;
public:

    int getValue()
    {
        return value;
    }
    void setValue(int value)
    {
        this->value = value;
    }

    MyClass(int value)
    {
        this->value = value;
    }
};


int main()
{
    MyClass* pTemp;
    MyClass m1(1);
    MyClass m2(2);
    UniquePtr<MyClass> u1(&m1);
    UniquePtr<MyClass> u2(&m2);
    auto val5 = UniquePtr<MyClass>::make(5);
    UniquePtr<int> valInt(new int[3]);
    auto val10 = UniquePtr<MyClass>::make(10);
    auto val20 = UniquePtr<MyClass>::make(20);

    valInt[0] = 4;
    valInt[1] = valInt[0];
    valInt[2] = 3;

    assert(4 == valInt[0]);
    assert(4 == valInt[1]);
    assert(valInt[2] == 3);

    assert(5 == val5->getValue());
    assert(10 == val10->getValue());

    swap(val5, val10);

    assert(10 == val5->getValue());
    assert(5 == val10->getValue());

    assert(val20 == val20);
    val20 = nullptr;
    assert(val20 == nullptr);
    assert(nullptr == val20);

    assert(val5 != val20);
    assert(val5 != nullptr);
    assert(nullptr != val5);

    assert(u2 > u1);
    assert(u2 >= u2);
    assert(u1 < u2);
    assert(u1 <= u2);

    val20 = std::move(val10);

    pTemp = val20.get();

    assert(pTemp == val20.release());

    u1.release();
    u2.release();
    
    return 0;
}