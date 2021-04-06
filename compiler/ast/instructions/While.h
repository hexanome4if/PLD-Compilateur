#pragma once

#include "Block.h"
#include "../expressions/Expr.h"
#include "../expressions/ConstExpr.h"
#include "Instr.h"

class While : public Instr
{
public:
	While(Expr *cond, Block *b) : Instr(WHILE), condition(cond), block(b) {}

	void addInstr(Instr *instr);

	virtual void debug(ostream &stream, int space) override
	{
		stream << "while (";
		condition->debug(stream, space);
		stream << ")" << endl;
		block->debug(stream, space + 1);
	}

	virtual bool hasFunctionCall() override
	{
		return condition->hasFunctionCall() || block->hasFunctionCall();
	}

    virtual int removeUnusedSymbols(function<void(Node*)> remove, Context* context) override
    {
	    return block->removeUnusedSymbols(remove, context);
	}
    virtual void checkUsedSymbols(Context* context) override {
	    block->checkUsedSymbols(context);
	    condition->checkUsedSymbols(context);
	}
    virtual void computeVarDependencies(Context* context) override
    {
	    condition->computeVarDependencies(nullptr, context);
        block->computeVarDependencies(context);
    }

    virtual void calculateExpressions(Context* context) override
    {
	    block->calculateExpressions(context);
    }

	// Get
	Block *getBlock() { return block; }
	Expr *getCondition() { return condition; }

private:
	Expr *condition;
	Block *block;
};
