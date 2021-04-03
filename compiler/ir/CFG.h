#pragma once

#include "BasicBlock.h"
#include "IRInstr.h"

class Ast;
class SymbolTable;

/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
   The entry block is the one with the same label as the AST function name.
     (it could be the first of bbs, or it could be defined by an attribute value)
   The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG
{
public:
	CFG(Ast *ast, SymbolTable *st);

	Ast *ast; /**< The AST this CFG comes from */

	void add_bb(BasicBlock *bb);

	// void buildIR();

	// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	// void gen_asm(ostream &o);
	// string IR_reg_to_asm(string reg, BasicBlock *bb); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
	// void gen_asm_prologue(ostream &o);
	// void gen_asm_epilogue(ostream &o);

	// symbol table methods
	// void add_to_symbol_table(string name, string t);
	// string create_new_tempvar(string t);
	//int get_var_index(string name);
	// string get_var_type(string name);

	// basic block management
	string new_BB_name();

	// Get
	vector<BasicBlock *> getBBs() { return bbs; }

protected:
	BasicBlock *current_bb;
	BasicBlock *entry_block;
	BasicBlock *exit_block;
	SymbolTable *symbolTable;
	vector<BasicBlock *> bbs; /**< all the basic blocks of this CFG*/
	//map <string, string> SymbolType; /**< part of the symbol table  */
	//map <string, int> SymbolIndex; /**< part of the symbol table  */

	//int nextFreeSymbolIndex; /**< to allocate new symbols in the symbol table */
	int nextBBnumber; /**< just for naming */
};
