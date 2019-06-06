#ifndef _generic_tree_h
#define _generic_tree_h

#include <stdlib.h>
#include "poligono.h"

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
        printf("Arvore nula!");
        return;
    }
    TAG *no = busca(arvore, cod);
    if(!no){
        printf("Nó não encontrado!");
        return;
    }
    printf("Codigo unico: %d", no->cod);
    printf("Pai: %d", no->pai);
    printf("Tipo do poligono: %d", no->no->tipo);
    //imprime_poligono(no->no->dados, no->no->tipo);
    printf("Area do poligono: %f", no->no->area );
}
//Recebe struct do poligono e usar poligono_id para calcular a area correta.
TAG* insere(TAG* arvore, int cod, int pai, void *poligono, enum poligono nome){

    if(pai == 0 && arvore!= NULL){
        printf("Não é possível inserir uma nova raiz!\n");
        return arvore;
    }

    TAG *pai_aux =  busca(arvore, pai);
    if(!pai_aux){
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
