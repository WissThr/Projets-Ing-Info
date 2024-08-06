# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <stdint.h>
# include <assert.h>
# include <stdbool.h>

typedef struct maillon_t{uint32_t data; struct maillon_t* suivant;}maillon;
typedef struct{maillon* tete; maillon* queue;}liste;
typedef struct {uint64_t taille; maillon *tete;}pile;

liste* creerListe();
maillon* creerMaillon(uint32_t x);
void addDébutListe(liste* l, uint32_t x);
void afficherListe(liste l);
uint32_t popListe(liste* l);
pile * pile_new();
void pile_push(pile* p,double v);
double pile_pop(pile*p);
void pile_free(pile*p);




int main (){
	liste* pl;
	pl=creerListe();
	for(int i=0;i<10;i++){
	    addDébutListe(pl,i);
	}
	afficherListe(*pl);
	printf("\n1er entiers:%d, ",popListe(pl));
	printf("\n2eme entiers:%d\n",popListe(pl));
	afficherListe(*pl);

	return EXIT_SUCCESS;

}

liste* creerListe(){
    liste* pl=(liste*)malloc(sizeof(liste));
    return pl;
}

maillon* creerMaillon(uint32_t x){
    maillon* m=(maillon*)malloc(sizeof(maillon));
    m->data=x;
    m->suivant=NULL;
    return m;
}

void addDébutListe(liste* l, uint32_t x){
    maillon* m = creerMaillon(x);
    if(l->queue ==NULL){
            l->queue=m;
            l->tete=m;
    }
    else{
        m->suivant=l->tete;
        l->tete=m;
    }
}

void afficherListe(liste l){
    maillon* mAct=l.tete;
    while(mAct!=l.queue){
        printf("%d, ",mAct->data);
        mAct=mAct->suivant;
    }
    printf("%d, ",l.queue->data);
}

uint32_t popListe(liste* l){
    assert( l->tete!=NULL);
    uint32_t x=l->tete->data;
    maillon* pt=l->tete;
    l->tete=l->tete->suivant;
    if(l->tete==NULL)
        l->queue=NULL;
    free(pt);
    return x;
}

pile * pile_new(){
    pile * face = malloc(sizeof(pile));
    face->taille = 0;
    face->tete= NULL;
    return face;
}

void pile_push(pile* p,double v){
    maillon * m = creerMaillon(v);
    if(p->taille!=0)
        m->suivant=p->tete;
    p->tete=m;
    p->taille=p->taille+1;
}

double pile_pop(pile*p){
    if(pileisempty(p)){
        assert(0);
    }
    maillon*m = p->tete;
    double v = m->data;
    p->tete=p->tete->suivant;
    p->taille=p->taille -1;
    free(m);
    return v;
}

void pile_free(pile*p){
    assert(p->tete!=NULL);
    maillon* m=p->tete;
    maillon* temp;
    while(m->suivant!=NULL){
        temp=m->suivant;
        free(m);
        m=temp;
    }
    free(m);
}

void pile_affiche(pile * p){
    assert(p->tete!=NULL);
    maillon* m=p->tete;
    while(m->suivant!=NULL){
        printf("%f, ",m->data);
        m=m->suivant;
    }
    printf("%f, ",m->data);
}

bool pileisempty(pile*p){
    if(p->taille==0)
        return true;
    else
        return false;
}
