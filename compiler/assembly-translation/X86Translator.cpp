#include <algorithm>
#include <math.h>
#include "X86Translator.h"
#include "../ir/BasicBlock.h"
#include "../ir/IRInstr.h"
#include "../ir/CFG.h"
#include "../symbols-management/Context.h"
#include "../symbols-management/VarSymbol.h"

X86Translator::X86Translator(ostream &stream, CFG *cfg) : Translator(stream, cfg)
{
	// Define registers
	registers["a"] = nullptr;
	registers["b"] = nullptr;
	registers["c"] = nullptr;
	registers["d"] = nullptr;
	registers["e"] = nullptr;
	registers["f"] = nullptr;
}

void X86Translator::genBlock(BasicBlock *bb)
{
	clearRegisters();
	currentContext = bb->getContext();

	o << "." << bb->getLabel() << ":" << endl;

	genBlockInstructions(bb);

	if (bb->getTestVarName() != "")
	{
		string reg = putSymbolInRegister(bb->getTestVarName(), vector<string>(), bb->getTestTypeName());
		string type = getSuffixe(bb->getTestTypeName());
		o << "  cmp" << type << " $0, " << getRegisterWithSize(reg, bb->getTestTypeName()) << endl;
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
	string reg = putSymbolInRegister(params[1], vector<string>(), instr->getType());
	string type = getSuffixe(instr->getType());
	o << "  mov" << type << " " << getRegisterWithSize(reg, instr->getType()) << ", " << getSymbolMemAddress(params[0]) << endl;
	unsetSymbolFromRegister(params[0]);
}

void X86Translator::genConst(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string type = getSuffixe(instr->getType());
	o << "  mov" << type << " $" << params[1] << ", " << getSymbolMemAddress(params[0]) << endl;
	unsetSymbolFromRegister(params[0]);
}

void X86Translator::genAdd(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string reg1 = putSymbolInRegister(params[1], vector<string>{params[2]}, instr->getType());
	string reg2 = putSymbolInRegister(params[2], vector<string>{params[1]}, instr->getType());
	string type = getSuffixe(instr->getType());

	o << "  add" << type << " " << getRegisterWithSize(reg2, instr->getType()) << ", " << getRegisterWithSize(reg1, instr->getType()) << endl;
	o << "  mov" << type << " " << getRegisterWithSize(reg1, instr->getType()) << ", " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], reg1, instr->getType());
}

void X86Translator::genSub(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string reg1 = putSymbolInRegister(params[1], vector<string>{params[2]}, instr->getType());
	string reg2 = putSymbolInRegister(params[2], vector<string>{params[1]}, instr->getType());
	string type = getSuffixe(instr->getType());

	o << "  sub" << type << " " << getRegisterWithSize(reg2, instr->getType()) << ", " << getRegisterWithSize(reg1, instr->getType()) << endl;
	o << "  mov" << type << " " << getRegisterWithSize(reg1, instr->getType()) << ", " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], reg1, instr->getType());
}

void X86Translator::genMul(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string reg1 = putSymbolInRegister(params[1], vector<string>{params[2]}, instr->getType());
	string reg2 = putSymbolInRegister(params[2], vector<string>{params[1]}, instr->getType());
	string type = getSuffixe(instr->getType());

	o << "  imul" << type << " " << getRegisterWithSize(reg2, instr->getType()) << ", " << getRegisterWithSize(reg1, instr->getType()) << endl;
	o << "  mov" << type << " " << getRegisterWithSize(reg1, instr->getType()) << ", " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], reg1, instr->getType());
}

void X86Translator::genDiv(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string type = getSuffixe(instr->getType());
	putSymbolInRegister(params[1], instr->getType(), "a");
	string reg = putSymbolInRegister(params[2], vector<string>(), instr->getType());
	o << "  cltd" << endl;
	o << "  idiv" << type << " " << getRegisterWithSize(reg, instr->getType()) << endl;
	o << "  mov" << type << " %eax, " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], "a", instr->getType());
}

void X86Translator::genComp(IRInstr *instr, string op)
{
	vector<string> params = instr->getParams();
	string type = getSuffixe(instr->getType());
	string reg1 = putSymbolInRegister(params[1], vector<string>{params[2]}, instr->getType());
	string reg2 = putSymbolInRegister(params[2], vector<string>{params[1]}, instr->getType());
	o << "  cmp" << type << " " << getRegisterWithSize(reg1, instr->getType()) << ", " << getRegisterWithSize(reg2, instr->getType()) << endl;
	o << op << " %al" << endl;
	o << "  movzbl %al, %eax" << endl;
	o << "  movl %eax, " << getSymbolMemAddress(params[0]) << endl;

	unsetSymbolFromRegister(params[0]);
	setSymbolInRegister(params[0], "a", instr->getType());
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

void X86Translator::genAnd(IRInstr *instr)
{
}

void X86Translator::genOr(IRInstr *instr)
{
}

void X86Translator::genXor(IRInstr *instr)
{
}

void X86Translator::genCall(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	for (int i = params.size() - 1; i >= 2; i -= 2)
	{
		TypeName tn = static_cast<TypeName>(stoi(params[i]));
		string type = getSuffixe(tn);
		if (i > 13)
		{
			putSymbolInRegister(params[i - 1], tn, "d");
			o << "  pushq %rdx" << endl;
		}
		else
		{
			string reg = getRegFromParameterIndex((i - 1) / 2);
			putSymbolInRegister(params[i - 1], tn, reg);
		}
	}

	o << "  call " << params[0] << endl;

	int nbExcessVar = params.size() - 8;
	if (nbExcessVar > 0)
	{
		o << "  addq $" << to_string(nbExcessVar * 8) << ", %rsp" << endl;
	}
	string type = getSuffixe(instr->getType());
	o << "  mov" << type << " " << getRegisterWithSize("a", instr->getType()) << ", " << getSymbolMemAddress(params[1]) << endl;
	setSymbolInRegister(params[1], "a", instr->getType());
}

void X86Translator::genRet(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string type = getSuffixe(instr->getType());
	string reg = putSymbolInRegister(params[0], vector<string>(), instr->getType());
	o << "  mov" << type << " " << getRegisterWithSize(reg, instr->getType()) << ", " << getRegisterWithSize("a", instr->getType()) << endl;
}

void X86Translator::genProlog(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	o << ".global " << params[0] << endl;
	o << params[0] << ":" << endl;
	o << "  pushq %rbp" << endl;
	o << "  movq %rsp, %rbp" << endl;

	bool hasFunctionCall = params[1] == "true";
	int definedSymbolsSize = stoi(params[2]);

	if (hasFunctionCall && definedSymbolsSize > 0)
	{
		o << "  subq $" << to_string(int(ceil(definedSymbolsSize / 16.)) * 16) << ", %rsp" << endl;
	}

	for (int i = 3; i < params.size(); i += 2)
	{
		TypeName tn = static_cast<TypeName>(stoi(params[i + 1]));
		string type = getSuffixe(tn);
		if (i > 14)
		{
			o << "  mov" << type << " " << to_string(16 + (i - 7) * 8) << "(%rbp), " << getRegisterWithSize("a", tn) << endl;
			o << "  mov" << type << " " << getRegisterWithSize("a", tn) << ", " << getSymbolMemAddress(params[i]) << endl;
			setSymbolInRegister(params[i], "a", tn);
		}
		else
		{
			string reg = getRegFromParameterIndex((i - 1) / 2);
			o << "  mov" << type << " " << getRegisterWithSize(reg, tn) << ", " << getSymbolMemAddress(params[i]) << endl;
			setSymbolInRegister(params[i], reg, tn);
		}
	}
}

void X86Translator::genEpilog(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	bool hasFunctionCall = params[0] == "true";
	int definedSymbolSize = stoi(params[1]);
	if (hasFunctionCall && definedSymbolSize > 0)
	{
		o << "  leave" << endl;
	}
	else
	{
		o << "  popq %rbp" << endl;
	}
	o << "  ret" << endl;
}

void X86Translator::genR_Mem_Tab(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string type = getSuffixe(instr->getType());

	putSymbolInRegister(params[2], instr->getType(), "a");
	o << "  cltq" << endl;
	o << "  mov" << type << " -" << Translator::getSymbolMemAddress(params[1]) << "(%rbp, %rax, " << getMemorySizeFromType(instr->getType()) << "), " << getRegisterWithSize("a", instr->getType()) << endl;
	o << "  mov" << type << " " << getRegisterWithSize("a", instr->getType()) << ", " << getSymbolMemAddress(params[0]) << endl;
}

void X86Translator::genW_Mem_Tab(IRInstr *instr)
{
	vector<string> params = instr->getParams();
	string type = getSuffixe(instr->getType());

	putSymbolInRegister(params[1], instr->getType(), "a");
	string reg = putSymbolInRegister(params[2], vector<string>(), instr->getType());
	o << "  cltq" << endl;
	o << "  mov" << type << " " << getRegisterWithSize(reg, instr->getType()) << ", ";
	o << "-" << Translator::getSymbolMemAddress(params[0]) << "(%rbp, %rax, " << getMemorySizeFromType(instr->getType()) << ")" << endl;
}

string X86Translator::getRegFromParameterIndex(int index)
{
	switch (index)
	{
	case 1:
		return "f";
	case 2:
		return "e";
	case 3:
		return "d";
	case 4:
		return "c";
	case 5:
		return "8";
	case 6:
		return "9";
	}
	return "";
}

string X86Translator::getSymbolAddress(string name)
{
	map<string, vector<string> *>::iterator it;
	for (it = registers.begin(); it != registers.end(); ++it)
	{
		if (it->second != nullptr && it->second->at(0) == name)
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

string X86Translator::putSymbolInRegister(string name, vector<string> requiredSymbols, TypeName tn)
{
	if (isSymbolInRegister(name, tn))
	{
		return getSymbolAddress(name);
	}
	string reg = getAvailableRegister(requiredSymbols);
	string type = getSuffixe(tn);
	VarSymbol *var = (VarSymbol *)currentContext->getSymbol(name);
	if (getMemorySizeFromType(var->getVarType()) < getMemorySizeFromType(tn))
	{
		string oldType = getSuffixe(var->getVarType());
		o << "  mov" << oldType << " " << getSymbolMemAddress(name) << ", " << getRegisterWithSize(reg, var->getVarType()) << endl;
		o << "  movs" << oldType << type << " " << getRegisterWithSize(reg, var->getVarType()) << ", " << getRegisterWithSize(reg, tn) << endl;
	}
	else
	{
		string oldType = getSuffixe(var->getVarType());
		o << "  mov" << oldType << " " << getSymbolMemAddress(name) << ", " << getRegisterWithSize(reg, var->getVarType()) << endl;
	}
	setSymbolInRegister(name, reg, tn);

	return reg;
}

string X86Translator::putSymbolInRegister(string name, TypeName tn, string reg)
{
	string type = getSuffixe(tn);
	VarSymbol *var = (VarSymbol *)currentContext->getSymbol(name);
	if (getMemorySizeFromType(var->getVarType()) < getMemorySizeFromType(tn))
	{
		string oldType = getSuffixe(var->getVarType());
		o << "  mov" << oldType << " " << getSymbolMemAddress(name) << ", " << getRegisterWithSize(reg, var->getVarType()) << endl;
		o << "  movs" << oldType << type << " " << getRegisterWithSize(reg, var->getVarType()) << ", " << getRegisterWithSize(reg, tn) << endl;
	}
	else
	{

		string oldType = getSuffixe(var->getVarType());
		o << "  mov" << oldType << " " << getSymbolMemAddress(name) << ", " << getRegisterWithSize(reg, var->getVarType()) << endl;
	}

	setSymbolInRegister(name, reg, tn);

	return reg;
}

string X86Translator::getSuffixe(TypeName tn)
{
	switch (getMemorySizeFromType(tn))
	{
	case 8:
		return "q";
	case 4:
		return "l";
	case 1:
		return "b";
	default:
		return "l";
	}
}

string X86Translator::getRegisterWithSize(string reg, TypeName tn)
{
	switch (getMemorySizeFromType(tn))
	{
	case 8:
		if (reg > "7" && reg <= "9")
		{
			return "%r" + reg;
		}
		else if (reg < "e")
		{
			return "%r" + reg + "x";
		}
		else if (reg == "e")
		{
			return "%rsi";
		}
		else if (reg == "f")
		{
			return "%rdi";
		}

	case 4:
		if (reg > "7" && reg <= "9")
		{
			return "%r" + reg + "d";
		}
		else if (reg < "e")
		{
			return "%e" + reg + "x";
		}
		else if (reg == "e")
		{
			return "%esi";
		}
		else if (reg == "f")
		{
			return "%edi";
		}
	case 1:
		if (reg > "7" && reg <= "9")
		{
			return "%r" + reg + "b";
		}
		else if (reg < "e")
		{
			return "%" + reg + "l";
		}
		else if (reg == "e")
		{
			return "%sil";
		}
		else if (reg == "f")
		{
			return "%dil";
		}
	default:
		return "";
	}
}
