#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include <string>
#include <ostream>
#include <boost/any.hpp>

#include "Exception.h"

namespace ALang { namespace Dt {

struct DtValue;

struct DataType
{
    ~DataType() {}

    virtual DtValue & Assign( DtValue & Lhs, const DtValue & Rhs );

    virtual DtValue Add( const DtValue & Lhs, const DtValue & Rhs );

    virtual DtValue Substract( const DtValue & Lhs, const DtValue & Rhs );

    virtual DtValue Multiply( const DtValue & Lhs, const DtValue & Rhs );

    virtual DtValue Divide( const DtValue & Lhs, const DtValue & Rhs );

    virtual DtValue & SubScriptGet( const DtValue & Lhs, int Index );
    virtual DtValue & SubScriptSet( DtValue & Lhs, int Index );

    virtual DtValue Size( const DtValue & Lhs );

    virtual void To_Stream( std::ostream & Out, const DtValue & Rhs );
};

struct DataTypeDouble : public DataType 
{
    DtValue Add( const DtValue & Lhs, const DtValue & Rhs );

    DtValue Substract( const DtValue & Lhs, const DtValue & Rhs );

    DtValue Multiply( const DtValue & Lhs,  const DtValue & Rhs );

    DtValue Divide( const DtValue & Lhs, const DtValue & Rhs );

    void To_Stream( std::ostream & Out, const DtValue & Rhs );
};

struct DataTypeString : public DataType
{
//    DtValue & Assign( DtValue & Lhs, const DtValue & Rhs );

    DtValue Add( const DtValue & Lhs, const DtValue & Rhs );

    DtValue Size( const DtValue & Lhs );

    void To_Stream( std::ostream & Out, const DtValue & Rhs );
};

struct DataTypeArray : public DataType
{
//    DtValue & Assign( DtValue & Lhs, const DtValue & Rhs );

    DtValue Add( const DtValue & Lhs, const DtValue & Rhs );

    DtValue Size( const DtValue & Lhs );

    // Throws std::out_of_range if Index >= Array.Size()
    DtValue & SubScriptGet( const DtValue & Lhs, int Index );

    // Throws std::out_of_range if Index < 0
    DtValue & SubScriptSet( DtValue & Lhs, int Index );

    void To_Stream( std::ostream & Out, const DtValue & Rhs );
};

struct DtValue
{
    boost::any
        Data;

    DataType
        *Type;

    DtValue();

    DtValue( double Val );
    DtValue( const char* Str );
    DtValue( const DtValue & Src );
    DtValue( const std::string & Str );
    DtValue( const std::vector<DtValue> & Arr ); 
    DtValue( const boost::any & D, DataType *T );

    DtValue & operator =  ( double Rhs );
    DtValue & operator =  ( const char* Rhs );
    DtValue & operator =  ( const DtValue & Rhs );
    DtValue & operator =  ( const std::string & Rhs );
    DtValue & operator =  ( const std::vector<DtValue> & Rhs );

    DtValue   operator +  ( const DtValue & Rhs );
    DtValue   operator -  ( const DtValue & Rhs );
    DtValue   operator *  ( const DtValue & Rhs );
    DtValue   operator /  ( const DtValue & Rhs );

    DtValue & operator [] ( int Index ) const;
    DtValue & operator [] ( int Index );
    
    DtValue Size();
};

}} // Namespace Dt, ALang

std::ostream & operator << ( std::ostream & Out, const ALang::Dt::DtValue & Val );

extern ALang::Dt::DataType       DtNull;
extern ALang::Dt::DataTypeArray  DtArray;
extern ALang::Dt::DataTypeDouble DtDouble;
extern ALang::Dt::DataTypeString DtString;

#endif
