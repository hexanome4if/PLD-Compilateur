#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccBaseVisitor.h"

#include "visitors/AstVisitor.h"
#include "visitors/SymbolVisitor.h"
#include "visitors/ErrorVisitor.h"

#include "ast/Ast.h"
#include "ir/generator/IRGenerator.h"
#include "assembly-translation/X86Translator.h"
#include "symbols-management/FuncSymbol.h"

using namespace antlr4;
using namespace std;

void standardFunctions(SymbolTable *symbolTable)
{
	FuncSymbol *putChar = new FuncSymbol("putchar", "int");
	putChar->used();
	symbolTable->addSymbol(putChar);
	FuncSymbol *getChar = new FuncSymbol("getchar", "int");
	getChar->used();
	symbolTable->addSymbol(getChar);
}

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
	if (lexer.getNumberOfSyntaxErrors() > 0)
		return 1;
	ifccParser parser(&tokens);
	tree::ParseTree *tree = parser.axiom();
	if (parser.getNumberOfSyntaxErrors() > 0)
		return 1;

	SymbolTable *symbolTable = new SymbolTable();

	standardFunctions(symbolTable);

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

	ErrorVisitor errorVisitor;
	errorVisitor.visit(tree);
	ErrorManager *errorManager = errorVisitor.getErrorManager();
	if (errorManager->hasErrorOrWarning())
	{
		errorManager->showAll(cerr);
		if (errorManager->hasError())
		{
			return 1;
		}
	}

	Ast *ast = new Ast();
	AstVisitor astVisitor(ast, symbolTable);
	astVisitor.visit(tree);


	ast->removeUnusedSymbols(symbolTable);
    // ast->debug(cout);


	CFG *cfg = new CFG(ast, symbolTable);
	IRGenerator *irGenerator = new IRGenerator(ast, cfg, symbolTable);
	irGenerator->generate();

	symbolTable->assignMemoryAddresses();
	X86Translator *translator = new X86Translator(cout, cfg);
	translator->translate();

	return 0;
}
