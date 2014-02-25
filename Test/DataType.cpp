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

//    d1 = & d2;

    std::cout << d1 << "\n";

    a1[0] = d1;
    a1[1] = s1;

    a2[0] = d2;
    a2[1] = & a1;

    a2[ "Hi" ] = 1;
    
    std::cout << a1 << "Size: " << Size( a1 ) << "\n";
    std::cout << a2 << "Size: " << Size( a2 ) << "\n";
    
    a1[0] = 9;

    std::cout << a2 << "Size: " << Size( a2 ) << "\n";
}
