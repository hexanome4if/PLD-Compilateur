#include "IR.h"

class IRInstr {
 
   public:

	/**  constructor */
	IRInstr(BasicBlock* bb_, Operation op, Type t, vector<string> params) {
        this.bb = bb_;
        this.op = op;
        this.t = t;
        this.params = params;
    }
	
	/** Actual code generation */
    /**< x86 assembly code generation for this IR instruction */
	void gen_asm(ostream &o) {
        switch(op) {
            case copy :
                o << "mov" << "l ou q ou etc..." << "";
                break;
            case ldconst :
                break;
            default :
        }
    } 
	
}

class BasicBlock {
    public:

        // Constructor
	    BasicBlock(CFG* cfg, string entry_label) {
            this.cfg = cfg;
            this.label = entry_label;
        }

        /**< x86 assembly code generation for this basic block (very simple) */
	    void gen_asm(ostream &o) {
            // TO DO !
        }

	    void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params) {
            // TO DO !
        }

    protected:
}

class CFG {
    public:
	    CFG(DefFonction* ast) {
            this.ast = ast;
        }

	    DefFonction* ast; /**< The AST this CFG comes from */
	
	    void add_bb(BasicBlock* bb); 

	    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	    void gen_asm(ostream& o);
	    string IR_reg_to_asm(string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
	    void gen_asm_prologue(ostream& o);
	    void gen_asm_epilogue(ostream& o);

	    // symbol table methods
	    void add_to_symbol_table(string name, Type t);
	    string create_new_tempvar(Type t);
	    int get_var_index(string name);
	    Type get_var_type(string name);

	    // basic block management
	    string new_BB_name();
	    BasicBlock* current_bb;

    protected:
	    map <string, Type> SymbolType; /**< part of the symbol table  */
	    map <string, int> SymbolIndex; /**< part of the symbol table  */
	    int nextFreeSymbolIndex; /**< to allocate new symbols in the symbol table */
	    int nextBBnumber; /**< just for naming */
	
	    vector <BasicBlock*> bbs; /**< all the basic blocks of this CFG*/
}
