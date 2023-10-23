%{

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "y.tab.h"
#include "../symbol_table/symbol_table.h"

void yyerror();

%}

lower [a-z]
upper [A-Z]
alpha [a-zA-Z]
digit [0-9]
alnum [a-zA-Z0-9]

%%

[ \t\n]+ ;

{digit}+ {
    insert_symbol_table(yytext, "NUMBER");
    yylval.sym_idx = hash(yytext) % TABLE_SIZE;
    return NUMBER;
}

{alnum}*{digit}{alnum}* {
    insert_symbol_table(yytext, "VERB");
    yylval.sym_idx = hash(yytext) % TABLE_SIZE;
    return VERB;
}

\@{alnum}+ {
    insert_symbol_table(yytext, "PREPOSITION");
    yylval.sym_idx = hash(yytext) % TABLE_SIZE;
    return PREPOSITION;
}

{upper}{alpha}* {
    insert_symbol_table(yytext, "NOUN");
    yylval.sym_idx = hash(yytext) % TABLE_SIZE;
    return NOUN;
}

{lower}+ {
    insert_symbol_table(yytext, "ADWORD");
    yylval.sym_idx = hash(yytext) % TABLE_SIZE;
    return ADWORD;
}

[\.\?\!] {
    insert_symbol_table(yytext, "PUNCTUATION");
    yylval.sym_idx = hash(yytext) % TABLE_SIZE;
    return PUNCTUATION;
}

. yyerror();

%%

int yywrap() {
    return 1;
}
