#pragma once

#include "../../ast/instructions/For.h"
#include "../../ast/instructions/Func.h"
#include "../../ast/instructions/If.h"
#include "../../ast/instructions/While.h"
#include "../CFG.h"
#include "../BasicBlock.h"

class IRGenerator;

class IRBlockGenerator
{
public:
	IRBlockGenerator(CFG *cfg, IRGenerator *irGenerator) : cfg(cfg), irGenerator(irGenerator) {}

	void genFor(For *forLoop);
	void genFunc(Func *func);
	void genIf(If *ifBlock);
	void genWhile(While *whileLoop);

private:
	CFG *cfg;
	IRGenerator *irGenerator;
};
