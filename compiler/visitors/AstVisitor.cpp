
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "AstVisitor.h"
#include "../symbols-management/type.h"
#include "../ast/instructions/Block.h"
#include "../ast/instructions/Func.h"
#include "../ast/instructions/Instr.h"
#include "../ast/instructions/While.h"
#include "../ast/instructions/If.h"
#include "../ast/instructions/For.h"
#include "../ast/instructions/Ret.h"
#include "../ast/instructions/Aff.h"
#include "../ast/instructions/FuncCall.h"
#include "../ast/instructions/ArrAff.h"
#include "../ast/expressions/Expr.h"
#include "../ast/expressions/VarExpr.h"
#include "../ast/expressions/ArrExpr.h"
#include "../ast/expressions/ConstExpr.h"
#include "../ast/expressions/CharExpr.h"
#include "../ast/expressions/Not.h"
#include "../ast/expressions/operator/BinOp.h"
#include "../ast/expressions/operator/UnOp.h"
#include "../ast/expressions/bitwise/AndBitwise.h"
#include "../ast/expressions/bitwise/OrBitwise.h"
#include "../ast/expressions/bitwise/XorBitwise.h"
#include "../ast/expressions/comparison/EqualCompare.h"
#include "../ast/expressions/comparison/InfCompare.h"
#include "../ast/expressions/comparison/NotEqualCompare.h"
#include "../ast/expressions/comparison/SupCompare.h"
#include "../ast/expressions/logic/LogicalAnd.h"
#include "../ast/expressions/logic/LogicalOr.h"
#include <type_traits>

AstVisitor::AstVisitor(Ast *ast, SymbolTable *symbolTable) : BaseVisitor(), ast(ast), symbolTable(symbolTable)
{
	symbolTable->reinitRun();
}

antlrcpp::Any AstVisitor::visitAxiom(ifccParser::AxiomContext *ctx)
{
	returnCode = (int)visitChildren(ctx);
	return returnCode;
}

antlrcpp::Any AstVisitor::visitProg(ifccParser::ProgContext *ctx)
{
	vector<ifccParser::FuncContext *> func = ctx->func();

	for (int i = 0; i < func.size(); ++i)
	{
		Node *node = (Node *)visit(func[i]);
		ast->addNode(node);
	}
	return 0;
}

antlrcpp::Any AstVisitor::visitFunc(ifccParser::FuncContext *context)
{
	vector<antlr4::tree::TerminalNode *> types = context->TYPE();
	vector<antlr4::tree::TerminalNode *> names = context->NAME();
	string functionType = types[0]->getText();
	string functionName = names[0]->getText();

	symbolTable->getNextInnerContext();

	Block *block = (Block *)visit(context->block());

	symbolTable->closeContext();

	Func *func = new Func(getSymbolTypeFromString(functionType), functionName, block);

	return (Node *)func;
}

antlrcpp::Any AstVisitor::visitBlock(ifccParser::BlockContext *context)
{
	Context *symbContext = symbolTable->getNextInnerContext();
	Block *block = new Block(symbContext);
	int res = 0;

	vector<ifccParser::InstrContext *> instr = context->instr();
	vector<ifccParser::InstrContext *>::iterator it;

	for (it = instr.begin(); it != instr.end(); ++it)
	{
		auto visited = visit(*it);
		//cout << "visited: " <<  typeid(visited).name() << endl;
		if (visited.is<Instr *>())
		{
			//cout << "addInstr" << endl;
			block->addInstr((Instr *)visited);
		}
		else if (visited.is<vector<Instr *>>())
		{
			vector<Instr *> v_aff = visited.as<vector<Instr *>>();
			//cout << "addInstr2" << endl;
			for (int i = 0; i < v_aff.size(); ++i)
			{
				block->addInstr(v_aff[i]);
				//cout << "addInstr3" << endl;
			}
		}
	}

	symbolTable->closeContext();
	return block;
}

antlrcpp::Any AstVisitor::visitInstr(ifccParser::InstrContext *context)
{
	Instr *instr;
	if (context->funccall())
	{
		instr = (Instr *)visit(context->funccall());
	}
	else if (context->vardefaff())
	{
		return visit(context->vardefaff());
	}
	else if(context->arraydef())
	{
		auto inst = visit(context->arraydef());
		return inst;
	}
	else if(context->arraydefaff())
	{
		return visit(context->arraydefaff());
	}
	else
	{
		instr = visitChildren(context);
	}
	return instr;

}

antlrcpp::Any AstVisitor::visitWhiledef(ifccParser::WhiledefContext *context)
{
	Expr *expr = (Expr *)visit(context->expr());
	Block *b = (Block *)visit(context->block());
	Instr *w = new While(expr, b);
	return w;
}

antlrcpp::Any AstVisitor::visitIfdef(ifccParser::IfdefContext *context)
{
	Expr *expr = (Expr *)visit(context->expr());
	Block *bIf = (Block *)visit(context->block());
	Block *bElse = context->elsedef() == nullptr ? nullptr : (Block *)visit(context->elsedef());
	Instr *i = new If(expr, bIf, bElse);
	return i;
}

antlrcpp::Any AstVisitor::visitElsedef(ifccParser::ElsedefContext *context)
{
	return visit(context->block());
}

antlrcpp::Any AstVisitor::visitFordef(ifccParser::FordefContext *context)
{
	Expr *init = (Expr *)visit(context->expr(0));
	Expr *condition = (Expr *)visit(context->expr(1));
	Expr *progression = (Expr *)visit(context->expr(2));
	Block *b = (Block *)visit(context->block());
	Instr *f = new For(init, condition, progression, b);
	return f;
}

antlrcpp::Any AstVisitor::visitFunc_return(ifccParser::Func_returnContext *context)
{
	Expr *expr = (Expr *)visit(context->expr());
	Instr *ret = new Ret(expr);
	return ret;
}

antlrcpp::Any AstVisitor::visitVardefaff(ifccParser::VardefaffContext *context)
{
	string varType = context->TYPE()->getText();
	string varName = context->NAME()->getText();

	vector<Instr *> v_aff;
	if (context->expr() != nullptr)
	{
		Expr *expr = (Expr *)visit(context->expr());
		Instr *aff = new Aff(varName, expr, getSymbolTypeFromString(varType));
		v_aff.push_back(aff);
	}
	vector<ifccParser::VirgulenameContext *> virgulename = context->virgulename();
	vector<ifccParser::VirgulenameContext *>::iterator it;

	for (it = virgulename.begin(); it != virgulename.end(); ++it)
	{
		Instr *aff_vn = (Instr *)visit(*it);
		if (aff_vn != nullptr)
		{
			v_aff.push_back(aff_vn);
		}
	}

	return v_aff;
}

antlrcpp::Any AstVisitor::visitVirgulename(ifccParser::VirgulenameContext *context)
{
	string varName = context->NAME()->getText();
	Instr *aff = nullptr;
	if (context->expr() != nullptr)
	{
		Expr *expr = (Expr *)visit(context->expr());
		VarSymbol *vs = (VarSymbol *)symbolTable->getSymbol(varName);
		aff = new Aff(varName, expr, vs->getVarType());
	}
	return aff;
}

antlrcpp::Any AstVisitor::visitVaraff(ifccParser::VaraffContext *context)
{
	string varName = context->NAME()->getText();
	Expr *expr = (Expr *)visit(context->expr());
	VarSymbol *vs = (VarSymbol *)symbolTable->getSymbol(varName);
	Instr *instr = new Aff(varName, expr, vs->getVarType());
	return instr;
}

antlrcpp::Any AstVisitor::visitFunccall(ifccParser::FunccallContext *context)
{
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
	Instr *i = fc;
	return i;
}

antlrcpp::Any AstVisitor::visitVirguleexpr(ifccParser::VirguleexprContext *context)
{
	return (Expr *)visit(context->expr());
}

antlrcpp::Any AstVisitor::visitExpr(ifccParser::ExprContext *context)
{
	vector<antlr4::tree::TerminalNode *> name = context->NAME();
	ifccParser::ExprsimpleContext *escontext = context->exprsimple();
	if (name.size() > 0)
	{
		//cout << "Has name" << endl;
		if (escontext != nullptr)
		{
			//cout << "Has escontext" << endl;
			Expr *expr = (Expr *)visit(escontext);
			VarSymbol *vs = (VarSymbol *)symbolTable->getSymbol(name[name.size() - 1]->getText());
			Expr *aff = new Aff(name[name.size() - 1]->getText(), expr, vs->getVarType());
			for (int i = name.size() - 2; i >= 0; --i)
			{
				vs = (VarSymbol *)symbolTable->getSymbol(name[i]->getText());
				aff = new Aff(name[i]->getText(), aff, vs->getVarType());
			}
			return aff;
		}
		else
		{
			if (name.size() == 1)
			{
			    VarSymbol* vs = (VarSymbol*)symbolTable->getSymbol(name[name.size() - 1]->getText());
				Expr *expr = new VarExpr(vs->getVarType(), name[name.size() - 1]->getText());
				return expr;
			}
			else
			{
				VarSymbol *vs = (VarSymbol *)symbolTable->getSymbol(name[name.size() - 2]->getText());
				Expr *aff = new Aff(name[name.size() - 2]->getText(), new VarExpr(vs->getVarType(), name[name.size() - 1]->getText()), vs->getVarType());
				for (int i = name.size() - 3; i >= 0; --i)
				{
					vs = (VarSymbol *)symbolTable->getSymbol(name[i]->getText());
					aff = new Aff(name[i]->getText(), aff, vs->getVarType());
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

antlrcpp::Any AstVisitor::visitPar(ifccParser::ParContext *context)
{
	return visit(context->exprsimple());
}

antlrcpp::Any AstVisitor::visitConst(ifccParser::ConstContext *context)
{
	string value = context->CONST()->getText();
	Expr *constExpr = new ConstExpr(value, INT_32);
	return constExpr;
}

antlrcpp::Any AstVisitor::visitName(ifccParser::NameContext *context)
{
	string varName = context->NAME()->getText();
	VarSymbol* vs = (VarSymbol*)symbolTable->getSymbol(varName);
	Expr *expr = new VarExpr(vs->getVarType(), varName);
	return expr;
}

antlrcpp::Any AstVisitor::visitFunctioncall(ifccParser::FunctioncallContext *ctx)
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

antlrcpp::Any AstVisitor::visitAffecsimple(ifccParser::AffecsimpleContext *context)
{
	string varName = context->NAME()->getText();
	Expr *expr = (Expr *)visit(context->exprsimple());
	VarSymbol *vs = (VarSymbol *)symbolTable->getSymbol(varName);
	Expr *aff = new Aff(varName, expr, vs->getVarType());
	return aff;
}

antlrcpp::Any AstVisitor::visitNegative(ifccParser::NegativeContext *context)
{
	Expr *expr = (Expr *)visit(context->exprsimple());
	Expr *up = new UnOp(expr, Expr::NEGL);
	return up;
}

antlrcpp::Any AstVisitor::visitMultdiv(ifccParser::MultdivContext *context)
{
	bool isMult = visit(context->binopmd());
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *bo;
	if (isMult)
	{
		bo = new BinOp(expr0, expr1, Expr::MULT);
	}
	else
	{
		bo = new BinOp(expr0, expr1, Expr::DIV);
	}
	return bo;
}

antlrcpp::Any AstVisitor::visitPlusmoins(ifccParser::PlusmoinsContext *context)
{
	bool isPlus = visit(context->binoppm());
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *bo;
	if (isPlus)
	{
		bo = new BinOp(expr0, expr1, Expr::ADD);
	}
	else
	{
		bo = new BinOp(expr0, expr1, Expr::SUBS);
	}
	return bo;
}

antlrcpp::Any AstVisitor::visitBinoppm(ifccParser::BinoppmContext *context)
{
	bool isPlus = context->getText() == "+";
	return isPlus;
}

antlrcpp::Any AstVisitor::visitBinopmd(ifccParser::BinopmdContext *context)
{
	bool isMult = context->getText() == "*";
	return isMult;
}

antlrcpp::Any AstVisitor::visitAffecchar(ifccParser::AffeccharContext *context)
{
	string charValue = context->CHARAC()->getText();
	charValue = charValue.substr(1, 1);
	Expr *charExpr = new CharExpr(charValue);
	return charExpr;
}

antlrcpp::Any AstVisitor::visitAndbitwise(ifccParser::AndbitwiseContext *context)
{
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *abw = new AndBitwise(expr0, expr1);
	return abw;
}

antlrcpp::Any AstVisitor::visitOrbitwise(ifccParser::OrbitwiseContext *context)
{
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *obw = new OrBitwise(expr0, expr1);
	return obw;
}

antlrcpp::Any AstVisitor::visitXorbitwise(ifccParser::XorbitwiseContext *context)
{
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *xbw = new XorBitwise(expr0, expr1);
	return xbw;
}

antlrcpp::Any AstVisitor::visitInfcompare(ifccParser::InfcompareContext *context)
{
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *icmp = new InfCompare(expr0, expr1);
	return icmp;
}

antlrcpp::Any AstVisitor::visitSupcompare(ifccParser::SupcompareContext *context)
{
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *scmp = new SupCompare(expr0, expr1);
	return scmp;
}
antlrcpp::Any AstVisitor::visitNotequalcompare(ifccParser::NotequalcompareContext *context)
{
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *necmp = new NotEqualCompare(expr0, expr1);
	return necmp;
}
antlrcpp::Any AstVisitor::visitEqualcompare(ifccParser::EqualcompareContext *context)
{
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *ecmp = new EqualCompare(expr0, expr1);
	return ecmp;
}

antlrcpp::Any AstVisitor::visitLogicalAND(ifccParser::LogicalANDContext *context)
{
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *eland = new LogicalAND(expr0, expr1);
	return eland;
}

antlrcpp::Any AstVisitor::visitLogicalOR(ifccParser::LogicalORContext *context)
{
	Expr *expr0 = (Expr *)visit(context->exprsimple(0));
	Expr *expr1 = (Expr *)visit(context->exprsimple(1));
	Expr *elor = new LogicalOR(expr0, expr1);
	return elor;
}

antlrcpp::Any AstVisitor::visitNot(ifccParser::NotContext *context)
{
	Expr *expr = (Expr *)visit(context->exprsimple());
	Expr *up = new Not(expr);
	return up;
}

/* Visit Array */
antlrcpp::Any AstVisitor::visitArraydef(ifccParser::ArraydefContext *context)
{
	return nullptr;
}

antlrcpp::Any AstVisitor::visitArrayaff(ifccParser::ArrayaffContext *context)
{
	string arrName = context -> arrayaccess() -> NAME() -> getText();
	Expr* expr = (Expr*) visit(context->expr());
	Expr* index = (Expr*) visit(context->arrayaccess());
	Instr* instr = new ArrAff(arrName, index, expr);
	return instr;
}

antlrcpp::Any AstVisitor::visitArraydefaff(ifccParser::ArraydefaffContext *context)
{
	string arrType = context -> TYPE() -> getText();
	string arrName = context -> NAME() -> getText();
	vector<Instr*> arr_aff;
	int i = 0;
	int arrsize = ((ArrSymbol*)symbolTable->getSymbol(arrName))->getLength();
	if(context->arraycontent() != nullptr)
	{
		vector<Expr*> exprs = visit(context->arraycontent());
		vector<Expr*>::iterator it;
		int index = 0;
		for(it = exprs.begin() ; it!=exprs.end() && i<arrsize ; ++it)
		{
			Expr * cur_index = new ConstExpr(to_string(index++), INT_32);
			Instr* instr = new ArrAff(arrName, cur_index,*it);
			arr_aff.push_back(instr);
			i++;
		}
	}

	return arr_aff;
}

antlrcpp::Any AstVisitor::visitArraycontent(ifccParser::ArraycontentContext *context)
{
	vector<Expr*> exprs;
	vector<ifccParser::ExprContext*> expr = context->expr();
	vector<ifccParser::ExprContext*>::iterator it;
	for(it = expr.begin(); it != expr.end(); ++it)
	{
		auto visited = visit(*it);
		exprs.push_back((Expr*) visited);
	}
	return exprs;
}

antlrcpp::Any AstVisitor::visitArrayaccess(ifccParser::ArrayaccessContext *context)
{
	return visit(context->expr());
}

antlrcpp::Any AstVisitor::visitArrayexpr(ifccParser::ArrayexprContext *context) {
	string name = context->arrayaccess()->NAME()->getText();
	VarSymbol* varSymbol = (VarSymbol*)symbolTable->getSymbol(name);
	Expr* index = (Expr*) visit(context->arrayaccess());
	Expr* arrExpr = new ArrExpr(name, index, varSymbol->getVarType());
	return arrExpr;
}

int AstVisitor::getReturnCode()
{
	return returnCode;
}

antlrcpp::Any AstVisitor::aggregateResult(antlrcpp::Any aggregate, const antlrcpp::Any &nextResult)
{
	return nextResult;
}
