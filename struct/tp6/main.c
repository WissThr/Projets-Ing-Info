#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mypile_u32.h"


int main()
{
    pilepreall_u32* pa=pilepreall_u32_new();
    
    for (uint64_t i=0; i<200000000; i++)
    {
        if (rand() < RAND_MAX/3 && !Pile_u32_isEmpty(pa->occupes))
        {
            pilepreall_u32_pop(pa);
        }
        else
        {
            pilepreall_u32_push(pa, rand()%10000);
        }
    }
    
    printf("%ld\n", pa->occupes->taille);
    
	return(0);
}
