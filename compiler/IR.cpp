// #include "IR.h"
// #include "ast.h"

/** Actual code generation */
/**< x86 assembly code generation for this IR instruction */
/*
void IRInstr ::gen_asm(ostream &o)
{

	string suffix = "l";
	if (t == "int64")
	{
		suffix = "q";
	}
	switch (op)
	{
	case copy:
		if (params.size() == 2)
		{
			//mov var1, rax
			o << "mov" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB());
			o << ", %eax" << endl;
			//mov eax, var0
			o << "mov" << suffix << " %eax, ";
			o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB()) << endl;
		}
		break;
	case ldconst:
		if (params.size() == 2)
		{
			//mov const, var
			o << "mov" << suffix << " $" << params[1];
			o << ", " << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB()) << endl;
		}
		break;
	case add:
		if (params.size() == 3)
		{
			o << "mov" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB());
			o << ", %eax" << endl;

			o << "add" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[2], this->getBB());
			o << ", %eax" << endl;

			o << "mov" << suffix << " %eax, ";
			o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB());
			o << endl;
		}
		break;
	case sub: // sub dest, src <-- dest = dest - src
		if (params.size() == 3)
		{
			o << "mov" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB());
			o << ", %eax" << endl;

			o << "sub" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[2], this->getBB());
			o << ", %eax" << endl;

			o << "mov" << suffix << " %eax, ";
			o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB());
			o << endl;
		}
		break;
	case mul: // mul S ：R[%rdx] : R[%eax] <-- S * R[%eax]
		if (params.size() == 3)
		{
			o << "mov" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB());
			o << ", %eax" << endl;

			o << "imul" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[2], this->getBB());
			o << ", %eax" << endl;

			o << "mov" << suffix << " %eax, ";
			o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB());
			o << endl;
		}
		break;
	case rmem: //rmem dest addr
		if (params.size() == 2)
		{
			//mov addr, eax
			o << "mov" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB());
			o << ", %eax" << endl;
			//mov [eax], dest
			o << "mov" << suffix << " [%eax], ";
			o << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB());
			o << endl;
		}
		break;
	case wmem: //wmem addr var
		if (params.size() == 2)
		{
			//mov addr, eax
			o << "mov" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB());
			o << ", %eax" << endl;
			//mov var, r10
			o << "mov" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB());
			o << ", %r10" << endl;
			//mov r10, [eax]
			o << "mov" << suffix << " %r10, [%eax]" << endl; //!!! faut vérifier
		}
		break;
	case cmp_eq: //cmp_eq dest op1 op2
		if (params.size() == 3)
		{
			//cmp op1, op2
			o << "cmp" << suffix;
			o << " " << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB()) << ", ";
			o << this->bb->cfg->IR_reg_to_asm(params[2], this->getBB()) << endl;
			//sete %al : obtenir la valeur du flag ZF
			o << "sete %al" << endl;
			o << "movzbl %al, %eax" << endl;
			//mov %eax, dest
			o << "mov" << suffix << " %eax, ";
			o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB()) << endl;
		}
		break;
	case cmp_le: //cmp_le dest op1 op2 : dest = op1 <= op2
		if (params.size() == 3)
		{
			//cmp op1, op2
			o << "cmp" << suffix;
			o << " " << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB()) << ", ";
			o << this->bb->cfg->IR_reg_to_asm(params[2], this->getBB()) << endl;
			//setle %al : obtenir le resultat de la comparaison
			o << "setle %al" << endl;
			o << "movzbl %al, %eax" << endl;
			//mov %eax, dest
			o << "mov" << suffix << " %eax, ";
			o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB()) << endl;
		}
		break;
	case cmp_lt: //cmp_le dest op1 op2 : dest = op1 < op2 (faut inverser les deux ops si necessaire)
		if (params.size() == 3)
		{
			//cmp op1, op2
			o << "cmp" << suffix;
			o << " " << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB()) << ", ";
			o << this->bb->cfg->IR_reg_to_asm(params[2], this->getBB()) << endl;
			//setle %al : obtenir le resultat de la comparaison
			o << "setl %al" << endl;
			o << "movzbl %al, %eax" << endl;
			//mov %eax, dest
			o << "mov" << suffix << " %eax, ";
			o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB()) << endl;
		}
		break;
	case call:
	{ //call lable dest params[]
		int NombreDeVarExces = params.size() - 8;
		for (int i = params.size() - 1; i >= 2; i--)
		{
			if (i > 7)
			{
				o << "movl " << this->bb->cfg->IR_reg_to_asm(params[i], this->getBB()) << ", %edx" << endl;
				o << "pushq %rdx" << endl;
			}
			else
			{
				//Attention!!! problem 32/64 bits à gérer ici!
				o << "movl " << this->bb->cfg->IR_reg_to_asm(params[i], this->getBB());
				o << ", ";
				switch (i)
				{
				case 7:
					o << "%r9d";
					break;
				case 6:
					o << "%r8d";
					break;
				case 5:
					o << "%ecx";
					break;
				case 4:
					o << "%edx";
					break;
				case 3:
					o << "%esi";
					break;
				case 2:
					o << "%edi";
					break;
				}
				o << endl;
			}
		}

		o << "call " << params[0] << endl;

		if (NombreDeVarExces > 0)
		{
			o << "addq "
				<< "$" << NombreDeVarExces * 8 << ", %rsp" << endl;
		}
		//si destination est de 32 bits
		o << "movl %eax, " << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB()) << endl;
		// o << "movq %eax, " << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB()) << endl;
		break;
	}
	case div:
		if (params.size() == 3)
		{
			o << "mov" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[1], this->getBB());
			o << ", %eax" << endl;
			o << "cltd" << endl;
			o << "idiv" << suffix << " ";
			o << this->bb->cfg->IR_reg_to_asm(params[2], this->getBB()) << endl;

			o << "mov" << suffix << " %eax, ";
			o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB());
			o << endl;
		}
		break;
	case ret:
		o << "mov" << suffix << " ";
		o << this->bb->cfg->IR_reg_to_asm(params[0], this->getBB()) << ", %eax" << endl;

		break;
	case prol:
	{
		o << ".global " << params[0] << endl;
		o << params[0] << ":" << endl;
		o << "pushq %rbp" << endl;
		o << "movq %rsp, %rbp" << endl;
		o << "subq	$16, %rsp" << endl;

		// Récupération des paramètres
		int NombreDeVarExces = params.size() - 7;
		for (int i = 1; i < params.size(); ++i)
		{
			if (i > 6)
			{
				o << "movl " << to_string(16 + (i - 7) * 8) << "(%rbp), %eax" << endl;
				o << "movl %eax, " << this->bb->cfg->IR_reg_to_asm(params[i], this->getBB()) << endl;
			}
			else
			{
				//Attention!!! problem 32/64 bits à gérer ici!
				o << "movl ";
				switch (i)
				{
				case 6:
					o << "%r9d";
					break;
				case 5:
					o << "%r8d";
					break;
				case 4:
					o << "%ecx";
					break;
				case 3:
					o << "%edx";
					break;
				case 2:
					o << "%esi";
					break;
				case 1:
					o << "%edi";
					break;
				}
				o << ", ";
				o << this->bb->cfg->IR_reg_to_asm(params[i], this->getBB());
				o << endl;
			}
		}

		break;
	}
	case epil:
		o << "addq	$16, %rsp" << endl;
		o << "popq %rbp" << endl;
		o << "ret" << endl;
		break;
	}
}
*/
