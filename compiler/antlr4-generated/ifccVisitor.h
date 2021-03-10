
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "ifccParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ifccParser.
 */
class  ifccVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ifccParser.
   */
    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *context) = 0;

    virtual antlrcpp::Any visitProg(ifccParser::ProgContext *context) = 0;

    virtual antlrcpp::Any visitFunc(ifccParser::FuncContext *context) = 0;

    virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *context) = 0;

    virtual antlrcpp::Any visitBlock_content(ifccParser::Block_contentContext *context) = 0;

    virtual antlrcpp::Any visitFunc_return_const(ifccParser::Func_return_constContext *context) = 0;

    virtual antlrcpp::Any visitFunc_return_var(ifccParser::Func_return_varContext *context) = 0;

    virtual antlrcpp::Any visitVardefaff(ifccParser::VardefaffContext *context) = 0;

    virtual antlrcpp::Any visitVardef(ifccParser::VardefContext *context) = 0;

    virtual antlrcpp::Any visitVirgulename(ifccParser::VirgulenameContext *context) = 0;

    virtual antlrcpp::Any visitVaraffvar(ifccParser::VaraffvarContext *context) = 0;

    virtual antlrcpp::Any visitVaraffconst(ifccParser::VaraffconstContext *context) = 0;


};

