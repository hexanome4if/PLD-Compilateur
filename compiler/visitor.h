
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"

#include "symbol-table/SymbolTable.h"

using namespace std;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class Visitor : public ifccVisitor
{
public:

Visitor();

virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override;
virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override;
virtual antlrcpp::Any visitFunc(ifccParser::FuncContext *context) override;
virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *context) override;
virtual antlrcpp::Any visitBlock_content(ifccParser::Block_contentContext *context) override;
virtual antlrcpp::Any visitFunc_return_const(ifccParser::Func_return_constContext *context) override;
virtual antlrcpp::Any visitFunc_return_var(ifccParser::Func_return_varContext *context) override;
virtual antlrcpp::Any visitVardefaff(ifccParser::VardefaffContext *context) override;
virtual antlrcpp::Any visitVardef(ifccParser::VardefContext *context) override;
virtual antlrcpp::Any visitVirgulename(ifccParser::VirgulenameContext *context) override;
virtual antlrcpp::Any visitVaraffvar(ifccParser::VaraffvarContext *context) override;
virtual antlrcpp::Any visitVaraffconst(ifccParser::VaraffconstContext *context) override;

private:

SymbolTable symbolTable;
};
