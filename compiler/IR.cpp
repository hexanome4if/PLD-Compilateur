#include "IR.h"

class IRInstr {
 
   public:

	/**  constructor */
	IRInstr(BasicBlock* bb_, Operation operation, Type type, vector<string> params_) {
        bb = bb_;
        op = operation;
        t = type;
        params = params_;
    }
	/** Actual code generation */
    /**< x86 assembly code generation for this IR instruction */
	void gen_asm(ostream &o) {
        string suffix = this->t.getLetter();
        switch(op) {
            case copy :
                if(params.size()==2){
                    //mov var1, rax
                    o << "mov" << suffix << " ";
                    o << this->bb->cfg->IR_reg_to_asm(params[1]);
                    o << ", %rax" << endl;
                    //mov rax, var0
                    o << "mov" << suffix << " %rax, ";
                    o << this->bb->cfg->IR_reg_to_asm(params[0]) << endl;
                }
                break;
            case ldconst :
                if(params.size()==2){
                    //mov const, var
                    o << "mov" << suffix << " $" << params[1];
                    o << ", " << this->bb->cfg->IR_reg_to_asm(params[0]) << endl;
                }
                break;
            case add :
                if(params.size()==3){
                    o << "mov" << suffix << " ";
                    o << this->bb->cfg->IR_reg_to_asm(params[1]);
                    o << ", %rax" << endl;

                    o << "add" << suffix << " ";
                    o << this->bb->cfg->IR_reg_to_asm(params[2]);
                    o << ", %rax" << endl;

                    o << "mov" << suffix << " %rax, ";
                    o << this->bb->cfg->IR_reg_to_asm(params[0]);
                    o << endl;
                }
                break;
            case sub : // sub dest, src <-- dest = dest - src
                if(params.size()==3){
                    o << "mov" << suffix << " -";
                    o << this.bb->cfg->get_var_index(params[2]);
                    o << "(%rbp), %rax" << endl;

                    o << "sub" << suffix << " -";
                    o << this.bb->cfg->get_var_index(params[1]);
                    o << "(%rbp), %rax" << endl;

                    o << "mov" << suffix << " %rax, -";
                    o << this.bb->cfg->get_var_index(params[0]);
                    o << "(%rbp)" << endl;
                }
                break;
            case mul : // mul S ：R[%rdx] : R[%rax] <-- S * R[%rax]
                if(params.size()==3){
                    o << "mov" << suffix << " -";
                    o << this->bb->cfg->get_var_index(params[1]);
                    o << "(%rbp), %rax" << endl;

                    o << "sub" << suffix << " -";
                    o << this->bb->cfg->get_var_index(params[2]);
                    o << "(%rbp)" << endl;

                    o << "mov" << suffix << " %rax, -";
                    o << this->bb->cfg->get_var_index(params[0]);
                    o << "(%rbp)" << endl;
                }
                break;
            case rmem : //rmem dest addr
                if(params.size()==2){
                    //mov addr, rax
                    o << "mov" << suffix << " -";
                    o << this->bb->cfg->get_var_index(params[1]);
                    o << "(%rbp), %rax" << endl;
                    //mov [rax], dest
                    o << "mov" << suffix << " [%rax], -";
                    o << this->bb->cfg->get_var_index(params[1]);
                    o << "(%rbp)" << endl;
                }
                break;
            case wmem : //wmem addr var
                if(params.size()==2){
                    //mov addr, rax
                    o << "mov" << suffix << " -";
                    o << this->bb->cfg->get_var_index(params[0]);
                    o << "(%rbp), %rax" << endl;
                    //mov var, r10
                    o << "mov" << suffix << " -";
                    o << this->bb->cfg->get_var_index(params[1]);
                    o << "(%rbp), %r10" << endl;
                    //mov r10, [rax]
                    o << "mov" << suffix << " %r10, [%rax]" << endl; //!!! faut vérifier
                }
                break;
            case cmp_eq : //cmp_eq dest op1 op2
				if(params.size()==3){
					//cmp op1, op2
					o << "cmp" << suffix;
					o << " " << this->bb->cfg->IR_reg_to_asm(params[1]) << ", ";
					o << this->bb->cfg->IR_reg_to_asm(params[2]) << endl;
					//sete %al : obtenir la valeur du flag ZF
					o << "sete %al" << endl;
					o << "movzbl %al, %eax" << endl;
					//mov %eax, dest
					o << "mov" << suffix << " %eax, ";
					o << this->bb->cfg->IR_reg_to_asm(params[0]) << endl;
				}
				break;
			case cmp_le : //cmp_le dest op1 op2 : dest = op1 <= op2
				if(params.size()==3){
					//cmp op1, op2
					o << "cmp" << suffix;
					o << " " << this->bb->cfg->IR_reg_to_asm(params[1]) << ", ";
					o << this->bb->cfg->IR_reg_to_asm(params[2]) << endl;
					//setle %al : obtenir le resultat de la comparaison
					o << "setle %al" << endl;
					o << "movzbl %al, %eax" << endl;
					//mov %eax, dest
					o << "mov" << suffix << " %eax, ";
					o << this->bb->cfg->IR_reg_to_asm(params[0]) << endl;
				}
				break;
			case cmp_lt : //cmp_le dest op1 op2 : dest = op1 < op2 (faut inverser les deux ops si necessaire)
				if(params.size()==3){
					//cmp op1, op2
					o << "cmp" << suffix;
					o << " " << this->bb->cfg->IR_reg_to_asm(params[1]) << ", ";
					o << this->bb->cfg->IR_reg_to_asm(params[2]) << endl;
					//setle %al : obtenir le resultat de la comparaison
					o << "setl %al" << endl;
					o << "movzbl %al, %eax" << endl;
					//mov %eax, dest
					o << "mov" << suffix << " %eax, ";
					o << this->bb->cfg->IR_reg_to_asm(params[0]) << endl;
				}
				break;
            default :
        }
    } 
	
}

class BasicBlock {
    public:

        // Constructor
	    BasicBlock(CFG* cfg, string entry_label) {
            this->cfg = cfg;
            label = entry_label;
        }

        /**< x86 assembly code generation for this basic block (very simple) */
	    void gen_asm(ostream &o) {
            // TO DO !
            for(vector<int>::iterator it=instrs.begin();it!=instrs.end();it++){
				it->gen_asm(o);
			}
        }

	    void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params) {
            IRInstr instr = new IRInstr(*this, op, t, params);
            this->instrs.push_back(instr);
        }

    protected:
}

class CFG {
    public:
	    CFG(DefFonction* ast) {
            this->ast = ast;
        }

	    DefFonction* ast; /**< The AST this CFG comes from */
	
	    void add_bb(BasicBlock* bb); 

	    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	    void gen_asm(ostream& o);
	    string IR_reg_to_asm(string reg) {
			return ("-" + this->get_var_index(reg) + "(%rbp)");
		} /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
	    void gen_asm_prologue(ostream& o);
	    void gen_asm_epilogue(ostream& o);

	    // symbol table methods
	    void add_to_symbol_table(string name, string t);
	    string create_new_tempvar(string t);
	    int get_var_index(string name);
	    string get_var_type(string name);

	    // basic block management
	    string new_BB_name();
	    BasicBlock* current_bb;

    protected:
	    map <string, string> SymbolType; /**< part of the symbol table  */
	    map <string, int> SymbolIndex; /**< part of the symbol table  */
	    int nextFreeSymbolIndex; /**< to allocate new symbols in the symbol table */
	    int nextBBnumber; /**< just for naming */
	
	    vector <BasicBlock*> bbs; /**< all the basic blocks of this CFG*/
}
