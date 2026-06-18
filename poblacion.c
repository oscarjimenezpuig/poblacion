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

static int normal() {
    int const NORM[]={0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,8,8,9};
    const int SUMA=300;
    int numero=rnd(0,SUMA);
    int edad=0;
    for(;edad<=128;edad++) {
        if(edad<=40) numero-=NORM[edad];
        else if(edad>40 && edad<=80) numero-=NORM[80-edad];
        else numero-=1;
        if(numero==0) return edad;
    }
    return 0;
}

Persona* persona_new(int emi,int ema) {
    Persona* p=persona;
    while(p!=persona+POBMAX) {
        if(p->edm==0) {
            *p=(Persona){{rnd(0,1),rnd(emi,ema),normal()},rnd(0,256)};
            while(p->eda>=p->edm) {
                p->edm=normal();
            }
            if(p->gen==0){
                p->edm/=2;
                if(p->edm<p->eda) p->edm=p->eda;
            } else if(p->gen==256) {
                int e=p->edm*2;
                e=(e>128)?128:e;
                p->edm=e;
            }
            return p;
        }
        p++;
    }
    return NULL;
}

int hijo_new(Persona a,Persona b) {
    Persona* p=persona_new(0,0);
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
        if(persona_new(20,40)) ++res;
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

void emparejar() {
    //edad de emparejamiento 15 a 45
    const int PTH=10; //probabilidad de tener hijos
    for(int m=0;m<POBMAX;m++) {
        Persona* a=persona+m;
        if(a->eda>=15 && a->eda<=45 && a->gen!=0 && a->gen!=256 && a->emp==0) {
            for(int n=m+1;n<POBMAX;n++) {
                Persona* b=persona+n;
                if(b->eda>=15 && b->eda<=45 && b->gen!=0 && b->gen!=256 && b->emp==0 && b->sex!=a->sex) {
                    a->emp=b->emp=1;
                    if(rnd(0,99)<PTH) hijo_new(*a,*b);                
                    break;
                }
            }
        }
    }
}

int main() {
    printf("%i\n",personas_ini());
    emparejar();
    personas_prt();
}

