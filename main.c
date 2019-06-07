#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poligono.h"
#include "generic_tree.h"
#include "avl.h"

//TO-DO: Modificar a entrada de arquivo, passando pelo terminal.
int main(void){
    FILE  * file = fopen("dataset.txt", "r");

    TAG *arvore = inicializa();
    //NO *avl = NULL;

    if(!file){
        printf("Error: arquivo não encontrado!\n");
         exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t str_size = 0;

    int cod, cod_pai;
    char* nome_poli, *medidas;
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
        avl = insere_avl(cod, avl, busca(arvore, cod));
        //imprime_no(arvore, cod);
    }
    //printf("COD|COD_PAI|POLIGONO [MEDIDAS] AREA\n");

    int exit = 0;
    char codline[30], dados[30];
    char* decode, *action;
    while(!exit){
        printf("/>");
        scanf("%s", codline);
        printf("codline: %s\n", codline);

        if(!strcmp(codline, "insert")){
            //insert 15 10 TRI 1 1
            scanf("%d", &cod);
            scanf("%d", &cod_pai);
            scanf("%s", nome_poli);
            scanf("%[^\n\r]", dados);

            medidas = strtok(dados, "");
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
            scanf("%d", &cod);
            scanf("%d", &cod_pai);
            arvore = remove_no(arvore, cod, cod_pai);

        }else if(!strcmp(codline, "destroy")){
            arvore = libera(arvore);

        }else if(!strcmp(codline, "print_no")){
            scanf("%[^\n\r]", dados);
            int no = atoi(dados);
            imprime_no(arvore, no);

        }else if(!strcmp(codline, "print")){
            imprime(arvore);
            printf("\nAVL\n");
            imprime_avl(avl);

        }else if(!strcmp(codline, "exit")){
            exit = 1;
        }else if(!strcmp(codline, "help")){
            printf("\n");
            printf("################# Command List ###############\n");
            printf("#\tinsert cod_no cod_pai cod_poli x y z #\n");
            printf("#\tremove cod_no novo_pai               #\n");
            printf("#\tdestroy                              #\n");
            printf("#\tprint_no cod_no                      #\n");
            printf("#\tprint                                #\n");
            printf("#\texit                                 #\n");
            printf("##############################################");
            printf("\n\n");
        }else{
            printf("Comando nao encontrado!");
        }
    }

    arvore = libera(arvore);

    if(line) free(line);

	fclose(file);

    return 0;
}
