
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"
#include "symbol-table/SymbolTable.h"
#include "ast.h"

using namespace std;

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class Visitor : public ifccVisitor
{
public:

Visitor(Ast* ast);

antlrcpp::Any visitAxiom(ifccParser::AxiomContext *context) override;
antlrcpp::Any visitProg(ifccParser::ProgContext *context) override;
antlrcpp::Any visitFunc(ifccParser::FuncContext *context) override; //ok
antlrcpp::Any visitBlock(ifccParser::BlockContext *context) override; //ok
antlrcpp::Any visitInstr(ifccParser::InstrContext *context) override; //ok
antlrcpp::Any visitWhiledef(ifccParser::WhiledefContext *context) override;
antlrcpp::Any visitIfdef(ifccParser::IfdefContext *context) override;
antlrcpp::Any visitElsedef(ifccParser::ElsedefContext *context) override;
antlrcpp::Any visitFordef(ifccParser::FordefContext *context) override;
antlrcpp::Any visitFunc_return(ifccParser::Func_returnContext *context) override; //ok
antlrcpp::Any visitVardefaff(ifccParser::VardefaffContext *context) override; //ok
antlrcpp::Any visitVardef(ifccParser::VardefContext *context) override; //ok
antlrcpp::Any visitVirgulename(ifccParser::VirgulenameContext *context) override;
antlrcpp::Any visitVaraff(ifccParser::VaraffContext *context) override; //ok
antlrcpp::Any visitFunccall(ifccParser::FunccallContext *context) override;
antlrcpp::Any visitVirguleexpr(ifccParser::VirguleexprContext *context) override;
antlrcpp::Any visitPar(ifccParser::ParContext *context) override; //ok
antlrcpp::Any visitNegative(ifccParser::NegativeContext *context) override;
antlrcpp::Any visitConst(ifccParser::ConstContext *context) override; //ok
antlrcpp::Any visitFunctioncall(ifccParser::FunctioncallContext *context) override;
antlrcpp::Any visitAffecsimple(ifccParser::AffecsimpleContext *context) override;
antlrcpp::Any visitMultdiv(ifccParser::MultdivContext *context) override;
antlrcpp::Any visitName(ifccParser::NameContext *context) override; //ok
antlrcpp::Any visitPlusmoins(ifccParser::PlusmoinsContext *context) override;
antlrcpp::Any visitExpr(ifccParser::ExprContext *context) override; //ok
antlrcpp::Any visitBinopmd(ifccParser::BinopmdContext *context) override;
antlrcpp::Any visitBinoppm(ifccParser::BinoppmContext *context) override;

int getReturnCode();

private:

SymbolTable symbolTable;
int returnCode;
Ast* ast;
};
