#pragma once

#include "Block.h"
#include "../expressions/Expr.h"
#include "Instr.h"

class For : public Instr
{
public:
	For(Expr *i, Expr *cond, Expr *p, Block *b) : Instr(FOR), init(i), condition(cond), progression(p), block(b) {}

	void addInstr(Instr *instr);

	virtual bool hasFunctionCall() override { return false; }

    virtual void checkUsedSymbols(Context* context) override {}

    virtual int removeUnusedSymbols(function<void(Node*)> remove, Context* context) override { return 0; }

private:
	Expr *init;
	Expr *condition;
	Expr *progression;
	Block *block;
};
