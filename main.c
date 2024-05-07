/*POPA-DRAGHIA ROBIN - 314CB*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functii.h"

int main(int argc, char *argv[]) {
	// Verificăm dacă numărul de argumente este suficient pentru a rula programul
	if (argc < 4) {
		printf("Folosire: ./tema2 [-c1 | -c2 <K> | -c3 | -c4] [fisier_intrare] [fisier_iesire]");
		return 1;
	}

	// Verificăm opțiunile și argumentele și apelăm funcțiile corespunzătoare în funcție de acestea
	if (!strcmp("-c1", argv[1])) {
		// Opțiunea -c1: Construiește arborele de sufixe și afișează nivelurile utilizând BFS
		if (argc > 4) {
			printf("Folosire: -c1 [fisier_intrare] [fisier_iesire]");
			return 1;
		}
		FILE *fin = fopen(argv[2], "r");
		if (!fin) {
			return 1;
		}
		freopen(argv[3], "w", stdout);
		int n = 0;
		fscanf(fin, "%d", &n);
		Tree arb = IniT();
		for (int i = 0; i < n; i++) {
			char s[101];
			fscanf(fin, "%s", s);
			strcat(s, "$");
			ArbSuf(arb, s);
		}
		BFS(arb);
		fclose(fin);
		fclose(stdout);
	} else if (!strcmp("-c2", argv[1])) {
		// Opțiunea -c2: Construiește arborele de sufixe și rezolvă cerințele specifice
		if (argc > 5) {
			printf("Folosire: -c2 <K> [fisier_intrare] [fisier_iesire]");
			return 1;
		}
		FILE *fin = fopen(argv[3], "r");
		if (!fin) {
			return 1;
		}
		freopen(argv[4], "w", stdout);
		int n = 0;
		fscanf(fin, "%d", &n);
		Tree arb = IniT();
		for (int i = 0; i < n; i++) {
			char s[101];
			fscanf(fin, "%s", s);
			strcat(s, "$");
			ArbSuf(arb, s);
		}
		int CNT = 0, K = 0;
		printf("%d\n", BFS_nrfrunze(arb));
		if (strlen(argv[2]) == 1)
			K = argv[2][0] - '0';
		else {
			int l = strlen(argv[2]), t = 1;
			while (l > 1) {
				t *= 10;
				l--;
			}
			for (int i = 0; i < strlen(argv[2]); i++) {
				K += t * (argv[2][i] - '0');
				t /= 10;
			}
		}
		DFSHelper(arb, K, 0, &CNT);
		printf("%d\n", CNT);
		printf("%d\n", BFS_maxcopii(arb));
		fclose(fin);
		fclose(stdout);
	} else if (!strcmp("-c3", argv[1])) {
		// Opțiunea -c3: Construiește arborele de sufixe și rezolvă cerințele specifice
		if (argc > 4) {
			printf("Folosire: -c1 [fisier_intrare] [fisier_iesire]");
			return 1;
		}
		FILE *fin = fopen(argv[2], "r");
		if (!fin) {
			return 1;
		}
		freopen(argv[3], "w", stdout);
		int n = 0, m = 0;
		fscanf(fin, "%d%d", &n, &m);
		Tree arb = IniT();
		for (int i = 0; i < n; i++) {
			char s[101];
			fscanf(fin, "%s", s);
			strcat(s, "$");
			ArbSuf(arb, s);
		}
		for (int i = 0; i < m; i++) {
			char s[101];
			fscanf(fin, "%s", s);
			char a[101];
			strcpy(a, "");
			int g = 0;
			printRootToLeafPathsHelper(arb, s, a, 0, &g);
			printf("%d\n", g);
		}
		fclose(fin);
		fclose(stdout);
	} else if (!strcmp("-c4", argv[1])) {
		// Opțiunea -c4: Construiește arborele de sufixe comprimat și afișează nivelurile utilizând BFS
		if (argc > 4) {
			printf("Folosire: -c4 [fisier_intrare] [fisier_iesire]");
			return 1;
		}
		FILE *fin = fopen(argv[2], "r");
		if (!fin) {
			return 1;
		}
		freopen(argv[3], "w", stdout);
		int n = 0;
		fscanf(fin, "%d", &n);
		CompTree arb = InitCT();
		for (int i = 0; i < n; i++) {
			char s[101];
			fscanf(fin, "%s", s);
			strcat(s, "$");
			ArbSufComp(arb, s);
		}
		Compactizare(arb);
		BFSComp(arb);
		fclose(fin);
		fclose(stdout);
	}
	return 0;
}
