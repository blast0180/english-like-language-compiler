#ifndef _SYM_TAB_H
#define _SYM_TAB_H

#include <stdbool.h>

#define STRING_SIZE 100
#define TABLE_SIZE 1000

struct SymbolTable {
    char name[STRING_SIZE];
    char type[STRING_SIZE];
    bool filled;
};

extern struct SymbolTable symbol_table[TABLE_SIZE];

unsigned long hash(unsigned char*);
bool search_symbol_table(char*);
void insert_symbol_table(char*, char*);
void print_symbol_table();

#endif
