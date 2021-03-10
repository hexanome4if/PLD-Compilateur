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
             | varaffvar
             | varaffconst
          	 ;



func_return_const : 'return' CONST ';' ;

func_return_var: 'return' NAME ';' ;

vardefaff: TYPE NAME '=' CONST ';' ;

vardef: TYPE NAME virgulename* ';';
virgulename: ',' NAME ;

varaffvar: NAME '=' NAME ';' ;

varaffconst: NAME '=' CONST ';' ;

TYPE: 'int' | 'char' ;

CONST : [0-9]+ ;
NAME: [a-zA-Z0-9]+;


COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
