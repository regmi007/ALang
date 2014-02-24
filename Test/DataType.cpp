#include <iostream>

#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::Size;

int main()
{
    DtValue d1 = 2.3, d2 = 3.5;
    DtValue s1 = "Hello ", s2 = "World";
    DtValue a1 =  std::vector<DtValue>();
    DtValue a2 =  std::vector<DtValue>();

    a1[0] = d1;
    a1[1] = s1;

    a2[0] = d2;
    a1[1] = s2;
    
    d1 += d2;
    s1 += s2;
    a1 += a2;

    std::cout << "a1 Size: " << Size( a1 ) << "\n";
    std::cout << "d1: " << d1 << "\n";
    std::cout << "s1: " << s1 << "\n";
}
