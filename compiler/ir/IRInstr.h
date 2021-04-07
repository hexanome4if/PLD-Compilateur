#pragma once

#include <iostream>
#include <vector>
#include "../symbols-management/type.h"

using namespace std;

class BasicBlock;

class IRInstr
{

public:
	typedef enum
	{
		LD_CONST,
		COPY,
		ADD,
		SUB,
		MUL,
		R_MEM_TAB, //var1, var2, var3 : var1 = var2[var3]
		W_MEM_TAB, //var1, var2, var3 : var1[var2] = var3
		CALL,
		CMP_EQ,
		CMP_LT,
		CMP_LE,
		DIV,
		RET,
		PROLOG,
		EPILOG,
		B_AND,
		B_OR,
		B_XOR,
		B_NOT
	} Operation;
	/** The instructions themselves -- feel free to subclass instead */

	IRInstr(BasicBlock *bb_, Operation operation, TypeName type, vector<string> params_);

	bool hasFunctionCall();

	// Get
	BasicBlock *getBB()
	{
		return bb;
	}
	Operation getOp()
	{
		return op;
	}
	vector<string> getParams()
	{
		return params;
	}

	TypeName getType()
	{
		return t;
	}

private:
	BasicBlock *bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
	Operation op;
	TypeName t;
	vector<string> params; /**< For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
												 // if you subclass IRInstr, each IRInstr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design.
};
