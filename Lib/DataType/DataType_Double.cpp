#include "Datatype.h"

void DataType_Double:: m_MessageHandler( DataType_Message Msg, DataValue *Res, DataValue *Lhs, DataValue *Rhs )
{
    switch( Msg )
    {
        DataType_Message.MSG_INIT:
            Lhs->m_Data.Number = 0;
            break;
        DataType_Message.MSG_ADD:
            Res->m_Data.Number = Lhs->m_Data.Number + Rhs->m_Data.Number;
            break;
        DataType_Message.MSG_SUB:
            Res->m_Data.Number = Lhs->m_Data.Number - Rhs->m_Data.Number;
            break;
        DataType_Message.MSG_MUL:
            Res->m_Data.Number = Lhs->m_Data.Number * Rhs->m_Data.Number;
            break;
        DataType_Message.MSG_DIV:
            Res->m_Data.Number = Lhs->m_Data.Number / Rhs->m_Data.Number;
            break;

        DataType_Message.MSG_ADD_ASSIGN:
            Lhs->m_Data.Number += Rhs->m_Data.Number;
            break;
        DataType_Message.MSG_SUB_ASSIGN:
            Lhs->m_Data.Number -= Rhs->m_Data.Number;
            break;
        DataType_Message.MSG_MUL_ASSIGN:
            Lhs->m_Data.Number *= Rhs->m_Data.Number;
            break;
        DataType_Message.MSG_DIV_ASSIGN:
            Lhs->m_Data.Number /= Rhs->m_Data.Number;
            break;

        default:
            throw "Unsupported Msg";
    };
}

DataType_Double DtDouble;
