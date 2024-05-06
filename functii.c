#include "functii.h"
#include <string.h>

Tree IniT()
{
	Tree arb = (Tree)malloc(sizeof(Node));
	if (!arb)
		return NULL;
	for (int i = 0; i < 27; i++)
		arb->children[i] = NULL;
	arb->info = 0;
	arb->parinte = NULL;
	return arb;
}

void ArbSuf(Tree arb, char *s)
{
	int l = strlen(s);
	for (int i = 0; i < l; i++) {
		Tree aux = arb;
		for (int j = l - i - 1; j < l; j++) {
			int index = s[j] - 'a' + 1;
			if (s[j] == '$') {
				aux->children[0] = IniT();
				if (!aux->children[0])
					return;
				aux->children[0]->info = '$';
				aux->children[0]->parinte = aux;
			} else if (aux->children[index]) {
				aux = aux->children[index];
			} else {
				aux->children[index] = IniT();
				aux->children[index]->parinte = aux;
				aux = aux->children[index];
				aux->info = s[j];
			}
		}
	}
}

void BFS(Tree arb) {
	if (!arb)
		return;

	// Coada pentru BFS
	Tree queue[1000]; // Presupunem un număr maxim de 1000 de noduri în coadă
	int front = 0, rear = 0;
	int nodesInCurrentLevel = 1; // Numărul de noduri în nivelul curent
	int nodesInNextLevel = 0; // Numărul de noduri în nivelul următor

	// Adăugăm rădăcina în coadă
	queue[rear++] = arb;

	// Afișăm rădăcina înainte de a începe parcurgerea
	//printf("%c", arb->info);

	// Parcurgem nodurile în coadă
	while (front < rear) {
		Tree currentNode = queue[front++]; // Extragem primul nod din coadă

		// Afișăm informația din nodurile copil și incrementăm numărul de noduri în nivelul următor
		for (int i = 0; i < 27; i++) {
			if (currentNode->children[i]) {
				printf("%c ", currentNode->children[i]->info);
				queue[rear++] = currentNode->children[i];
				nodesInNextLevel++;
			}
		}

		// Dacă am terminat de afișat toate nodurile din nivelul curent, trecem la nivelul următor și afișăm un separator de linie
		if (--nodesInCurrentLevel == 0 && nodesInNextLevel > 0) {
			printf("\n");
			nodesInCurrentLevel = nodesInNextLevel;
			nodesInNextLevel = 0;
		}
	}
}

int BFS_maxcopii(Tree arb) {
	if (!arb)
		return 0;
	Tree queue[1000]; // Presupunem un număr maxim de 1000 de noduri în coadă
	int front = 0, rear = 0;
	int nodesInCurrentLevel = 1; // Numărul de noduri în nivelul curent
	int nodesInNextLevel = 0; // Numărul de noduri în nivelul următor
	int max = 0;
	queue[rear++] = arb;
	while (front < rear) {
		Tree currentNode = queue[front++]; // Extragem primul nod din coadă
		int nrfii = 0;
		for (int i = 0; i < 27; i++) {
			if (currentNode->children[i]) {
				queue[rear++] = currentNode->children[i];
				nodesInNextLevel++;
				nrfii++;
			}
		}
		if (--nodesInCurrentLevel == 0 && nodesInNextLevel > 0) {
			nodesInCurrentLevel = nodesInNextLevel;
			nodesInNextLevel = 0;
		}
		if (nrfii > max)
			max = nrfii;
	}
	return max;
}

int BFS_nrfrunze(Tree arb) {
	if (!arb)
		return 0;
	Tree queue[1000]; // Presupunem un număr maxim de 1000 de noduri în coadă
	int front = 0, rear = 0;
	int nodesInCurrentLevel = 1; // Numărul de noduri în nivelul curent
	int nodesInNextLevel = 0; // Numărul de noduri în nivelul următor
	int cnt = 0;
	queue[rear++] = arb;
	while (front < rear) {
		Tree currentNode = queue[front++]; // Extragem primul nod din coadă
		if (currentNode->info == '$')
			cnt++;
		for (int i = 0; i < 27; i++) {
			if (currentNode->children[i]) {
				queue[rear++] = currentNode->children[i];
				nodesInNextLevel++;
			}
		}
		if (--nodesInCurrentLevel == 0 && nodesInNextLevel > 0) {
			nodesInCurrentLevel = nodesInNextLevel;
			nodesInNextLevel = 0;
		}
	}
	return cnt;
}

void DFSHelper(Tree node, int K, int cnt, int *CNT) {
    if (node == NULL)
        return;

	cnt++;
	if (node->info == '$') {
		if (cnt - 1 == K)
			(*CNT)++;
	}
	if (!node->info) {
		cnt = 0;
	}

    for (int i = 0; i < 27; i++) {
        if (node->children[i]) {
            DFSHelper(node->children[i], K, cnt, CNT);
        }
    }
}

void printArray(char *path, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", path[i]);
    }
    printf("\n");
}

int compArray(char *path, int length, char *a) {
	int ok = 1;
    for (int i = 0; i < length; i++) {
        if (path[i] != a[i])
			ok = 0;
    }
    return ok;
}

void printRootToLeafPathsHelper(Tree node, char *a, char *path, int pathLen, int *g) {
    if (node == NULL)
        return;

    // Add current node's value to path
	if (node->info) {
    	path[pathLen] = node->info;
    	pathLen++;
	}

    // If current node is a leaf, print the path
    if (node->info == '$') {
		path[pathLen - 1] = '\0';
		pathLen--;
        if (pathLen == strlen(a)) {
			if (compArray(path, pathLen, a))
				(*g) = 1;
		}
    } else {
        // Recursive call for children nodes
        for (int i = 0; i < 27; i++) {
            if (node->children[i] != NULL) {
                printRootToLeafPathsHelper(node->children[i], a, path, pathLen, g);
            }
        }
    }
}