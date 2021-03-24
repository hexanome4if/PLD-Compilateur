grammar ifcc;

axiom : prog
			;

prog : func*;

func: TYPE NAME '(' ')' block ;
block: '{' instr* '}';

instr : func_return
             | vardef
			 | vardefaff
             | varaff
			 | whiledef
			 | ifdef
			 | fordef
			 | funccall
          	 ;

whiledef : 'while' '(' expr ')' block ;

ifdef : 'if' '(' expr ')' block elsedef? ;

elsedef : 'else' block ;

fordef : 'for' '(' expr ';' expr ';' expr ')' block ;

func_return : 'return' expr ';' ;

vardefaff: TYPE NAME '=' expr ';' ;

vardef: TYPE NAME virgulename* ';';
virgulename: ',' NAME ;

varaff: NAME '=' expr ';' ;

funccall : NAME '(' expr? virguleexpr* ')' ';' ;
virguleexpr: ',' expr ; 

exprsimple : exprsimple binopmd exprsimple #multdiv
		| exprsimple binoppm  exprsimple #plusmoins
		| '(' exprsimple ')' #par
		| NAME #name
		| CONST #const
		| '-' exprsimple #negative
		| funccall #functioncall
		| '(' NAME '=' exprsimple ')' #affecsimple
		;

expr : NAME ('=' NAME)* ('=' exprsimple)?
	| exprsimple
	;

binopmd: ('*' | '/');

binoppm: ('-' | '+');

TYPE: 'int' ;

CONST : [0-9]+ ;
NAME: [a-zA-Z0-9]+;


COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
