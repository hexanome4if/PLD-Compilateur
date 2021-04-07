#pragma once

#include "Block.h"
#include "../expressions/Expr.h"
#include "Instr.h"
#include "../expressions/ConstExpr.h"

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

    virtual void checkUsedSymbols(Context* context) override {
	    condition->checkUsedSymbols(context);
	    blockIf->checkUsedSymbols(context);
	    if (blockElse != nullptr)
        {
	        blockElse->checkUsedSymbols(context);
        }
	}

    virtual void computeVarDependencies(Context* context) override
    {
        condition->computeVarDependencies(nullptr, context);
        blockIf->computeVarDependencies(context);
        if (blockElse != nullptr)
        {
            blockElse->computeVarDependencies(context);
        }
    }

    virtual int removeUnusedSymbols(function<void(Node*)> remove, Context* context) override
    {
	    return blockIf->removeUnusedSymbols(remove, context) + (blockElse != nullptr ? blockElse->removeUnusedSymbols(remove, context) : 0);
    }

    virtual void calculateExpressions(Context* context) override
    {
        blockIf->calculateExpressions(context);
	    if (blockElse != nullptr)
        {
	        blockElse->calculateExpressions(context);
        }
    }

	virtual bool hasFunctionCall() override
	{
		return condition->hasFunctionCall() || blockIf->hasFunctionCall() || (blockElse != nullptr && blockElse->hasFunctionCall());
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
