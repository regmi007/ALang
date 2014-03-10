#ifndef __DATATYPE_H__
#define __DATATYPE_H__

#include <string>
#include <ostream>
#include <cstddef>
#include <boost/any.hpp>
#include <unordered_map>

#include "Exception.hpp"

namespace ALang { namespace Dt {

struct DtValue;

/** Base class for all datatype.
 */
struct DataType
{
    ~DataType() {}

    /** Function defining how = should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & Assign( DtValue & Lhs, const DtValue & Rhs );

    /** Function defining how = should be handled by each datatype.
     * this assignment is for handalig assignment by pointer.
     * eg, DtValue v = & SomeValue
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & Assign( DtValue & Lhs,       DtValue * Rhs );

    /** Function defining how + should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue   Add( const DtValue & Lhs, const DtValue & Rhs );

    /** Function defining how += should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & AddAssign( DtValue & Lhs, const DtValue & Rhs );

    /** Function defining how - should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue   Substract( const DtValue & Lhs, const DtValue & Rhs );
    
    /** Function defining how -= should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & SubstractAssign( DtValue & Lhs, const DtValue & Rhs );

    /** Function defining how assignment should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue   Multiply( const DtValue & Lhs, const DtValue & Rhs );
    
    /** Function defining how *= should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & MultiplyAssign( DtValue & Lhs, const DtValue & Rhs );

    /** Function defining how / should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue   Divide( const DtValue & Lhs, const DtValue & Rhs );
    
    /** Function defining how /= should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & DivideAssign( DtValue & Lhs, const DtValue & Rhs );

    /** Function defining how < should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual bool LessThan( const DtValue & Lhs, const DtValue & Rhs );
    
    /** Function defining how > should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual bool GreaterThan( const DtValue & Lhs, const DtValue & Rhs );

    /** Function defining how <= should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual bool LessThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );
    
    /** Function defining how >= should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual bool GreaterThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );

    /** Function defining how == should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual bool EqualTo( const DtValue & Lhs, const DtValue & Rhs );

    /** Function defining how  a = Val[ 'Key' ] should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & SubScriptGetKey( const DtValue & Lhs, const std::string & Key );
    
    /** Function defining how Val[ 'Key' ] = a should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & SubScriptSetKey(       DtValue & Lhs, const std::string & Key );

    /** Function defining how a = Val[ i ] should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & SubScriptGetIndex( const DtValue & Lhs, std::size_t Index );
    
    /** Function defining how Val[ i ] = a should be handled by each datatype.
     * @param Lhs Value on the left.
     * @param Rhs Value on the right.
     */
    virtual DtValue & SubScriptSetIndex(       DtValue & Lhs, std::size_t Index );

    /** Function defining how Size() should be handled by each datatype.
     * @param Lhs Value on the left.
     */
    virtual DtValue Size( const DtValue & Lhs );

    /** Function defining how data should be streamed by each datatype.
     * @param Out Stream to send output to.
     * @param Rhs Value on the right.
     */
    virtual void ToStream( std::ostream & Out, const DtValue & Rhs );
};

/** Datatype Double.
 */
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

    bool LessThan( const DtValue & Lhs, const DtValue & Rhs );
    bool GreaterThan( const DtValue & Lhs, const DtValue & Rhs );

    bool LessThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );
    bool GreaterThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );

    bool EqualTo( const DtValue & Lhs, const DtValue & Rhs );

    void ToStream( std::ostream & Out, const DtValue & Rhs );
};

/** Datatype String.
 */
struct DataTypeString : public DataType
{
    DtValue   Add( const DtValue & Lhs, const DtValue & Rhs );
    DtValue & AddAssign( DtValue & Lhs, const DtValue & Rhs );

    bool LessThan( const DtValue & Lhs, const DtValue & Rhs );
    bool GreaterThan( const DtValue & Lhs, const DtValue & Rhs );

    bool LessThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );
    bool GreaterThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );

    bool EqualTo( const DtValue & Lhs, const DtValue & Rhs );

    DtValue Size( const DtValue & Lhs );

    void ToStream( std::ostream & Out, const DtValue & Rhs );
};

/** Datatype Array.
 */
struct DataTypeArray : public DataType
{
    DtValue   Add( const DtValue & Lhs, const DtValue & Rhs );
    DtValue & AddAssign( DtValue & Lhs, const DtValue & Rhs );

    DtValue Size( const DtValue & Lhs );

    // Throws std::out_of_range if Index >= Array.Size()
    DtValue & SubScriptGetIndex( const DtValue & Lhs, std::size_t Index );

    DtValue & SubScriptSetIndex( DtValue & Lhs, std::size_t Index );

    bool LessThan( const DtValue & Lhs, const DtValue & Rhs );
    bool GreaterThan( const DtValue & Lhs, const DtValue & Rhs );

    bool LessThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );
    bool GreaterThanEqualTo( const DtValue & Lhs, const DtValue & Rhs );

    bool EqualTo( const DtValue & Lhs, const DtValue & Rhs );

    void ToStream( std::ostream & Out, const DtValue & Rhs );
};

/** Datatype Structure.
 */
struct DataTypeStruct : public DataType
{
    DtValue Size( const DtValue & Lhs );

    DtValue & SubScriptGetKey( const DtValue & Lhs, const std::string & Key );

    DtValue & SubScriptSetKey( DtValue & Lhs, const std::string & Key );

    bool EqualTo( const DtValue & Lhs, const DtValue & Rhs );

    void ToStream( std::ostream & Out, const DtValue & Rhs );
};

/** Datatype Ast Node.
 */
struct DataTypeAstNode : public DataType
{
};

/** Type that can hold any data.
 */
struct DtValue
{
    boost::any
        Data;       ///< Data belonging tothis value.

    DataType
        *Type;      ///< Datatype of data this value holding.

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
    DtValue & operator =  (       DtValue * Rhs );
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

/** Find size of each data
 * s = Size( arr ), gives length of an array.
 * @param Val Value whose size is to be determined.
 */
DtValue Size( const DtValue & Val );

typedef std::unordered_map< std::string, DtValue > DtValueMap;
typedef std::vector< DtValue > DtValueVec;
typedef std::vector< std::string > StringVec;

}} // Namespace Dt, ALang

std::ostream & operator << ( std::ostream & Out, const ALang::Dt::DtValue & Val );

extern ALang::Dt::DataType       DtNull;

extern ALang::Dt::DataTypeArray  DtArray;
extern ALang::Dt::DataTypeDouble DtDouble;
extern ALang::Dt::DataTypeString DtString;
extern ALang::Dt::DataTypeStruct DtStruct;

extern ALang::Dt::DataTypeAstNode DtAstNode;

#endif
