#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poligono.h"

//TO-DO: Modificar a entrada de arquivo, passando pelo terminal.
//TO-DO: Tratar a ultima linha da leitura de arquivo.
int main(void){
    FILE  * file = fopen("dataset.txt", "r");
    int a,b,d,e,f;
    char *line = NULL;
    
    //char c[4], ch;
    char str[13];
    size_t str_size = 0;

    if(!file){
        printf("Error: arquivo não encontrado!\n");
         exit(EXIT_FAILURE);
    }
    while(getline(&line, &str_size, file) != -1){
        sscanf(line, "%d/%d/%s %d %d %d", &a, &b, str, &d, &e, &f);
        
        printf("%d %d %s %d %d %d\n", a,b,str,d,e,f);
        //int cod = atoi(strtok(str, "/"));
        //int cod_par = atoi(strtok(NULL, "/"));
        //char* nome_poli = strtok(NULL, " ");
        //char* medidas = strtok(NULL, "");
        //printf("%d %d %s %s\n", cod, cod_par, nome_poli, medidas);

        enum poligono cod_poli = string_to_enum(str);
        printf("%d", cod_poli);

    }
    
    if(line) free(line);
    
	fclose(file);

    return 0;
}
