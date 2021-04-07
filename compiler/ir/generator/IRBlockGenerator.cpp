#include "IRBlockGenerator.h"

#include "IRGenerator.h"

void IRBlockGenerator::genFunc(Func *func)
{
				//Générer prologue
				BasicBlock *prologue = new BasicBlock(cfg, cfg->new_BB_name(), func->getBlock()->getContext());
				BasicBlock *body = new BasicBlock(cfg, func->getName(), func->getBlock()->getContext());
				BasicBlock *epilogue = new BasicBlock(cfg, cfg->new_BB_name(), func->getBlock()->getContext());

				cfg->add_bb(prologue);
				cfg->add_bb(body);
				cfg->add_bb(epilogue);

				bool hasFunctionCall = func->getBlock()->hasFunctionCall();
				int definedSymbolsSize = func->getBlock()->getContext()->getParentContext()->getTotalContextSize();

				vector<string> irParams;
				irParams.push_back(func->getName());
				irParams.push_back(hasFunctionCall ? "true" : "false");
				irParams.push_back(to_string(definedSymbolsSize));

				FuncSymbol* funcSymbol = (FuncSymbol*)func->getBlock()->getContext()->getSymbol(func->getName());
				vector<FuncSymbol::Param> params = funcSymbol->getParams();
				for (int i = 0; i < params.size(); ++i)
				{
								irParams.push_back(params[i].name);
								irParams.push_back(to_string(params[i].type));
				}

				prologue->add_IRInstr(IRInstr::PROLOG, VOID, irParams);

				//Générer la fonction
				prologue->setExitTrue(body);
				irGenerator->setCurrentBB(body);
				body->setExitTrue(epilogue);
				irGenerator->setCurrentFunc(func);
				irGenerator->genBlock(func->getBlock());
				irGenerator->setCurrentFunc(nullptr);

				//Générer épilogue
				irParams.clear();
				irParams.push_back(hasFunctionCall ? "true" : "false");
				irParams.push_back(to_string(definedSymbolsSize));
				epilogue->add_IRInstr(IRInstr::EPILOG, VOID, irParams);
}

void IRBlockGenerator::genIf(If *ifBlock)
{
				BasicBlock *parentBlock = irGenerator->getCurrentBB();
				BasicBlock *nextBlock = new BasicBlock(cfg, cfg->new_BB_name(), parentBlock->getContext());
				BasicBlock *testBlock = new BasicBlock(cfg, cfg->new_BB_name(), parentBlock->getContext());

				if (parentBlock->getExitTrue() != nullptr)
				{
								nextBlock->setExitTrue(parentBlock->getExitTrue());
				}

				cfg->add_bb(testBlock);
				cfg->add_bb(nextBlock);

				parentBlock->setExitTrue(testBlock);
				irGenerator->setCurrentBB(testBlock);
				string varCond = irGenerator->genExpr(ifBlock->getCondition());
				testBlock->setTestVarName(varCond);
				VarSymbol *symbol = (VarSymbol *)parentBlock->getContext()->getSymbol(varCond);
				testBlock->setTestTypeName(symbol->getVarType());

				BasicBlock *blockTrue = new BasicBlock(cfg, cfg->new_BB_name(), ifBlock->getBlockIf()->getContext());
				cfg->add_bb(blockTrue);

				blockTrue->setExitTrue(nextBlock);

				irGenerator->setCurrentBB(blockTrue);
				irGenerator->genBlock(ifBlock->getBlockIf());
				testBlock->setExitTrue(blockTrue);

				if (ifBlock->getBlockElse() != nullptr)
				{
								BasicBlock *blockFalse = new BasicBlock(cfg, cfg->new_BB_name(), ifBlock->getBlockElse()->getContext());
								cfg->add_bb(blockFalse);
								irGenerator->setCurrentBB(blockFalse);

								blockFalse->setExitTrue(nextBlock);
								irGenerator->genBlock(ifBlock->getBlockElse());

								testBlock->setExitFalse(blockFalse);
				}
				else
				{
								testBlock->setExitFalse(nextBlock);
				}

				irGenerator->setCurrentBB(nextBlock);
}

void IRBlockGenerator::genWhile(While *whileLoop)
{
				BasicBlock *parentBlock = irGenerator->getCurrentBB();
				BasicBlock *nextBlock = new BasicBlock(cfg, cfg->new_BB_name(), parentBlock->getContext());
				BasicBlock *testBlock = new BasicBlock(cfg, cfg->new_BB_name(), parentBlock->getContext());

				if (parentBlock->getExitTrue() != nullptr)
				{
								nextBlock->setExitTrue(parentBlock->getExitTrue());
				}

				cfg->add_bb(testBlock);
				cfg->add_bb(nextBlock);

				parentBlock->setExitTrue(testBlock);
				irGenerator->setCurrentBB(testBlock);

				string varCond = irGenerator->genExpr(whileLoop->getCondition());
				testBlock->setTestVarName(varCond);
				VarSymbol *symbol = (VarSymbol *)parentBlock->getContext()->getSymbol(varCond);
				testBlock->setTestTypeName(symbol->getVarType());

				BasicBlock *blockWhile = new BasicBlock(cfg, cfg->new_BB_name(), whileLoop->getBlock()->getContext());
				cfg->add_bb(blockWhile);

				blockWhile->setExitTrue(testBlock);

				irGenerator->setCurrentBB(blockWhile);
				irGenerator->genBlock(whileLoop->getBlock());

				testBlock->setExitTrue(blockWhile);
				testBlock->setExitFalse(nextBlock);

				irGenerator->setCurrentBB(nextBlock);
}

void IRBlockGenerator::genFor(For *forLoop)
{
}
