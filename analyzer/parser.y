%{

#include <stdio.h>
#include <stdlib.h>

#include "../AST/AST.h"
#include "../graph/graph.h"
#include "../symbol_table/symbol_table.h"

int yylex();
void yyerror();
extern FILE* yyin;

%}

%union {
    struct node_type_tag* node_ptr;
    int sym_idx;
};

%start A
%token <sym_idx> VERB NOUN ADWORD PUNCTUATION PREPOSITION NUMBER

%type <node_ptr> B C D

%%

A : A B {ex($2); free_node($2);}
  |
  ;

B : C VERB D {$$ = verb(symbol_table[$2].name, $1, $3);}
  ;

C : NOUN {$$ = noun(symbol_table[$1].name, NULL, NULL);}
  | NOUN ADWORD {$$ = adword(symbol_table[$2].name, noun(symbol_table[$1].name, NULL, NULL), NULL);}
  | ADWORD NOUN {$$ = noun(symbol_table[$2].name, adword(symbol_table[$1].name, NULL, NULL), NULL);}
  | ADWORD NOUN ADWORD {$$ = adword(symbol_table[$3].name, noun(symbol_table[$2].name, adword(symbol_table[$1].name, NULL, NULL), NULL), NULL);}
  ;

D : PUNCTUATION {$$ = NULL;}
  | NOUN PUNCTUATION {$$ = noun(symbol_table[$1].name, NULL, NULL);}
  | ADWORD PUNCTUATION {$$ = adword(symbol_table[$1].name, NULL, NULL);}
  | ADWORD NOUN PUNCTUATION {$$ = noun(symbol_table[$2].name, adword(symbol_table[$1].name, NULL, NULL), NULL);}
  ;

%%

void yyerror() {
    printf("Error\n");
    exit(0);
}

int main(int argc, char** argv) {
    yyin = fopen(argv[1], "r");
    yyparse();
    print_symbol_table();
    return 0;
}
