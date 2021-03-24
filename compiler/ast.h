#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "./symbol-table/Context.h" 
#include "expr.h"
using namespace std;

typedef enum {
    int64,
    int32
} Type ;

typedef enum {
    AFF,
//    DECL,
    DECLAFF,
    RET,
    IF,
    WHILE,
    FOR,
    FUNCCALL
} Instruction;

class Block {
    public :
        Block(Context* c) : context(c) {}
        void addInstr(Instr instr);
        vector<Instr> instrs;
        Context* context;
};

class Func {
    public : 
        Func(int t, string n, Context* c) : type(t), name(n), block(Block(c)) {}
        void addParam(string param);
        void addInstr(Instr instr);

        int type;
        string name;
        vector<string> params;
        Block block;
};




class Instr {
    public :
        Instr(Instruction inst) : instruction(inst) {}
        int instruction;
};



class Aff : public Instr, public Expr {
    public :
        Aff(string id, Expr ex) : Instr(AFF), varId(id), expr(ex) {}
        string varId;
        Expr expr;
};

/*
class Decl : public Instr {
    Decl(int t, string id) : Instr(DECL), type(t), varId(id) {}
    int type;
    string varId;
};
*/

class DeclAff : public Instr {
    public :
        DeclAff(string id, Expr ex) : Instr(DECLAFF), varId(id), expr(ex) {}
        string varId;
        Expr expr;
};

class Ret : public Instr {
    public :
        Ret(Expr ex): Instr(RET), expr(ex) {}
        Expr expr;
};

class If : public Instr {
    public :
        If(Expr cond, Context* cif, Context* celse): Instr(IF), condition(cond), 
            blockIf(Block(cif)), blockElse(Block(celse)){ }
        void addInstrIf(Instr instr);
        void addInstrElse(Instr instr);    
        Expr condition;
        Block blockIf;
        Block blockElse;
};

class While : public Instr {
    public :
        While(Expr cond, Context* c): Instr(WHILE), condition(cond), block(Block(c)){}
        void addInstr(Instr instr);   
        Expr condition;
        Block block;
};

class For : public Instr {
    public :
        For(Expr i, Expr cond, Expr p, Context* c) : Instr(FOR), init(i), condition(cond), progression(p), block(Block(c)) {}
        void addInstr(Instr instr);  
        Expr init;
        Expr condition;
        Expr progression;
        Block block;
};

class FuncCall : public Instr, public Expr {
    public :
        FuncCall(string fn): Instr(FUNCCALL), funcName(fn) {}
        void addParam(Expr param);  
        string funcName;
        vector<Expr> params;
};


#endif