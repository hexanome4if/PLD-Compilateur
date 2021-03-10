
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
    setState(20);
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
    setState(26);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ifccParser::TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(22);
        func();
        setState(23);
        prog();
        break;
      }

      case ifccParser::EOF: {
        enterOuterAlt(_localctx, 2);
        setState(25);
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
    setState(28);
    match(ifccParser::TYPE);
    setState(29);
    match(ifccParser::NAME);
    setState(30);
    match(ifccParser::T__0);
    setState(31);
    match(ifccParser::T__1);
    setState(32);
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

ifccParser::Block_contentContext* ifccParser::BlockContext::block_content() {
  return getRuleContext<ifccParser::Block_contentContext>(0);
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

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    match(ifccParser::T__2);
    setState(35);
    block_content();
   
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

ifccParser::Block_contentContext* ifccParser::Block_contentContext::block_content() {
  return getRuleContext<ifccParser::Block_contentContext>(0);
}

ifccParser::Func_return_varContext* ifccParser::Block_contentContext::func_return_var() {
  return getRuleContext<ifccParser::Func_return_varContext>(0);
}

ifccParser::VardefContext* ifccParser::Block_contentContext::vardef() {
  return getRuleContext<ifccParser::VardefContext>(0);
}

ifccParser::VaraffvarContext* ifccParser::Block_contentContext::varaffvar() {
  return getRuleContext<ifccParser::VaraffvarContext>(0);
}

ifccParser::VaraffconstContext* ifccParser::Block_contentContext::varaffconst() {
  return getRuleContext<ifccParser::VaraffconstContext>(0);
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
    setState(53);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(37);
      func_return_const();
      setState(38);
      block_content();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(40);
      func_return_var();
      setState(41);
      block_content();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(43);
      vardef();
      setState(44);
      block_content();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(46);
      varaffvar();
      setState(47);
      block_content();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(49);
      varaffconst();
      setState(50);
      block_content();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(52);
      match(ifccParser::T__3);
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
    setState(55);
    match(ifccParser::T__4);
    setState(56);
    match(ifccParser::CONST);
    setState(57);
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
    setState(59);
    match(ifccParser::T__4);
    setState(60);
    match(ifccParser::NAME);
    setState(61);
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

tree::TerminalNode* ifccParser::VardefContext::CONST() {
  return getToken(ifccParser::CONST, 0);
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
  enterRule(_localctx, 14, ifccParser::RuleVardef);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    match(ifccParser::TYPE);
    setState(64);
    match(ifccParser::NAME);
    setState(65);
    match(ifccParser::T__6);
    setState(66);
    match(ifccParser::CONST);
    setState(67);
    match(ifccParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VaraffvarContext ------------------------------------------------------------------

ifccParser::VaraffvarContext::VaraffvarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ifccParser::VaraffvarContext::NAME() {
  return getTokens(ifccParser::NAME);
}

tree::TerminalNode* ifccParser::VaraffvarContext::NAME(size_t i) {
  return getToken(ifccParser::NAME, i);
}


size_t ifccParser::VaraffvarContext::getRuleIndex() const {
  return ifccParser::RuleVaraffvar;
}

antlrcpp::Any ifccParser::VaraffvarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVaraffvar(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VaraffvarContext* ifccParser::varaffvar() {
  VaraffvarContext *_localctx = _tracker.createInstance<VaraffvarContext>(_ctx, getState());
  enterRule(_localctx, 16, ifccParser::RuleVaraffvar);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(69);
    match(ifccParser::NAME);
    setState(70);
    match(ifccParser::T__6);
    setState(71);
    match(ifccParser::NAME);
    setState(72);
    match(ifccParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VaraffconstContext ------------------------------------------------------------------

ifccParser::VaraffconstContext::VaraffconstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::VaraffconstContext::NAME() {
  return getToken(ifccParser::NAME, 0);
}

tree::TerminalNode* ifccParser::VaraffconstContext::CONST() {
  return getToken(ifccParser::CONST, 0);
}


size_t ifccParser::VaraffconstContext::getRuleIndex() const {
  return ifccParser::RuleVaraffconst;
}

antlrcpp::Any ifccParser::VaraffconstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitVaraffconst(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::VaraffconstContext* ifccParser::varaffconst() {
  VaraffconstContext *_localctx = _tracker.createInstance<VaraffconstContext>(_ctx, getState());
  enterRule(_localctx, 18, ifccParser::RuleVaraffconst);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    match(ifccParser::NAME);
    setState(75);
    match(ifccParser::T__6);
    setState(76);
    match(ifccParser::CONST);
    setState(77);
    match(ifccParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> ifccParser::_decisionToDFA;
atn::PredictionContextCache ifccParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ifccParser::_atn;
std::vector<uint16_t> ifccParser::_serializedATN;

std::vector<std::string> ifccParser::_ruleNames = {
  "axiom", "prog", "func", "block", "block_content", "func_return_const", 
  "func_return_var", "vardef", "varaffvar", "varaffconst"
};

std::vector<std::string> ifccParser::_literalNames = {
  "", "'('", "')'", "'{'", "'}'", "'return'", "';'", "'='"
};

std::vector<std::string> ifccParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "CONST", "TYPE", "NAME", "COMMENT", "DIRECTIVE", 
  "WS"
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
    0x3, 0xf, 0x52, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 
    0x3, 0x1d, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 
    0x38, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x2, 0x2, 0xc, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x2, 0x2, 0x2, 
    0x4d, 0x2, 0x16, 0x3, 0x2, 0x2, 0x2, 0x4, 0x1c, 0x3, 0x2, 0x2, 0x2, 
    0x6, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x8, 0x24, 0x3, 0x2, 0x2, 0x2, 0xa, 0x37, 
    0x3, 0x2, 0x2, 0x2, 0xc, 0x39, 0x3, 0x2, 0x2, 0x2, 0xe, 0x3d, 0x3, 0x2, 
    0x2, 0x2, 0x10, 0x41, 0x3, 0x2, 0x2, 0x2, 0x12, 0x47, 0x3, 0x2, 0x2, 
    0x2, 0x14, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 0x5, 0x4, 0x3, 0x2, 
    0x17, 0x3, 0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x5, 0x6, 0x4, 0x2, 0x19, 
    0x1a, 0x5, 0x4, 0x3, 0x2, 0x1a, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1d, 
    0x7, 0x2, 0x2, 0x3, 0x1c, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0x1d, 0x5, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x7, 0xb, 
    0x2, 0x2, 0x1f, 0x20, 0x7, 0xc, 0x2, 0x2, 0x20, 0x21, 0x7, 0x3, 0x2, 
    0x2, 0x21, 0x22, 0x7, 0x4, 0x2, 0x2, 0x22, 0x23, 0x5, 0x8, 0x5, 0x2, 
    0x23, 0x7, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x7, 0x5, 0x2, 0x2, 0x25, 
    0x26, 0x5, 0xa, 0x6, 0x2, 0x26, 0x9, 0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 
    0x5, 0xc, 0x7, 0x2, 0x28, 0x29, 0x5, 0xa, 0x6, 0x2, 0x29, 0x38, 0x3, 
    0x2, 0x2, 0x2, 0x2a, 0x2b, 0x5, 0xe, 0x8, 0x2, 0x2b, 0x2c, 0x5, 0xa, 
    0x6, 0x2, 0x2c, 0x38, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x5, 0x10, 0x9, 
    0x2, 0x2e, 0x2f, 0x5, 0xa, 0x6, 0x2, 0x2f, 0x38, 0x3, 0x2, 0x2, 0x2, 
    0x30, 0x31, 0x5, 0x12, 0xa, 0x2, 0x31, 0x32, 0x5, 0xa, 0x6, 0x2, 0x32, 
    0x38, 0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 0x5, 0x14, 0xb, 0x2, 0x34, 0x35, 
    0x5, 0xa, 0x6, 0x2, 0x35, 0x38, 0x3, 0x2, 0x2, 0x2, 0x36, 0x38, 0x7, 
    0x6, 0x2, 0x2, 0x37, 0x27, 0x3, 0x2, 0x2, 0x2, 0x37, 0x2a, 0x3, 0x2, 
    0x2, 0x2, 0x37, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x37, 0x30, 0x3, 0x2, 0x2, 
    0x2, 0x37, 0x33, 0x3, 0x2, 0x2, 0x2, 0x37, 0x36, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0xb, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x7, 0x7, 0x2, 0x2, 0x3a, 
    0x3b, 0x7, 0xa, 0x2, 0x2, 0x3b, 0x3c, 0x7, 0x8, 0x2, 0x2, 0x3c, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x7, 0x7, 0x2, 0x2, 0x3e, 0x3f, 0x7, 
    0xc, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x8, 0x2, 0x2, 0x40, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0x41, 0x42, 0x7, 0xb, 0x2, 0x2, 0x42, 0x43, 0x7, 0xc, 0x2, 
    0x2, 0x43, 0x44, 0x7, 0x9, 0x2, 0x2, 0x44, 0x45, 0x7, 0xa, 0x2, 0x2, 
    0x45, 0x46, 0x7, 0x8, 0x2, 0x2, 0x46, 0x11, 0x3, 0x2, 0x2, 0x2, 0x47, 
    0x48, 0x7, 0xc, 0x2, 0x2, 0x48, 0x49, 0x7, 0x9, 0x2, 0x2, 0x49, 0x4a, 
    0x7, 0xc, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0x8, 0x2, 0x2, 0x4b, 0x13, 0x3, 
    0x2, 0x2, 0x2, 0x4c, 0x4d, 0x7, 0xc, 0x2, 0x2, 0x4d, 0x4e, 0x7, 0x9, 
    0x2, 0x2, 0x4e, 0x4f, 0x7, 0xa, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x8, 0x2, 
    0x2, 0x50, 0x15, 0x3, 0x2, 0x2, 0x2, 0x4, 0x1c, 0x37, 
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
