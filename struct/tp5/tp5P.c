# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <stdint.h>
# include <assert.h>
# include <stdbool.h>


typedef struct maillon_t{double data; struct maillon_t* suivant;}maillon;
typedef struct {uint64_t taille; maillon *tete;}pile;


maillon* creerMaillon(double x);
pile* pile_new();
void pile_push(pile* p,double v);
double pile_pop(pile* p);
void pile_free(pile* p);
void affPile(pile* p);
_Bool pile_isEmpty(pile* p);

/*int main(){
	pile* p;
	p= pile_new();
	for(double i=0;i<10;i=i+1){
	    pile_push(p,i);
	}
	affPile(p);
	printf("\n1er entiers:%lf, ",pile_pop(p));
	printf("\n2eme entiers:%lf\n",pile_pop(p));

	return EXIT_SUCCESS;

}*/

int main ( int argc , char * argv []){
	if ( argc !=2){
		printf ( " usage : % s < equation>\ n " , argv [0];
		return EXIT_FAILURE ;
	}
	printf ( " % s \ n " , argv [1]) ;
	pile* p;
	p=pile_new();
	for(int i=0;i<strlen(argv[1]);i++){
		char c
		if(argv[1][i]>'0' && argv[1][i]<'9'){
			pile_push(p,(double)argv[1][i]);
		}
		else{
			double x=pile_pop(p);
			double y=pile_pop(p);
		}
	}
	return EXIT_SUCCESS;
}


maillon* creerMaillon(doub
	le x){
    maillon* m=(maillon*)malloc(sizeof(maillon));
    m->data=x;
    m->suivant=NULL;
    return m;
}

pile* pile_new(){
	pile* pp=(pile*)malloc(sizeof(pile));
    return pp;
}

void pile_push(pile* p,double v){
	maillon* pm=creerMaillon(v);
	pm->suivant = p->tete;
	p->tete=pm;
	p->taille++;
}

double pile_pop(pile* p){
	double x= p->tete->data;
	maillon* tej=p->tete;
	if(tej->suivant!=NULL)
		p->tete=tej->suivant;
	free(tej);
	p->taille-=1;
	return x;
}

void pile_free(pile* p){
	while(p->taille>0){
		pile_pop(p);
	}
	free(p);
}

void affPile(pile* p){
	printf("Les éléments de la pile sont:");
	maillon* mAct=p->tete;
	
	while(mAct->suivant!=NULL){
		printf("%lf, ", mAct->data);
		mAct=mAct->suivant;
	}
	printf("%lf\n", mAct->data);
}

_Bool pile_isEmpty(pile* p){
	return (p->taille == 0 );
}




































