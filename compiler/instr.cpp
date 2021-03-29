#include "instr.h"
#include "IR.h"

/*string Block :: buildIR (CFG* cfg) {
				for (int i = 0; i < instrs.size(); i++) {
								instrs[i]->buildIR(cfg);
				}
				return "";
}*/

/*string Aff :: buildIR (CFG* cfg) {
				//IRInstr(cfg->current_bb, copy, TypeName t, vector<string> params)
			return "";
}*/

void Block::addInstr(Instr* i)
{
	instrs.push_back(i);
}

void Func::addParam(string p) {
				params.push_back(p);
}

void Func::addInstr(Instr* i) {
				block->addInstr(i);
}

void FuncCall::addParam(Expr* e) {
				params.push_back(e);
}
