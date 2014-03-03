#ifndef __AST_H__
#define __AST_H__

#include "DataType.hpp"

using ALang::Ast::Node;
using ALang::Dt::DtValue;

Node::~Node()
{
}

DtValue Node::Evaluate();
{
	return DtValue();
};



#endif
