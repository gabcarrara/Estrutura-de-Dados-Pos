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

//TO-DO: Criar switch e case para cada enum, modificar o parametro de entrada.
//Calcula area para um determinado poligono, se caso esse poligono nao existir, retorna -1.
float calcula_area(void* poligono, enum_poli nome){
    TCIR* teste = (TCIR*)malloc(sizeof(TCIR));
    TCIR* teste2;
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

    /* switch (nome)
    {
       case 1:
         TCIR* cir = (TCIR*)malloc(sizeof(TCIR));
         cir = poligono;
         area = M_PI*pow(cir->raio, 2);
       break;

       case QUA:
         TQUA* qua = (TQUA*) poligono;
         area = pow(qua->lado, 2);
       break;

       case RET:
         struct retangulo* ret = (struct retangulo*) poligono;
         area = ret->base*ret->altura;
       break;

       case TRI:
         TTRI* tri = (TTRI*) poligono;
         area = (tri->base*tri->altura)/2;
       break;

       case TRA:
         TTRA* tra = (TTRA*) poligono;
         area = ((tra->base_menor+tra->base_maior)*tra->altura)/2;
       break;

       default:
         area = -1;
    }
    return area;*/
}
