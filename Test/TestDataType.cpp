#include <iostream>

#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::MakeDouble;

struct TestType
{
    TestType()
    {
        std::cout << "Created\n";
        Value = 0;
    }

    TestType( const TestType & T )
    {
        Value = T.Value;
        std::cout << "Copy Created\n";
    }

    TestType & operator = ( const TestType & T )
    {
        std::cout << "Copying.\n";
        Value = T.Value;

        return *this;
    }

    int Value;
};

int main()
{
    DtValue V( 2.3, & DtDouble );
    DtValue V1( std::string("asd"), & DtString );
    DtValue V2( std::vector<DtValue>(), & DtArray );

    V2[0] = V;
    V2[5] = V1;

    std::cout << V2 << " : " << V2.Size() << "\n";
}
