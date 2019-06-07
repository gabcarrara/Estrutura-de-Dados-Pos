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
    char* codline;
    char* decode, action_codline;
    while(!exit){
        printf("insert cod_no cod_pai cod_poli x y z\n");
        printf("remove cod_no novo_pai\n");
        printf("destroy\n");
        printf("print_no cod_no\n");
        printf("print\n");
        printf("exit\n");

        scanf("%s", codline);
        codline = strtok(codline, "");
        int i=0;
        while(codline!=NULL){
            codline = strtok(codline, " ");
            printf("%s", codline);

            if(!strcmp(codline, "insert")){
                cod = atoi(strtok(NULL, " "));
                cod_pai = atoi(strtok(NULL, " "));
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

            }else if(!strcmp(codline, "remove")){
                exit = 1;

            }else if(!strcmp(codline, "destroy")){
                libera(arvore);

            }else if(!strcmp(codline, "print_no")){
                int no = atoi(strtok(NULL, ""));
                imprime_no(arvore, no);

            }else if(!strcmp(codline, "print")){
                imprime(arvore);

            }else if(!strcmp(codline, "exit")){
                exit = 1;
            }

            //codline = strtok(NULL, "");
        }
    }

    libera(arvore);

    if(line) free(line);

	fclose(file);

    return 0;
}
