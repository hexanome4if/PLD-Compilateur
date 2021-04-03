#include <algorithm>
#include "X86Translator.h"
#include "../ir/BasicBlock.h"
#include "../ir/IRInstr.h"
#include "../ir/CFG.h"
#include "../symbols-management/Context.h"
#include "../symbols-management/VarSymbol.h"

X86Translator::X86Translator(ostream &stream, CFG *cfg) : Translator(stream, cfg)
{
	// Define registers
	registers["%eax"] = "";
	registers["%ebx"] = "";
	registers["%ecx"] = "";
	registers["%edx"] = "";
	registers["%esi"] = "";
	registers["%edi"] = "";
}

void X86Translator::genBlock(BasicBlock *bb)
{
	currentContext = bb->getContext();

	o << "." << bb->getLabel() << ":" << endl;

	genBlockInstructions(bb);

	if (bb->getTestVarName() != "")
	{
		o << "  cmpl $0, " << getSymbolAddress(bb->getTestVarName()) << endl;
		o << "  je ." << bb->getExitFalse()->getLabel() << endl;
	}

	if (bb->getExitTrue() != nullptr)
	{
		o << "  jmp ." << bb->getExitTrue()->getLabel() << endl;
	}
}

void X86Translator::genCopy(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string reg = putSymbolInRegister(params[1], vector<string>());

	o << "  movl " << reg << ", " << getSymbolMemAddress(params[0]) << endl;
	unsetSymbolFromRegister(params[0]);
}

void X86Translator::genConst(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	o << "  movl $" << params[1] << ", " << getSymbolMemAddress(params[0]) << endl;
	unsetSymbolFromRegister(params[0]);
}

void X86Translator::genAdd(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string reg1 = putSymbolInRegister(params[1], vector<string>{params[2]});

	o << "  addl " << getSymbolAddress(params[2]) << ", " << reg1 << endl;
	o << "  movl " << reg1 << ", " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], reg1);
}

void X86Translator::genSub(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string reg1 = putSymbolInRegister(params[1], vector<string>{params[2]});

	o << "  subl " << getSymbolAddress(params[2]) << ", " << reg1 << endl;
	o << "  movl " << reg1 << ", " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], reg1);
}

void X86Translator::genMul(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string reg1 = putSymbolInRegister(params[1], vector<string>{params[2]});

	o << "  imull " << getSymbolAddress(params[2]) << ", " << reg1 << endl;
	o << "  movl " << reg1 << ", " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], reg1);
}

void X86Translator::genDiv(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	o << "  movl " << getSymbolAddress(params[1]) << ", %eax" << endl;
	o << "  cltd" << endl;
	o << "  idivl " << getSymbolAddress(params[2]) << endl;
	o << "  movl %eax, " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], "%eax");
}

void X86Translator::genComp(IRInstr *instr, string op)
{
	vector<string> params = instr->getParams();
	o << "  cmpl " << getSymbolAddress(params[1]) << ", " << getSymbolAddress(params[2]) << endl;
	o << op << " %al" << endl;
	o << "  movzbl %al, %eax" << endl;
	o << "  movl %eax, " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], "%eax");
}

void X86Translator::genCompEq(IRInstr *instr)
{
	genComp(instr, "sete");
}

void X86Translator::genCompLe(IRInstr *instr)
{
	genComp(instr, "setle");
}

void X86Translator::genCompLt(IRInstr *instr)
{
	genComp(instr, "setl");
}

void X86Translator::genCall(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	for (int i = params.size() - 1; i >= 2; --i)
	{
		if (i > 7)
		{
			o << "  movl " << getSymbolAddress(params[i]) << ", %edx" << endl;
			o << "  pushq %rdx" << endl;
		}
		else
		{
			string reg = getRegFromParameterIndex(i - 1);
			o << "  movl " << getSymbolAddress(params[i]) << ", " << reg << endl;
		}
	}

	o << "  call " << params[0] << endl;

	int nbExcessVar = params.size() - 8;
	if (nbExcessVar > 0)
	{
		o << "  addq $" << to_string(nbExcessVar * 8) << ", %rsp" << endl;
	}

	o << "  movl %eax, " << getSymbolMemAddress(params[1]) << endl;
	setSymbolInRegister(params[1], "%eax");
}

void X86Translator::genRet(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	o << "  movl " << getSymbolAddress(params[0]) << ", %eax" << endl;
}

void X86Translator::genProlog(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	o << ".global " << params[0] << endl;
	o << params[0] << ":" << endl;
	o << "  pushq %rbp" << endl;
	o << "  movq %rsp, %rbp" << endl;
	o << "  subq $16, %rsp" << endl;

	for (int i = 1; i < params.size(); ++i)
	{
		if (i > 6)
		{
			o << "  movl " << to_string(16 + (i - 7) * 8) << "(%rbp), %eax" << endl;
			o << "  movl %eax, " << getSymbolMemAddress(params[i]) << endl;
			setSymbolInRegister(params[i], "%eax");
		}
		else
		{
			string reg = getRegFromParameterIndex(i);
			o << "  movl " << reg << ", " << getSymbolMemAddress(params[i]) << endl;
			setSymbolInRegister(params[i], reg);
		}
	}
}

void X86Translator::genEpilog(IRInstr *instr)
{
	o << "  addq $16, %rsp" << endl;
	o << "  popq %rbp" << endl;
	o << "  ret" << endl;
}

string X86Translator::getRegFromParameterIndex(int index)
{
	switch (index)
	{
	case 1:
		return "%edi";
	case 2:
		return "%esi";
	case 3:
		return "%edx";
	case 4:
		return "%ecx";
	case 5:
		return "%r8d";
	case 6:
		return "%r9d";
	}
	return "";
}

string X86Translator::getSymbolAddress(string name)
{
	map<string, string>::iterator it;
	for (it = registers.begin(); it != registers.end(); ++it)
	{
		if (it->second == name)
		{
			return it->first;
		}
	}
	return "-" + to_string(((VarSymbol *)currentContext->getSymbol(name))->getMemoryAddress()) + "(%rbp)";
}

string X86Translator::getSymbolMemAddress(string name)
{
	string memAddress = Translator::getSymbolMemAddress(name);
	return "-" + memAddress + "(%rbp)";
}

string X86Translator::putSymbolInRegister(string name, vector<string> requiredSymbols)
{
	if (isSymbolInRegister(name))
	{
		return getSymbolAddress(name);
	}
	string reg = getAvailableRegister(requiredSymbols);

	o << "  movl " << getSymbolMemAddress(name) << ", " << reg << endl;

	setSymbolInRegister(name, reg);

	return reg;
}
