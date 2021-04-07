#include <algorithm>
#include "Translator.h"
#include "../symbols-management/VarSymbol.h"
#include "../ir/BasicBlock.h"
#include "../ir/CFG.h"
#include "../ir/IRInstr.h"
#include "../symbols-management/Context.h"

Translator::Translator(ostream &stream, CFG *cfg) : o(stream), cfg(cfg)
{
}

void Translator::translate()
{
	vector<BasicBlock *> bbs = cfg->getBBs();
	for (int i = 0; i < bbs.size(); ++i)
	{
		genBlock(bbs[i]);
	}
}

void Translator::genInstr(IRInstr *instr)
{
	switch (instr->getOp())
	{
	case IRInstr::COPY:
		genCopy(instr);
		break;
	case IRInstr::LD_CONST:
		genConst(instr);
		break;
	case IRInstr::ADD:
		genAdd(instr);
		break;
	case IRInstr::SUB:
		genSub(instr);
		break;
	case IRInstr::MUL:
		genMul(instr);
		break;
	case IRInstr::DIV:
		genDiv(instr);
		break;
	case IRInstr::CMP_EQ:
		genCompEq(instr);
		break;
	case IRInstr::CMP_LE:
		genCompLe(instr);
		break;
	case IRInstr::CMP_LT:
		genCompLt(instr);
		break;
	case IRInstr::B_AND:
		genAnd(instr);
		break;
	case IRInstr::B_OR:
		genOr(instr);
		break;
	case IRInstr::B_XOR:
		genXor(instr);
		break;
	case IRInstr::B_NOT:
		genNot(instr);
		break;
	case IRInstr::CALL:
		genCall(instr);
		break;
	case IRInstr::RET:
		genRet(instr);
		break;
	case IRInstr::PROLOG:
		genProlog(instr);
		break;
	case IRInstr::EPILOG:
		genEpilog(instr);
		break;
	default:
		break;
	}
}

string Translator::getAvailableRegister(vector<string> requiredSymbols)
{
	vector<string> overridableRegisters;
	map<string, string>::iterator it;
	for (it = registers.begin(); it != registers.end(); ++it)
	{
		if (it->second == "")
		{
			return it->first;
		}
		else if (find(requiredSymbols.begin(), requiredSymbols.end(), it->second) == requiredSymbols.end())
		{
			overridableRegisters.push_back(it->first);
		}
	}
	return overridableRegisters[0];
}

bool Translator::isSymbolInRegister(string name)
{
	map<string, string>::iterator it;
	for (it = registers.begin(); it != registers.end(); ++it)
	{
		if (it->second == name)
		{
			return true;
		}
	}
	return false;
}

string Translator::getSymbolMemAddress(string name)
{
	return to_string(((VarSymbol *)currentContext->getSymbol(name))->getMemoryAddress());
}

void Translator::unsetSymbolFromRegister(string name)
{
	map<string, string>::iterator it;
	for (it = registers.begin(); it != registers.end(); ++it)
	{
		if (it->second == name)
		{
			registers[it->first] = "";
		}
	}
}

void Translator::setSymbolInRegister(string symbolName, string reg)
{
	registers[reg] = symbolName;
}

void Translator::genBlockInstructions(BasicBlock *bb)
{
	vector<IRInstr *> instrs = bb->getInstrs();

	for (int i = 0; i < instrs.size(); ++i)
	{
		genInstr(instrs[i]);
	}
}
