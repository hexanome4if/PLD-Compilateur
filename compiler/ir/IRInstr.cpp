#include "IRInstr.h"
#include "BasicBlock.h"

/** IRInstr **/

IRInstr::IRInstr(BasicBlock *bb_, Operation operation, TypeName type, vector<string> params_)
{

				bb = bb_;
				op = operation;
				t = type;
				params = params_;
}

bool IRInstr::hasFunctionCall()
{
				if (op == IRInstr::CALL)
				{
								return true;
				}

				return false;
}
