#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include <string>
#include <ostream>
#include <cstddef>
#include <boost/any.hpp>
#include <unordered_map>

#include "Exception.h"

namespace ALang { namespace Dt {

struct DtValue;

struct DataType
{
    ~DataType() {}

    virtual DtValue & Assign( DtValue & Lhs, const DtValue & Rhs );
    virtual DtValue & Assign( DtValue & Lhs, const DtValue * Rhs );

    virtual DtValue   Add( const DtValue & Lhs, const DtValue & Rhs );
    virtual DtValue & AddAssign( DtValue & Lhs, const DtValue & Rhs );

    virtual DtValue   Substract( const DtValue & Lhs, const DtValue & Rhs );
    virtual DtValue & SubstractAssign( DtValue & Lhs, const DtValue & Rhs );

    virtual DtValue   Multiply( const DtValue & Lhs, const DtValue & Rhs );
    virtual DtValue & MultiplyAssign( DtValue & Lhs, const DtValue & Rhs );

    virtual DtValue   Divide( const DtValue & Lhs, const DtValue & Rhs );
    virtual DtValue & DivideAssign( DtValue & Lhs, const DtValue & Rhs );

    virtual bool LessThan( const DtValue & Lhs, const DtValue & Rhs );
    virtual bool GreaterThan( const DtValue & Lhs, const DtValue & Rhs );

    virtual bool LessThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );
    virtual bool GreaterThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );

    virtual bool EqualTo( const DtValue & Lhs, const DtValue & Rhs );

    virtual DtValue & SubScriptGetKey( const DtValue & Lhs, const std::string & Key );
    virtual DtValue & SubScriptSetKey(       DtValue & Lhs, const std::string & Key );

    virtual DtValue & SubScriptGetIndex( const DtValue & Lhs, std::size_t Index );
    virtual DtValue & SubScriptSetIndex(       DtValue & Lhs, std::size_t Index );

    virtual DtValue Size( const DtValue & Lhs );

    virtual void ToStream( std::ostream & Out, const DtValue & Rhs );
};

struct DataTypeDouble : public DataType 
{
    DtValue   Add( const DtValue & Lhs, const DtValue & Rhs );
    DtValue & AddAssign( DtValue & Lhs, const DtValue & Rhs );

    DtValue   Substract( const DtValue & Lhs, const DtValue & Rhs );
    DtValue & SubstractAssign( DtValue & Lhs, const DtValue & Rhs );

    DtValue   Multiply( const DtValue & Lhs,  const DtValue & Rhs );
    DtValue & MultiplyAssign( DtValue & Lhs, const DtValue & Rhs );

    DtValue   Divide( const DtValue & Lhs, const DtValue & Rhs );
    DtValue & DivideAssign( DtValue & Lhs, const DtValue & Rhs );

    void ToStream( std::ostream & Out, const DtValue & Rhs );
};

struct DataTypeString : public DataType
{
    DtValue   Add( const DtValue & Lhs, const DtValue & Rhs );
    DtValue & AddAssign( DtValue & Lhs, const DtValue & Rhs );

    DtValue Size( const DtValue & Lhs );

    void ToStream( std::ostream & Out, const DtValue & Rhs );
};

struct DataTypeArray : public DataType
{
    DtValue   Add( const DtValue & Lhs, const DtValue & Rhs );
    DtValue & AddAssign( DtValue & Lhs, const DtValue & Rhs );

    DtValue Size( const DtValue & Lhs );

    // Throws std::out_of_range if Index >= Array.Size()
    DtValue & SubScriptGetIndex( const DtValue & Lhs, std::size_t Index );

    DtValue & SubScriptSetIndex(       DtValue & Lhs, std::size_t Index );

    void ToStream( std::ostream & Out, const DtValue & Rhs );
};

struct DataTypeStruct : public DataType
{
    DtValue Size( const DtValue & Lhs );

    //DtValue & SubScriptGetKey( const DtValue & Lhs, const std::string & Key );

    DtValue & SubScriptSetKey(       DtValue & Lhs, const std::string & Key );

    void ToStream( std::ostream & Out, const DtValue & Rhs );
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
    DtValue( const std::vector< DtValue > & Arr ); 
    DtValue( const boost::any & D, DataType *T );
    DtValue( const std::unordered_map< std::string, DtValue > & Map ); 

    DtValue & operator =  ( double Rhs );
    DtValue & operator =  ( const char* Rhs );
    DtValue & operator =  ( const DtValue & Rhs );
    DtValue & operator =  ( const DtValue * Rhs );
    DtValue & operator =  ( const std::string & Rhs );
    DtValue & operator =  ( const std::vector< DtValue > & Rhs );
    DtValue & operator =  ( const std::unordered_map< std::string, DtValue > & Rhs ); 

    DtValue   operator +  ( const DtValue & Rhs ) const;
    DtValue   operator -  ( const DtValue & Rhs ) const;
    DtValue   operator *  ( const DtValue & Rhs ) const;
    DtValue   operator /  ( const DtValue & Rhs ) const;

    DtValue & operator += ( const DtValue & Rhs );
    DtValue & operator -= ( const DtValue & Rhs );
    DtValue & operator *= ( const DtValue & Rhs );
    DtValue & operator /= ( const DtValue & Rhs );

    bool operator <  ( const DtValue & Rhs ) const;
    bool operator >  ( const DtValue & Rhs ) const;
    bool operator <= ( const DtValue & Rhs ) const;
    bool operator >= ( const DtValue & Rhs ) const;
    bool operator == ( const DtValue & Rhs ) const;
    bool operator != ( const DtValue & Rhs ) const;

    DtValue & operator [] ( std::size_t Index ) const;
    DtValue & operator [] ( std::size_t Index );

    DtValue & operator [] ( const std::string & Key ) const;
    DtValue & operator [] ( const std::string & Key );
};

DtValue Size( const DtValue & Val );

}} // Namespace Dt, ALang

std::ostream & operator << ( std::ostream & Out, const ALang::Dt::DtValue & Val );

extern ALang::Dt::DataType       DtNull;
extern ALang::Dt::DataTypeArray  DtArray;
extern ALang::Dt::DataTypeDouble DtDouble;
extern ALang::Dt::DataTypeString DtString;
extern ALang::Dt::DataTypeStruct DtStruct;

#endif
