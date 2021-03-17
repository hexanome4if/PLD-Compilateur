
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
virtual antlrcpp::Any visitFunc_return(ifccParser::Func_returnContext *context) override;
virtual antlrcpp::Any visitVardefaff(ifccParser::VardefaffContext *context) override;
virtual antlrcpp::Any visitVardef(ifccParser::VardefContext *context) override;
virtual antlrcpp::Any visitVirgulename(ifccParser::VirgulenameContext *context) override;
virtual antlrcpp::Any visitVaraff(ifccParser::VaraffContext *context) override;
virtual antlrcpp::Any visitPar(ifccParser::ParContext *context) override;
virtual antlrcpp::Any visitConst(ifccParser::ConstContext *context) override;
virtual antlrcpp::Any visitName(ifccParser::NameContext *context) override;
virtual antlrcpp::Any visitNegative(ifccParser::NegativeContext *context) override;
virtual antlrcpp::Any visitMultdiv(ifccParser::MultdivContext *context) override;
virtual antlrcpp::Any visitPlusmoins(ifccParser::PlusmoinsContext *context) override;
virtual antlrcpp::Any visitBinoppm(ifccParser::BinoppmContext *context) override;
virtual antlrcpp::Any visitBinopmd(ifccParser::BinopmdContext *context) override;

int getReturnCode();

private:

SymbolTable symbolTable;
int returnCode;
};
