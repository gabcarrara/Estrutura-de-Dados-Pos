#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poligono.h"

//TO-DO: Modificar a entrada de arquivo, passando pelo terminal.
//TO-DO: Tratar a ultima linha da leitura de arquivo.
int main(void){
    FILE  * file = fopen("dataset.txt", "r");
    int a,b,d,e;
    char c[4], ch;
    char str[13];
    int str_size = 30;

    if(!file){
        printf("Error: arquivo não encontrado!\n");
         exit(EXIT_FAILURE);
    }
    while(fgets(str, str_size, file) != NULL){
        //sscanf(str, "%d/%d/%s %d %d", &a,&b,c,&d,&e);
        //printf("%d %d %s %d %d", a,b,c,d,e);
        int cod = atoi(strtok(str, "/"));
        int cod_par = atoi(strtok(NULL, "/"));
        char* nome_poli = strtok(NULL, " ");
        char* medidas = strtok(NULL, "");
        printf("%d %d %s %s\n", cod, cod_par, nome_poli, medidas);

        enum poligono cod_poli = string_to_enum(nome_poli);
        printf("%d", cod_poli);

    }

	fclose(file);

    return 0;
}
