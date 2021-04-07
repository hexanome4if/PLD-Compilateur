#pragma once

#include "../CFG.h"
#include "../../symbols-management/SymbolTable.h"
#include "../../ast/instructions/Instr.h"
#include "IRBlockGenerator.h"
#include "IRInstrGenerator.h"
#include "expressions/IRExprGenerator.h"
#include "expressions/IROperatorGenerator.h"

class IRGenerator
{
public:
IRGenerator(Ast *ast, CFG *cfg, SymbolTable *symbolTable);

void generate();

void genNode(Node *node);
void genBlock(Block *block);
void genInstruction(Instr *instr);
string genExpr(Expr *expr);

string createTempVar(TypeName type);

// Get
Context *getCurrentContext() {
				return currentContext;
}
BasicBlock *getCurrentBB() {
				return currentBB;
}

Func *getCurrentFunc() {
				return currentFunc;
}

// Set
void setCurrentContext(Context *context) {
				currentContext = context;
}
void setCurrentBB(BasicBlock *bb) {
				currentBB = bb;
}

void setCurrentFunc(Func *func) {
				currentFunc = func;
}

private:
Ast *ast;
CFG *cfg;
SymbolTable *symbolTable;
BasicBlock *currentBB;
Context *currentContext;
Func* currentFunc = nullptr;

IRBlockGenerator *blockGenerator;
IRInstrGenerator *instrGenerator;
IRExprGenerator *exprGenerator;
IROperatorGenerator *operatorGenerator;
};
