
// Generated from ifcc.g4 by ANTLR 4.7.2


#include "visitor.h"

Visitor::Visitor() {
				symbolTable = SymbolTable();
}

antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *ctx)
{
				returnCode = (int) visitChildren(ctx);
				return returnCode;
}
antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx)
{
				int res = 0;
				vector<ifccParser::FuncContext *> func = ctx->func();
				vector<ifccParser::FuncContext *>::iterator it;

				for(it = func.begin(); it!=func.end(); ++it) {
								res += (int) visit(*it);
				}
				return res>0 ? 1 : 0;
}

antlrcpp::Any Visitor::visitFunc(ifccParser::FuncContext *context)
{
				string functionType = context->TYPE()->getText();
				string functionName = context->NAME()->getText();

				cout << ".globl " << functionName << "\n";
				cout << " " << functionName << ": \n";
				cout << "   pushq %rbp\n";
				cout << "   movq %rsp, %rbp\n";

				int res = (int) visitChildren(context);

				cout << "   popq %rbp\n";
				cout << "   ret\n";

				return res;
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *context)
{
				symbolTable.openContext();
				int res = 0;

				vector<ifccParser::Block_contentContext *> block_content = context->block_content();
				vector<ifccParser::Block_contentContext *>::iterator it;

				for(it = block_content.begin(); it!=block_content.end(); ++it) {
								res += (int) visit(*it);
				}

				symbolTable.closeContext();
				return res>0 ? 1 : 0;
}

antlrcpp::Any Visitor::visitBlock_content(ifccParser::Block_contentContext *context)
{
				int res =  visitChildren(context);
				return res;
}

antlrcpp::Any Visitor::visitFunc_return_const(ifccParser::Func_return_constContext *context)
{
				string returnConst = context->CONST()->getText();

				cout << "   movl $" << returnConst << ", %eax\n";

				return 0;
}

antlrcpp::Any Visitor::visitFunc_return_var(ifccParser::Func_return_varContext *context)
{
				string returnVar = context->NAME()->getText();

				if (!symbolTable.symbolExists(returnVar)) {
								cerr << "Undefined variable '" << returnVar << "'" << endl;
								return 1;
				}

				Symbol* varSymbol = symbolTable.getSymbol(returnVar);

				// Write ASSEMBLY code
				cout << "   movl -" << varSymbol->getMemoryAddress() << "(%rbp), %eax\n";

				return 0;
}

antlrcpp::Any Visitor::visitVardefaff(ifccParser::VardefaffContext *context)  {
				string varType = context->TYPE()->getText();
				string varName = context->NAME()->getText();

				if (symbolTable.symbolExists(varName)) {
								// ERROR here
								cerr << "Variable " << varName << " already defined." << endl;
								return 1;
				}

				// Add the variable in the symbol table
				string varValue = context->CONST()->getText();
				Symbol* symbol = symbolTable.addSymbol(varName, varType, varValue);

				// Write ASSEMBLY code
				cout << "   movl $" << symbol->getValue() << ", -" << symbol->getMemoryAddress() << "(%rbp)\n";

				return 0;
}

antlrcpp::Any Visitor::visitVardef(ifccParser::VardefContext *context)  {
				string varType = context->TYPE()->getText();
				string varName = context->NAME()->getText();

				if (symbolTable.symbolExists(varName)) {
								// ERROR here
								cerr << "Variable " << varName << " already defined." << endl;
								return 1;
				}

				// Add the variable in the symbol table
				Symbol* symbol = symbolTable.addSymbol(varName, varType, "0");
				// Write ASSEMBLY code
				cout << "   movl $" << symbol->getValue() << ", -" << symbol->getMemoryAddress() << "(%rbp)\n";

				vector<ifccParser::VirgulenameContext *> virgulename = context->virgulename();
				vector<ifccParser::VirgulenameContext *>::iterator it;

				for(it = virgulename.begin(); it!=virgulename.end(); ++it) {
								string varname = visit(*it);

								if (symbolTable.symbolExists(varname)) {
												// ERROR here
												cerr << "Variable " << varName << " already defined." << endl;
												return 1;
								}

								// Add the variable in the symbol table
								symbol = symbolTable.addSymbol(varname, varType, "0");
								// Write ASSEMBLY code
								cout << "   movl $" << symbol->getValue() << ", -" << symbol->getMemoryAddress() << "(%rbp)\n";
				}

				return 0;
}

antlrcpp::Any Visitor::visitVirgulename(ifccParser::VirgulenameContext *context)  {
				return context->NAME()->getText();
}

antlrcpp::Any Visitor::visitVaraff(ifccParser::VaraffContext *context) {
				string varName = context->NAME()->getText();
				Symbol* expr = visit(context->expr());
				if (expr == nullptr ) return 1;
				if (!symbolTable.symbolExists(varName)) {
								cerr << "Undefined variable named '" << varName << "'" << endl;
								return 1;
				}

				// Get variable symbol
				Symbol* varSymbol = symbolTable.getSymbol(varName);

				// Write ASSEMBLY code
				cout << "   movl -" << expr->getMemoryAddress() << "(%rbp), %eax\n";
				cout << "   movl %eax, -" << varSymbol->getMemoryAddress() << "(%rbp)\n";
				return 0;
}

antlrcpp::Any Visitor::visitPar(ifccParser::ParContext *context) {
				return visit(context->expr());
}

antlrcpp::Any Visitor::visitDiv(ifccParser::DivContext *context) {
				return nullptr;
}

antlrcpp::Any Visitor::visitMult(ifccParser::MultContext *context) {
				Symbol* expr0 = visit(context->expr(0));
				Symbol* expr1 = visit(context->expr(1));
				if (expr0 == nullptr || expr1== nullptr) return nullptr;
				Symbol* temp = symbolTable.addTempSymbol("int","0");
				cout << "   movl	-"<< expr0->getMemoryAddress() <<"(%rbp), %edx\n";
				cout << "   movl	-"<< expr1->getMemoryAddress() <<"(%rbp), %eax\n";
				cout << "   imull	%edx, %eax\n";
				cout << "   movl	%eax, -"<< temp->getMemoryAddress() <<"(%rbp)"<< endl;
				return temp;
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *context) {
				string value = context->CONST()->getText();
				Symbol* temp = symbolTable.addTempSymbol("int",value);
				cout << "   movl $" << value << ", -" << temp->getMemoryAddress() << "(%rbp)\n";
				return temp;
}

antlrcpp::Any Visitor::visitName(ifccParser::NameContext *context) {
				string varName = context->NAME()->getText();
				if (!symbolTable.symbolExists(varName)) {
								cerr << "Undefined variable named '" << varName << "'" << endl;
								return nullptr;
				}

				// Get variable symbol
				Symbol* varSymbol = symbolTable.getSymbol(varName);
				return varSymbol;
}

antlrcpp::Any Visitor::visitSubstr(ifccParser::SubstrContext *context) {
				return nullptr;
}

antlrcpp::Any Visitor::visitPlus(ifccParser::PlusContext *context) {
				Symbol* expr0 = visit(context->expr(0));
				Symbol* expr1 = visit(context->expr(1));
				if (expr0 == nullptr || expr1== nullptr) return nullptr;
				Symbol* temp = symbolTable.addTempSymbol("int","0");
				cout << "   movl	-"<< expr0->getMemoryAddress() <<"(%rbp), %edx\n";
				cout << "   movl	-"<< expr1->getMemoryAddress() <<"(%rbp), %eax\n";
				cout << "   addl	%edx, %eax\n";
				cout << "   movl	%eax, -"<< temp->getMemoryAddress() <<"(%rbp)"<< endl;
				return temp;
}

int Visitor::getReturnCode() {
				return returnCode;
}
