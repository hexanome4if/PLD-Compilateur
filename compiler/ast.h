#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

class Instr;
class Block;
class Expr;

typedef enum {
    int64,
    int32
} Type ;

typedef enum {
    AFF,
    DECL,
    DECLAFF,
    RET
} Instruction;

class Func {
    public : 
        Func(int t, string n) : type(t), name(n) {}
        void addParam(Decl param);
        void addInstr(Instr instr);

        int type;
        string name;
        vector<Decl> params;
        vector<Instr> block;
};


class Instr {
    Instr(int inst) : instruction(inst) {}
    int instruction;
};



class Aff : public Instr {
    Aff(string id, Expr ex) : Instr(AFF), varId(id), expr(ex) {}
    string varId;
    Expr expr;
};

class Decl : public Instr {
    Decl(int t, string id) : Instr(DECL), type(t), varId(id) {}
    int type;
    string varId;
};

class DeclAff : public Decl {
    DeclAff(int type, string id, Expr ex) : Instr(DECLAFF), Decl(t,id), expr(ex) {}
    Expr expr;
};

class Ret : public Instr {
    Ret(Expr ex): Instr(RET), expr(ex) {}
    Expr expr;
}





#endif