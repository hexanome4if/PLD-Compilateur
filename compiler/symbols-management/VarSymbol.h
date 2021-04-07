#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "Symbol.h"
#include "type.h"

using namespace std;

class VarSymbol : public Symbol
{
public:
	// Constructors
	VarSymbol(string name, TypeName varType) : Symbol(name, VARIABLE), varType(varType), isInitialized(false), isUsed(false) {}

	VarSymbol(string name, TypeName varType, bool initialized) : Symbol(name, VARIABLE), varType(varType), isInitialized(initialized), isUsed(false) {}

	virtual int getMemorySize() override
	{
		return getMemorySizeFromType(varType);
	}

	virtual void reinitUsedSymbols() override
	{
		isUsed = false;
	}

	void computeDependencyCycle()
	{
		hasDependencyCycle = isCyclicUtil(new vector<VarSymbol *>(), new vector<VarSymbol *>());
	}

	// Setters
	void initialized() { isInitialized = true; }

	void used() { isUsed = true; }

	virtual void setMemoryAddress(int memoryAddress) { this->memoryAddress = memoryAddress; }
	void setValue(string val) { value = val; }
	void addDependency(VarSymbol *var) { dependsOn.push_back(var); }

	// Getters
	TypeName getVarType() { return varType; }

	int getMemoryAddress() { return memoryAddress; }

	bool getIsInitialized() { return isInitialized; }
	bool getIsUsed() { return isUsed; }
	bool getHasDependencyCycle() { return hasDependencyCycle; }
	string getValue() { return value; }
	vector<VarSymbol *> getDependencies() { return dependsOn; }

protected:
	TypeName varType;
	int memoryAddress;
	bool isInitialized;
	bool isUsed;
	string value = "undefined";
	vector<VarSymbol *> dependsOn;
	bool hasDependencyCycle = true;

	bool isCyclicUtil(vector<VarSymbol *> *visited, vector<VarSymbol *> *recStack)
	{
		if (find(visited->begin(), visited->end(), this) == visited->end())
		{
			visited->push_back(this);
			recStack->push_back(this);
			for (int i = 0; i < dependsOn.size(); ++i)
			{
				if (find(visited->begin(), visited->end(), dependsOn[i]) == visited->end() && dependsOn[i]->isCyclicUtil(visited, recStack))
				{
					return true;
				}
				else if (find(recStack->begin(), recStack->end(), dependsOn[i]) != recStack->end())
				{
					return true;
				}
			}
		}
		remove(recStack->begin(), recStack->end(), this);
		return false;
	}
};

class ArrSymbol : public VarSymbol
{
public:
	ArrSymbol(string name, TypeName varType, int length) : VarSymbol(name, varType), length(length) {}
	ArrSymbol(string name, TypeName varType, int length, bool initialized) : VarSymbol(name, varType, initialized), length(length) {}
	virtual int getMemorySize() override
	{
		return getMemorySizeFromType(varType) * length;
	}
	int getMemoryAddressFromIndex(int index)
	{
		return (memoryAddress + index * getMemorySizeFromType(varType));
	}
	void setMemoryAddress(int memoryAddress) override
	{
		this->memoryAddress = memoryAddress + getMemorySize() - getMemorySizeFromType(varType);
	}
	int getLength(){
		return length;
	}

private:
	int length;
};
