#include <stdlib.h>
#include <string.h>

#include "AST.h"

node_type* verb(char* name, node_type* a, node_type* b) {
    node_type* p = (node_type*)malloc(sizeof(node_type));

    p->type = type_verb;
    p->verb.name = (char*)malloc(strlen(name) + 1);
    strcpy(p->verb.name, name);

    p->verb.left = a;
    p->verb.right = b;

    return p;
}

node_type* noun(char* name, node_type* a, node_type* b) {
    node_type* p = (node_type*)malloc(sizeof(node_type));

    p->type = type_noun;
    p->noun.name = (char*)malloc(strlen(name) + 1);
    strcpy(p->noun.name, name);

    p->noun.left = a;
    p->noun.right = b;

    return p;
}

node_type* adword(char* name, node_type* a, node_type* b) {
    node_type* p = (node_type*)malloc(sizeof(node_type));

    p->type = type_adword;
    p->adword.name = (char*)malloc(strlen(name) + 1);
    strcpy(p->adword.name, name);

    p->adword.left = a;
    p->adword.right = b;

    return p;
}

void free_node(node_type* p) {
    if (p == NULL)
        return;

    switch (p->type) {
        case type_verb:
            free(p->verb.name);
            free_node(p->verb.left);
            free_node(p->verb.right);
            break;
        case type_noun:
            free(p->noun.name);
            free_node(p->noun.left);
            free_node(p->noun.right);
            break;
        case type_adword:
            free(p->adword.name);
            free_node(p->adword.left);
            free_node(p->adword.right);
            break;
    }
    free(p);
}
