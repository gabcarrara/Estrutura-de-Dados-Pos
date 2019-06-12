#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poligono.h"
#include "generic_tree.h"
#include "avl.h"
#include "b_tree.h"

void help(void){
    //TO-DO: Imprime AVL
    printf("\n");
    printf("################## COMMAND LIST #################\n");
    printf("#\tinsert cod_no cod_pai cod_poly x y z \t#\n");
    printf("#\tupdate_polygon cod_no cod_poly x y z \t#\n");
    printf("#\tremove cod_no novo_pai               \t#\n");
    printf("#\tdestroy                              \t#\n");
    printf("#\tprint_no cod_no                      \t#\n");
    printf("#\tprint_generic                        \t#\n");
    printf("#\tgeneric_to_balanced                  \t#\n");
    printf("#\tgeneric_to_b                         \t#\n");
    printf("#\texit                                 \t#\n");
    printf("#\thelp                                 \t#\n");
    printf("#################################################");
    printf("\n\n");
}

//TO-DO: Modificar a entrada de arquivo, passando pelo terminal.
int main(int argc, char **argv){

	//printf("%s", argv[1]);
	char *file_name = argv[1];

	if(!file_name){
		printf("Sem parametro de entrada para nome de arquivo\n");
		exit(EXIT_FAILURE);
	}

	FILE  * file = fopen(file_name, "r");
    TAG *arvore = inicializa();
    NO *avl = inicializa_avl();
    TAB *b = inicializa_b();
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

        int i=0, controle=1;
        while(medidas!=NULL){
            val = strtok(medidas, " ");
            values[i] = atoi(val);
            if(values[i]<0) controle=0;
            medidas = strtok(NULL, "");
            i++;
        }
        if(controle){
            enum poligono cod_poli = string_to_enum(nome_poli);
            if(!cod_poli) {
                printf("Cod_poly inválido!\n");
            }else{
                void * poli = cria(cod_poli, values);
                arvore = insere(arvore, cod, cod_pai, poli, cod_poli);
            }
        }else{
            printf("Medida inválida!\n");
        }
    }

    int exit = 0;
    char codline[30], dados[30];
    char* decode, *action;
    help();
    while(!exit){
        printf("/>");
        scanf("%s", codline);

        if(!strcmp(codline, "insert")){
            //insert 15 10 TRI 1 1
            scanf("%d", &cod);
            scanf("%d", &cod_pai);
            scanf("%s", nome_poli);
            scanf("%[^\n\r]", dados);

            medidas = strtok(dados, "");
            int i=0, controle=1;
            while(medidas!=NULL){
                val = strtok(medidas, " ");
                values[i] = atoi(val);
                if(values[i]<0) controle=0;
                medidas = strtok(NULL, "");
                i++;
            }
            if(controle){
                enum poligono cod_poli = string_to_enum(nome_poli);
                if(!cod_poli) {
                    printf("Cod_poly inválido!\n");
                }else{
                    void * poli = cria(cod_poli, values);
                    arvore = insere(arvore, cod, cod_pai, poli, cod_poli);
                }
            }else{
                printf("Medida inválida!\n");
            }

        }else if(!strcmp(codline, "update_polygon")){
            //update_polygon 1 CIR 10
            scanf("%d", &cod);
            scanf("%s", nome_poli);
            scanf("%[^\n\r]", dados);

            medidas = strtok(dados, "");
            int i=0, controle=1;
            while(medidas!=NULL){
                val = strtok(medidas, " ");
                values[i] = atoi(val);
                if(values[i]<0) controle=0;
                medidas = strtok(NULL, "");
                i++;
            }

            if(controle){
                enum poligono cod_poli = string_to_enum(nome_poli);
                if(!cod_poli) {
                    printf("Cod_poly inválido!\n");
                }else{
                    atualiza_poligono(arvore, cod, cod_poli, values);
                }
            }else{
                printf("Medida inválida!\n");
            }

        }else if(!strcmp(codline, "remove")){
            scanf("%d", &cod);
            scanf("%d", &cod_pai);
            arvore = remove_no(arvore, cod, cod_pai);

        }else if(!strcmp(codline, "destroy")){
            arvore = libera(arvore);

        }else if(!strcmp(codline, "print_no")){
            scanf("%[^\n\r]", dados);
            int cod_no = atoi(dados);
            imprime_no(arvore, cod_no);

        }else if(!strcmp(codline, "print_generic")){
            imprime(arvore);

        }else if(!strcmp(codline, "generic_to_balanced")){
            avl = generic_to_avl(arvore, avl);
            if(!avl){
                printf("Arvore vazia!\n");
            }else{
                printf("\n############## BALANCED TREE ##############\n");
                imprime_avl(avl);
                printf("##############################################");
                printf("\n\n");
                printf("\n########## BALANCED TREE - Polygon ##########\n");
				printf("COD | COD_PAI | POLIGONO | AREA\n");
                imprime_poly_avl(avl);
                printf("##############################################");
                printf("\n\n");
                libera_avl(avl);
            }

        }else if(!strcmp(codline, "generic_to_b")){
            b = generic_to_b(arvore, b);
            if(!b){
                printf("Arvore vazia!\n");
            }else{
                printf("\n################### B TREE #################\n");
                Imprime(b,0);
                printf("##############################################");
                printf("\n\n");
                printf("\n############### B TREE - Polygon #############\n");
				printf("COD | COD_PAI | POLIGONO | AREA\n");
                imprime_poly_b(b);
                printf("##############################################");
                printf("\n\n");
                b = libera_b(b);
            }

        }else if(!strcmp(codline, "exit")){
            exit = 1;
        }else if(!strcmp(codline, "help")){
            help();
        }else{
            printf("Comando nao encontrado!\n");
        }

		int c;
		while ((c = getchar()) != '\n' && c != EOF);

    }

    arvore = libera(arvore);

    if(line) free(line);

	fclose(file);

    return 0;
}
