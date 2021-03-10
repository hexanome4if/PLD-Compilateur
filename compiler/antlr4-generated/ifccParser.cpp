
// Generated from ifcc.g4 by ANTLR 4.7.2


#include "ifccVisitor.h"

#include "ifccParser.h"


using namespace antlrcpp;
using namespace antlr4;

ifccParser::ifccParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ifccParser::~ifccParser() {
  delete _interpreter;
}

std::string ifccParser::getGrammarFileName() const {
  return "ifcc.g4";
}

const std::vector<std::string>& ifccParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ifccParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- AxiomContext ------------------------------------------------------------------

ifccParser::AxiomContext::AxiomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::ProgContext* ifccParser::AxiomContext::prog() {
  return getRuleContext<ifccParser::ProgContext>(0);
}


size_t ifccParser::AxiomContext::getRuleIndex() const {
  return ifccParser::RuleAxiom;
}

antlrcpp::Any ifccParser::AxiomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAxiom(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::AxiomContext* ifccParser::axiom() {
  AxiomContext *_localctx = _tracker.createInstance<AxiomContext>(_ctx, getState());
  enterRule(_localctx, 0, ifccParser::RuleAxiom);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(24);
    prog();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgContext ------------------------------------------------------------------

ifccParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::FuncContext* ifccParser::ProgContext::func() {
  return getRuleContext<ifccParser::FuncContext>(0);
}

ifccParser::ProgContext* ifccParser::ProgContext::prog() {
  return getRuleContext<ifccParser::ProgContext>(0);
}

tree::TerminalNode* ifccParser::ProgContext::EOF() {
  return getToken(ifccParser::EOF, 0);
}


size_t ifccParser::ProgContext::getRuleIndex() const {
  return ifccParser::RuleProg;
}

antlrcpp::Any ifccParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ProgContext* ifccParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 2, ifccParser::RuleProg);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(30);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ifccParser::TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(26);
        func();
        setState(27);
        prog();
        break;
      }

      case ifccParser::EOF: {
        enterOuterAlt(_localctx, 2);
        setState(29);
        match(ifccParser::EOF);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncContext ------------------------------------------------------------------

ifccParser::FuncContext::FuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::FuncContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

tree::TerminalNode* ifccParser::FuncContext::NAME() {
  return getToken(ifccParser::NAME, 0);
}

ifccParser::BlockContext* ifccParser::FuncContext::block() {
  return getRuleContext<ifccParser::BlockContext>(0);
}


size_t ifccParser::FuncContext::getRuleIndex() const {
  return ifccParser::RuleFunc;
}

antlrcpp::Any ifccParser::FuncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFunc(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::FuncContext* ifccParser::func() {
  FuncContext *_localctx = _tracker.createInstance<FuncContext>(_ctx, getState());
  enterRule(_localctx, 4, ifccParser::RuleFunc);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    match(ifccParser::TYPE);
    setState(33);
    match(ifccParser::NAME);
    setState(34);
    match(ifccParser::T__0);
    setState(35);
    match(ifccParser::T__1);
    setState(36);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

ifccParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ifccParser::Block_contentContext *> ifccParser::BlockContext::block_content() {
  return getRuleContexts<ifccParser::Block_contentContext>();
}

ifccParser::Block_contentContext* ifccParser::BlockContext::block_content(size_t i) {
  return getRuleContext<ifccParser::Block_contentContext>(i);
}


size_t ifccParser::BlockContext::getRuleIndex() const {
  return ifccParser::RuleBlock;
}

antlrcpp::Any ifccParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::BlockContext* ifccParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 6, ifccParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    match(ifccParser::T__2);
    setState(42);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ifccParser::T__4)
      | (1ULL << ifccParser::TYPE)
      | (1ULL << ifccParser::NAME))) != 0)) {
      setState(39);
      block_content();
      setState(44);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(45);
    match(ifccParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Block_contentContext ------------------------------------------------------------------

ifccParser::Block_contentContext::Block_contentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::Func_return_constContext* ifccParser::Block_contentContext::func_return_const() {
  return getRuleContext<ifccParser::Func_return_constContext>(0);
}

ifccParser::Func_return_varContext* ifccParser::Block_contentContext::func_return_var() {
  return getRuleContext<ifccParser::Func_return_varContext>(0);
}

ifccParser::VardefContext* ifccParser::Block_contentContext::vardef() {
  return getRuleContext<ifccParser::VardefContext>(0);
}

ifccParser::VardefaffContext* ifccParser::Block_contentContext::vardefaff() {
  return getRuleContext<ifccParser::VardefaffContext>(0);
}

ifccParser::VaraffContext* ifccParser::Block_contentContext::varaff() {
  return getRuleContext<ifccParser::VaraffContext>(0);
}


size_t ifccParser::Block_contentContext::getRuleIndex() const {
  return ifccParser::RuleBlock_content;
}

antlrcpp::Any ifccParser::Block_contentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitBlock_content(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::Block_contentContext* ifccParser::block_content() {
  Block_contentContext *_localctx = _tracker.createInstance<Block_contentContext>(_ctx, getState());
  enterRule(_localctx, 8, ifccParser::RuleBlock_content);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(52);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(47);
      func_return_const();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(48);
      func_return_var();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(49);
      vardef();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(50);
      vardefaff();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(51);
      varaff();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_return_constContext ------------------------------------------------------------------

ifccParser::Func_return_constContext::Func_return_constContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::Func_return_constContext::CONST() {
  return getToken(ifccParser::CONST, 0);
}


size_t ifccParser::Func_return_constContext::getRuleIndex() const {
  return ifccParser::RuleFunc_return_const;
}

antlrcpp::Any ifccParser::Func_return_constContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFunc_return_const(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::Func_return_constContext* ifccParser::func_return_const() {
  Func_return_constContext *_localctx = _tracker.createInstance<Func_return_constContext>(_ctx, getState());
  enterRule(_localctx, 10, ifccParser::RuleFunc_return_const);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(54);
    match(ifccParser::T__4);
    setState(55);
    match(ifccParser::CONST);
    setState(56);
    match(ifccParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_return_varContext ------------------------------------------------------------------

ifccParser::Func_return_varContext::Func_return_varContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::Func_return_varContext::NAME() {
  return getToken(ifccParser::NAME, 0);
}


size_t ifccParser::Func_return_varContext::getRuleIndex() const {
  return ifccParser::RuleFunc_return_var;
}

antlrcpp::Any ifccParser::Func_return_varContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFunc_return_var(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::Func_return_varContext* ifccParser::func_return_var() {
  Func_return_varContext *_localctx = _tracker.createInstance<Func_return_varContext>(_ctx, getState());
  enterRule(_localctx, 12, ifccParser::RuleFunc_return_var);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    match(ifccParser::T__4);
    setState(59);
    match(ifccParser::NAME);
    setState(60);
    match(ifccParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardefaffContext ------------------------------------------------------------------

ifccParser::VardefaffContext::VardefaffContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::VardefaffContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

tree::TerminalNode* ifccParser::VardefaffContext::NAME() {
  return getToken(ifccParser::NAME, 0);
}

tree::TerminalNode* ifccParser::VardefaffContext::CONST() {
  return getToken(ifccParser::CONST, 0);
}


size_t ifccParser::VardefaffContext::getRuleIndex() const {
  return ifccParser::RuleVardefaff;
}

antlrcpp::Any ifccParser::VardefaffContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVardefaff(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VardefaffContext* ifccParser::vardefaff() {
  VardefaffContext *_localctx = _tracker.createInstance<VardefaffContext>(_ctx, getState());
  enterRule(_localctx, 14, ifccParser::RuleVardefaff);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
    match(ifccParser::TYPE);
    setState(63);
    match(ifccParser::NAME);
    setState(64);
    match(ifccParser::T__6);
    setState(65);
    match(ifccParser::CONST);
    setState(66);
    match(ifccParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardefContext ------------------------------------------------------------------

ifccParser::VardefContext::VardefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::VardefContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

tree::TerminalNode* ifccParser::VardefContext::NAME() {
  return getToken(ifccParser::NAME, 0);
}

std::vector<ifccParser::VirgulenameContext *> ifccParser::VardefContext::virgulename() {
  return getRuleContexts<ifccParser::VirgulenameContext>();
}

ifccParser::VirgulenameContext* ifccParser::VardefContext::virgulename(size_t i) {
  return getRuleContext<ifccParser::VirgulenameContext>(i);
}


size_t ifccParser::VardefContext::getRuleIndex() const {
  return ifccParser::RuleVardef;
}

antlrcpp::Any ifccParser::VardefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVardef(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VardefContext* ifccParser::vardef() {
  VardefContext *_localctx = _tracker.createInstance<VardefContext>(_ctx, getState());
  enterRule(_localctx, 16, ifccParser::RuleVardef);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    match(ifccParser::TYPE);
    setState(69);
    match(ifccParser::NAME);
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ifccParser::T__7) {
      setState(70);
      virgulename();
      setState(75);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(76);
    match(ifccParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VirgulenameContext ------------------------------------------------------------------

ifccParser::VirgulenameContext::VirgulenameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::VirgulenameContext::NAME() {
  return getToken(ifccParser::NAME, 0);
}


size_t ifccParser::VirgulenameContext::getRuleIndex() const {
  return ifccParser::RuleVirgulename;
}

antlrcpp::Any ifccParser::VirgulenameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVirgulename(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VirgulenameContext* ifccParser::virgulename() {
  VirgulenameContext *_localctx = _tracker.createInstance<VirgulenameContext>(_ctx, getState());
  enterRule(_localctx, 18, ifccParser::RuleVirgulename);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    match(ifccParser::T__7);
    setState(79);
    match(ifccParser::NAME);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VaraffContext ------------------------------------------------------------------

ifccParser::VaraffContext::VaraffContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::VaraffContext::NAME() {
  return getToken(ifccParser::NAME, 0);
}

ifccParser::ExprContext* ifccParser::VaraffContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}


size_t ifccParser::VaraffContext::getRuleIndex() const {
  return ifccParser::RuleVaraff;
}

antlrcpp::Any ifccParser::VaraffContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVaraff(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VaraffContext* ifccParser::varaff() {
  VaraffContext *_localctx = _tracker.createInstance<VaraffContext>(_ctx, getState());
  enterRule(_localctx, 20, ifccParser::RuleVaraff);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(ifccParser::NAME);
    setState(82);
    match(ifccParser::T__6);
    setState(83);
    expr(0);
    setState(84);
    match(ifccParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ifccParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ifccParser::ExprContext::getRuleIndex() const {
  return ifccParser::RuleExpr;
}

void ifccParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParContext ------------------------------------------------------------------

ifccParser::ExprContext* ifccParser::ParContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::ParContext::ParContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::ParContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitPar(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DivContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::DivContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::DivContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::DivContext::DivContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::DivContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitDiv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MultContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::MultContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::MultContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::MultContext::MultContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::MultContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitMult(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::ConstContext::CONST() {
  return getToken(ifccParser::CONST, 0);
}

ifccParser::ConstContext::ConstContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::ConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitConst(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NameContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::NameContext::NAME() {
  return getToken(ifccParser::NAME, 0);
}

ifccParser::NameContext::NameContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::NameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitName(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubstrContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::SubstrContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::SubstrContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::SubstrContext::SubstrContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::SubstrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitSubstr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PlusContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::PlusContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::PlusContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::PlusContext::PlusContext(ExprContext *ctx) { copyFrom(ctx); }

antlrcpp::Any ifccParser::PlusContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitPlus(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ExprContext* ifccParser::expr() {
   return expr(0);
}

ifccParser::ExprContext* ifccParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ifccParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  ifccParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, ifccParser::RuleExpr, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(93);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ifccParser::T__0: {
        _localctx = _tracker.createInstance<ParContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(87);
        match(ifccParser::T__0);
        setState(88);
        expr(0);
        setState(89);
        match(ifccParser::T__1);
        break;
      }

      case ifccParser::NAME: {
        _localctx = _tracker.createInstance<NameContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(91);
        match(ifccParser::NAME);
        break;
      }

      case ifccParser::CONST: {
        _localctx = _tracker.createInstance<ConstContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(92);
        match(ifccParser::CONST);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(109);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(107);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<PlusContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(95);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(96);
          match(ifccParser::T__8);
          setState(97);
          expr(8);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<MultContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(98);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(99);
          match(ifccParser::T__9);
          setState(100);
          expr(7);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<SubstrContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(101);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(102);
          match(ifccParser::T__10);
          setState(103);
          expr(6);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<DivContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(104);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(105);
          match(ifccParser::T__11);
          setState(106);
          expr(5);
          break;
        }

        } 
      }
      setState(111);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool ifccParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 11: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ifccParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 6);
    case 2: return precpred(_ctx, 5);
    case 3: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> ifccParser::_decisionToDFA;
atn::PredictionContextCache ifccParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ifccParser::_atn;
std::vector<uint16_t> ifccParser::_serializedATN;

std::vector<std::string> ifccParser::_ruleNames = {
  "axiom", "prog", "func", "block", "block_content", "func_return_const", 
  "func_return_var", "vardefaff", "vardef", "virgulename", "varaff", "expr"
};

std::vector<std::string> ifccParser::_literalNames = {
  "", "'('", "')'", "'{'", "'}'", "'return'", "';'", "'='", "','", "'+'", 
  "'*'", "'-'", "'/'"
};

std::vector<std::string> ifccParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "TYPE", "CONST", "NAME", 
  "COMMENT", "DIRECTIVE", "WS"
};

dfa::Vocabulary ifccParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ifccParser::_tokenNames;

ifccParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x14, 0x73, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x21, 0xa, 0x3, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x7, 0x5, 0x2b, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x2e, 0xb, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 
    0x37, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x4a, 0xa, 0xa, 
    0xc, 0xa, 0xe, 0xa, 0x4d, 0xb, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 
    0xd, 0x60, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x7, 0xd, 0x6e, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x71, 0xb, 0xd, 0x3, 0xd, 
    0x2, 0x3, 0x18, 0xe, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 
    0x14, 0x16, 0x18, 0x2, 0x2, 0x2, 0x73, 0x2, 0x1a, 0x3, 0x2, 0x2, 0x2, 
    0x4, 0x20, 0x3, 0x2, 0x2, 0x2, 0x6, 0x22, 0x3, 0x2, 0x2, 0x2, 0x8, 0x28, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x36, 0x3, 0x2, 0x2, 0x2, 0xc, 0x38, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x10, 0x40, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x46, 0x3, 0x2, 0x2, 0x2, 0x14, 0x50, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x53, 0x3, 0x2, 0x2, 0x2, 0x18, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x1b, 0x5, 0x4, 0x3, 0x2, 0x1b, 0x3, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1d, 
    0x5, 0x6, 0x4, 0x2, 0x1d, 0x1e, 0x5, 0x4, 0x3, 0x2, 0x1e, 0x21, 0x3, 
    0x2, 0x2, 0x2, 0x1f, 0x21, 0x7, 0x2, 0x2, 0x3, 0x20, 0x1c, 0x3, 0x2, 
    0x2, 0x2, 0x20, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x21, 0x5, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0x23, 0x7, 0xf, 0x2, 0x2, 0x23, 0x24, 0x7, 0x11, 0x2, 0x2, 
    0x24, 0x25, 0x7, 0x3, 0x2, 0x2, 0x25, 0x26, 0x7, 0x4, 0x2, 0x2, 0x26, 
    0x27, 0x5, 0x8, 0x5, 0x2, 0x27, 0x7, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2c, 
    0x7, 0x5, 0x2, 0x2, 0x29, 0x2b, 0x5, 0xa, 0x6, 0x2, 0x2a, 0x29, 0x3, 
    0x2, 0x2, 0x2, 0x2b, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2a, 0x3, 0x2, 
    0x2, 0x2, 0x2c, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2f, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x7, 0x6, 0x2, 0x2, 
    0x30, 0x9, 0x3, 0x2, 0x2, 0x2, 0x31, 0x37, 0x5, 0xc, 0x7, 0x2, 0x32, 
    0x37, 0x5, 0xe, 0x8, 0x2, 0x33, 0x37, 0x5, 0x12, 0xa, 0x2, 0x34, 0x37, 
    0x5, 0x10, 0x9, 0x2, 0x35, 0x37, 0x5, 0x16, 0xc, 0x2, 0x36, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0x36, 0x32, 0x3, 0x2, 0x2, 0x2, 0x36, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 0x36, 0x35, 0x3, 0x2, 0x2, 
    0x2, 0x37, 0xb, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x7, 0x7, 0x2, 0x2, 
    0x39, 0x3a, 0x7, 0x10, 0x2, 0x2, 0x3a, 0x3b, 0x7, 0x8, 0x2, 0x2, 0x3b, 
    0xd, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x7, 0x7, 0x2, 0x2, 0x3d, 0x3e, 
    0x7, 0x11, 0x2, 0x2, 0x3e, 0x3f, 0x7, 0x8, 0x2, 0x2, 0x3f, 0xf, 0x3, 
    0x2, 0x2, 0x2, 0x40, 0x41, 0x7, 0xf, 0x2, 0x2, 0x41, 0x42, 0x7, 0x11, 
    0x2, 0x2, 0x42, 0x43, 0x7, 0x9, 0x2, 0x2, 0x43, 0x44, 0x7, 0x10, 0x2, 
    0x2, 0x44, 0x45, 0x7, 0x8, 0x2, 0x2, 0x45, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x47, 0x7, 0xf, 0x2, 0x2, 0x47, 0x4b, 0x7, 0x11, 0x2, 0x2, 0x48, 
    0x4a, 0x5, 0x14, 0xb, 0x2, 0x49, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x4d, 
    0x3, 0x2, 0x2, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x3, 
    0x2, 0x2, 0x2, 0x4c, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4b, 0x3, 0x2, 
    0x2, 0x2, 0x4e, 0x4f, 0x7, 0x8, 0x2, 0x2, 0x4f, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0x50, 0x51, 0x7, 0xa, 0x2, 0x2, 0x51, 0x52, 0x7, 0x11, 0x2, 0x2, 
    0x52, 0x15, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x7, 0x11, 0x2, 0x2, 0x54, 
    0x55, 0x7, 0x9, 0x2, 0x2, 0x55, 0x56, 0x5, 0x18, 0xd, 0x2, 0x56, 0x57, 
    0x7, 0x8, 0x2, 0x2, 0x57, 0x17, 0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x8, 
    0xd, 0x1, 0x2, 0x59, 0x5a, 0x7, 0x3, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0x18, 
    0xd, 0x2, 0x5b, 0x5c, 0x7, 0x4, 0x2, 0x2, 0x5c, 0x60, 0x3, 0x2, 0x2, 
    0x2, 0x5d, 0x60, 0x7, 0x11, 0x2, 0x2, 0x5e, 0x60, 0x7, 0x10, 0x2, 0x2, 
    0x5f, 0x58, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5f, 
    0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 
    0xc, 0x9, 0x2, 0x2, 0x62, 0x63, 0x7, 0xb, 0x2, 0x2, 0x63, 0x6e, 0x5, 
    0x18, 0xd, 0xa, 0x64, 0x65, 0xc, 0x8, 0x2, 0x2, 0x65, 0x66, 0x7, 0xc, 
    0x2, 0x2, 0x66, 0x6e, 0x5, 0x18, 0xd, 0x9, 0x67, 0x68, 0xc, 0x7, 0x2, 
    0x2, 0x68, 0x69, 0x7, 0xd, 0x2, 0x2, 0x69, 0x6e, 0x5, 0x18, 0xd, 0x8, 
    0x6a, 0x6b, 0xc, 0x6, 0x2, 0x2, 0x6b, 0x6c, 0x7, 0xe, 0x2, 0x2, 0x6c, 
    0x6e, 0x5, 0x18, 0xd, 0x7, 0x6d, 0x61, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x64, 
    0x3, 0x2, 0x2, 0x2, 0x6d, 0x67, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6a, 0x3, 
    0x2, 0x2, 0x2, 0x6e, 0x71, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x6d, 0x3, 0x2, 
    0x2, 0x2, 0x6f, 0x70, 0x3, 0x2, 0x2, 0x2, 0x70, 0x19, 0x3, 0x2, 0x2, 
    0x2, 0x71, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x9, 0x20, 0x2c, 0x36, 0x4b, 0x5f, 
    0x6d, 0x6f, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ifccParser::Initializer ifccParser::_init;
