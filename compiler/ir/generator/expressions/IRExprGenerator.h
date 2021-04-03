#pragma once

#include "../../../ast/expressions/ConstExpr.h"
#include "../../../ast/expressions/VarExpr.h"

class IRGenerator;

class IRExprGenerator
{

public:
	IRExprGenerator(IRGenerator *generator) : generator(generator) {}

	void genChar();
	string genConst(ConstExpr *constExpr);
	string genVar(VarExpr *varExpr);
	void genNot();

private:
	IRGenerator *generator;
};
