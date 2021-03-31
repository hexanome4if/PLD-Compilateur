#include "instr.h"
#include "IR.h"

/*string Block :: buildIR (CFG* cfg) {
				for (int i = 0; i < instrs.size(); i++) {
								instrs[i]->buildIR(cfg);
				}
				return "";
}*/

/*string Aff :: buildIR (CFG* cfg) {
				//IRInstr(cfg->current_bb, copy, TypeName t, vector<string> params)
			return "";
}*/

void Block::addInstr(Instr *i)
{
	instrs.push_back(i);
}

void Block::debug(ostream &stream, int space)
{
	showSpaces(stream, space);
	stream << "Block" << endl;
	context->debug(stream, space);
	for (int i = 0; i < instrs.size(); ++i)
	{
		showSpaces(stream, space + 1);
		instrs[i]->debug(stream, space);
		stream << endl;
	}
}

void Func::addParam(string p)
{
	params.push_back(p);
}

void Func::addInstr(Instr *i)
{
	block->addInstr(i);
}

void Func::debug(ostream &stream, int space)
{
	showSpaces(stream, space);
	stream << "Function " << name << endl;
	block->debug(stream, ++space);
}

void FuncCall::addParam(Expr *e)
{
	params.push_back(e);
}

void Aff::debug(ostream &stream, int space)
{
	stream << "(" << varId << " = ";
	expr->debug(stream, space);
	stream << ")";
}
void Ret::debug(ostream &stream, int space)
{
	stream << "return ";
	expr->debug(stream, space);
}

void If::debug(ostream &stream, int space)
{
	stream << "if (";
	condition->debug(stream, space);
	stream << ")" << endl;
	blockIf->debug(stream, space + 1);
	if (blockElse != nullptr)
	{
		showSpaces(stream, space);
		stream << "else" << endl;
		blockElse->debug(stream, space + 1);
	}
}

void While::debug(ostream &stream, int space)
{
	stream << "while (";
	condition->debug(stream, space);
	stream << ")" << endl;
	block->debug(stream, space + 1);
}

void FuncCall::debug(ostream &stream, int space)
{
	stream << "call to function " << funcName << " with parameters ";
	for (int i = 0; i < params.size(); ++i)
	{
		params[i]->debug(stream, space);
		stream << " | ";
	}
}
