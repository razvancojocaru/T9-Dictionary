//Cojocaru Mihail-Razvan, 313CA
#include <iostream>
#include <cstdlib>
#include <string>
#include "treap.h"

/*Structura care retine in primul membru numarul de aparitii
si in cel de-al doilea cuvantul in sine*/
struct mypair {
	int first;
	char second[25];
	
	mypair() {}
	
	void make_pair(int f, char* s) {
		first = f;
		strcpy(second, s);
	}
};

struct Trie {

	Treap< mypair > *treap;
	Trie *fiu[10];
	
	/*Pointerii fiu[0] si fiu[1] nu sunt folositi.
	Am folosit un vector pentru lizibilitate.*/
	Trie() {
		treap = new Treap< mypair >;
		for (int i=2; i<10; i++)
			fiu[i] = NULL;
	}

	~Trie() {
		for (int i=2; i<10; i++)
			if (fiu[i]) delete fiu[i];
		delete treap;
	}

	void insert(char* cuv, int prioritate) {
	
		int size = strlen(cuv);
		mypair p;
		
		/*Folosind o bucla for, parcurgem noduri din trie, pentru a ajunge
		la nodul corespunzatoru cuvantului citit.
		Pe masura ce traversam trie-ul, creem noduri pe parcurs.*/
		Trie *T = this;
		
		for (int i=0; i<size; i++) {
			/*Folosind un switch transformam cuvantul in codul corespunzator*/
			switch ( cuv[i] ) {
				case 'a' :
				case 'b' :
				case 'c' :
					if ( T->fiu[2] == NULL ) {
						T->fiu[2] = new Trie;
					}
					T = T->fiu[2];		
					break;
				case 'd' :
				case 'e' :
				case 'f' :
					if ( T->fiu[3] == NULL ) {
						T->fiu[3] = new Trie;
					}
					T = T->fiu[3];
					break;
				case 'g' :
				case 'h' :
				case 'i' :
					if ( T->fiu[4] == NULL ) {
						T->fiu[4] = new Trie;
					}
					T = T->fiu[4];
					break;
				case 'j' :
				case 'k' :
				case 'l' :
					if ( T->fiu[5] == NULL ) {
						T->fiu[5] = new Trie;
					}
					T = T->fiu[5];
					break;
				case 'm' :
				case 'n' :
				case 'o' :
					if ( T->fiu[6] == NULL ) {
						T->fiu[6] = new Trie;
					}
					T = T->fiu[6];
					break;
				case 'p' :
				case 'q' :
				case 'r' :
				case 's' :
					if ( T->fiu[7] == NULL ) {
						T->fiu[7] = new Trie;
					}
					T = T->fiu[7];
					break;
				case 't' :
				case 'u' :
				case 'v' :
					if ( T->fiu[8] == NULL ) {
						T->fiu[8] = new Trie;
					}
					T = T->fiu[8];
					break;
				default :
					if ( T->fiu[9] == NULL ) {
						T->fiu[9] = new Trie;
					}
					T = T->fiu[9];
			}
		}
		
		/*T = nodul din trie corspunzator cuvantului.
		Inseram cuvantul in treap-ul nodului respectiv*/
		p.make_pair(prioritate, cuv);
		T->treap->insert(T->treap, p, rand()%1000 );
		return;
	}
	
	void find(char* cod, int nr, char* cuvant) {
		int size = strlen(cod);
		mypair p;
		
		/*Folosind un for, parcurgem trie-ul pentru a ajunge la nodul
		corespunzator codului citit*/
		Trie *T = this;
		
		for (int i=0; i<size; i++) {
			/*Scadem 48 deoarece cifrele au codul ascii '0'=48, '1'=49, etc.*/
			T = T->fiu[ cod[i]-48 ];
		}

		/*Daca numarul dupa * depaseste numarul de cuvinte din treap, cautarea
		se continua ciclic*/
		nr = nr % T->treap->nr_nodes;
		
		p = T->treap->findK(nr);

		/*Stergem elementul gasit din treap, incremendam numarul de aparitii
		si il inseram din nou.*/
		T->treap->erase(T->treap, p);
		p.first++;
		T->treap->insert(T->treap, p, rand()%1000);
		
		/*Retinem cuvantul gasit*/
		strcpy(cuvant, p.second);
		
		return;
	}
	
};
