#ifndef _generic_tree_h
#define _generic_tree_h

include "poligono.h"

typedef struct arvore {
    int cod;
    int pai;
    struct info *no;
    //Filho da esquerda
    struct arvore *filho;
    //Filho da direita
    struct arvore *irmao;
}TAG;

typedef struct info{
    int tipo;
    void *dados;
    float area;
}TI;

void imprime(TAG *arvore){
    
    
}    

//TO-DO: Recebe struct do poligono e usar poligono_id para calcular a area correta.
TAG* insere(TAG* arvore, int cod, int pai, void *poligono, enum_poli nome){
    
    if(pai == 0 && arvore!= NULL){
        printf("Não é possível inserir uma nova raiz!");
        return arvore;
    }
    
    TAG *pai_aux =  busca(arvore, pai);
    if(!pai_aux){
        printf("Pai não encontrado");
        reutrn arvore;
    }
    
    TAG *novo = (TAG*)malloc(sizeof(TAG));
    novo->cod = cod;
    novo->pai = pai;
    novo->no = (TI*)malloc(sizeof(TI));
    novo->no->tipo = poligono_id;
    novo->no->dados = poligono;
    novo->no->area = calcula_area(poligono, nome);
    novo->filho = NULL;
    //insere como ultimo irmao
    novo->irmao = NULL;
    
    if(pai == 0 ) return novo;
    
    
    TAG *irmaos = pai_aux->filho;
    
    if(!irmaos){
        pai_aux->filho = novo;
        return arvore;
    }
    
    while(irmaos->irmao) irmaos = irmaos->irmao;
    irmaos->irmao = novo;
    
    printf("Nó inserido com sucesso!");
    return arvore;
}

TAG* inicializa(){
    return NULL;
}

TAG* remove(TAG* arvore, int cod, int cod_novo_pai)


//Busco um no da arvore pelo seu codigo unico
TAG* busca(TAG* arvore, int cod){
    if(!arvore || arvore->cod == cod) return arvore;
    TAG *irmao = busca(arvore->irmao, cod);
    if(irmao) return irmao;
    reutrn busca(arvore->filho);
}

//This is destroy. :)
void libera(TAG* arvore)
#endif
