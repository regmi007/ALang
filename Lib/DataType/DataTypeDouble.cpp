#include <iostream>

#include "DataType.hpp"

using ALang::Dt::DtValue;
using ALang::Dt::DataTypeDouble;

using ALang::Error::OperationError;

DtValue DataTypeDouble::Add( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    const double *PLhs = boost::any_cast< const double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    DtValue Val = ( *PLhs ) + ( *PRhs );
    
    return Val;
}

DtValue DataTypeDouble::Substract( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    const double *PLhs = boost::any_cast< const double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    DtValue Val = ( *PLhs ) - ( *PRhs );
    
    return Val;
}

DtValue DataTypeDouble::Multiply( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    const double *PLhs = boost::any_cast< const double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    DtValue Val = ( *PLhs ) * ( *PRhs );
    
    return Val;
}

DtValue DataTypeDouble::Divide( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    const double *PLhs = boost::any_cast< const double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    DtValue Val = ( *PLhs ) / ( *PRhs );
    
    return Val;
}

DtValue & DataTypeDouble::AddAssign( DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    double *PLhs = boost::any_cast< double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    ( *PLhs ) += ( *PRhs );
    return Lhs;
}

DtValue & DataTypeDouble::SubstractAssign( DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    double *PLhs = boost::any_cast< double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    ( *PLhs ) -= ( *PRhs );
    return Lhs;
}

DtValue & DataTypeDouble::MultiplyAssign( DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    double *PLhs = boost::any_cast< double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    ( *PLhs ) *= ( *PRhs );
    return Lhs;
}

DtValue & DataTypeDouble::DivideAssign( DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "Cannot add type other than DataTypeDouble." );

    double *PLhs = boost::any_cast< double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    ( *PLhs ) /= ( *PRhs );
    return Lhs;
}

void DataTypeDouble::ToStream( std::ostream & Out, const DtValue & Rhs )
{
    const double *PRhs = nullptr;
    
    if( Rhs.Data.type() == typeid( double ) )
        PRhs = boost::any_cast< const double >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PRhs = boost::any_cast< const double >( PData );        
    }

    if( PRhs != nullptr )
        Out << *PRhs;
}

bool DataTypeDouble::LessThan( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "<, Cannot compare type other than DataTypeDouble." );

    const double *PLhs = boost::any_cast< const double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    return ( *PLhs ) < ( *PRhs );
}

bool DataTypeDouble::LessThanEqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "<=, Cannot compare type other than DataTypeDouble." );

    const double *PLhs = boost::any_cast< const double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    return ( *PLhs ) <= ( *PRhs );
}

bool DataTypeDouble::GreaterThan( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( ">, Cannot compare type other than DataTypeDouble." );

    const double *PLhs = boost::any_cast< const double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    return ( *PLhs ) > ( *PRhs );
}

bool DataTypeDouble::GreaterThanEqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( ">=, Cannot compare type other than DataTypeDouble." );

    const double *PLhs = boost::any_cast< const double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    return ( *PLhs ) >= ( *PRhs );
}

bool DataTypeDouble::EqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    if( Rhs.Data.type() != typeid( double ) )
        throw OperationError( "==, Cannot compare type other than DataTypeDouble." );

    const double *PLhs = boost::any_cast< const double >( & Lhs.Data );
    const double *PRhs = boost::any_cast< const double >( & Rhs.Data );

    return ( *PLhs ) == ( *PRhs );
}

DataTypeDouble DtDouble;
