#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "visitor.h"
#include "ast.h"
#include "symbol-visitor.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv)
{
	stringstream in;
	if (argn == 2)
	{
		ifstream lecture(argv[1]);
		in << lecture.rdbuf();
	}
	ANTLRInputStream input(in.str());
	ifccLexer lexer(&input);
	CommonTokenStream tokens(&lexer);

	tokens.fill();
	//  for (auto token : tokens.getTokens()) {
	//    std::cout << token->toString() << std::endl;
	//  }
	if (lexer.getNumberOfSyntaxErrors() > 0)
		return 1;
	ifccParser parser(&tokens);
	tree::ParseTree *tree = parser.axiom();
	if (parser.getNumberOfSyntaxErrors() > 0)
		return 1;

	SymbolTable *symbolTable = new SymbolTable();
	SymbolVisitor symbolVisitor(symbolTable);
	symbolVisitor.visit(tree);
	symbolTable->setCreationDone();

	ErrorManager *symbolErrorManager = symbolVisitor.getErrorManager();
	if (symbolErrorManager->hasErrorOrWarning())
	{
		symbolErrorManager->showAll(cerr);
		if (symbolErrorManager->hasError())
		{
			return 1;
		}
	}

	Ast *ast = new Ast();
	Visitor visitor(ast, symbolTable);
	visitor.visit(tree);
	ast->debug(cout);
	cout << "apres debug" << endl;
	CFG * cfg = new CFG(ast);
	cout << "apres CFG" << endl;
	cfg->buildIR();

	return 0;
}
