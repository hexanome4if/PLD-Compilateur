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

	// Set
	Context *getCurrentContext() { return currentContext; }
	BasicBlock *getCurrentBB() { return currentBB; }

	// Get
	void setCurrentContext(Context *context) { currentContext = context; }
	void setCurrentBB(BasicBlock *bb) { currentBB = bb; }
	IRExprGenerator *getIRExprGenerator() { return exprGenerator; }

private:
	Ast *ast;
	CFG *cfg;
	SymbolTable *symbolTable;
	BasicBlock *currentBB;
	Context *currentContext;

	IRBlockGenerator *blockGenerator;
	IRInstrGenerator *instrGenerator;
	IRExprGenerator *exprGenerator;
	IROperatorGenerator *operatorGenerator;
};
