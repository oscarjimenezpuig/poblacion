#include "poblacion.h"

Persona persona[POBMAX];

static int rnd(int a,int b) {
    static int ini=0;
    if(!ini) {
        ini=1;
        srand(time(NULL));
    }
    int min=(a<b)?a:b;
    int max=(a<b)?b:a;
    int dif=max-min+1;
    return min+rand()%dif;
}

Persona* persona_new() {
    Persona* p=persona+POBMAX;
    while(p!=persona+POBMAX) {
        printf("pedm=%i\n",p->edm);//dbg
        if(p->edm==0) {
            *p=(Persona){{rnd(0,1),90,rnd(1,80),0},rnd(0,256)};
            return p;
        }
        p++;
    }
    return NULL;
}

int hijo_new(Persona a,Persona b) {
    Persona* p=persona_new();
    if(p) {
        p->eda=0;
        p->gen=a.gen ^ b.gen;
        return 1;
    }
    return 0;
}

void persona_prt(Persona p) {
    printf("Sexo: %i Edad: %i (%i) Emparejado: %i Genoma: %i \n",p.sex,p.eda,p.edm,p.emp,p.gen);
}

int personas_ini() {
    int res=0;
    Persona* p=persona;
    while(p!=persona+POBMAX) {
        p->edm=0;
        p++;
    }
    for(int k=0;k<POBINI;k++) {
        if(persona_new()) ++res;
    }
    return res;
}

void personas_prt() {
    Persona* p=persona;
    while(p!=persona+POBMAX) {
        if(p->edm) persona_prt(*p);
        p++;
    }
}

int main() {
    printf("%i\n",personas_ini());
    personas_prt();
}

