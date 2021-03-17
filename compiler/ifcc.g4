grammar ifcc;

axiom : prog
			;

prog : func*;

func: TYPE NAME '(' ')' block ;
block: '{' block_content* '}';

block_content: func_return
             | vardef
						 | vardefaff
             | varaff
          	 ;


func_return : 'return' expr ';' ;

vardefaff: TYPE NAME '=' expr ';' ;

vardef: TYPE NAME virgulename* ';';
virgulename: ',' NAME ;

varaff: NAME '=' expr ';' ;

expr: expr binopmd expr #multdiv
		| expr binoppm  expr #plusmoins
		| '(' expr ')' #par
		| NAME #name
		| CONST #const
		| '-' expr #negative
		;

binopmd: '*' #mult
			 | '/' #div
			 ;

binoppm: ('-' | '+');

TYPE: 'int' ;

CONST : [0-9]+ ;
NAME: [a-zA-Z0-9]+;


COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
