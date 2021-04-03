#include "IROperatorGenerator.h"
#include "../IRGenerator.h"

string IROperatorGenerator::genBin(BinOp *binOp)
{
	string var1 = generator->genExpr(binOp->getExpr1());
	string var2 = generator->genExpr(binOp->getExpr2());
	string var3 = generator->createTempVar(INT_32);

	IRInstr::Operation op;
	switch (binOp->getOperation())
	{
	case Expr::ADD:
		op = IRInstr::ADD;
		break;
	case Expr::MULT:
		op = IRInstr::MUL;
		break;
	case Expr::DIV:
		op = IRInstr::DIV;
		break;
	case Expr::SUBS:
		op = IRInstr::SUB;
		break;
	default:
		break;
	}

	vector<string> params;
	params.push_back(var3);
	params.push_back(var1);
	params.push_back(var2);

	generator->getCurrentBB()->add_IRInstr(op, "int32", params);

	return var3;
}

// TODO change this
string IROperatorGenerator::genUn(UnOp *unOp)
{
	Expr *zero = new ConstExpr("0");

	Expr *minus = new BinOp(zero, unOp->getExpr(), Expr::SUBS);

	string var = generator->genExpr(minus);
	return var;
}
