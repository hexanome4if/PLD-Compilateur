
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

TypeName getTypeFromString(string string_type)
{
	if (string_type == "int")
	{
		return int32;
	}
	return int32; //TODO ajouter char
}

Visitor::Visitor(Ast *ast, SymbolTable *symbolTable) : ast(ast), symbolTable(symbolTable)
{
	symbolTable->reinitRun();
}

antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *ctx)
{
	returnCode = (int)visitChildren(ctx);
	return returnCode;
}

antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx)
{
	vector<ifccParser::FuncContext *> func = ctx->func();

	for (int i = 0; i < func.size(); ++i)
	{
		Node *node = (Node *)visit(func[i]);
		ast->addNode(node);
	}
	return 0;
}

antlrcpp::Any Visitor::visitFunc(ifccParser::FuncContext *context)
{
	string functionType = context->TYPE()->getText();
	string functionName = context->NAME()->getText();

	Block *block = (Block *)visit(context->block());
	Node *func = new Func(getTypeFromString(functionType), functionName, block);

	return func;
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *context)
{
	Context *symbContext = symbolTable->getNextInnerContext();
	Block *block = new Block(symbContext);
	int res = 0;

	vector<ifccParser::InstrContext *> instr = context->instr();
	vector<ifccParser::InstrContext *>::iterator it;

	for (it = instr.begin(); it != instr.end(); ++it)
	{
		auto visited = visit(*it);
		if (visited.is<Instr *>())
		{
			block->addInstr((Instr *)visited);
		}
	}

	symbolTable->closeContext();
	return block;
}

antlrcpp::Any Visitor::visitInstr(ifccParser::InstrContext *context)
{
	cout << "Instr" << endl;
	Instr *instr;
	if (context->funccall())
	{
		instr = (Instr *)visit(context->funccall());
	}
	else if (context->vardef())
	{
		visit(context->vardef());
		return nullptr;
	}
	else
	{
		instr = visitChildren(context);
	}
	// Instr *instr = (Instr *)visitChildren(context);
	cout << "End instr" << endl;
	return instr;
}

antlrcpp::Any Visitor::visitWhiledef(ifccParser::WhiledefContext *context)
{
	Expr *expr = (Expr *)visit(context->expr());
	Block *b = (Block *)visit(context->block());
	Instr *w = new While(expr, b);
	return w;
}

antlrcpp::Any Visitor::visitIfdef(ifccParser::IfdefContext *context)
{
	Expr *expr = (Expr *)visit(context->expr());
	Block *bIf = (Block *)visit(context->block());
	Block *bElse = context->elsedef() == nullptr ? nullptr : (Block *)visit(context->elsedef());
	Instr *i = new If(expr, bIf, bElse);
	return i;
}

antlrcpp::Any Visitor::visitElsedef(ifccParser::ElsedefContext *context)
{
	return visit(context->block());
}

antlrcpp::Any Visitor::visitFordef(ifccParser::FordefContext *context)
{
	Expr *init = (Expr *)visit(context->expr(0));
	Expr *condition = (Expr *)visit(context->expr(1));
	Expr *progression = (Expr *)visit(context->expr(2));
	Block *b = (Block *)visit(context->block());
	Instr *f = new For(init, condition, progression, b);
	return f;
}

antlrcpp::Any Visitor::visitFunc_return(ifccParser::Func_returnContext *context)
{
	Expr *expr = (Expr *)visit(context->expr());
	Instr *ret = new Ret(expr);
	return ret;
}

antlrcpp::Any Visitor::visitVardefaff(ifccParser::VardefaffContext *context)
{
	cout << "Var def aff" << endl;
	string varType = context->TYPE()->getText();
	string varName = context->NAME()->getText();

	Expr *expr = (Expr *)visit(context->expr());
	Instr *aff = new Aff(varName, expr);
	cout << "End var def aff" << endl;
	return aff;
}

// TODO for now we could remove this
antlrcpp::Any Visitor::visitVardef(ifccParser::VardefContext *context)
{
	cout << "Var def" << endl;
	string varType = context->TYPE()->getText();
	string varName = context->NAME()->getText();

	vector<ifccParser::VirgulenameContext *> virgulename = context->virgulename();
	vector<ifccParser::VirgulenameContext *>::iterator it;

	for (it = virgulename.begin(); it != virgulename.end(); ++it)
	{
		string varname = visit(*it);
	}

	cout << "End var def" << endl;
	return nullptr;
}

antlrcpp::Any Visitor::visitVirgulename(ifccParser::VirgulenameContext *context)
{
	return context->NAME()->getText();
}

antlrcpp::Any Visitor::visitVaraff(ifccParser::VaraffContext *context)
{
	string varName = context->NAME()->getText();
	Expr *expr = (Expr *)visit(context->expr());

	Instr *instr = new Aff(varName, expr);
	return instr;
}

antlrcpp::Any Visitor::visitFunccall(ifccParser::FunccallContext *context)
{
	cout << "Func call" << endl;
	string funcName = context->NAME()->getText();
	FuncCall *fc = new FuncCall(funcName);
	if (context->expr() != nullptr)
	{
		fc->addParam((Expr *)visit(context->expr()));
		vector<ifccParser::VirguleexprContext *> virguleexpr = context->virguleexpr();
		vector<ifccParser::VirguleexprContext *>::iterator it;
		for (it = virguleexpr.begin(); it != virguleexpr.end(); ++it)
		{
			fc->addParam((Expr *)visit(*it));
		}
	}
	cout << "End func call" << endl;
	Instr *i = fc;
	return i;
}

antlrcpp::Any Visitor::visitVirguleexpr(ifccParser::VirguleexprContext *context)
{
	return (Expr *)visit(context->expr());
}

antlrcpp::Any Visitor::visitExpr(ifccParser::ExprContext *context)
{
	cout << "Expr" << endl;
	vector<antlr4::tree::TerminalNode *> name = context->NAME();
	ifccParser::ExprsimpleContext *escontext = context->exprsimple();
	if (name.size() > 0)
	{
		cout << "Has name" << endl;
		if (escontext != nullptr)
		{
			cout << "Has escontext" << endl;
			Expr *expr = (Expr *)visit(escontext);
			Expr *aff = new Aff(name[name.size() - 1]->getText(), expr);
			for (int i = name.size() - 2; i >= 0; --i)
			{
				aff = new Aff(name[i]->getText(), aff);
			}
			return aff;
		}
		else
		{
			if (name.size() == 1)
			{
				Expr *expr = new VarExpr(name[name.size() - 1]->getText());
				return expr;
			}
			else
			{
				Expr *aff = new Aff(name[name.size() - 2]->getText(), new VarExpr(name[name.size() - 1]->getText()));
				for (int i = name.size() - 3; i >= 0; --i)
				{
					aff = new Aff(name[i]->getText(), aff);
				}
				return aff;
			}
		}
	}
	else
	{
		Expr *var = (Expr *)visit(escontext);
		return var;
	}
}

antlrcpp::Any Visitor::visitPar(ifccParser::ParContext *context)
{
	return visit(context->exprsimple());
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *context)
{
	string value = context->CONST()->getText();
	Expr *constExpr = new ConstExpr(value);
	return constExpr;
}

antlrcpp::Any Visitor::visitName(ifccParser::NameContext *context)
{
	string varName = context->NAME()->getText();
	Expr *expr = new VarExpr(varName);
	return expr;
}

antlrcpp::Any Visitor::visitFunctioncall(ifccParser::FunctioncallContext *ctx)
{
	ifccParser::FunccallContext *context = ctx->funccall();
	string funcName = context->NAME()->getText();
	FuncCall *fc = new FuncCall(funcName);
	if (context->expr() != nullptr)
	{
		fc->addParam((Expr *)visit(context->expr()));
		vector<ifccParser::VirguleexprContext *> virguleexpr = context->virguleexpr();
		vector<ifccParser::VirguleexprContext *>::iterator it;
		for (it = virguleexpr.begin(); it != virguleexpr.end(); ++it)
		{
			fc->addParam((Expr *)visit(*it));
		}
	}
	Expr *e = fc;
	return e;
}

antlrcpp::Any Visitor::visitAffecsimple(ifccParser::AffecsimpleContext *context)
{
	string varName = context->NAME()->getText();
	Expr *expr = (Expr *)visit(context->exprsimple());
	Expr *aff = new Aff(varName, expr);
	return aff;
}

antlrcpp::Any Visitor::visitNegative(ifccParser::NegativeContext *context)
{
	Expr *expr = (Expr *)visit(context->exprsimple());
	Expr *up = new UnOp(expr, NEGL);
	return up;
}

antlrcpp::Any Visitor::visitMultdiv(ifccParser::MultdivContext *context)
{
	bool isMult = visit(context->binopmd());
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *bo;
	if (isMult)
	{
		bo = new BinOp(expr0, expr1, MULT);
	}
	else
	{
		bo = new BinOp(expr0, expr1, DIV);
	}
	return bo;
}

antlrcpp::Any Visitor::visitPlusmoins(ifccParser::PlusmoinsContext *context)
{
	bool isPlus = visit(context->binoppm());
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *bo;
	if (isPlus)
	{
		bo = new BinOp(expr0, expr1, ADD);
	}
	else
	{
		bo = new BinOp(expr0, expr1, SUBS);
	}
	return bo;
}

antlrcpp::Any Visitor::visitBinoppm(ifccParser::BinoppmContext *context)
{
	bool isPlus = context->getText() == "+";
	return isPlus;
}

antlrcpp::Any Visitor::visitBinopmd(ifccParser::BinopmdContext *context)
{
	bool isMult = context->getText() == "*";
	return isMult;
}

int Visitor::getReturnCode()
{
	return returnCode;
}

antlrcpp::Any Visitor::aggregateResult(antlrcpp::Any aggregate, const antlrcpp::Any &nextResult)
{
	return nextResult;
}
