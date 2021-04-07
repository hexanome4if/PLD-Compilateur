#include "IRExprGenerator.h"
#include "../IRGenerator.h"

string IRExprGenerator::genConst(ConstExpr *constExpr)
{
				string var = generator->createTempVar(constExpr->getConstType());

				vector<string> params;
				params.push_back(var);
				params.push_back(constExpr->getVal());

				generator->getCurrentBB()->add_IRInstr(IRInstr::LD_CONST, constExpr->getConstType(), params);

				return var;
}

string IRExprGenerator::genChar(CharExpr *charExpr)
{
    string var = generator->createTempVar(CHAR);

    vector<string> params;
    params.push_back(var);
    params.push_back(to_string(int(charExpr->getChar())));

    generator->getCurrentBB()->add_IRInstr(IRInstr::LD_CONST, CHAR, params);

    return var;
}

string IRExprGenerator::genVar(VarExpr *varExpr)
{
				return varExpr->getVarName();
}

string IRExprGenerator::genArrExpr(ArrExpr * arrExpr)
{
	string var1 = generator -> createTempVar(arrExpr->getType());
	string var2 = arrExpr->getArrName();
	string var3 = generator -> genExpr(arrExpr->getIndexExpr());

	vector<string> params;
	params.push_back(var1);
	params.push_back(var2);
	params.push_back(var3);

	generator->getCurrentBB()->add_IRInstr(IRInstr::R_MEM_TAB, arrExpr->getType(), params);
	return var1;
}


string IRExprGenerator::genNot(Not* _not )
{
	string var = generator->genExpr(_not->getExpr());

	vector<string> params;
	params.push_back(var);

	generator->getCurrentBB()->add_IRInstr(IRInstr::B_NOT, "int32", params);

	return var;
}
