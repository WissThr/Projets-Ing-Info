
#include "mypile_u32.h"

pile_u32 **Pile_u32_new()
{
    pile_u32 **p = calloc(1, sizeof(pile_u32*));
    
    if(p==NULL)
    {
        fprintf(stderr, "Pile_u32_new : Erreur Allocation Memoire.\n");
        return(NULL);
    }
    
    return p;
}


_Bool Pile_a_isEmpty(pile_u32 **p)
{
    return p->tete==NULL;
}


maillon_a *Maillon_a_new()
{
    maillon_a *m = calloc(1, sizeof(maillon_a));
    
    if(m==NULL)
    {
        fprintf(stderr, "Maillon_u32_new : Erreur Allocation Memoire.\n");
        return(NULL);
    }

    return m;
}


maillon_a* Pile_a_pop(pile_u32 **p)
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
