%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "grammarfile.tab.h"
	#include "symbolTable.h"
    #include <string.h>
    
    char t = 'A';

    #define ECHO fwrite(yytext, yyleng, 1, yyout)
    void incCount(int inc);

%}

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*


%%
"char"                              {ECHO; return(CHAR); }
"int"                               {ECHO; return(INT); }
"float"								{ECHO; return(FLOAT); }
"print"		                        {ECHO; return(PRINT);}
"void"			                    {ECHO; return(VOID); }
"while"								{ECHO; yylval.strval = strdup(yytext); return (WHILE);}
";"									{ECHO; return(yytext[0]); }
("{"|"<%")							{ECHO; incCount(+1); return(yytext[0]); }
("}"|"%>")							{ECHO; incCount(-1); return(yytext[0]);}
","									{ECHO; return(yytext[0]); }
":"									{ECHO; return(yytext[0]); }
"="									{ECHO; return(yytext[0]); }
"("									{ECHO; return(yytext[0]); }
")"									{ECHO; return(yytext[0]); }
("["|"<:")							{ECHO; return ('['); }
("]"|":>")							{ECHO; return( ']'); }
"."									{ECHO; return(yytext[0]); }
"&"									{ECHO; return(yytext[0]); }
"!"									{ECHO; return(yytext[0]); }
"~"									{ECHO; return(yytext[0]); }
"-"									{ECHO; return(yytext[0]); }
"+"									{ECHO; return(yytext[0]); }
"*"									{ECHO; return(yytext[0]); }
"/"									{ECHO; return(yytext[0]); }
"%"									{ECHO; return(yytext[0]); }
"<"									{ECHO; return(yytext[0]); }
">"									{ECHO; return(yytext[0]); }
"^"									{ECHO; return(yytext[0]); }
"|"									{ECHO; return(yytext[0]); }
"?"									{ECHO; return(yytext[0]); }
L?\"(\\.|[^\\"])*\"                 {ECHO; return(LITERAL); }
{L}({L}|{D})*						{ECHO; yylval.strval = strdup(yytext); return(IDENTIFIER);}
[0-9]*								{ECHO; yylval.ival = atoi(yytext); return (CONSTANT);}
[ \t\v\n\f]		                    {ECHO;}
.									{}


%%

void incCount(int inc){
    if(inc==1)
    {
        pushScope(&t);
        t++;
        // printf("--------------------\n");
    }
    else
        popScope();
    // printf(" // scope <=> %d\n",curScope->scopeDepth);
}

int yywrap(void){
	return 1;
}
