#include "IRInstrGenerator.h"
#include "IRGenerator.h"

string IRInstrGenerator::genAff(Aff *aff)
{
				string varExpr = generator->genExpr(aff->getExpr());
				string varName = aff->getVarName();

				vector<string> params;

				params.push_back(varName);
				params.push_back(varExpr);

				generator->getCurrentBB()->add_IRInstr(IRInstr::COPY, aff->getType(), params);

				return varName;
}

string IRInstrGenerator::genFuncCall(FuncCall *funcCall)
{
				string retVar = generator->createTempVar(generator->getCurrentFunc()->getType());

				vector<string> irParams;
				irParams.push_back(funcCall->getFuncName());
				irParams.push_back(retVar);
                FuncSymbol* funcSymbol = (FuncSymbol*)generator->getCurrentContext()->getSymbol(funcCall->getFuncName());

                vector<FuncSymbol::Param> funcParams = funcSymbol->getParams();
				vector<Expr *> params = funcCall->getParams();
				for (int i = 0; i < params.size(); ++i)
				{
								string varExpr = generator->genExpr(params[i]);
								irParams.push_back(varExpr);
								irParams.push_back(to_string(funcParams[i].type));
				}

				generator->getCurrentBB()->add_IRInstr(IRInstr::CALL, generator->getCurrentFunc()->getType(), irParams);
 				return retVar;
}

string IRInstrGenerator::genRet(Ret *ret)
{
				string varExpr = generator->genExpr(ret->getExpr());

				vector<string> params;
				params.push_back(varExpr);

				generator->getCurrentBB()->add_IRInstr(IRInstr::RET, generator->getCurrentFunc()->getType(), params);

				return varExpr;
}

string IRInstrGenerator::genArrAff(ArrAff * arrAff)
{
	string var1 = arrAff->getArrName();
	string var2 = generator->genExpr(arrAff->getIndexExpr());
	string var3 = generator->genExpr(arrAff->getExpr());

	VarSymbol* varSymbol = (VarSymbol*)generator->getCurrentContext()->getSymbol(arrAff->getArrName());

	vector<string> params;
	params.push_back(var1);
	params.push_back(var2);
	params.push_back(var3);

	generator->getCurrentBB()->add_IRInstr(IRInstr::W_MEM_TAB, varSymbol->getVarType(), params);

	return var1;
}