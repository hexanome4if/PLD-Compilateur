#pragma once

#include "../../../ast/expressions/bitwise/AndBitwise.h"
#include "../../../ast/expressions/bitwise/OrBitwise.h"
#include "../../../ast/expressions/bitwise/XorBitwise.h"

class IRGenerator;

class IRBitwiseGenerator
{

public:

	IRBitwiseGenerator(IRGenerator *generator) : generator(generator) {}

	string genAnd(AndBitwise *b_and);
	string genOr(OrBitwise *b_or);
	string genXor(XorBitwise *b_xor);

private:
	IRGenerator *generator;
	
};
