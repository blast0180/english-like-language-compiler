#ifndef _AST_H
#define _AST_H

typedef enum {
    type_verb,
    type_noun,
    type_adword
} node_enum;

typedef struct {
    char* name;
    struct node_type_tag* left;
    struct node_type_tag* right;
} verb_node_type;

typedef struct {
    char* name;
    struct node_type_tag* left;
    struct node_type_tag* right;
} noun_node_type;

typedef struct {
    char* name;
    struct node_type_tag* left;
    struct node_type_tag* right;
} adword_node_type;

typedef struct node_type_tag {
    node_enum type;
    union {
        verb_node_type verb;
        noun_node_type noun;
        adword_node_type adword;
    };
} node_type;

node_type* verb(char*, node_type*, node_type*);
node_type* noun(char*, node_type*, node_type*);
node_type* adword(char*, node_type*, node_type*);
void free_node(node_type*);

#endif
