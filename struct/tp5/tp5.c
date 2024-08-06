# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <stdint.h>
# include <assert.h>

typedef struct maillon_t{uint32_t data; struct maillon_t* suivant;}maillon;
typedef struct{maillon* tete; maillon* queue;}liste;

liste* creerListe();
maillon* creerMaillon(uint32_t x);
void addDébutListe(liste* l, uint32_t x);
void afficherListe(liste l);
uint32_t popListe(liste* l);



int main (){
printf("1\n");
fflush(NULL);
liste* pl;
printf("1\n");
fflush(NULL);
pl=creerListe();
printf("2\n");
fflush(NULL);
for(int i=0;i<10;i++){
    addDébutListe(pl,i);
}
printf("affListe:");
fflush(NULL);
afficherListe(*pl);
printf("\n1er entiers:%d, ",popListe(pl));
printf("\n2eme entiers:%d\n",popListe(pl));
afficherListe(*pl);
free(pl);
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
