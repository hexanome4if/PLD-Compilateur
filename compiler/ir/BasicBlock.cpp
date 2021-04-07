#include "BasicBlock.h"

/** BasicBloc **/

// Constructor
BasicBlock::BasicBlock(CFG *cfg, string entry_label, Context *ctx)
{
	exit_true = nullptr;
	exit_false = nullptr;
	this->cfg = cfg;
	this->context = ctx;
	label = entry_label;
}

void BasicBlock ::add_IRInstr(IRInstr::Operation op, TypeName t, vector<string> params)
{
	IRInstr *instr = new IRInstr(this, op, t, params);
	instrs.push_back(instr);
}

bool BasicBlock::hasFunctionCall()
{
	for (int i = 0; i < instrs.size(); ++i)
	{
		if (instrs[i]->hasFunctionCall())
		{
			return true;
		}
	}

	if (exit_true != nullptr)
	{
		if (exit_true->hasFunctionCall())
		{
			return true;
		}
	}

	if (exit_false != nullptr)
	{
		if (exit_false->hasFunctionCall())
		{
			return true;
		}
	}

	return false;
}
