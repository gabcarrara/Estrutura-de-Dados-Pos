#ifndef _generic_tree_h
#define _generic_tree_h

typedef struct arvore {
  
}TAG;
 
typedef struct info{

}TI;

void imprime(TAG *arvore)

TAG* insere(TAG* arvore, TAG* pai, TI* info)

TAG* inicializa()

TAG* remove(TAG* arvore, int id)

TAG* busca(TAG* arvore, int id)
 
#endif