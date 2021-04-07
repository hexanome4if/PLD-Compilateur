/*
#include "instr.h"
#include "IR.h"
*/
/* BuildIR for the expr */
/*
string BinOp ::buildIR(CFG *cfg)
{

	string var1 = expr1->buildIR(cfg);
	string var2 = expr2->buildIR(cfg);
	string var3 = cfg->create_new_tempvar("int32");
	IRInstr::Operation op;
	switch (operation)
	{
	case ADD:
		op = IRInstr::add;
		break;
	case MULT:
		op = IRInstr::mul;
		break;
	case DIV:
		op = IRInstr::div;
		break;
	case SUBS:
		op = IRInstr::sub;
		break;
	default:
		break;
	}
	vector<string> params;
	params.push_back(var3);
	params.push_back(var1);
	params.push_back(var2);
	cfg->current_bb->add_IRInstr(op, "int32", params);
	return var3;
}

string UnOp ::buildIR(CFG *cfg)
{
	Expr *zero = new ConstExpr("0");
	BinOp minus = BinOp(zero, expr, SUBS);
	string var = minus.buildIR(cfg);
	return var;
}

string ConstExpr ::buildIR(CFG *cfg)
{
	string var = cfg->create_new_tempvar("int32");
	vector<string> params;
	params.push_back(var);
	params.push_back(val);
	cfg->current_bb->add_IRInstr(IRInstr ::ldconst, "int32", params);
	return var;
}

string VarExpr ::buildIR(CFG *cfg)
{
	return varName;
}

string Block ::buildIR(CFG *cfg)
{
	cfg->symbolTable->setCurrentContext(context);
	for (int i = 0; i < instrs.size(); i++)
	{
		instrs[i]->buildIR(cfg);
	}
	cfg->symbolTable->setCurrentContext(context->getParentContext());
	return "BLOCK";
}

string Aff ::buildIR(CFG *cfg)
{
	string varExpr = expr->buildIR(cfg);
	vector<string> params;
	params.push_back(varId);
	params.push_back(varExpr);
	cfg->current_bb->add_IRInstr(IRInstr::copy, "int32", params);
	return varId;
}

string Ret ::buildIR(CFG *cfg)
{
	string varExpr = expr->buildIR(cfg);
	vector<string> params;
	params.push_back(varExpr);
	cfg->current_bb->add_IRInstr(IRInstr::ret, "int32", params);
	return varExpr;
}

string Func ::buildIR(CFG *cfg)
{
	//Générer prologue
	BasicBlock *prologue = new BasicBlock(cfg, cfg->new_BB_name(), block->context);
	BasicBlock *body = new BasicBlock(cfg, name, block->context);
	BasicBlock *epilogue = new BasicBlock(cfg, cfg->new_BB_name(), nullptr);
	cfg->add_bb(prologue);
	cfg->add_bb(body);
	cfg->add_bb(epilogue);

	vector<string> ir_params;
	ir_params.push_back(name);
	for (int i = 0; i < params.size(); ++i)
	{
		ir_params.push_back(params[i]);
	}
	prologue->add_IRInstr(IRInstr::prol, "notype", ir_params);

	//Générer la fonction
	prologue->exit_true = body;
	//cfg->add_bb(body);
	cfg->current_bb = body;
	body->exit_true = epilogue;
	block->buildIR(cfg);

	//Générer épilogue
	vector<string> empty;
	epilogue->add_IRInstr(IRInstr::epil, "notype", empty);
	//cfg->add_bb(epilogue);

	return "FUNCTION";
}

string FuncCall::buildIR(CFG *cfg)
{
	string ret_var = cfg->create_new_tempvar("int32");
	vector<string> ir_params;
	ir_params.push_back(funcName);
	ir_params.push_back(ret_var);
	for (int i = 0; i < params.size(); ++i)
	{
		string varExpr = params[i]->buildIR(cfg);
		ir_params.push_back(varExpr);
	}
	cfg->current_bb->add_IRInstr(IRInstr::call, "int32", ir_params);
	return ret_var;
}

string If::buildIR(CFG *cfg)
{
	BasicBlock *parentBlock = cfg->current_bb;
	BasicBlock *nextBlock = new BasicBlock(cfg, cfg->new_BB_name(), parentBlock->context);
	BasicBlock *testBlock = new BasicBlock(cfg, cfg->new_BB_name(), parentBlock->context);
	if (parentBlock->exit_true != nullptr)
	{
		nextBlock->exit_true = parentBlock->exit_true;
	}
	cfg->add_bb(testBlock);
	cfg->add_bb(nextBlock);
	parentBlock->exit_true = testBlock;
	cfg->current_bb = testBlock;
	string varCond = condition->buildIR(cfg);
	testBlock->test_var_name = varCond;
	BasicBlock *blockTrue = new BasicBlock(cfg, cfg->new_BB_name(), blockIf->context);
	cfg->add_bb(blockTrue);
	blockTrue->exit_true = nextBlock;
	cfg->current_bb = blockTrue;
	blockIf->buildIR(cfg);
	testBlock->exit_true = blockTrue;
	if (blockElse != nullptr)
	{
		BasicBlock *blockFalse = new BasicBlock(cfg, cfg->new_BB_name(), blockElse->context);
		cfg->add_bb(blockFalse);
		cfg->current_bb = blockFalse;
		blockFalse->exit_true = nextBlock;
		blockElse->buildIR(cfg);
		testBlock->exit_false = blockFalse;
	}
	else
	{
		testBlock->exit_false = nextBlock;
	}
	cfg->current_bb = nextBlock;
	return "IF";
}

string While::buildIR(CFG *cfg)
{
	BasicBlock *parentBlock = cfg->current_bb;
	BasicBlock *nextBlock = new BasicBlock(cfg, cfg->new_BB_name(), parentBlock->context);
	BasicBlock *testBlock = new BasicBlock(cfg, cfg->new_BB_name(), parentBlock->context);
	if (parentBlock->exit_true != nullptr)
	{
		nextBlock->exit_true = parentBlock->exit_true;
	}
	cfg->add_bb(testBlock);
	cfg->add_bb(nextBlock);
	parentBlock->exit_true = testBlock;
	cfg->current_bb = testBlock;
	string varCond = condition->buildIR(cfg);
	testBlock->test_var_name = varCond;
	BasicBlock *blockWhile = new BasicBlock(cfg, cfg->new_BB_name(), block->context);
	cfg->add_bb(blockWhile);
	blockWhile->exit_true = testBlock;
	cfg->current_bb = blockWhile;
	block->buildIR(cfg);
	testBlock->exit_true = blockWhile;
	testBlock->exit_false = nextBlock;
	cfg->current_bb = nextBlock;
	return "WHILE";
}
*/
