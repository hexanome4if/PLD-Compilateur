#include "IRCompGenerator.h"
#include "IRExprGenerator.h"
#include "../IRGenerator.h"


string IRCompGenerator::genEqual(EqualCompare *eq_cmp)
{

	string var1 = generator->genExpr(eq_cmp->getExpr1());
	string var2 = generator->genExpr(eq_cmp->getExpr2());
	string var3 = generator->createTempVar(INT_32);

	vector<string> params;
	params.push_back(var3);
	params.push_back(var1);
	params.push_back(var2);

	generator->getCurrentBB()->add_IRInstr(IRInstr::CMP_EQ, "int32", params);

	return var3;
}

string IRCompGenerator::genInf(InfCompare *inf_cmp)
{

	string var1 = generator->genExpr(inf_cmp->getExpr1());
	string var2 = generator->genExpr(inf_cmp->getExpr2());
	string var3 = generator->createTempVar(INT_32);

	vector<string> params;
	params.push_back(var3);
	params.push_back(var1);
	params.push_back(var2);

	generator->getCurrentBB()->add_IRInstr(IRInstr::CMP_LT, "int32", params);

	return var3;
}

string IRCompGenerator::genNotEqual(NotEqualCompare *ne_cmp)
{

	string var1 = generator->genExpr(ne_cmp->getExpr1());
	string var2 = generator->genExpr(ne_cmp->getExpr2());
	string var3 = generator->createTempVar(INT_32);

	vector<string> params;
	params.push_back(var3);
	params.push_back(var1);
	params.push_back(var2);

	generator->getCurrentBB()->add_IRInstr(IRInstr::CMP_EQ, "int32", params);

	Expr *cmp = new ConstExpr(var3);
	Not *not_cmp = new Not(cmp);

	string var = generator->getIRExprGenerator()->genNot(not_cmp);

	return var;
}

string IRCompGenerator::genSup(SupCompare *sup_cmp){

	string var1 = generator->genExpr(sup_cmp->getExpr1());
	string var2 = generator->genExpr(sup_cmp->getExpr2());
	string var3 = generator->createTempVar(INT_32);

	vector<string> params;
	params.push_back(var3);
	params.push_back(var2); // on inverse l'ordre des vars
	params.push_back(var1);
	
	generator->getCurrentBB()->add_IRInstr(IRInstr::CMP_LT, "int32", params);

	return var3;
}	