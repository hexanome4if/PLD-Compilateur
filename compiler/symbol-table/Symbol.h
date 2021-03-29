#pragma once

#include <string>

using namespace std;

class Symbol {
public:
Symbol(string name, string type) : name(name), type(type) {
}
string getType();
string getName();

private:
string name;
string type;
};
