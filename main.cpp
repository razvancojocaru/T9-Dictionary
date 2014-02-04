//Cojocaru Mihail-Razvan, 313CA
#include <fstream>
#include "trie.h"
#include <string.h>
#include <stdio.h>


int main() {
srand(time(0));

FILE *f, *g;
f = fopen("date.in", "rt");
g = fopen("date.out", "wt");

/*n - retine nr de cuvinte introduse in dictionar
	m - nr de interogari (coduri introduse)
	prio - retine prioritatea fiecarui cuvant introdus
	cuvant - retine cuvantul introdus
	cod - retine codurile introduse (interogarile) 
	nr - variabila care retine valoarea dupa (*) */
int n, m, nr;
char *cuvant = new char[25];
char *cod = new char[50];
int prio;

Trie *trie = new Trie;

fscanf(f, "%d", &n);

/*Introducem cuvintele in dictionar*/
for (int i=0; i<n; i++){
	fscanf(f, "%s", cuvant);
	fscanf(f, "%d", &prio);
	trie->insert(cuvant, prio);
}

fscanf(f, "%d", &m);

/*token - variabila care retine codul efectiv, inainte de (*) 
	cod2 - variabila auxiliara, folosita pentru strtok si pentru a retine
			cuvantul obtinut cu functia find din trie */
char* token;
char* cod2 = new char[50];
for (int i=0; i<m; i++) {

	fscanf(f, "%s", cod);
	strcpy(cod2, cod);
	token = strtok(&cod2[0], "*");
	
	/*Verificam daca avem cod simplu sau cu (*) */
	if (strlen(cod) > strlen(token) ) {
	
		/*Convertim string-ul de la * incepand */
		nr = atoi(&cod[strlen(token)+1]);
		trie->find(token, nr, cod2);
		fprintf(g, "%s\n", cod2);
		
	}
	else {
	
		/*Pentru cod simplu, consideram nr=0 */
		trie->find(token, 0, cod2);
		fprintf(g, "%s\n", cod2);
		
	}

}

fclose(f);
fclose(g);
delete[] cod2;
delete[] cod;
delete[] cuvant;
delete trie;
return 0;
}
