#pragma once

#include "../../../ast/expressions/comparison/EqualCompare.h"
#include "../../../ast/expressions/comparison/InfCompare.h"
#include "../../../ast/expressions/comparison/NotEqualCompare.h"
#include "../../../ast/expressions/comparison/SupCompare.h"

#include "../../../ast/expressions/Not.h"

class IRGenerator;

class IRCompGenerator
{

public:
	IRCompGenerator(IRGenerator *generator) : generator(generator) {}
	
	string genEqual(EqualCompare *eq_cmp);
	string genInf(InfCompare *inf_cmp);
	string genNotEqual(NotEqualCompare *ne_cmp);
	string genSup(SupCompare *sup_cmp);

private:
	IRGenerator *generator;		
};
