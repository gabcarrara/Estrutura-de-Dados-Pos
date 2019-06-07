#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poligono.h"
#include "generic_tree.h"

//TO-DO: Modificar a entrada de arquivo, passando pelo terminal.
int main(void){    
    FILE  * file = fopen("dataset.txt", "r");

    TAG* arvore = (TAG*)malloc(sizeof(TAG));
    arvore = inicializa();


    if(!file){
        printf("Error: arquivo não encontrado!\n");
         exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t str_size = 0;

    int cod, cod_pai;
    char* nome_poli, * medidas;
    int *values = (int*)malloc(sizeof(int)*3);
    char * val;
    while(getline(&line, &str_size, file) != -1){
        int cod = atoi(strtok(line, "/"));
	    int cod_pai = atoi(strtok(NULL, "/"));
	    nome_poli = strtok(NULL, " ");
        medidas = strtok(NULL, "");

        for(int i=0; i<3; i++){
            values[i] = 0;
        }

        int i=0;
        while(medidas!=NULL){
            val = strtok(medidas, " ");
            values[i] = atoi(val);
            medidas = strtok(NULL, "");
            i++;
        }

        enum poligono cod_poli = string_to_enum(nome_poli);
        void * poli = cria(cod_poli, values);
        arvore = insere(arvore, cod, cod_pai, poli, cod_poli);
        //imprime_no(arvore, cod);
    }
    //printf("COD|COD_PAI|POLIGONO [MEDIDAS] AREA\n");

    //insere no
    //remove no
    //destroy Arvore
    //imprime no
    //imprime Arvore
    int exit = 0;
    char codline[30];
    char* decode, *action;
    while(!exit){
        printf("\n");
        printf("insert cod_no cod_pai cod_poli x y z\n");
        printf("remove cod_no novo_pai\n");
        printf("destroy\n");
        printf("print_no cod_no\n");
        printf("print\n");
        printf("exit\n");
        printf("\n");

        scanf("%s", codline);
        printf("codline: %s\n", codline);

        if(!strcmp(codline, "insert")){
            scanf("%d", &cod);
            scanf("%d", &cod_pai);
            scanf("%s", nome_poli);
            scanf("%d %d %d", &values[0], &values[1], &values[2]);

            /*for(int i=0; i<3; i++){
                values[i] = 0;
            }
            int i=0;
            while(medidas!=NULL){
                val = strtok(medidas, " ");
                values[i] = atoi(val);
                medidas = strtok(NULL, "");
                i++;
            }*/

            enum poligono cod_poli = string_to_enum(nome_poli);
            void * poli = cria(cod_poli, values);
            arvore = insere(arvore, cod, cod_pai, poli, cod_poli);

        }else if(!strcmp(codline, "remove")){
            exit = 1;

        }else if(!strcmp(codline, "destroy")){
            libera(arvore);

        }else if(!strcmp(codline, "print_no")){
            int no = -1;
            scanf("%d", &no);
            printf("no: %d\n", no);
            imprime_no(arvore, no);

        }else if(!strcmp(codline, "print")){
            imprime(arvore);

        }else if(!strcmp(codline, "exit")){
            exit = 1;
        }else{
            printf("Comando nao encontrado!");
        }
    }

    imprime(arvore);

    arvore = libera(arvore);

    if(line) free(line);

	fclose(file);

    return 0;
}
