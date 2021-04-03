#pragma once

#include "Node.h"
#include "Instr.h"
#include "../../symbols-management/Context.h"

class Block : public Node
{
public:
	Block(Context *c) : Node(BLOCK), context(c) {}

	void addInstr(Instr *instr) { instrs.push_back(instr); }

	virtual void debug(ostream &stream, int space) override
	{
		showSpaces(stream, space);
		stream << "Block" << endl;
		context->debug(stream, space);
		for (int i = 0; i < instrs.size(); ++i)
		{
			showSpaces(stream, space + 1);
			instrs[i]->debug(stream, space);
			stream << endl;
		}
	}

	bool hasFunctionCall()
	{
		for (int i = 0; i < instrs.size(); ++i)
		{
			if (instrs[i]->hasFunctionCall())
			{
				return true;
			}
		}
		return false;
	}

	// Get
	Context *getContext() { return context; }
	vector<Instr *> getInstrs() { return instrs; }

private:
	vector<Instr *> instrs;
	Context *context;
};
