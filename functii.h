#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	struct node *parinte;
	char info;
	struct node *children[27];
} Node, *Tree;

Tree IniT();
void ArbSuf(Tree arb, char *s);
void BFS(Tree arb);
int BFS_maxcopii(Tree arb);
int BFS_nrfrunze(Tree arb);
void DFSHelper(Tree node, int K, int cnt, int *CNT);
void printRootToLeafPathsHelper(Tree node, char *a, char *path, int pathLen, int *g);