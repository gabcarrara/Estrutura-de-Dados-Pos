#include <stdio.h>

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
typedef enum poligono tipo_poli ;

//TO-DO: Criar switch e case para cada enum, modificar o parametro de entrada.
float calculo_area(tipo_poli poli){

    return 0.0;
}
