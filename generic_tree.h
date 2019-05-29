#ifndef _generic_tree_h
#define _generic_tree_h

include "poligono.h"

typedef struct arvore {
    int cod;
    struct info * no;
    //Filho da esquerda
    struct arvore *filho; 
    //Filho da direita
    struct arvore *irmao;
}TAG;

typedef struct info{
    int tipo;
    void * dados;
    float area;
}TI;

void imprime(TAG *arvore)

//TO-DO: Recebe struct do poligono e usa poligono_id para calcular a area correta.
TAG* insere(TAG* arvore, TAG* pai, void *poligono, int poligono_id)

TAG* inicializa(){
    return NULL;
}

TAG* remove(TAG* arvore, int cod, int cod_novo_pai)

TAG* busca(TAG* arvore, int cod)

void libera(TAG* arvore)
#endif
