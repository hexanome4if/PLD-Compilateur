
// #include "IR.h"

// class IRInstr {

//    public:

// 	/*  constructor */
// 	IRInstr(BasicBlock* bb_, Operation op, Type t, vector<string> params) {
//         this.bb = bb_;
//         this.op = op;
//         this.t = t;
//         this.params = params;
//     }

// 	/** Actual code generation */
//     /**< x86 assembly code generation for this IR instruction */
// 	void gen_asm(ostream &o) {
//         string suffix = this->t.getLetter();
//         switch(op) {
//             case copy :
//                 if(params.size()==2){
//                     //mov var1, rax
//                     o << "mov" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[1]);
//                     o << "(%rbp), %rax" << endl;
//                     //mov rax, var0
//                     o << "mov" << suffix << " %rax, -";
//                     o << this.bb->cfg->get_var_index(params[0]);
//                     o << "(%rbp)" << endl;
//                 }
//                 break;
//             case ldconst :
//                 if(params.size()==2){
//                     //mov const, var
//                     o << "mov" << suffix << " $" << params[1];
//                     int index = this.bb->cfg->get_var_index(params[0]);
//                     o << ", -" << index << "(%rbp)" << endl;
//                 }
//                 break;
//             case add :
//                 if(params.size()==3){
//                     o << "mov" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[1]);
//                     o << "(%rbp), %rax" << endl;

//                     o << "add" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[2]);
//                     o << "(%rbp), %rax" << endl;

//                     o << "mov" << suffix << " %rax, -";
//                     o << this.bb->cfg->get_var_index(params[0]);
//                     o << "(%rbp)" << endl;
//                 }
//                 break;
//             case sub : // sub dest, src <-- dest = dest - src
//                 if(params.size()==3){
//                     o << "mov" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[2]);
//                     o << "(%rbp), %rax" << endl;

//                     o << "sub" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[1]);
//                     o << "(%rbp), %rax" << endl;

//                     o << "mov" << suffix << " %rax, -";
//                     o << this.bb->cfg->get_var_index(params[0]);
//                     o << "(%rbp)" << endl;
//                 }
//                 break;
//             case mul : // mul S ：R[%rdx] : R[%rax] <-- S * R[%rax]
//                 if(params.size()==3){
//                     o << "mov" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[1]);
//                     o << "(%rbp), %rax" << endl;

//                     o << "sub" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[2]);
//                     o << "(%rbp)" << endl;

//                     o << "mov" << suffix << " %rax, -";
//                     o << this.bb->cfg->get_var_index(params[0]);
//                     o << "(%rbp)" << endl;
//                 }
//                 break;
//             case rmem : //rmem dest addr
//                 if(params.size()==2){
//                     //mov addr, rax
//                     o << "mov" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[1]);
//                     o << "(%rbp), %rax" << endl;
//                     //mov [rax], dest
//                     o << "mov" << suffix << " [%rax], -";
//                     o << this.bb->cfg->get_var_index(params[1]);
//                     o << "(%rbp)" << endl;
//                 }
//                 break;
//             case wmem : //wmem addr var
//                 if(params.size()==2){
//                     //mov addr, rax
//                     o << "mov" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[0]);
//                     o << "(%rbp), %rax" << endl;
//                     //mov var, r10
//                     o << "mov" << suffix << " -";
//                     o << this.bb->cfg->get_var_index(params[1]);
//                     o << "(%rbp), %r10" << endl;
//                     //mov r10, [rax]
//                     o << "mov" << suffix << " %r10, [%rax]" << endl; //!!! faut vérifier
//                 }
//                 break;
//             case cmp_eq : //cmp_eq dest op1 op2
// 				if(params.size()==3){
// 					//cmp op1 op2
// 					o << "cmp";
// 					o << " -" << this.bb->cfg->get_var_index(params[1]) << "(%rbp), ";
// 					o << " -" << this.bb->cfg->get_var_index(params[2]) << "(%rbp)" << endl;
// 					//LAHF %ah = x1xxxxxx si egale, x0xxxxxx si !=
// 					o << "lahf" << endl;
// 					//mov 7eme bit de ah(ZF) --> dest
// 				}
//             default :
//         }
//     }

// }

// class BasicBlock {
//     public:

//         // Constructor
// 	    BasicBlock(CFG* cfg, string entry_label) {
//             this.cfg = cfg;
//             this.label = entry_label;
//         }

//         /**< x86 assembly code generation for this basic block (very simple) */
// 	    void gen_asm(ostream &o) {
//             // TO DO !
//         }

// 	    void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params) {
//             // TO DO !
//         }

//     protected:
// }

// class CFG {
//     public:
// 	    CFG(DefFonction* ast) {
//             this.ast = ast;
//         }

// 	    DefFonction* ast; /**< The AST this CFG comes from */

// 	    void add_bb(BasicBlock* bb);

// 	    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
// 	    void gen_asm(ostream& o);
// 	    string IR_reg_to_asm(string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
// 	    void gen_asm_prologue(ostream& o);
// 	    void gen_asm_epilogue(ostream& o);

// 	    // symbol table methods
// 	    void add_to_symbol_table(string name, Type t);
// 	    string create_new_tempvar(Type t);
// 	    int get_var_index(string name);
// 	    Type get_var_type(string name);

// 	    // basic block management
// 	    string new_BB_name();
// 	    BasicBlock* current_bb;

//     protected:
// 	    map <string, Type> SymbolType; /**< part of the symbol table  */
// 	    map <string, int> SymbolIndex; /**< part of the symbol table  */
// 	    int nextFreeSymbolIndex; /**< to allocate new symbols in the symbol table */
// 	    int nextBBnumber; /**< just for naming */

// 	    vector <BasicBlock*> bbs; /**< all the basic blocks of this CFG*/
// }
// */
