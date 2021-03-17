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
			 | while
			 | if
			 | for
			 | funccall
          	 ;

while : 'while' '(' expr ')' block ;

if : 'if' '(' expr ')' block else? ;

else : 'else' block ;

for : 'for' '(' expr ';' expr ';' expr ')' block ;

func_return : 'return' expr ';' ;

vardefaff: TYPE NAME '=' expr ';' ;

vardef: TYPE NAME virgulename* ';';
virgulename: ',' NAME ;

varaff: NAME '=' expr ';' ;

funccall : NAME '(' expr? virguleexpr* ')' ';' ;
virguleexpr: ',' expr ; 

expr: expr binopmd expr #multdiv
		| expr binoppm  expr #plusmoins
		| '(' expr ')' #par
		| NAME #name
		| CONST #const
		| '-' expr #negative
		| funccall
		;

binopmd: ('*' | '/');

binoppm: ('-' | '+');

TYPE: 'int' ;

CONST : [0-9]+ ;
NAME: [a-zA-Z0-9]+;


COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
