#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define POBMAX 65535
#define POBINI 100

typedef unsigned char u1;

typedef struct {
    struct {
        u1 sex : 1;
        u1 eda : 7;
        u1 edm : 7;
        u1 emp : 1;
    };
    u1 gen;
} Persona;


extern Persona persona[POBMAX];

Persona* persona_new(int edad_min,int edad_max);

int hijo_new(Persona a,Persona b);

void persona_prt(Persona p);

int personas_ini();

void personas_prt();

void emparejar();

void hijos();

void muerte();





