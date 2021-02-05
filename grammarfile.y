%{
    #include <stdio.h>			
    #include <stdlib.h>
    #include <ctype.h> 
	
	#include "symbolTable.h"

    void yyerror(char *s);

    int symbolics[52];
%}

%token PTR_OP 
%token AND_OP OR_OP MOD_ASSIGN 
%token LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME
%token CHAR INT FLOAT VOID
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN
%token PRINT
%token CONSTANT LITERAL IDENTIFIER SIZEOF

%start program


%%

program
    : external_declaration
    | program external_declaration
    ;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
    | declaration_specifiers declarator compound_statement
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

statement
	: compound_statement
	| expression_statement
	| iteration_statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
    ;


expression_statement
	: ';'
	| expression ';'
	;

declaration
    : declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	;

declarator
	: direct_declarator
	;

direct_declarator
	: IDENTIFIER
	| '(' declarator ')'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

parameter_type_list
	: parameter_list
    ;

parameter_list
	: parameter_declaration
	| parameter_list ',' parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER

init_declarator_list
	: init_declarator
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator
	| declarator '=' initializer
	;

declaration_specifiers
	: type_specifier
	| type_specifier declaration_specifiers
    ;

type_specifier
	: VOID
	| CHAR
	| INT
    | FLOAT
	| TYPE_NAME
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

assignment_expression
	: assignment_operator assignment_expression
    | CONSTANT
	;

assignment_operator
	: '='
    ;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

%%


int main()
{
	initScope();
	printf(" // scope <=> %d\n",curScope->scopeDepth);
	return yyparse();
}

void yyerror (char *s) {fprintf(stderr, "%s\n",s);}