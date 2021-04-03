#pragma once

#include "../../ast/instructions/Aff.h"
#include "../../ast/instructions/FuncCall.h"
#include "../../ast/instructions/Ret.h"

class IRGenerator;

class IRInstrGenerator
{
public:
	IRInstrGenerator(IRGenerator *irGenerator) : generator(irGenerator) {}

	string genAff(Aff *aff);
	string genFuncCall(FuncCall *funcCall);
	string genRet(Ret *ret);

private:
	IRGenerator *generator;
};
