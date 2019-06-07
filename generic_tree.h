#ifndef _generic_tree_h
#define _generic_tree_h

#include <stdlib.h>
#include "poligono.h"

typedef struct arvore {
    int cod;
    int pai;
    struct info *no;
    struct arvore *filho; //Filho da esquerda
    struct arvore *irmao; //Filho da direita
}TAG;

typedef struct info{
    int tipo;
    void *dados;
    float area;
}TI;

//Busco um no da arvore pelo seu codigo unico
TAG* busca(TAG* arvore, int cod){
    if(!arvore || arvore->cod == cod) return arvore;
    TAG *irmao = busca(arvore->irmao, cod);
    if(irmao) return irmao;
    return busca(arvore->filho, cod);
}

void imprime(TAG *arvore);

void imprime_no(TAG *arvore, int cod){
    if(!arvore){
        printf("Arvore nula!\n");
        return;
    }
    TAG *no = busca(arvore, cod);
    if(!no){
        printf("Nó não encontrado!\n");
        return;
    }
    printf("%d|", no->cod);
    printf("%d|", no->pai);
    imprime_poligono(no->no->dados, no->no->tipo);
    printf(" %f", no->no->area);
    printf("\n");
}


//Recebe struct do poligono e usar poligono_id para calcular a area correta.
TAG* insere(TAG* arvore, int cod, int pai, void *poligono, enum poligono nome){
    if(pai == 0 && arvore){
        printf("Não é possível inserir uma nova raiz!\n");
        return arvore;
    }

    TAG *pai_aux =  busca(arvore, pai);
    if(!pai_aux && arvore){
        printf("Pai não encontrado.\n");
        return arvore;
    }

    TAG *novo = (TAG*)malloc(sizeof(TAG));
    novo->cod = cod;
    novo->pai = pai;
    novo->no = (TI*)malloc(sizeof(TI));
    novo->no->tipo = nome;
    novo->no->dados = poligono;
    novo->no->area = calcula_area(poligono, nome);
    novo->filho = NULL;
    novo->irmao = NULL; //insere como ultimo irmao.

    if(pai == 0) return novo;

    TAG *irmaos = pai_aux->filho;
    if(!irmaos){
        pai_aux->filho = novo;
        return arvore;
    }

    while(irmaos->irmao) irmaos = irmaos->irmao;
    irmaos->irmao = novo;

    return arvore;
}

TAG* inicializa(){
    return NULL;
}

TAG* remove_no(TAG* arvore, int cod, int cod_novo_pai);

//This is destroy. :)
void libera(TAG* arvore){
    if(arvore){
        libera(arvore->irmao);
        libera(arvore->filho);
        free(arvore->no->dados);
        free(arvore->no);
        free(arvore);
    }
}
#endif
