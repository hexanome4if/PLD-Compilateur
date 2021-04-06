#pragma once

#include "Node.h"
#include "Block.h"
#include "../../symbols-management/type.h"
#include "../../symbols-management/FuncSymbol.h"

class Func : public Node
{
public:


	Func(TypeName t, string n, Block *b) : Node(FUNCTION), type(t), name(n), block(b)
	{
	}

	void addInstr(Instr *i)
	{
		block->addInstr(i);
	}

	virtual void debug(ostream &stream, int space) override
	{
		showSpaces(stream, space);
		stream << "Function " << name << endl;
		block->debug(stream, ++space);
	}

	virtual int removeUnusedSymbols(function<void(Node *)> remove, Context *context) override
	{
		FuncSymbol *funcSymbol = (FuncSymbol *)context->getSymbol(name);
		if (!funcSymbol->getIsUsed())
		{
			remove(this);
			return 1;
		}
		return block->removeUnusedSymbols(remove, context);
	}

	virtual void calculateExpressions(Context *context) override
	{
		return block->calculateExpressions(context);
	}

	virtual void checkUsedSymbols(Context *context) override
	{
		block->checkUsedSymbols(context);
	}

	virtual void computeVarDependencies(Context *context) override
	{
		block->computeVarDependencies(context);
	}
	// Get
	string getName()
	{
		return name;
	}
	Block *getBlock()
	{
		return block;
	}
	TypeName getType()
	{
		return type;
	}

private:
	TypeName type;
	string name;
	Block *block;
};
