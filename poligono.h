#include <stdio.h>
#include <math.h>

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

//TO-DO: Criar switch e case para cada enum, modificar o parametro de entrada.
//Calcula area para um determinado poligono, se caso esse poligono nao existir, retorna -1.
float calcula_area(void* poligono, enum_poli nome){
    float area = 0.0;
    switch (nome)
    {
       case CIR:
         cir = (circulo*) poligono;
         area = M_PI*pow(cir->raio, 2);
       break;

       case QUA:
         qua = (quadrado*) poligono;
         area = pow(qua->lado, 2);
       break;

       case RET:
         ret = (retangulo*) poligono;
         area = ret->base*ret->altura;
       break;

       case TRI:
         tri = (triangulo*) poligono;
         area = (tri->base*tri->altura)/2;
       break;

       case TRA:
         tra = (trapezio*) poligono;
         area = ((tra->base_menor+tra->base_maior)*tra->altura)/2;
       break;

       default
         area = -1;
    }
    return area;
}
