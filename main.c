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
    while(getline(&line, &str_size, file) != -1){
        sscanf(line, "%d/%d/%s %d %d %d", &cod, &cod_pai, nome_poli, &values[0], &values[1], &values[2]);

        printf("%d %d %s %d %d %d\n", cod, cod_pai, nome_poli, values[0], values[1], values[2]);


        enum poligono cod_poli = string_to_enum(nome_poli);
        printf("%d", cod_poli);

        //void * poli = cria(cod_poli, values);

        //TAG* insere(arvore, cod, cod_pai, poli, cod_poli);

    }

    if(line) free(line);

	fclose(file);

    return 0;
}
