#pragma once

#include "../../ast/instructions/Aff.h"
#include "../../ast/instructions/FuncCall.h"
#include "../../ast/instructions/Ret.h"
#include "../../ast/instructions/ArrAff.h"

class IRGenerator;

class IRInstrGenerator
{
public:
	IRInstrGenerator(IRGenerator *irGenerator) : generator(irGenerator) {}

	string genAff(Aff *aff);
	string genArrAff(ArrAff * arrAff);
	string genFuncCall(FuncCall *funcCall);
	string genRet(Ret *ret);

private:
	IRGenerator *generator;
};
