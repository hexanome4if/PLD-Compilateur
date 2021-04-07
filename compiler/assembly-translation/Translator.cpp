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
	case IRInstr::R_MEM_TAB:
		genR_Mem_Tab(instr);
		break;
	case IRInstr::W_MEM_TAB:
		genW_Mem_Tab(instr);
		break;
	default:
		break;
	}
}

string Translator::getAvailableRegister(vector<string> requiredSymbols)
{
	vector<string> overridableRegisters;
	map<string, vector<string> *>::iterator it;
	for (it = registers.begin(); it != registers.end(); ++it)
	{
		if (it->second == nullptr)
		{
			return it->first;
		}
		else if (find(requiredSymbols.begin(), requiredSymbols.end(), it->second->at(0)) == requiredSymbols.end())
		{
			overridableRegisters.push_back(it->first);
		}
	}
	return overridableRegisters[0];
}

bool Translator::isSymbolInRegister(string name, TypeName tn)
{
	map<string, vector<string> *>::iterator it;
	for (it = registers.begin(); it != registers.end(); ++it)
	{
		if (it->second != nullptr && it->second->at(0) == name && it->second->at(1) == to_string(tn))
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
	map<string, vector<string> *>::iterator it;
	for (it = registers.begin(); it != registers.end(); ++it)
	{
		if (it->second != nullptr && it->second->at(0) == name)
		{
			registers[it->first] = nullptr;
		}
	}
}

void Translator::setSymbolInRegister(string symbolName, string reg, TypeName tn)
{
	registers[reg] = new vector<string>{symbolName, to_string(tn)};
}

void Translator::genBlockInstructions(BasicBlock *bb)
{
	vector<IRInstr *> instrs = bb->getInstrs();

	for (int i = 0; i < instrs.size(); ++i)
	{
		genInstr(instrs[i]);
	}
}

void Translator::clearRegisters()
{
	map<string, vector<string> *>::iterator it;
	for (it = registers.begin(); it != registers.end(); ++it)
	{
		registers[it->first] = nullptr;
	}
}
