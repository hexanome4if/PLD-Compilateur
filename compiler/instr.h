#pragma once

#include <string>
#include <vector>
#include "./symbol-table/Context.h"
#include "expr.h"
#include "IR.h"

using namespace std;

TypeName getTypeFromString(string string_type) {
				if(string_type == "int") {
								return int32;
				}
				return int32; //TODO ajouter char
}

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

class Node {
public:
virtual string buildIR(CFG* cfg);
};

class Instr : public Node {
public:
Instr(Instruction inst) : instruction(inst) {
}
virtual string buildIR(CFG* cfg);
int instruction;
};

class Block : public Node {
public:
Block(Context* c) : context(c) {
}
void addInstr(Instr instr);
string buildIR(CFG* cfg);
vector<Instr> instrs;
Context* context;
};

class Func : public Node {
public:
Func(TypeName t, string n, Block b) : type(t), name(n), block(b) {
}
void addParam(string param);
void addInstr(Instr instr);
string buildIR(CFG* cfg);
TypeName type;
string name;
vector<string> params;
Block block;
};



class Aff : public Instr, public Expr {
public:
Aff(string id, Expr ex) : Instr(AFF), varId(id), expr(ex) {
}
string buildIR(CFG* cfg);
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

/*class DeclAff : public Instr {
   public:
   DeclAff(string id, Expr ex) : Instr(DECLAFF), varId(id), expr(ex) {
   }
   string buildIR(CFG* cfg);
   string varId;
   Expr expr;
   };*/

class Ret : public Instr {
public:
Ret(Expr ex) : Instr(RET), expr(ex) {
}
string buildIR(CFG* cfg);
Expr expr;
};

class If : public Instr {
public:
If(Expr cond, Block bif, Block belse) : Instr(IF), condition(cond),
				blockIf(bif), blockElse(belse){
}
void addInstrIf(Instr instr);
void addInstrElse(Instr instr);
string buildIR(CFG* cfg);
Expr condition;
Block blockIf;
Block blockElse;
};

class While : public Instr {
public:
While(Expr cond, Block b) : Instr(WHILE), condition(cond), block(b){
}
void addInstr(Instr instr);
string buildIR(CFG* cfg);
Expr condition;
Block block;
};

class For : public Instr {
public:
For(Expr i, Expr cond, Expr p, Block b) : Instr(FOR), init(i), condition(cond), progression(p), block(b) {
}
void addInstr(Instr instr);
string buildIR(CFG* cfg);
Expr init;
Expr condition;
Expr progression;
Block block;
};

class FuncCall : public Instr, public Expr {
public:
FuncCall(string fn) : Instr(FUNCCALL), funcName(fn) {
}
void addParam(Expr param);
string buildIR(CFG* cfg);
string funcName;
vector<Expr> params;
};
