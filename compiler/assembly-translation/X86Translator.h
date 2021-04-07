#pragma once

#include "Translator.h"
#include "../symbols-management/type.h"

class X86Translator : public Translator
{
public:
	X86Translator(ostream &stream, CFG *cfg);

protected:
	virtual void genCopy(IRInstr *instr) override;
	virtual void genConst(IRInstr *instr) override;
	virtual void genAdd(IRInstr *instr) override;
	virtual void genSub(IRInstr *instr) override;
	virtual void genMul(IRInstr *instr) override;
	virtual void genDiv(IRInstr *instr) override;
	virtual void genCompEq(IRInstr *instr) override;
	virtual void genCompLe(IRInstr *instr) override;
	virtual void genCompLt(IRInstr *instr) override;
	virtual void genAnd(IRInstr *instr) override;
	virtual void genOr(IRInstr *instr) override;
	virtual void genXor(IRInstr *instr) override;
	
	virtual void genCall(IRInstr *instr) override;
	virtual void genRet(IRInstr *instr) override;
	virtual void genProlog(IRInstr *instr) override;
	virtual void genEpilog(IRInstr *instr) override;
	virtual void genR_Mem_Tab(IRInstr *instr) override;
	virtual void genW_Mem_Tab(IRInstr *instr) override;

	virtual void genBlock(BasicBlock *bb) override;

	virtual string putSymbolInRegister(string name, vector<string> requiredSymbols, TypeName tn) override;
	virtual string putSymbolInRegister(string name, TypeName tn, string reg) override;

	virtual string getSymbolAddress(string name) override;
	virtual string getSymbolMemAddress(string name) override;

	void genComp(IRInstr *instr, string op);
	string getRegFromParameterIndex(int index);
	string getSuffixe(TypeName tn);

	virtual string getRegisterWithSize(string reg, TypeName tn) override;

		//virtual string putArrayValueInRegister(string name, int index, vector<string> requiredSymbols) override;
};
