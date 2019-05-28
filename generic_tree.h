#ifndef _generic_tree_h
#define _generic_tree_h

typedef struct arvore {
    int cod;
    struct info * no;
    //Filho da esquerda e filho da direita.
    struct arvore * filho, irmao;
}TAG;

typedef struct info{
    int tipo;
    void * info;
    float area;
}TI;

void imprime(TAG *arvore)

TAG* insere(TAG* arvore, TAG* pai, TI* info)

TAG* inicializa()

TAG* remove(TAG* arvore, int id)

TAG* busca(TAG* arvore, int id)

#endif
