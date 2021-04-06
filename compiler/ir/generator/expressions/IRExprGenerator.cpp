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
