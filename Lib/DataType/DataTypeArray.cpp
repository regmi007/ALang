#include <stdexcept>

#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DataTypeArray;

using ALang::Error::OperationError;

DtValue DataTypeArray::Add ( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( std::vector< DtValue > ) )
        throw OperationError( "Cannot add type other than DataTypeString." );

    DtValue Val = std::vector< DtValue >();
    std::vector<DtValue> *PVal = const_cast< std::vector< DtValue >* >( boost::any_cast< std::vector< DtValue >>( & Val.Data ));

    std::vector<DtValue> *PLhs = const_cast< std::vector< DtValue >* >( boost::any_cast< std::vector< DtValue >>( & Lhs.Data ));
    std::vector<DtValue> *PRhs = const_cast< std::vector< DtValue >* >( boost::any_cast< std::vector< DtValue >>( & Rhs.Data ));

    std::size_t Size = PLhs->size();

    for( std::size_t i = 0; i < Size; ++i )
        PVal->push_back( ( *PLhs )[ i ]);

    Size = PRhs->size();

    for( std::size_t i = 0; i < Size; ++i )
        PVal->push_back( ( *PRhs )[ i ]);
 
   return Val;
}

void DataTypeArray::To_Stream( std::ostream & Out, const DtValue & Rhs )
{
    std::vector<DtValue> *Vec = const_cast<std::vector<DtValue>*>( boost::any_cast<std::vector<DtValue>>( & Rhs.Data ));
    std::size_t Size = Vec->size();

    Out << "[ ";
    for( std::size_t i = 0; i < Size; ++i )
    {
        Out << ( *Vec )[ i ];

        if( i != Size - 1 )
            Out << ", ";
    }
    Out << " ]";
}

DtValue DataTypeArray::Size( const DtValue & Lhs )
{
    std::vector<DtValue> *Vec = const_cast<std::vector<DtValue>*>( boost::any_cast<std::vector<DtValue>>( & Lhs.Data ));
    DtValue Val = ( double ) Vec->size();
    return Val;
}

DtValue & DataTypeArray::SubScriptGet( const DtValue & Lhs, std::size_t Index )
{
    std::vector<DtValue> *Vec = const_cast<std::vector<DtValue>*>( boost::any_cast<std::vector<DtValue>>( & Lhs.Data ));
    return Vec->at( Index );
}


DtValue & DataTypeArray::SubScriptSet( DtValue & Lhs, std::size_t Index )
{
    if( Index < 0 )
        throw std::out_of_range( "Index can't be less than 0." );

    std::vector< DtValue > *Vec = boost::any_cast<std::vector<DtValue>>( & Lhs.Data );

    if( Index < Vec->size() )
        return ( *Vec )[ Index ];

    if( Index == Vec->size() )
    {
        DtValue V;
        Vec->push_back( V );
        return (*Vec)[ Index ];
    }

    Vec->resize( Index + 1 );
    return ( *Vec )[ Index ];
}

DataTypeArray DtArray;
