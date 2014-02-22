#include <stdexcept>

#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DataTypeArray;

using ALang::Error::OperationError;

/*
DtValue & DataTypeString::Assign( DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( std::string ) )
        throw OperationError( "Cannot assigh type other than DataTypeString." );

    Lhs.Data = Rhs.Data;
    return Lhs;
}
*/

DtValue DataTypeArray::Add ( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( std::vector< DtValue > ) )
        throw OperationError( "Cannot add type other than DataTypeString." );

    int Size = boost::any_cast< std::vector< DtValue >>( Lhs.Data ).size();

    DtValue Val;
    Val.Data = std::vector< DtValue >();
    Val.Type = Lhs.Type;
 
    for( int i = 0; i < Size; ++i )
    {
        boost::any_cast< std::vector< DtValue >>( Val.Data ).push_back(
            boost::any_cast< std::vector< DtValue >>( Lhs.Data )[ i ]
        );
    }

    Size = boost::any_cast< std::vector< DtValue >>( Rhs.Data ).size();

    for( int i = 0; i < Size; ++i )
    {
        boost::any_cast< std::vector< DtValue >>( Val.Data ).push_back(
            boost::any_cast< std::vector< DtValue >>( Rhs.Data )[ i ]
        );
    }
 
   return Val;
}

void DataTypeArray::To_Stream( std::ostream & Out, const DtValue & Rhs )
{
    int Size = boost::any_cast< std::vector< DtValue >>( Rhs.Data ).size();

    Out << "[ ";
    for( int i = 0; i < Size; ++i )
    {
        Out << boost::any_cast< std::vector< DtValue >>( Rhs.Data )[ i ];

        if( i != Size - 1 )
            Out << ", ";
    }
    Out << " ]";
}

DtValue DataTypeArray::Size( const DtValue & Lhs )
{
    DtValue Val;
    Val.Data = boost::any_cast< std::vector< DtValue >>( Lhs.Data ).size();
    Val.Type = & DtDouble;
    return Val;
}

DtValue & DataTypeArray::SubScriptGet( const DtValue & Lhs, int Index )
{
    return boost::any_cast< std::vector< DtValue >>( Lhs.Data ).at( Index );
}


DtValue & DataTypeArray::SubScriptSet( DtValue & Lhs, int Index )
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
