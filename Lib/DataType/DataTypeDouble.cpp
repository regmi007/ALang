#include <iostream>

#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DataTypeDouble;

using ALang::Error::OperationError;

DtValue DataTypeDouble::Add( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    DtValue Val;
    Val.Data = boost::any_cast<double>( Lhs.Data ) + boost::any_cast<double>( Rhs.Data );
    Val.Type = Lhs.Type;
    
    return Val;
}

DtValue DataTypeDouble::Substract( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    DtValue Val;
    Val.Data = boost::any_cast<double>( Lhs.Data ) - boost::any_cast<double>( Rhs.Data );
    Val.Type = Lhs.Type;
    
    return Val;
}

DtValue DataTypeDouble::Multiply( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    DtValue Val;
    Val.Data = boost::any_cast<double>( Lhs.Data ) * boost::any_cast<double>( Rhs.Data );
    Val.Type = Lhs.Type;
    
    return Val;
}

DtValue DataTypeDouble::Divide( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    DtValue Val;
    Val.Data = boost::any_cast<double>( Lhs.Data ) / boost::any_cast<double>( Rhs.Data );
    Val.Type = Lhs.Type;
    
    return Val;
}

void DataTypeDouble::To_Stream( std::ostream & Out, const DtValue & Rhs )
{
    Out << boost::any_cast<double>( Rhs.Data );
}

DataTypeDouble DtDouble;
