#include "IRGenerator.h"
#include "../../ast/Ast.h"

IRGenerator::IRGenerator(Ast *ast, CFG *cfg, SymbolTable *symbolTable) : ast(ast), cfg(cfg), symbolTable(symbolTable)
{
	instrGenerator = new IRInstrGenerator(this);
	blockGenerator = new IRBlockGenerator(cfg, this);

	exprGenerator = new IRExprGenerator(this);
	operatorGenerator = new IROperatorGenerator(this);
}

void IRGenerator::generate()
{
	vector<Node *> nodes = ast->getNodes();
	for (int i = 0; i < nodes.size(); ++i)
	{
		genNode(nodes[i]);
	}
}

void IRGenerator::genNode(Node *node)
{
	switch (node->getNodeType())
	{
	case Node::FUNCTION:
		blockGenerator->genFunc((Func *)node);
		break;
	case Node::INSTRUCTION:
		genInstruction((Instr *)node);
		break;
	}
}

void IRGenerator::genBlock(Block *block)
{
	symbolTable->setCurrentContext(block->getContext());
	setCurrentContext(block->getContext());
	vector<Instr *> instrs = block->getInstrs();
	for (int i = 0; i < instrs.size(); i++)
	{
		genInstruction(instrs[i]);
	}
	symbolTable->setCurrentContext(block->getContext()->getParentContext());
}

void IRGenerator::genInstruction(Instr *instruction)
{
	switch (instruction->getInstrType())
	{
	case Instr::AFF:
		instrGenerator->genAff((Aff *)instruction);
		break;
	case Instr::FUNCCALL:
		instrGenerator->genFuncCall((FuncCall *)instruction);
		break;
	case Instr::RETURN:
		instrGenerator->genRet((Ret *)instruction);
		break;
	case Instr::WHILE:
		blockGenerator->genWhile((While *)instruction);
		break;
	case Instr::FOR:
		blockGenerator->genFor((For *)instruction);
		break;
	case Instr::IF:
		blockGenerator->genIf((If *)instruction);
		break;
	case Instr::ARRAFF:
		instrGenerator->genArrAff((ArrAff*) instruction);
		break;
	}
}

string IRGenerator::genExpr(Expr *expr)
{
	switch (expr->getExprType())
	{
	case Expr::Type::AFF:
		return instrGenerator->genAff((Aff *)expr);
	case Expr::Type::BIN_OP:
		return operatorGenerator->genBin((BinOp *)expr);
	case Expr::Type::CONST:
		return exprGenerator->genConst((ConstExpr *)expr);
    case Expr::Type::CHAR:
        return exprGenerator->genChar((CharExpr *)expr);
	case Expr::Type::FUNC_CALL:
		return instrGenerator->genFuncCall((FuncCall *)expr);
	case Expr::Type::VAR:
		return exprGenerator->genVar((VarExpr *)expr);
	case Expr::Type::UN_OP:
		return operatorGenerator->genUn((UnOp *)expr);
	case Expr::Type::ARRAFF:
		return exprGenerator -> genArrExpr((ArrExpr*)expr);
	}
	return "";
}

string IRGenerator::createTempVar(TypeName type)
{
	Symbol *s = symbolTable->addTempSymbol(type);
	return s->getName();
}
