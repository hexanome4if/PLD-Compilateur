
// Generated from ifcc.g4 by ANTLR 4.7.2


#include "visitor.h"

Visitor::Visitor() {
				symbolTable = SymbolTable();
}

antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *ctx)
{
				return visitChildren(ctx);
}
antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx)
{
				return visitChildren(ctx);
// int retval = stoi(ctx->CONST()->getText());
// cout << ".globl	main\n"
// 													" main: \n"
// 													" 	movl	$"
// 										<< retval << ", %eax\n"
// 																							" 	ret\n";
}

antlrcpp::Any Visitor::visitFunc(ifccParser::FuncContext *context)
{
				string functionType = context->TYPE()->getText();
				string functionName = context->NAME()->getText();

				cout << ".globl " << functionName << "\n";
				cout << " " << functionName << ": \n";
				cout << "   pushq %rbp\n";
				cout << "   movq %rsp, %rbp\n";

				visitChildren(context);

				cout << "   popq %rbp\n";
				cout << "   ret\n";

				return 0;
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *context)
{
				symbolTable.openContext();
				visitChildren(context);
				symbolTable.closeContext();
				return 0;
}

antlrcpp::Any Visitor::visitBlock_content(ifccParser::Block_contentContext *context)
{

				visitChildren(context);

				return 0;
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


antlrcpp::Any Visitor::visitVaraffvar(ifccParser::VaraffvarContext *context)  {
				string varName = context->NAME(0)->getText();
				string otherVarName = context->NAME(1)->getText();

				if (!symbolTable.symbolExists(varName)) {
								cerr << "Undefined variable named '" << varName << "'" << endl;
								return 1;
				}

				if (!symbolTable.symbolExists(otherVarName)) {
								cerr << "Undefined variable named '" << otherVarName << "'" << endl;
								return 1;
				}

				// Get variables symbols
				Symbol* varSymbol = symbolTable.getSymbol(varName);
				Symbol* otherVarSymbol = symbolTable.getSymbol(otherVarName);

				// Check variables types
				if (varSymbol->getType() != otherVarSymbol->getType()) {
								cerr << "Incompatible type" << endl;
								return 1;
				}

				varSymbol->setValue(otherVarSymbol->getValue());

				// Write ASSEMBLY code
				cout << "   movl -" << otherVarSymbol->getMemoryAddress() << "(%rbp), %eax\n";
				cout << "   movl %eax, -" << varSymbol->getMemoryAddress() << "(%rbp)\n";

				return 0;
}

antlrcpp::Any Visitor::visitVaraffconst(ifccParser::VaraffconstContext *context)  {
				string varName = context->NAME()->getText();
				string varValue = context->CONST()->getText();

				if (!symbolTable.symbolExists(varName)) {
								cerr << "Undefined variable named '" << varName << "'" << endl;
								return 1;
				}

				// Get variable symbol
				Symbol* varSymbol = symbolTable.getSymbol(varName);
				varSymbol->setValue(varValue);

				// Write ASSEMBLY code
				cout << "   movl $" << varSymbol->getValue() << ", -" << varSymbol->getMemoryAddress() << "(%rbp)\n";

				return 0;
}
