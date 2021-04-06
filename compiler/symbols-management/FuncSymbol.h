#pragma once

#include <string>
#include "Symbol.h"

using namespace std;

class FuncSymbol : public Symbol
{
public:
    typedef struct
    {
        string name;
        TypeName type;
    } Param;

	FuncSymbol(string name, string returnType) : Symbol(name, FUNCTION), returnType(returnType) {}

	void used() { isUsed = true; }

    void addParam(TypeName type, string name)
    {
        params.push_back({name = name, type = type});
    }

    virtual void reinitUsedSymbols() override
    {
	    if (name != "main")
        {
            isUsed = false;
        }
    }

	// Get
	bool getIsUsed() { return isUsed; }
    vector<Param> getParams()
    {
        return params;
    }

private:
	string returnType;
	bool isUsed;
    vector<Param> params;
};
