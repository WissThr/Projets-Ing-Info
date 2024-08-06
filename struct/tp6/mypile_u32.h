#ifndef __MYPILE_U32_H__
#define __MYPILE_U32_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>


typedef struct maillon_u32
{
    struct maillon_u32 *next;
    uint32_t data;
} maillon_u32;

typedef struct maillon_as
{
    struct maillon_as *next;
    maillon_u32* adresse;
} maillon_a;


typedef struct pile_u32
{
    maillon_u32 *tete;
    uint64_t taille;
} pile_u32;


typedef struct pilepreall_u32
{
	pile_u32 * occupes ;
	pile_u32 * libres ;
	pile_u32 ** a;
} pilepreall_u32 ;


pile_u32 *Pile_u32_new();
maillon_u32* Pile_u32_pop(pile_u32 *p);
_Bool Pile_u32_isEmpty(pile_u32 *p);
void Pile_u32_push(pile_u32 *p, maillon_u32* d);
maillon_u32* Maillon_u32_new();

pilepreall_u32* pilepreall_u32_new();
_Bool pilepreall_u32_isEmpty(pilepreall_u32* pa);
void pilepreall_u32_push(pilepreall_u32* pa, uint32_t e);
uint32_t pilepreall_u32_pop(pilepreall_u32* pa);
void creerNvlLibre(pilepreall_u32* pa);


#endif
