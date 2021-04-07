#pragma once

#include "../../../ast/expressions/ConstExpr.h"
#include "../../../ast/expressions/VarExpr.h"
#include "../../../ast/expressions/Not.h"
#include "../../../ast/expressions/CharExpr.h"
#include "../../../ast/expressions/ArrExpr.h"

class IRGenerator;

class IRExprGenerator
{

public:
	IRExprGenerator(IRGenerator *generator) : generator(generator) {}

	void genChar();
	string genConst(ConstExpr *constExpr);
	string genChar(CharExpr *charExpr);
	string genVar(VarExpr *varExpr);
	string genNot(Not *_not);
	string genArrExpr(ArrExpr *arrExpr);

private:
	IRGenerator *generator;
};
