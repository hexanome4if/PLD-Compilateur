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

class BinOp : public Expr{
    public :
        BinOp(Expr e1, Expr e2, int op) : expr1(e1), expr2(e2), operation(op) {}
        Expr expr1;
        Expr expr2;
        int operation;
};


class ConstExpr : public Expr {
    public :
        ConstExpr(string v) : val(v) {}
        string val;
};


class VarExpr : public Expr {
    public :
        VarExpr(string v) : varName(v) {}
        string varName;
};

#endif