grammar ifcc;

axiom
		: prog
		;

prog
		: func*
		;

func
		: TYPE NAME '(' ')' block
		| TYPE NAME '(' TYPE NAME (',' TYPE NAME)* ')' block
		;

block
		: '{' instr* '}'
		;

instr
		: func_return
		| vardefaff
		| aff
		| whiledef
		| ifdef
		| fordef
		| funccall ';'
		| arraydef
		| arraydefaff
    ;

whiledef
		: 'while' '(' expr ')' block
		;

ifdef
		: 'if' '(' expr ')' block elsedef?
		;

elsedef
		: 'else' block
		;

fordef
		: 'for' '(' expr ';' expr ';' expr ')' block
		;

func_return
		: 'return' expr ';'
		;

vardefaff
		: TYPE NAME ('=' expr)? virgulename* ';'
		;

virgulename
		: ',' NAME ('=' expr)?
		;

aff
		: NAME '=' expr ';'			#varaff
		| arrayaccess '=' expr ';'	#arrayaff
		;

funccall
		: (NAME '(' ')')
		| (NAME '(' expr virguleexpr* ')')
		;
virguleexpr
		: ',' expr
		;


expr
		: (NAME ('=' NAME)* ('=' exprsimple)?)
		| (exprsimple)
		;

exprsimple
		: exprsimple binopmd exprsimple 	#multdiv
		| exprsimple binoppm  exprsimple 	#plusmoins
		| '(' exprsimple ')' 							#par
		| NAME 														#name
		| CONST 													#const
		| '-' exprsimple 									#negative
		| '!' exprsimple 									#not
		| funccall 												#functioncall
		| '(' NAME '=' exprsimple ')' 		#affecsimple
		| CHARAC									        #affecchar
		| arrayaccess					#arrayexpr
		| exprsimple '&' exprsimple       #andbitwise
		| exprsimple '^' exprsimple       #xorbitwise
		| exprsimple '|' exprsimple       #orbitwise
		| exprsimple '==' exprsimple  #equalcompare
		| exprsimple '!=' exprsimple  #notequalcompare
		| exprsimple '<' exprsimple   #infcompare
		| exprsimple '>' exprsimple   #supcompare
		| exprsimple '||' exprsimple #logicalOR
		| exprsimple '&&' exprsimple #logicalAND
		;

binopmd: ('*' | '/');

binoppm: ('-' | '+');


arraydef: TYPE NAME '[' CONST ']' ';' ;

arraydefaff : TYPE NAME '[' CONST? ']' '=' '{' arraycontent? '}' ';' ;

arraycontent : expr (',' expr)* ;

arrayaccess : NAME '[' expr ']' ;

TYPE: 'int' | 'char' | 'void' | 'int64_t' | 'short' | 'long';

CONST : [0-9]+ ;
NAME: [a-zA-Z0-9]+;
CHARAC: '\''[a-zA-Z0-9 ]'\'' ;

COMMENT : '/*' .*? '*/' -> skip;
INLINE_COMMENT : '//' .*? '\n' -> skip;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
