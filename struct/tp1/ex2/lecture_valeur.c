#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#define TAILLE_CHAINE 30

typedef enum { DOUBLE , LONG , ULONG } TypeGenerique ;

typedef struct{
	TypeGenerique type ;
	union{
		double d ;
		uint64_t u ;
		int64_t i ;
	} data ;
} generique ;

generique demanderValeur(){
    char chaine[TAILLE_CHAINE];
    char *pc, c;
    uint32_t cpt_points, cpt_neg, cpt_nondigit;
    uint32_t i;
    
    generique gen;
    
    
    double rd;
    uint64_t rul;
    int64_t rl;
    
    
    //On recupere la chaine entree par l'utilisateur
    fgets(chaine, sizeof(chaine), stdin);
    
    //On doit faire un petit nettoyage après au cas où l'utilisateur ait entré plus de caractères que nécessaire (plus de TAILLE_CHAINE)...
    if(strchr(chaine, '\n') == NULL) //Ah, pas de retour a la ligne dans chaine : l'utilisateur a tapé trop de caractères
    {
        c = fgetc(stdin);
        while (c!='\n' && c!=EOF)
            c = fgetc(stdin);
    }
    //Ok, on a correctement vidé l'entrée standard
    
    cpt_points=0;
    cpt_neg=0;
    cpt_nondigit=0;
    //On va compter le nombre de points decimaux et de symboles "-" dans le chaine... On va aussi vérifier que la chaine est correcte. Si ce n'est pas le cas, on quitte !
    for(i=0; chaine[i]!='\0'; i+=1)
    {
        if (chaine[i]=='.') //Le caractère est-il un point ?
            cpt_points+=1;
        else if (chaine[i]=='-') //Le caractère est-il un symbole négatif ?
            cpt_neg+=1;
        else if ((chaine[i]<'0' || chaine[i]>'9') && chaine[i]!='\n')
            cpt_nondigit+=1;
        
    }
    
    if (cpt_points > 1 || cpt_neg > 1 || (cpt_neg==1 && chaine[0]!='-') || cpt_nondigit > 0)
    {
        fprintf(stderr, "Erreur, la chaine entrée n'a pas le bon format\n");
        assert(0); //Il faudrait éviter ca... Mais que retourner avec cette fonction ?
    } //Arrive a ce point, on a le bon format ! On peut faire de la conversion
    else if(cpt_points == 1)
    {
        //L'utilisateur a entré un double, on le convertit
        rd = strtod(chaine, &pc);
        gen.data.d=rd;
        gen.type=DOUBLE;
        return gen;
    }
    else if(cpt_neg == 0)
    {
        //L'utilisateur a entre un entier non signé
        rul = strtoul(chaine, &pc, 10);
        gen.data.u=rul;
        gen.type=ULONG;
        return gen;
    }
    else
    {
        //L'utilisateur a entre un entier signé
        rl = strtol(chaine, &pc, 10);

        gen.data.i=rl;
        gen.type=LONG;
        return gen;
    }

    
}

void affGen(generique gen){
	switch(gen.type){
		case DOUBLE:
			printf("la valeur entree est %lf qui est un double\n", gen.data.d);
			break;
	
		case ULONG:
			printf("la valeur entree est %lu qui est un ULong\n", gen.data.u);
			break;
	
		case LONG:
			printf("la valeur entree est %ld qui est un Long\n", gen.data.i);
			break;
	}
}

generique addGen(generique g, generique j){
	generique k;
	if(g.type==DOUBLE || j.type==DOUBLE){
		k.type= DOUBLE;

		return k;
	}
	else if(g.type==ULONG || j.type==ULONG){
		k.type= ULONG;
	}
	else{
		k.type=LONG;
	}
}


int main(int argc, const char * argv[]) {
    generique g;
    generique j;
    g=demanderValeur();
    j=demanderValeur();
    //affGen(gen);
    addGen(g,j);
    return 0;
}

















































