#include "mypile_u32.h"


pile_u32 *Pile_u32_new()
{
    pile_u32 *p = calloc(1, sizeof(pile_u32));
    
    if(p==NULL)
    {
        fprintf(stderr, "Pile_u32_new : Erreur Allocation Memoire.\n");
        return(NULL);
    }
    
    return p;
}


_Bool Pile_u32_isEmpty(pile_u32 *p)
{
    return p->tete==NULL;
}


maillon_u32 *Maillon_u32_new()
{
    maillon_u32 *m = calloc(1, sizeof(maillon_u32));
    
    if(m==NULL)
    {
        fprintf(stderr, "Maillon_u32_new : Erreur Allocation Memoire.\n");
        return(NULL);
    }

    return m;
}


maillon_u32* Pile_u32_pop(pile_u32 *p)
{
    maillon_u32 *tmp;
    
    if (Pile_u32_isEmpty(p))
    {
        fprintf(stderr, "Erreur : Pile_u32_pop alors que la pile est vide.\n");
        assert(0);
    }
    
    tmp = p->tete;
    p->tete = p->tete->next;
    p->taille-=1;
    return(tmp);
}


void Pile_u32_push(pile_u32 *p, maillon_u32* d)
{
    d->next = p->tete;
    p->tete = d;
    p->taille+=1;
}


void Pile_u32_free(pile_u32 *p)
{
    while (!Pile_u32_isEmpty(p))
        free(Pile_u32_pop(p));
    free(p);
}

/*///////////////////////////////////////////////////////////////////////
																		/
						PILE PRE ALL									/
																		/
///////////////////////////////////////////////////////////////////////*/



pilepreall_u32* pilepreall_u32_new(){
	pile_u32* p=Pile_u32_new();
	pile_u32* po=Pile_u32_new();
	pilepreall_u32* pa= calloc(1, sizeof(pilepreall_u32));
	pa->libres=p;
	pa->occupes=po;
    
    if(pa==NULL)
    {
        fprintf(stderr, "Pile_u32_new : Erreur Allocation Memoire.\n");
        return(NULL);
    }
    return pa;
}

_Bool pilepreall_u32_isEmpty(pilepreall_u32* pa){
	return Pile_u32_isEmpty(pa->occupes);
}

uint32_t pilepreall_u32_pop(pilepreall_u32* pa){
	maillon_u32* m=Pile_u32_pop(pa->occupes);
	uint32_t e=m->data;
	Pile_u32_push(pa->libres,m);
	return e;
}

void pilepreall_u32_push(pilepreall_u32* pa, uint32_t e){
	if(Pile_u32_isEmpty(pa->libres)){
		creerNvlLibre(pa);
	}
	
	Pile_u32_push(pa->occupes,Pile_u32_pop(pa->libres));
	pa->occupes->tete->data=e;
}

void creerNvlLibre(pilepreall_u32* pa){
	uint64_t t = 2*(pa->occupes->taille+1);
	maillon_u32* m=calloc(t, sizeof(maillon_u32));
	printf("%llu\n", t);
	for(int i=0;i<t-1;i++){
		m[i].next=&m[i+1];
	}
	pa->libres->tete=m;
}


















































