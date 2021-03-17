grammar ifcc;

axiom : prog
			;

prog : func prog | EOF;

func: TYPE NAME '(' ')' block ;
block: '{' block_content* '}';

block_content: func_return_const
             | func_return_var
             | vardef
						 | vardefaff
             | varaff
          	 ;



func_return_const : 'return' CONST ';' ;

func_return_var: 'return' NAME ';' ;

vardefaff: TYPE NAME '=' CONST ';' ;

vardef: TYPE NAME virgulename* ';';
virgulename: ',' NAME ;

varaff: NAME '=' expr ';' ;

expr: expr '+' expr #plus
		| expr '*' expr #mult
		| expr '-' expr #substr
		| expr '/' expr #div
		| '(' expr ')' #par
		| NAME #name
		| CONST #const
		;

TYPE: 'int' | 'char' ;

CONST : [0-9]+ ;
NAME: [a-zA-Z0-9]+;


COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
