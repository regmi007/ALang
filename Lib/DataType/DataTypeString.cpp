#include "DataType.h"

using ALang::Dt::DtValue;
using ALang::Dt::DataTypeString;

using ALang::Error::OperationError;

DtValue DataTypeString::Add ( const DtValue & Lhs, const DtValue & Rhs )
{
    const std::string *PStrLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::string ) )
        PStrLhs = boost::any_cast< const std::string >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PStrLhs = boost::any_cast< const std::string >( PData );        
    }

    const std::string *PStrRhs = nullptr;

    if( Rhs.Data.type() == typeid( std::string ) )
        PStrRhs = boost::any_cast< const std::string >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PStrRhs = boost::any_cast< const std::string >( PData );        
    }
 
    DtValue Val = std::string();
    std::string *PStrVal  = boost::any_cast< std::string >( & Val.Data );

    PStrVal->append( PStrLhs->c_str() );
    PStrVal->append( PStrRhs->c_str() );

    return Val;
}

DtValue & DataTypeString::AddAssign( DtValue & Lhs, const DtValue & Rhs )
{
    std::string *PStrLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::string ) )
        PStrLhs = boost::any_cast< std::string >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PStrLhs = boost::any_cast< std::string >( PData );        
    }

    const std::string *PStrRhs = nullptr;

    if( Rhs.Data.type() == typeid( std::string ) )
        PStrRhs = boost::any_cast< const std::string >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PStrRhs = boost::any_cast< const std::string >( PData );        
    }
 
    PStrLhs->append( PStrRhs->c_str() );

    return Lhs;
}


void DataTypeString::ToStream( std::ostream & Out, const DtValue & Rhs )
{
    const std::string *PStrRhs = nullptr;

    if( Rhs.Data.type() == typeid( std::string ) )
        PStrRhs = boost::any_cast< const std::string >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PStrRhs = boost::any_cast< const std::string >( PData );        
    }

    Out << "'" << *PStrRhs << "'";
}

DtValue DataTypeString::Size( const DtValue & Lhs )
{
    const std::string *PStrLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::string ) )
        PStrLhs = boost::any_cast< const std::string >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PStrLhs = boost::any_cast< const std::string >( PData );        
    }
    
    DtValue Val = ( double ) PStrLhs->size();
    return Val;
}

bool DataTypeString::LessThan( const DtValue & Lhs, const DtValue & Rhs )
{
    const std::string *PStrLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::string ) )
        PStrLhs = boost::any_cast< const std::string >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PStrLhs = boost::any_cast< const std::string >( PData );        
    }

    const std::string *PStrRhs = nullptr;

    if( Rhs.Data.type() == typeid( std::string ) )
        PStrRhs = boost::any_cast< const std::string >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PStrRhs = boost::any_cast< const std::string >( PData );        
    }
 
    return ( *PStrLhs ) < ( *PStrRhs );
}

bool DataTypeString::LessThanEqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    const std::string *PStrLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::string ) )
        PStrLhs = boost::any_cast< const std::string >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PStrLhs = boost::any_cast< const std::string >( PData );        
    }

    const std::string *PStrRhs = nullptr;

    if( Rhs.Data.type() == typeid( std::string ) )
        PStrRhs = boost::any_cast< const std::string >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PStrRhs = boost::any_cast< const std::string >( PData );        
    }
 
    return ( *PStrLhs ) <= ( *PStrRhs );
}

bool DataTypeString::GreaterThan( const DtValue & Lhs, const DtValue & Rhs )
{
    const std::string *PStrLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::string ) )
        PStrLhs = boost::any_cast< const std::string >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PStrLhs = boost::any_cast< const std::string >( PData );        
    }

    const std::string *PStrRhs = nullptr;

    if( Rhs.Data.type() == typeid( std::string ) )
        PStrRhs = boost::any_cast< const std::string >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PStrRhs = boost::any_cast< const std::string >( PData );        
    }
 
    return ( *PStrLhs ) > ( *PStrRhs );
}

bool DataTypeString::GreaterThanEqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    const std::string *PStrLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::string ) )
        PStrLhs = boost::any_cast< const std::string >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PStrLhs = boost::any_cast< const std::string >( PData );        
    }

    const std::string *PStrRhs = nullptr;

    if( Rhs.Data.type() == typeid( std::string ) )
        PStrRhs = boost::any_cast< const std::string >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PStrRhs = boost::any_cast< const std::string >( PData );        
    }
 
    return ( *PStrLhs ) >= ( *PStrRhs );
}

bool DataTypeString::EqualTo( const DtValue & Lhs, const DtValue & Rhs )
{
    const std::string *PStrLhs = nullptr;

    if( Lhs.Data.type() == typeid( std::string ) )
        PStrLhs = boost::any_cast< const std::string >( & Lhs.Data );

    else if( Lhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Lhs.Data );
        PStrLhs = boost::any_cast< const std::string >( PData );        
    }

    const std::string *PStrRhs = nullptr;

    if( Rhs.Data.type() == typeid( std::string ) )
        PStrRhs = boost::any_cast< const std::string >( & Rhs.Data );

    else if( Rhs.Data.type() == typeid( boost::any* ) )
    {
        boost::any *PData = boost::any_cast< boost::any* >( Rhs.Data );
        PStrRhs = boost::any_cast< const std::string >( PData );        
    }

    return ( *PStrLhs ) == ( *PStrRhs );
}

DataTypeString DtString;
