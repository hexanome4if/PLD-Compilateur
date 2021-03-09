
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"

#include "symbol-table/SymbolTable.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class Visitor : public ifccVisitor
{
public:

    Visitor() {
        symbolTable = SymbolTable();
    }

	virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override
	{
		return visitChildren(ctx);
	}
	virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override
	{
        return visitChildren(ctx);
		// int retval = stoi(ctx->CONST()->getText());
		// std::cout << ".globl	main\n"
		// 													" main: \n"
		// 													" 	movl	$"
		// 										<< retval << ", %eax\n"
		// 																							" 	ret\n";
	}

	virtual antlrcpp::Any visitFunc(ifccParser::FuncContext *context) override
	{
		std::string functionType = context->TYPE()->getText();
		std::string functionName = context->NAME()->getText();

		std::cout << ".globl " << functionName << "\n";
		std::cout << " " << functionName << ": \n";
		std::cout << "   pushq %rbp\n";
		std::cout << "   movq %rsp, %rbp\n";

		visitChildren(context);

		std::cout << "   popq %rbp\n";
		std::cout << "   ret\n";

		return 0;
	}

	virtual antlrcpp::Any visitBlock(ifccParser::BlockContext *context) override
	{
        symbolTable.openContext();
		visitChildren(context);
        symbolTable.closeContext();
		return 0;
	}

	virtual antlrcpp::Any visitBlock_content(ifccParser::Block_contentContext *context) override
	{

		visitChildren(context);

		return 0;
	}

    virtual antlrcpp::Any visitFunc_return_const(ifccParser::Func_return_constContext *context) override
	{
		std::string returnConst = context->CONST()->getText();

		std::cout << "   movl $" << returnConst << ", %eax\n";

		return 0;
	}

    virtual antlrcpp::Any visitFunc_return_var(ifccParser::Func_return_varContext *context) override
    {
        std::string returnVar = context->NAME()->getText();

        if (!symbolTable.symbolExists(returnVar)) {
            std::cerr << "Undefined variable '" << returnVar << "'" << std::endl;
            return 1;
        }

        Symbol* varSymbol = symbolTable.getSymbol(returnVar);

        // Write ASSEMBLY code
        std::cout << "   movl -" << varSymbol->getMemoryAddress() << "(%rbp), %eax\n";

        return 0;
    }

	virtual antlrcpp::Any visitVardef(ifccParser::VardefContext *context) override {
        std::string varName = context->NAME()->getText();

        if (symbolTable.symbolExists(varName)) {
            // ERROR here
            return 1;
        }

        // Add the variable in the symbol table
        std::string varType = context->TYPE()->getText();
        std::string varValue = context->CONST()->getText();
        Symbol* symbol = symbolTable.addSymbol(varName, varType, varValue);

        // Write ASSEMBLY code
        std::cout << "   movl $" << symbol->getValue() << ", -" << symbol->getMemoryAddress() << "(%rbp)\n";

        return 0;
    }


    virtual antlrcpp::Any visitVaraffvar(ifccParser::VaraffvarContext *context) override {
        std::string varName = context->NAME(0)->getText();
        std::string otherVarName = context->NAME(1)->getText();

        if (!symbolTable.symbolExists(varName)) {
            std::cerr << "Undefined variable named '" << varName << "'" << std::endl;
            return 1;
        }

        if (!symbolTable.symbolExists(otherVarName)) {
            std::cerr << "Undefined variable named '" << otherVarName << "'" << std::endl;
            return 1;
        }

        // Get variables symbols
        Symbol* varSymbol = symbolTable.getSymbol(varName);
        Symbol* otherVarSymbol = symbolTable.getSymbol(otherVarName);

        // Check variables types
        if (varSymbol->getType() != otherVarSymbol->getType()) {
            std::cerr << "Incompatible type" << std::endl;
            return 1;
        }

        varSymbol->setValue(otherVarSymbol->getValue());

        // Write ASSEMBLY code
        std::cout << "   movl -" << otherVarSymbol->getMemoryAddress() << "(%rbp), %eax\n";
        std::cout << "   movl %eax, -" << varSymbol->getMemoryAddress() << "(%rbp)\n";

        return 0;
    }

    virtual antlrcpp::Any visitVaraffconst(ifccParser::VaraffconstContext *context) override {
        std::string varName = context->NAME()->getText();
        std::string varValue = context->CONST()->getText();

        if (!symbolTable.symbolExists(varName)) {
            std::cerr << "Undefined variable named '" << varName << "'" << std::endl;
            return 1;
        }

        // Get variable symbol
        Symbol* varSymbol = symbolTable.getSymbol(varName);
        varSymbol->setValue(varValue);

        // Write ASSEMBLY code
        std::cout << "   movl $" << varSymbol->getValue() << ", -" << varSymbol->getMemoryAddress() << "(%rbp)\n";

        return 0;
    }

private:
    SymbolTable symbolTable;
};
