#include "IRExprGenerator.h"
#include "../IRGenerator.h"

string IRExprGenerator::genConst(ConstExpr *constExpr)
{
	string var = generator->createTempVar(INT_32);

	vector<string> params;
	params.push_back(var);
	params.push_back(constExpr->getVal());

	generator->getCurrentBB()->add_IRInstr(IRInstr::LD_CONST, "int32", params);

	return var;
}

string IRExprGenerator::genVar(VarExpr *varExpr)
{
	return varExpr->getVarName();
}
