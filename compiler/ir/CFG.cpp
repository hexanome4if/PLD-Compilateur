#include "CFG.h"
#include "../symbols-management/VarSymbol.h"
#include "../symbols-management/SymbolTable.h"
#include "BasicBlock.h"
#include "../ast/instructions/Node.h"
#include "../ast/Ast.h"

/** CFG **/

CFG::CFG(Ast *ast, SymbolTable *st)
{
	this->ast = ast;
	this->symbolTable = st;
	st->reinitRun();
	nextBBnumber = 0;
}

void CFG ::add_bb(BasicBlock *bb)
{
	bbs.push_back(bb);
}

// void CFG ::gen_asm(ostream &o)
// {
// 	for (int i = 0; i < bbs.size(); ++i)
// 	{
// 		bbs[i]->gen_asm(o);
// 	}
// }

// string CFG ::IR_reg_to_asm(string reg, BasicBlock *bb)
// {
// 	string res = "-" + to_string(((VarSymbol *)bb->getContext()->getSymbol(reg))->getMemoryAddress()) + "(%rbp)";
// 	return res;
// }

// void CFG ::gen_asm_prologue(ostream &o)
// {
// 	// TO DO
// }

// void CFG ::gen_asm_epilogue(ostream &o)
// {
// 	// TO DO
// }

// void CFG ::add_to_symbol_table(string name, string t)
// {
// 	VarSymbol *vs = new VarSymbol(name, t);
// 	symbolTable->addSymbol(vs);
// }

// string CFG ::get_var_type(string name)
// {
// 	return ((VarSymbol *)symbolTable->getSymbol(name))->getVarType();
// }

string CFG ::new_BB_name()
{
	string res = "BB_" + to_string(nextBBnumber);
	nextBBnumber++;
	return res;
}
