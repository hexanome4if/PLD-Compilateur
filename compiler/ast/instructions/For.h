#pragma once

#include "Block.h"
#include "../expressions/Expr.h"
#include "Instr.h"

class For : public Instr
{
public:
	For(Expr *i, Expr *cond, Expr *p, Block *b) : Instr(FOR), init(i), condition(cond), progression(p), block(b) {}

	void addInstr(Instr *instr);

private:
	Expr *init;
	Expr *condition;
	Expr *progression;
	Block *block;
};
