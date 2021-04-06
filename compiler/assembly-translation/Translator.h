#pragma once

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Context;
class CFG;
class IRInstr;
class BasicBlock;

class Translator
{

public:
Translator(ostream &stream, CFG *cfg);
virtual void translate();

protected:
virtual void genInstr(IRInstr *instr);

virtual void genCopy(IRInstr *instr) = 0;
virtual void genConst(IRInstr *instr) = 0;
virtual void genAdd(IRInstr *instr) = 0;
virtual void genSub(IRInstr *instr) = 0;
virtual void genMul(IRInstr *instr) = 0;
virtual void genDiv(IRInstr *instr) = 0;
virtual void genCompEq(IRInstr *instr) = 0;
virtual void genCompLe(IRInstr *instr) = 0;
virtual void genCompLt(IRInstr *instr) = 0;
virtual void genCall(IRInstr *instr) = 0;
virtual void genRet(IRInstr *instr) = 0;
virtual void genProlog(IRInstr *instr) = 0;
virtual void genEpilog(IRInstr *instr) = 0;

virtual void genBlock(BasicBlock *bb) = 0;
virtual void genBlockInstructions(BasicBlock *bb);

virtual string putSymbolInRegister(string name, vector<string> requiredSymbols, TypeName tn) = 0;

virtual string getAvailableRegister(vector<string> requiredSymbols);
virtual string getSymbolAddress(string name) = 0;
virtual bool isSymbolInRegister(string name, TypeName tn);
virtual string getSymbolMemAddress(string name);
virtual void unsetSymbolFromRegister(string name);
virtual void setSymbolInRegister(string symbolName, string reg, TypeName tn);
virtual string getRegisterWithSize(string reg, TypeName tn) = 0;

map<string, vector<string> >  registers;
Context *currentContext;
ostream &o;
CFG *cfg;
};
