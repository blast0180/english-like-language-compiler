#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../AST/AST.h"
#include "../temp/y.tab.h"

int del = 7;
int eps = 3;

void graph_init(void);
void graph_finish();
void graph_box(char* s, int* w, int* h);
void graph_draw_box(char* s, int c, int l);
void graph_draw_arrow(int c1, int l1, int c2, int l2);

void ex_node(node_type* p, int c, int l, int* ce, int* cm);


int ex(node_type* p) {
    int rte, rtm;

    graph_init();
    ex_node(p, 0, 0, &rte, &rtm);
    graph_finish();
    return 0;
}

void ex_node(node_type* p, int c, int l, int* ce, int* cm) {
    int w, h;
    char* s;
    int cbar;
    int k;
    int che, chm;
    int cs;
    char word[100];

    if (p == NULL)
        return;

    strcpy(word, "???");
    s = word;
    switch (p->type) {
        case type_verb:
            sprintf(s, "VERB(%s)", p->verb.name);
            break;
        case type_noun:
            sprintf(s, "NOUN(%s)", p->noun.name);
            break;
        case type_adword:
            sprintf(s, "ADWORD(%s)", p->adword.name);
            break;
    }
    graph_box(s, &w, &h);
    cbar = c;
    *ce = c + w;
    *cm = c + w / 2;

    if ((p->type == type_noun && p->noun.left == NULL && p->noun.right == NULL) || (p->type == type_adword && p->adword.left == NULL && p->adword.right == NULL)) {
        graph_draw_box(s, cbar, l);
        return;
    }
    
    cs = c;
    if (p->type == type_verb && p->verb.left != NULL) {
        ex_node(p->verb.left, cs, l + h + eps, &che, &chm);
        cs = che;
    }
    if (p->type == type_verb && p->verb.right != NULL) {
        ex_node(p->verb.right, cs, l + h + eps, &che, &chm);
        cs = che;
    }
    if (p->type == type_noun && p->noun.left != NULL) {
        ex_node(p->noun.left, cs, l + h + eps, &che, &chm);
        cs = che;
    }
    if (p->type == type_noun && p->noun.right != NULL) {
        ex_node(p->noun.right, cs, l + h + eps, &che, &chm);
        cs = che;
    }
    if (p->type == type_adword && p->adword.left != NULL) {
        ex_node(p->adword.left, cs, l + h + eps, &che, &chm);
        cs = che;
    }
    if (p->type == type_adword && p->adword.right != NULL) {
        ex_node(p->adword.right, cs, l + h + eps, &che, &chm);
        cs = che;
    }
    if (w < che - c) {
        cbar += (che - c - w) / 2;
        *ce = che;
        *cm = (c + che) / 2;
    }
    graph_draw_box(s, cbar, l);

    cs = c;
    if (p->type == type_verb && p->verb.left != NULL) {
        ex_node(p->verb.left, cs, l + h + eps, &che, &chm);
        graph_draw_arrow(*cm, l + h, chm, l + h + eps - 1);
        cs = che;
    }

    if (p->type == type_verb && p->verb.right != NULL) {
        ex_node(p->verb.right, cs, l + h + eps, &che, &chm);
        graph_draw_arrow(*cm, l + h, chm, l + h + eps - 1);
        cs = che;
    }
    if (p->type == type_noun && p->noun.left != NULL) {
        ex_node(p->noun.left, cs, l + h + eps, &che, &chm);
        graph_draw_arrow(*cm, l + h, chm, l + h + eps - 1);
        cs = che;
    }
    if (p->type == type_noun && p->noun.right != NULL) {
        ex_node(p->noun.right, cs, l + h + eps, &che, &chm);
        graph_draw_arrow(*cm, l + h, chm, l + h + eps - 1);
        cs = che;
    }
    if (p->type == type_adword && p->adword.left != NULL) {
        ex_node(p->adword.left, cs, l + h + eps, &che, &chm);
        graph_draw_arrow(*cm, l + h, chm, l + h + eps - 1);
        cs = che;
    }
    if (p->type == type_adword && p->adword.right != NULL) {
        ex_node(p->adword.right, cs, l + h + eps, &che, &chm);
        graph_draw_arrow(*cm, l + h, chm, l + h + eps - 1);
        cs = che;
    }
}

#define lmax 200
#define cmax 200

char graph[lmax][cmax];
int graphNumber = 0;

void graph_test (int l, int c) {   
    int ok;
    ok = 1;
    if (l < 0)
        ok = 0;
    if (l >= lmax)
        ok = 0;
    if (c < 0)
        ok = 0;
    if (c >= cmax)
        ok = 0;
    if (ok)
        return;
    printf ("\n+++error: l = %d, c = %d not in drawing rectangle 0, 0 ... %d, %d", l, c, lmax, cmax);
    exit (1);
}

void graph_init (void) {
    int i, j;
    for (i = 0; i < lmax; i++)
        for (j = 0; j < cmax; j++)
            graph[i][j] = ' ';
}

void graph_finish() {
    int i, j;
    for (i = 0; i < lmax; i++) {
        for (j = cmax-1; j > 0 && graph[i][j] == ' '; j--);
            graph[i][cmax-1] = 0;
            if (j < cmax-1)
                graph[i][j+1] = 0;
            if (graph[i][j] == ' ')
                graph[i][j] = 0;
    }
    for (i = lmax-1; i > 0 && graph[i][0] == 0; i--);
    printf ("\n# AST %d\n\n", ++graphNumber);
    for (j = 0; j <= i; j++)
        printf ("\n%s", graph[j]);
    printf("\n");
}

void graph_box (char *s, int *w, int *h) {
    *w = strlen (s) + del;
    *h = 1;
}

void graph_draw_box (char *s, int c, int l) {
    int i;
    graph_test(l, c+strlen(s)-1+del);
    for (i = 0; i < strlen (s); i++)
        graph[l][c+i+del] = s[i];
}

void graph_draw_arrow (int c1, int l1, int c2, int l2) {
    int m;
    graph_test (l1, c1);
    graph_test (l2, c2);
    m = (l1 + l2) / 2;

    while (l1 != m) {
        graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--;
    }
    while (c1 != c2) {
        graph[l1][c1] = '-'; if (c1 < c2) c1++; else c1--;
    }
    while (l1 != l2) {
        graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--;
    }
    
    graph[l1][c1] = '|';
}
