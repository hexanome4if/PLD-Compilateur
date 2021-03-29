
// Generated from ifcc.g4 by ANTLR 4.7.2

#include "visitor.h"

Visitor::Visitor(Ast* ast)
				: ast(ast)
{
				symbolTable = SymbolTable();
}

antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *ctx)
{
				returnCode = (int)visitChildren(ctx);
				return returnCode;
}
antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx)
{
				int res = 0;
				vector<ifccParser::FuncContext *> func = ctx->func();
				vector<ifccParser::FuncContext *>::iterator it;

				for (it = func.begin(); it != func.end(); ++it)
				{
								res += (int)visit(*it);
				}
				return res > 0 ? 1 : 0;
}

antlrcpp::Any Visitor::visitFunc(ifccParser::FuncContext *context)
{
				string functionType = context->TYPE()->getText();
				string functionName = context->NAME()->getText();

				Block block = (Block)visitChildren(context);
				Func func = Func(getTypeFromString(functionType), functionName, block);

				return func;
}

antlrcpp::Any Visitor::visitBlock(ifccParser::BlockContext *context)
{
				Context* context = symbolTable.openContext();
				Block block = Block(context);
				int res = 0;

				vector<ifccParser::InstrContext *> instr = context->instr();
				vector<ifccParser::InstrContext *>::iterator it;

				for (it = instr.begin(); it != instr.end(); ++it)
				{
								Instr* visited = visit(*it);
								if (visited != nullptr) block.addInstr(*visited);

				}

				symbolTable.closeContext();
				return block;
}

antlrcpp::Any Visitor::visitInstr(ifccParser::InstrContext *context)
{
				Inst* instr = (Instr*) visitChildren(context);
				return instr;
}

antlrcpp::Any Visitor::visitWhiledef(ifccParser::WhiledefContext *context) {
				Expr expr = visit(context->expr());
				if (expr == nullptr) return nullptr;
				Block b = visit(context->block());
				While w = While(expr,b);
				return w;
}

antlrcpp::Any Visitor::visitIfdef(ifccParser::IfdefContext *context) {
				Expr expr = visit(context->expr());
				if (expr == nullptr) return nullptr;
				Block bIf = visit(context->block());
				Block bElse = context->elsedef() == nullptr ? Block() : visit(context->elsedef()); //TODO changer en pointeur plus tards nullptr
				If i = If(expr,b);
				return w;
}

antlrcpp::Any Visitor::visitElsedef(ifccParser::ElsedefContext *context) {
				return visit(context->block());
}

antlrcpp::Any Visitor::visitFordef(ifccParser::FordefContext *context) {
				Expr init = visit(context->expr(0));
				if (init == nullptr) return nullptr;
				Expr condition = visit(context->expr(1));
				if (condition == nullptr) return nullptr;
				Expr progression = visit(context->expr(2));
				if (progression == nullptr) return nullptr;
				Block b = visit(context->block());
				For f = For(init,condition,progression,b);
}


antlrcpp::Any Visitor::visitFunc_return(ifccParser::Func_returnContext *context)
{
				Expr expr = visit(context->expr());
				if (expr == nullptr) return nullptr;
				Ret* ret = new Ret(expr);
				return ret;
}

antlrcpp::Any Visitor::visitVardefaff(ifccParser::VardefaffContext *context)
{
				string varType = context->TYPE()->getText();
				string varName = context->NAME()->getText();

				if (symbolTable.symbolExists(varName))
				{
								// ERROR here
								cerr << "Variable " << varName << " already defined." << endl;
								return nullptr;
				}

				// Add the variable in the symbol table
				Expr expr = visit(context->expr());
				if (expr == nullptr) return nullptr;
				symbolTable.addSymbol(varName, varType);
				Aff* aff = new Aff(varName, expr);
				return aff;
}

antlrcpp::Any Visitor::visitVardef(ifccParser::VardefContext *context)
{
				string varType = context->TYPE()->getText();
				string varName = context->NAME()->getText();

				if (symbolTable.symbolExists(varName))
				{
								// ERROR here
								cerr << "Variable " << varName << " already defined." << endl;
								return nullptr;
				}

				// Add the variable in the symbol table
				Symbol *symbol = symbolTable.addSymbol(varName, varType);

				vector<ifccParser::VirgulenameContext *> virgulename = context->virgulename();
				vector<ifccParser::VirgulenameContext *>::iterator it;

				for (it = virgulename.begin(); it != virgulename.end(); ++it)
				{
								string varname = visit(*it);

								if (symbolTable.symbolExists(varname))
								{
												// ERROR here
												cerr << "Variable " << varName << " already defined." << endl;
												return nullptr;
								}

								// Add the variable in the symbol table
								symbol = symbolTable.addSymbol(varname, varType);
				}

				return nullptr;
}

antlrcpp::Any Visitor::visitVirgulename(ifccParser::VirgulenameContext *context)
{
				return context->NAME()->getText();
}

antlrcpp::Any Visitor::visitVaraff(ifccParser::VaraffContext *context)
{
				string varName = context->NAME()->getText();
				Expr expr = (Expr) visit(context->expr());
				if (expr == nullptr)
								return nullptr;
				if (!symbolTable.symbolExists(varName))
				{
								cerr << "Undefined variable named '" << varName << "'" << endl;
								return nullptr;
				}

				return new Aff(varName, expr);
}

antlrcpp::Any Visitor::visitFunccall(ifccParser::FunccallContext *context){
				string funcName = context->NAME()->getText();
				FunCall fc = FuncCall(funcName);
				if(context->expr() != nullptr) {
								fc.addParam((Expr) visit(context->expr()));
								vector<ifccParser::VirguleexprContext *> virguleexpr = context->virguleexpr();
								vector<ifccParser::VirguleexprContext *>::iterator it;
								for (it = virguleexpr.begin(); it != virguleexpr.end(); ++it)
								{
												fc.addParam((Expr) visit(*it));
								}
				}
				return fc;
}


antlrcpp::Any Visitor::visitVirguleexpr(ifccParser::VirguleexprContext *context){
				return (Expr) visit(context->expr());
}

antlrcpp::Any Visitor::visitExpr(ifccParser::ExprContext *context) {
				vector<antlr4::tree::TerminalNode *> name = context->NAME();
				ifccParser::ExprsimpleContext* escontext = context->exprsimple();
				if(name.size()>0) {
								if(escontext != nullptr) {
												Expr expr = visit(escontext);
												Aff* aff = new Aff(name[name.size()-1],expr);
												for (int i=name.size()-2; i>=0; --i) {
																aff = new Aff(name[i],*aff);
												}
												return aff;
								}else{
												Aff* aff = new Aff(name[name.size()-2],VarExpr(name[name.size()-1]));
												for (int i=name.size()-3; i>=0; --i) {
																aff = new Aff(name[i],*aff);
												}
												return aff;
								}

				}else{
								return visit(escontext);
				}
}

antlrcpp::Any Visitor::visitPar(ifccParser::ParContext *context)
{
				return visit(context->expr());
}

antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *context)
{
				string value = context->CONST()->getText();
				return new ConstExpr(value);
}

antlrcpp::Any Visitor::visitName(ifccParser::NameContext *context)
{
				string varName = context->NAME()->getText();
				if (!symbolTable.symbolExists(varName))
				{
								cerr << "Undefined variable named '" << varName << "'" << endl;
								return nullptr;
				}

				return new VarExpr(varName);
}

antlrcpp::Any Visitor::visitFunctioncall(ifccParser::FunctioncallContext *context) {

}

antlrcpp::Any Visitor::visitAffecsimple(ifccParser::AffecsimpleContext *context) {

}

antlrcpp::Any Visitor::visitNegative(ifccParser::NegativeContext *context)
{
				Expr expr = (Expr) visit(context->exprsimple());
				UnOp up = UnOp(expr, NEGL);
				if (expr== nullptr) return nullptr;
				Symbol *temp = symbolTable.addTempSymbol("int", "0");
				cout << "   movl	-"<< expr->getMemoryAddress() << "(%rbp), %eax\n";
				cout << "   negl %eax\n";
				cout << "   movl %eax, -" << temp->getMemoryAddress() << "(%rbp)\n";
				return temp;
}

antlrcpp::Any Visitor::visitMultdiv(ifccParser::MultdivContext *context)
{
				bool isMult = visit(context->binopmd());
				Symbol *expr0 = visit(context->expr(0));
				Symbol *expr1 = visit(context->expr(1));
				if (expr0 == nullptr || expr1 == nullptr)
								return nullptr;
				Symbol *temp = symbolTable.addTempSymbol("int", "0");

				if (isMult) {
								cout << "   movl	-"<< expr0->getMemoryAddress() << "(%rbp), %edx\n";
								cout << "   movl	-"<< expr1->getMemoryAddress() << "(%rbp), %eax\n";
								cout << "   imull	%edx, %eax\n";
								cout << "   movl	%eax, -"<< temp->getMemoryAddress() << "(%rbp)" << endl;
				} else {
								cout << "   movl	-"<< expr0->getMemoryAddress() << "(%rbp), %eax\n";
								cout << "   cltd\n";
								cout << "   idivl -" << expr1->getMemoryAddress() << "(%rbp)\n";
								cout << "   movl	%eax, -"<< temp->getMemoryAddress() << "(%rbp)" << endl;
				}
				return temp; antlrcpp::Any visitAffecsimple(ifccParser::AffecsimpleContext *context)

}

antlrcpp::Any Visitor::visitPlusmoins(ifccParser::PlusmoinsContext *context)
{
				bool isPlus = visit(context->binoppm());
				Symbol *expr0 = visit(context->expr(0));
				Symbol *expr1 = visit(context->expr(1));
				if (expr0 == nullptr || expr1 == nullptr) return nullptr;
				Symbol *temp = symbolTable.addTempSymbol("int", "0");

				if (isPlus) {
								cout << "   movl	-"<< expr0->getMemoryAddress() << "(%rbp), %edx\n";
								cout << "   movl	-"<< expr1->getMemoryAddress() << "(%rbp), %eax\n";
								cout << "   addl	%edx, %eax\n";
								cout << "   movl	%eax, -"<< temp->getMemoryAddress() << "(%rbp)" << endl;

				} else {
								cout << "   movl	-"<< expr0->getMemoryAddress() << "(%rbp), %eax\n";
								cout << "   movl	-"<< expr1->getMemoryAddress() << "(%rbp), %edx\n";
								cout << "   subl	%edx, %eax\n";
								cout << "   movl	%eax, -"<< temp->getMemoryAddress() << "(%rbp)" << endl;
				}

				return temp;
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
