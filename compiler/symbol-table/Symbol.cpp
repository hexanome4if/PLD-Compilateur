#include "Symbol.h"


string Symbol::getValue() {
    return value;
}

string Symbol::getType() {
    return type;
}

int Symbol::getMemoryAddress() {
    return memoryAddress;
}

void Symbol::setValue(string value) {
    this->value = value;
}