#include "instr.h"
#include "IR.h"

/* BuildIR for the expr */

string BinOp :: buildIR (CFG* cfg) {
    
    string var1 = expr1.buildIR(cfg);
    string var2 = expr2.buildIR(cfg);
    string var3 = cfg->create_new_tempvar("int64");
    IRInstr::Operation op;
    switch (operation){
        case ADD:
            op=IRInstr::add;
            break;
        case MULT:
            op=IRInstr::mul;
            break;
        case DIV:
            op=IRInstr::div;
            break;
        case SUBS:
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

string UnOp :: buildIR (CFG* cfg) {
    Expr zero = ConstExpr("0");
    BinOp minus = BinOp(zero, expr, SUBS);
    string var = minus.buildIR(cfg);
    return var;
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
    return "BLOCK";
}

string Aff :: buildIR (CFG* cfg) {
    string varExpr = expr.buildIR(cfg);
    vector<string> params;
    params.push_back(varId);
    params.push_back(varExpr);
    cfg->current_bb->add_IRInstr(IRInstr::copy, "int64", params);
    return varId;
}

string Ret :: buildIR(CFG *cfg) {
	string varExpr = expr.buildIR(cfg);
	vector<string> params;
	params.push_back(varExpr);
	cfg->current_bb->add_IRInstr(IRInstr::ret, "int64",params );
}

string Func :: buildIR(CFG* cfg) {
	//Générer prologue
	BasicBlock prologue = BasicBlock(cfg, cfg->new_BB_name());
	vector<string> empty;
	prologue.add_IRInstr(IRInstr::prol, "notype", empty);
	cfg->add_bb(&prologue);

	//Générer la fonction
	BasicBlock body = BasicBlock(cfg, name);
	prologue.exit_true = &body;
	cfg->add_bb(&body);
	cfg->current_bb = &body;
	block.buildIR(cfg);

	
	//Générer épilogue
	BasicBlock epilogue = BasicBlock(cfg, cfg->new_BB_name());
	epilogue.add_IRInstr(IRInstr::epil, "notype", empty);
	body.exit_true= &epilogue;
	cfg->add_bb(&epilogue);
}

/*
void Func::addParam(Decl p) {
    params.push_back(p);
}
*/
/*
void Func::addInstr(Instr i) {
    block.push_back(i);
}
*/
