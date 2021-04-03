#pragma once

#include "Block.h"
#include "../expressions/Expr.h"
#include "Instr.h"

class If : public Instr
{
public:
	If(Expr *cond, Block *bif, Block *belse) : Instr(IF), condition(cond), blockIf(bif), blockElse(belse) {}

	void addInstrIf(Instr *instr);

	void addInstrElse(Instr *instr);

	virtual void debug(ostream &stream, int space) override
	{
		stream << "if (";
		condition->debug(stream, space);
		stream << ")" << endl;
		blockIf->debug(stream, space + 1);
		if (blockElse != nullptr)
		{
			showSpaces(stream, space);
			stream << "else" << endl;
			blockElse->debug(stream, space + 1);
		}
	}

	// Get
	Expr *getCondition() { return condition; }
	Block *getBlockIf() { return blockIf; }
	Block *getBlockElse() { return blockElse; }

private:
	Expr *condition;
	Block *blockIf;
	Block *blockElse;
};
