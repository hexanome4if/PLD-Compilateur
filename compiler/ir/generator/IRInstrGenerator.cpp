#include "IRInstrGenerator.h"
#include "IRGenerator.h"

string IRInstrGenerator::genAff(Aff *aff)
{
	string varExpr = generator->genExpr(aff->getExpr());
	string varName = aff->getVarName();

	vector<string> params;

	params.push_back(varName);
	params.push_back(varExpr);

	generator->getCurrentBB()->add_IRInstr(IRInstr::COPY, "int32", params);

	return varName;
}

string IRInstrGenerator::genFuncCall(FuncCall *funcCall)
{
	string retVar = generator->createTempVar("int32");

	vector<string> irParams;
	irParams.push_back(funcCall->getFuncName());
	irParams.push_back(retVar);

	vector<Expr *> params = funcCall->getParams();
	for (int i = 0; i < params.size(); ++i)
	{
		string varExpr = generator->genExpr(params[i]);
		irParams.push_back(varExpr);
	}

	generator->getCurrentBB()->add_IRInstr(IRInstr::CALL, "int32", irParams);

	return retVar;
}

string IRInstrGenerator::genRet(Ret *ret)
{
	string varExpr = generator->genExpr(ret->getExpr());

	vector<string> params;
	params.push_back(varExpr);

	generator->getCurrentBB()->add_IRInstr(IRInstr::RET, "int32", params);

	return varExpr;
}
