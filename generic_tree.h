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

void imprime_aux(TAG *arvore, int nivel){
    if(arvore){
        printf("%d<-%d",arvore->pai, arvore->cod);
        if(arvore->irmao){
            printf("\t");
            imprime_aux(arvore->irmao, nivel+1);
        }

        if(arvore->filho){
            printf("\n");
            for(int i=0 ; i< nivel; i++) printf("\t");
            imprime_aux(arvore->filho, nivel);
        }
    }
}

void imprime(TAG *arvore){
    if(arvore){
        printf("\n############## GENERIC TREE ##############\n");
        imprime_aux(arvore, 0);
        printf("\n##########################################\n\n");
    }
}

void imprime_no(TAG *arvore, int cod){
    if(!arvore){
        printf("Arvore nula!\n");
        return;
    }
    if(cod==-1){
        printf("No invalido!\n");
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

void realoca_filhos(TAG *pai_antigo, TAG *pai_novo){

    TAG *irmao_temp = pai_antigo->filho;
    while(irmao_temp){
        irmao_temp->pai=pai_novo->cod;
        irmao_temp = irmao_temp->irmao;
    }
    irmao_temp = pai_antigo->filho;

    if(!pai_novo->filho){
        pai_novo->filho=irmao_temp;
        return;
    }
    TAG *irmao_novo = pai_novo->filho;
    while(irmao_novo->irmao) irmao_novo=irmao_novo->irmao;
    irmao_novo->irmao = irmao_temp;
    return;

}
TAG* remove_no(TAG* arvore, int cod, int cod_novo_pai){
    //Verifica se a arvore existe
    if(!arvore){
        printf("Arvore invalida\n");
        return arvore;
    }
    //Verifica se o novo pai existe
    TAG *novo_pai_temp = busca(arvore, cod_novo_pai);
    if(!novo_pai_temp){
        printf("Novo pai invalido\n");
        return arvore;
    }
    //verifica se o no a ser removido existe
    TAG *temp = busca(arvore, cod);
    if(!temp || temp->pai==0){
        printf("No invalido\n");
        return arvore;
    }
    //Busca o pai do no a ser removido
    TAG *pai_temp = busca(arvore, temp->pai);
    //Pega o irmao do no a ser removido
    TAG *irmao_temp = pai_temp->filho;

    //Caso o no seja o primeiro filho
    if(irmao_temp == temp){
        realoca_filhos(temp, novo_pai_temp);
        pai_temp->filho = irmao_temp->irmao;
        imprime_no(temp, temp->cod);
        free(temp->no->dados);
        free(temp->no);
        free(temp);
        return arvore;
    }
    //Caso o no estaja no meio ou no fim da lista de irmaos
    TAG *irmao_ant = irmao_temp;
    irmao_temp = irmao_temp->irmao;

    while(irmao_temp->irmao != temp){
        irmao_ant = irmao_temp;
        irmao_temp = irmao_temp->irmao;
    }
    realoca_filhos(temp, novo_pai_temp);
    irmao_ant->irmao = temp->irmao;
    imprime_no(temp, temp->cod);
    free(temp->no->dados);
    free(temp->no);
    free(temp);
    return arvore;

}

//This is destroy. :)
TAG* libera(TAG* arvore){
    if(arvore){
        libera(arvore->irmao);
        libera(arvore->filho);
        free(arvore->no->dados);
        free(arvore->no);
        free(arvore);
    }
    return NULL;
}

//TO-DO: Atualizar pai.

void atualiza_poligono(TAG *arvore, int cod, int* values){


}


#endif
