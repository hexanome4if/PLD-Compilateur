#pragma once

#include "../../../ast/expressions/ConstExpr.h"
#include "../../../ast/expressions/VarExpr.h"
#include "../../../ast/expressions/Not.h"

class IRGenerator;

class IRExprGenerator
{

public:
	IRExprGenerator(IRGenerator *generator) : generator(generator) {}

	void genChar();
	string genConst(ConstExpr *constExpr);
	string genVar(VarExpr *varExpr);
	string genNot(Not *_not);

private:
	IRGenerator *generator;
};
