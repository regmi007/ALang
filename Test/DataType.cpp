#include <iostream>

#include "DataType.hpp"

using ALang::Dt::DtValue;
using ALang::Dt::Size;
using ALang::Dt::DtValueVec;
using ALang::Dt::DtValueMap;

int main()
{
    DtValue d1 = 2.3, d2 = 3.5;
    DtValue s1 = "Hello ", s2 = "World";

    DtValue a1 = DtValueVec();
    DtValue a2 =  DtValueVec();

    a1[0] = d1;
    a1[1] = s1;

    a2[0] = d2;
    a2[1] = s2;
    a2[2] = & a1;
 
    DtValue st1 = DtValueMap();

    st1[ "Hi" ] = a1;
    st1[ "Hello" ] = & a2;
    st1[ "A" ] = 2.45;
    st1[ "B" ] = "My name is shyam";

    st1[ "Hello" ][ 10 ] = "This is awesome !";
 
    std::cout << st1 << "\n";
}
