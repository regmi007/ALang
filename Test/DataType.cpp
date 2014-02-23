#include <iostream>

#include "DataType.h"

using ALang::Dt::DtValue;

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
    DtValue V = 2.3;
    DtValue V1 = "Hello World";
    DtValue V2 =  std::vector<DtValue>();

    V2[0] = V;
    V2[1] = V1;
    V2[2] = V;
    V2[3] = V1;

    std::cout << V2 << " : " << V2.Size() << "\n";
}
