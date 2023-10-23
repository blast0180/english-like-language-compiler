#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "symbol_table.h"

struct SymbolTable symbol_table[TABLE_SIZE];

// FNV(Fowler/Noll/Vo) hash.
unsigned long hash(unsigned char* name) {
    uint64_t FNV_PRIME = 1099511628211ULL;
    uint64_t hash = 14695981039346656037ULL;

    while (*name) {
        hash ^= (uint64_t)(*name++);
        hash *= FNV_PRIME;
    }
    return hash;
}

bool search_symbol_table(char* name) {
    unsigned long i = hash(name) % TABLE_SIZE;

    if (!symbol_table[i].filled)
        return false;
    if (strcmp(symbol_table[i].name, name) == 0)
        return true;
    
    for (int pi = i + 1; pi != i; pi = (pi + 1) % TABLE_SIZE)
        if (strcmp(symbol_table[pi].name, name) == 0)
            return true;
    
    return false;
}

void insert_symbol_table(char* name, char* type) {
    if (search_symbol_table(name))
        return;

    unsigned long i = hash(name) % TABLE_SIZE;
    if (!symbol_table[i].filled) {
        strcpy(symbol_table[i].name, name);
        strcpy(symbol_table[i].type, type);
        symbol_table[i].filled = true;
        return;
    }
    for (int pi = i + 1; pi != i; pi = (pi + 1) % TABLE_SIZE)
        if (!symbol_table[pi].filled) {
            strcpy(symbol_table[pi].name, name);
            strcpy(symbol_table[pi].type, type);
            symbol_table[pi].filled = true;
            return;
        }
}

void print_symbol_table() {
    printf("\n# Symbol Table\n");
    printf("\n+-----------------+-----------------+\n");
    printf("| token_name      | lexeme          |\n");
    printf("+-----------------+-----------------+\n");

    for (int i = 0; i < TABLE_SIZE; ++i)
        if (symbol_table[i].filled)
            printf("| %-15s | %-15s |\n", symbol_table[i].type, symbol_table[i].name);

    printf("+-----------------+-----------------+\n");
}
