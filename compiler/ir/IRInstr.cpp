#include "IRInstr.h"
#include "BasicBlock.h"

/** IRInstr **/

IRInstr::IRInstr(BasicBlock *bb_, Operation operation, string type, vector<string> params_)
{

	bb = bb_;
	op = operation;
	t = type;
	params = params_;
}
