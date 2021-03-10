#pragma once

#include <string>

using namespace std;

class Symbol {
public:
    Symbol(string name, string type, string value, int memoryAddress): name(name), type(type), value(value), memoryAddress(memoryAddress) {}
    string getValue();
    string getType();
    int getMemoryAddress();
    void setValue(string value);
private:
    string name;
    string type;
    string value;
    int memoryAddress;
};