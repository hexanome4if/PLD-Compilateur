#ifndef EXPR_H
#define EXPR_H


#include <string>
#include "IR.h"

typedef enum {
				ADD,
				MULT,
				DIV,
				SUBS,
				NEGL
} Operation;

class Expr {
public:
virtual string buildIR(CFG* cfg);
};

class BinOp : public Expr {
public:
BinOp(Expr e1, Expr e2, Operation op) : expr1(e1), expr2(e2), operation(op) {
}
Expr expr1;
Expr expr2;
Operation operation;
};

class UnOp : public Expr {
public:
UnOp(Expr e, Operation op) : expr(e), operation(op) {
}
Expr expr;
Operation operation;
};


class ConstExpr : public Expr {
public:
ConstExpr(string v) : val(v) {
}
string val;
};


class VarExpr : public Expr {
public:
VarExpr(string v) : varName(v) {
}
string varName;
};

#endif
