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

void BasicBlock ::add_IRInstr(IRInstr::Operation op, string t, vector<string> params)
{
	IRInstr *instr = new IRInstr(this, op, t, params);
	instrs.push_back(instr);
}
