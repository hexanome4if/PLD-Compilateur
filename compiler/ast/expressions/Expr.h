#pragma once

#include <iostream>
#include "../../symbols-management/Context.h"
#include "../../symbols-management/VarSymbol.h"

using namespace std;

class Expr
{

public:
	typedef enum
	{
		ADD,
		MULT,
		DIV,
		SUBS,
		NEGL
	} Operation;

	typedef enum
	{
		VAR,
		NOT,
		CONST,
		CHAR,
		BIN_OP,
		UN_OP,
		LOGIC_AND,
		LOGIC_OR,
		EQ_COMP,
		INF_COMP,
		NEQ_COMP,
		SUP_COMP,
		AND_BIT,
		OR_BIT,
		XOR_BIT,
		AFF,
		FUNC_CALL,
	} Type;

	Expr(Type type) : exprType(type) {}

	virtual void debug(ostream &stream, int space) {}

	virtual bool hasFunctionCall() { return false; }

    virtual void checkUsedSymbols(Context* context) = 0;
    virtual string getGuessedValue(Context* context) = 0;
    virtual void computeVarDependencies(VarSymbol* varSymbol, Context* context) = 0;

	// Get
	Type getExprType() { return exprType; }

private:
	Type exprType;
};
