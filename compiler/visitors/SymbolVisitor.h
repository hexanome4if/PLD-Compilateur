// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "../antlr4-generated/ifccBaseVisitor.h"
#include "../symbols-management/SymbolTable.h"
#include "../error-management/error-manager.h"
#include "../error-management/symbol/alreadydeclared-symbol-error.h"
#include "../error-management/symbol/undeclared-symbol-error.h"
#include "../error-management/symbol/undefined-symbol-warn.h"
#include "../error-management/symbol/unused-symbol-warn.h"
#include "../ast/Ast.h"

using namespace std;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class SymbolVisitor : public ifccBaseVisitor
{
public:
	SymbolVisitor(SymbolTable *symbolTable);

	void throwError(AbstractError *error);

	antlrcpp::Any visitFunc(ifccParser::FuncContext *context) override;								//ok
	antlrcpp::Any visitBlock(ifccParser::BlockContext *context) override;							//ok
	antlrcpp::Any visitVardefaff(ifccParser::VardefaffContext *context) override;			//ok
	antlrcpp::Any visitVirgulename(ifccParser::VirgulenameContext *context) override; //ok
	antlrcpp::Any visitVaraff(ifccParser::VaraffContext *context) override;						//ok
	antlrcpp::Any visitFunccall(ifccParser::FunccallContext *context) override;				//ok
	antlrcpp::Any visitAffecsimple(ifccParser::AffecsimpleContext *context) override; //ok
	antlrcpp::Any visitName(ifccParser::NameContext *context) override;								//ok
	antlrcpp::Any visitExpr(ifccParser::ExprContext *context) override;

	void postAnalysis();

	ErrorManager *getErrorManager(); //ok

private:
	SymbolTable *symbolTable;
	ErrorManager *errorManager;
};
