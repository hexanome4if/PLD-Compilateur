#include "ast.h"
#include "IR.h"
#include "expr.h"


string BinOp :: buildIR (CFG* cfg) {
    
    string var1 = expr1.buildIR(cfg);
    string var2 = expr2.buildIR(cfg);
    string var3 = cfg->create_new_tempvar("int64");
    IRInstr::Operation op;
    switch (operation){
        case add:
            op=IRInstr::add;
            break;
        case mult:
            op=IRInstr::mul;
            break;
        case divi:
            op=IRInstr::div;
            break;
        case subs:
            op=IRInstr::sub;
            break;    
    }
    vector<string> params;
    params.push_back(var3);
    params.push_back(var1);
    params.push_back(var2);
    cfg->current_bb->add_IRInstr(op, "int64", params);
    return var3;
}

string ConstExpr :: buildIR(CFG* cfg){
    string var = cfg->create_new_tempvar("int64");
    vector<string> params;
    params.push_back(var);
    params.push_back(val);
    cfg->current_bb->add_IRInstr(IRInstr :: ldconst, "int64", params);
    return var;
}

string VarExpr ::buildIR(CFG*cfg){
    return varName;
}


string Block :: buildIR (CFG* cfg) {
    for (int i = 0; i < instrs.size(); i++){
        instrs[i].buildIR(cfg);   
    }
}

string Aff :: buildIR (CFG* cfg) {
    
    IRInstr(cfg->current_bb, copy, cfg->get_var_type(varId), )
    
}

void Func::addParam(Decl p) {
    params.push_back(p);
}

void Func::addInstr(Instr i) {
    block.push_back(i);
}


