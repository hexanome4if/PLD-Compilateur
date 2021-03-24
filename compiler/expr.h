#ifndef EXPR_H
#define EXPR_H


#include <string>

typedef enum {
    add,
    mult,
    div,
    subs
} Operation; 

class Expr {

};

class BinOpMdExpr : public Expr{

    Expr expr1;
    Expr expr2;
    int operation;
};


class ConstExpr : public Expr {

    ConstExpr(string v) : val(v) {}
    string val;
}


class VarExpr : public Expr {

    VarExpr(string v) : varName(v) {}
    string varName;
}

#endif