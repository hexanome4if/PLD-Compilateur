
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "ifccVisitor.h"


/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ifccBaseVisitor : public ifccVisitor {
public:

  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunc(ifccParser::FuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlock_content(ifccParser::Block_contentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunc_return_const(ifccParser::Func_return_constContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunc_return_var(ifccParser::Func_return_varContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVardef(ifccParser::VardefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVaraffvar(ifccParser::VaraffvarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVaraffconst(ifccParser::VaraffconstContext *ctx) override {
    return visitChildren(ctx);
  }


};

