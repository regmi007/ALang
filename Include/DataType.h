#ifndef __DATATYPE_H__
#define __DATATYPE_H__

enum class DataType_Message
{
    MSG_INIT,

    MSG_ADD,
    MSG_SUB,
    MSG_MUL,
    MSG_DIV,

    MSG_ADD_ASSIGN,
    MSG_SUB_ASSIGN,
    MSG_MUL_ASSIGN,
    MSG_DIV_ASSIGN,
    
    MSG_PUSH_BACK;
};

struct DataValue;

struct DataType
{
    virtual void m_MessageHandler( DataType_Message Msg, DataValue *Res, DataValue *Lhs, DataValue *Rhs ) = 0;
    virtual ~DataType() {}
};

struct DataType_Double : public DataType
{
    void m_MessageHandler( DataType_Message Msg, DataValue *Res, DataValue *Lhs, DataValue *Rhs );
};

struct DataType_String : public DataType
{
    void m_MessageHandler( DataType_Message Msg, DataValue *Res, DataValue *Lhs, DataValue *Rhs );
};

struct DataValue
{
    union Res
    {
        double  Number;
        void*   Pointer;
    };
    
    Res
        m_Data;
        
    DataType
        *m_Type;

    Data( DataType *Type ) : m_Type( Type ) { }
};

extern DataType_Double DtDouble;
extern DataType_String DtString;

struct DataValue_Double : public DataValue
{
    DataValue_Double() : DataValue( & DtDouble )
    {
        m_Type->MessageHandler( DataType_Message.MSG_INIT, nullptr, this, nullptr );
    }
};

struct DataValue_String : public DataValue
{
    DataValue_String() : DataValue( & DtString )
    {
        m_Type->MessageHandler( DataType_Message.MSG_INIT, nullptr, this, nullptr );
    }
};

struct DataValue_Array : public DataValue
{
    DataValue_Array() : DataValue( & DtArray )
    {
        m_Type->MessageHandler( DataType_Message.MSG_INIT, nullptr, this, nullptr );
    }
};

#endif
