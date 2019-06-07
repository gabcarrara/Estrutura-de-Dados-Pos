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
    char* nome_poli;
    int *values = (int*)malloc(sizeof(int)*3);
    char * val;
    printf("COD|COD_PAI|POLIGONO [MEDIDAS] AREA\n");
    while(getline(&line, &str_size, file) != -1){
        //sscanf(line, "%d/%d/%s %d %d", &cod, &cod_pai, nome_poli, &values[0], &values[1]);
        //printf("%d %d %s %d %d\n", cod, cod_pai, nome_poli, values[0], values[1]);

        int cod = atoi(strtok(line, "/"));
	    int cod_pai = atoi(strtok(NULL, "/"));
	    char* nome_poli = strtok(NULL, " ");
        char* medidas = strtok(NULL, "");

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

        imprime_no(arvore, cod);
    }
    
    imprime(arvore);
    
    arvore = libera(arvore);
    
    if(line) free(line);

	fclose(file);

    return 0;
}
