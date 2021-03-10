grammar ifcc;

axiom : prog
			;

prog : func prog | EOF;

func: TYPE NAME '(' ')' block ;
block: '{' block_content;

block_content: func_return_const block_content
             | func_return_var block_content
             | vardef block_content
             | varaffvar block_content
             | varaffconst block_content
             | '}'
             ;



func_return_const : 'return' CONST ';' ;
func_return_var: 'return' NAME ';' ;
CONST : [0-9]+ ;

vardef: TYPE NAME '=' CONST ';' ;
varaffvar: NAME '=' NAME ';' ;
varaffconst: NAME '=' CONST ';' ;
TYPE: 'int' | 'char' ;
NAME: [a-zA-Z0-9]+;


COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
