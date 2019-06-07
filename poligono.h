#ifndef _poligono_h
#define _poligono_h

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct circulo{
    float raio;
}TCIR;

typedef struct quadrado{
    float lado;
}TQUA;

typedef struct retangulo{
    float base;
    float altura;
}TRET;

typedef struct triangulo{
    float base;
    float altura;
}TTRI;

typedef struct trapezio{
    float base_menor;
    float base_maior;
    float altura;
}TTRA;


enum poligono {
    CIR = 1,
    QUA = 2,
    RET = 3,
    TRI = 4,
    TRA = 5
};
typedef enum poligono enum_poli ;

float string_to_enum(char* nome){
    if(!strcmp(nome, "CIR")){
        return CIR;
    }else if(!strcmp(nome, "QUA")){
        return QUA;
    }else if(!strcmp(nome, "RET")){
        return RET;
    }else if(!strcmp(nome, "TRI")){
        return TRI;
    }else if(!strcmp(nome, "TRA")){
        return TRA;
    }
    return -1;
}

void* cria(enum_poli nome, int* values){
    if(nome==CIR){
        TCIR* cir = (TCIR*)malloc(sizeof(TCIR));
        cir->raio = values[0];
        return cir;
    }else if(nome==QUA){
        TQUA* qua = (TQUA*)malloc(sizeof(TQUA));
        qua->lado=values[0];
        return qua;
    }else if(nome==RET){
        TRET* ret = (TRET*)malloc(sizeof(TRET));
        ret->base=values[0];
        ret->altura=values[1];
        return ret;
    }else if(nome==TRI){
        TTRI* tri = (TTRI*)malloc(sizeof(TTRI));
        tri->base=values[0];
        tri->altura=values[1];
        return tri;
    }else if(nome==TRA){
        TTRA* tra = (TTRA*)malloc(sizeof(TTRA));
        tra->base_menor=values[0];
        tra->base_maior=values[1];
        tra->altura=values[2];
        return  tra;
    }
    return NULL;
}

//Calcula area para um determinado poligono, se caso esse poligono nao existir, retorna -1.
float calcula_area(void* poligono, enum_poli nome){
    if(nome==CIR){
        TCIR* cir = poligono;
        return M_PI*pow(cir->raio, 2);
    }else if(nome==QUA){
        TQUA* qua = poligono;
        return pow(qua->lado, 2);
    }else if(nome==RET){
        TRET* ret = poligono;
        return ret->base*ret->altura;
    }else if(nome==TRI){
        TTRI* tri = poligono;
        return (tri->base*tri->altura)/2;
    }else if(nome==TRA){
        TTRA* tra = poligono;
        return ((tra->base_menor+tra->base_maior)*tra->altura)/2;
    }
    return -1;
}

void imprime_poligono(void* poligono, enum_poli nome){
    if(nome==CIR){
        TCIR* cir = poligono;
        printf("CIR [ %f ]", cir->raio);
    }else if(nome==QUA){
        TQUA* qua = poligono;
        printf("QUA [ %f ]", qua->lado);
    }else if(nome==RET){
        TRET* ret = poligono;
        printf("RET [ %f %f ]", ret->base, ret->altura);
    }else if(nome==TRI){
        TTRI* tri = poligono;
        printf("TRI [ %f %f ]", tri->base, tri->altura);
    }else if(nome==TRA){
        TTRA* tra = poligono;
        printf("TRA [ %f %f %f ]", tra->base_menor, tra->base_maior, tra->altura);
    }
}

//TO-DO: Atualiza as dimencoes do poligono.

#endif
