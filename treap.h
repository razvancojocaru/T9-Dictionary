//Cojocaru Mihail-Razvan, 313CA
#include <iostream>
#include <string.h>
using namespace std;

template <typename T> struct Treap {
  T key;
  int priority;
  Treap<T> *left, *right;
  bool nil;

  int nr_nodes;

  // Creaza un nod nil
  Treap() : priority(-1), left(NULL), right(NULL), nil(true), nr_nodes(0) {}
  
  ~Treap() {
  	if (this->isNil())
  		return;
  	delete this->left;
  	delete this->right;
  }

  // Adaugam date, transformand un nod nil intr-un nod obisnuit
  void addData(T key, int priority) {
    this->nil = false;
    this->key = key;
    this->priority = priority;
    this->nr_nodes = 1;
    this->left = new Treap();
    this->right = new Treap();
  }

  // Stergem un nod obisnuit, transformandu-l intr-unul nil
  void delData() {
    this->nil = true;
    this->priority = -1;
    delete this->left;
    delete this->right;
    this->nr_nodes = 0;
  }

  bool isNil() {
    return this->nil;
  }

  void rotateRight(Treap<T> *&nod) {
    // Rotirea dreapta
	Treap<T> *aux = nod->left;
	nod->left = aux->right;
	aux->right = nod;
	
    // Recalculam dimensiunea subarborilor
    aux->nr_nodes = nod->nr_nodes;
    nod->nr_nodes = aux->nr_nodes - aux->left->nr_nodes - 1;
    
    nod = aux;
  }

  void rotateLeft(Treap<T> *&nod) {
    // Rotirea stanga
	Treap<T> *aux = nod->right;
	nod->right = aux->left;
	aux->left = nod;
	
    // Recalculam dimensiunea subarborilor
    aux->nr_nodes = nod->nr_nodes;
    nod->nr_nodes = aux->nr_nodes - aux->right->nr_nodes - 1;
    
    nod = aux;
  }

  void insert(Treap<T> *&fatherPointer, T key, int priority) {
    if (this->isNil()) {
      this->addData(key, priority);
      return ;
    }

    if ((key.first > this->key.first) || ((key.first == this->key.first) 
    				&& ( strcmp(key.second, this->key.second) < 0 ))) {
		left->insert(fatherPointer->left, key, priority);
    } else {
		right->insert(fatherPointer->right, key, priority);
    }

	// Rotiri si incrementare dimensiune
	this->nr_nodes++;
    if (this->left->priority > this->priority) {
		rotateRight(fatherPointer);
    } else if (this->right->priority > this->priority) {
		rotateLeft(fatherPointer);
    }
  }

  void erase(Treap<T> *&fatherPointer, T key) {

	if ((key.first > this->key.first) || ((key.first == this->key.first) && 
    						(strcmp(key.second, this->key.second) < 0 ))) {
    	
    	this->nr_nodes--;
		left->erase(fatherPointer->left, key);
    
	} else { 
    	if ((key.first < this->key.first) || 
    		(strcmp(key.second, this->key.second) > 0 )) {
    		
    		this->nr_nodes--;
			right->erase(fatherPointer->right, key);
    	
    	} else { 		
    		if (this->left->isNil() && this->right->isNil()) {
      			this->delData();
    		} else {
      			
      			if (this->left->priority > this->right->priority) {
					rotateRight(fatherPointer);
					fatherPointer->erase(fatherPointer, key);
      			} else {
					rotateLeft(fatherPointer);
					fatherPointer->erase(fatherPointer, key);
      			}
    		
    		}
    	}
    		
    }
  }


  T findK(int k) {
	// Determinare a k-a cheie
	// Nodul 0 - cel mai mic. Nodul n-1 cel mai mare 
	if (k == left->nr_nodes) {
    	return key;
    }
    if (k > left->nr_nodes) {
    	return right->findK(k - left->nr_nodes - 1);
    }
    else {
    	return left->findK(k);
    }
   }
};

