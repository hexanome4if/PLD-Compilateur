#include "ast.h"

void Func::addParam(Decl p) {
    params.push_back(p);
}

void Func::addInstr(Instr i) {
    block.push_back(i);
}