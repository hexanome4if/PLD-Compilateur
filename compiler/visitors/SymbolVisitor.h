// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "../antlr4-generated/ifccBaseVisitor.h"
#include "../symbols-management/SymbolTable.h"
#include "../error-management/symbol/AlreadyDeclaredSymbolError.h"
#include "../error-management/symbol/UndeclaredSymbolError.h"
#include "../error-management/symbol/UndefinedSymbolWarn.h"
#include "../error-management/symbol/UnusedSymbolWarn.h"
#include "../ast/Ast.h"
#include "BaseVisitor.h"

using namespace std;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class SymbolVisitor : public BaseVisitor
{
public:
	SymbolVisitor(SymbolTable *symbolTable);

	antlrcpp::Any visitFunc(ifccParser::FuncContext *context) override;								//ok
	antlrcpp::Any visitBlock(ifccParser::BlockContext *context) override;							//ok
	antlrcpp::Any visitVardefaff(ifccParser::VardefaffContext *context) override;			//ok
	antlrcpp::Any visitVirgulename(ifccParser::VirgulenameContext *context) override; //ok
	antlrcpp::Any visitVaraff(ifccParser::VaraffContext *context) override;						//ok
	antlrcpp::Any visitFunccall(ifccParser::FunccallContext *context) override;				//ok
	antlrcpp::Any visitAffecsimple(ifccParser::AffecsimpleContext *context) override; //ok
	antlrcpp::Any visitName(ifccParser::NameContext *context) override;								//ok
	antlrcpp::Any visitExpr(ifccParser::ExprContext *context) override;
	antlrcpp::Any visitArraydef(ifccParser::ArraydefContext *context) override;					//ok
	antlrcpp::Any visitArraydefaff(ifccParser::ArraydefaffContext *context) override;		//ok
	antlrcpp::Any visitArrayaff(ifccParser::ArrayaffContext *context) override;					//ok
	antlrcpp::Any visitArrayexpr(ifccParser::ArrayexprContext *context) override;				//TO DO
	antlrcpp::Any visitArraycontent(ifccParser::ArraycontentContext *context) override; //ok
	antlrcpp::Any visitArrayaccess(ifccParser::ArrayaccessContext *context) override;		//TO DO

	void postAnalysis();

private:
	SymbolTable *symbolTable;
};
