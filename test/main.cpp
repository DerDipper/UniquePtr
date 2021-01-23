#include "UniquePtr.h"
#include <utility>
#include <iostream>

class MyClass
{
    int value;
public:

    int otherValue;

    void print()
    {
        std::cout<<"MyClass: \n    Value: "<< value << std::endl;
    }
    MyClass(int value)
    {
        this->value = value;
        std::cout<<"Created MyClass with Value: "<< value << std::endl;
    }

    ~MyClass()
    {
        std::cout<<"Deleted MyClass with Value: "<< value << std::endl;
    }
};

UniquePtr<MyClass> func(UniquePtr<MyClass> p)
{
    p->print();

    return p;
}


int main()
{
    MyClass* pC;
    auto v = UniquePtr<MyClass>::make(4);
    auto k = UniquePtr<MyClass>::make(9);
    auto p = UniquePtr<MyClass>::make(10);
    auto l = std::move(v);

    k = func(std::move(l));

    k->print();

    std::cout
    << k.get() << std::endl
    << (pC = k.release()) << std::endl 
    << k.get() << std::endl;

    delete pC;
    
    p.swap(k);
    k->print();
    swap(p,k);
    p->print();

    return 0;
}