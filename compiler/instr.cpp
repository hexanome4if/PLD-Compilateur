#include "instr.h"
#include "IR.h"

string Block :: buildIR (CFG* cfg) {
				for (int i = 0; i < instrs.size(); i++) {
								instrs[i].buildIR(cfg);
				}
}

string Aff :: buildIR (CFG* cfg) {
				IRInstr(cfg->current_bb, copy, Type t, vector<string> params)

}

void Func::addParam(Decl p) {
				params.push_back(p);
}

void Func::addInstr(Instr i) {
				block.push_back(i);
}

void FuncCall::addParam(Expr e) {
				params.push_back(e);
}
