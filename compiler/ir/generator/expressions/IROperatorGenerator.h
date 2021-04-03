#pragma once

#include "../../../ast/expressions/operator/BinOp.h"
#include "../../../ast/expressions/operator/UnOp.h"

class IRGenerator;

class IROperatorGenerator
{
public:
	IROperatorGenerator(IRGenerator *irGenerator) : generator(irGenerator) {}
	string genBin(BinOp *binOp);
	string genUn(UnOp *unOp);

private:
	IRGenerator *generator;
};
