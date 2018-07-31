#include <iostream>
#include <map>
#include <vector>
#include "MyAllocator.h"
#include "MyContainer.h"

template<typename T>
T factorial(T n)
{
    T f=1;
    for(T i = 1; i <= n;++i)
        f*=i;
    return f;
};

int main(int argc, char **argv)
{

    std::map<int, int> sm;
    std::map<int, int, std::less<int>, MyAlloc<std::pair<int,int>,10>> cm;
    for (int i = 0; i < 10; i++)
    {
        sm.emplace(std::make_pair(i, factorial(i)));
        cm.emplace(std::make_pair(i, factorial(i)));
    }

    for(const auto& it : cm)
    {
        std::cout<< it.first << " " << it.second << std::endl;
    }

    MyContainer<int> dc;
    MyContainer<int, MyAlloc<int,10> > c;

    for(int i=0; i<11;++i)
    {
        try
        {
            dc.push_back(i+1);
            c.push_back(i+1);
        }
        catch (std::bad_alloc)
        {
            std::cerr << "bad_alloc";
        }
    }

    for(const auto& i : c)
    {
        std::cout<<i<<std::endl;
    }

    return 0;
}