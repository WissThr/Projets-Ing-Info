#include <stdio.h>
#include <stdlib.h>

int estMinuscule(char l);
int estMajuscule(char l);
char prochaineLettre(FILE* f);
char lettreLaPlusFrequente(FILE *f);
void decodageCesar(FILE *f, FILE *g);

int main(int argc, char *argv[]){
	FILE *f;
	FILE *g;
	char r;
	
	f = fopen(argv[1], "rb");
	g= fopen(argv[2], "w+");
	
//Si le fichier n’a pas ete ouvert correctement
	if( f == NULL || g == NULL ){
		fprintf(stderr, "Erreur : fichier mon_fichier.txt introuvable dans le repertoire courant\n");
//On quitte le programme
		return EXIT_FAILURE;
	}
	
	/*r=prochaineLettre(f);
	printf("%c",r);
	while( r!= ' '){
		r=prochaineLettre(f);
		printf("%c",r);
	}*/
	r=lettreLaPlusFrequente(f);
	
	printf("\nFin du fichier, lettre est: %c\n",r);
	
	decodageCesar(f,g);
	printf("fichier décodé !\n");
	fclose(f);
	fclose(g);
	
	return EXIT_SUCCESS;
	
}

int estMinuscule(char l){
	if( l >= 'a' && l <= 'z'){
		return 1;
	}
	else {
		return 0;
	}
}

int estMajuscule(char l){
	if( l >= 'A' && l <= 'Z'){
		return 1;
	}else {
		return 0;
	}
}

char prochaineLettre(FILE* f){
	char r;
	while(fscanf(f, "%c", &r)!=EOF){
		if(estMajuscule(r)==1 || estMinuscule(r)==1){
			return r;
		}
	}
	return ' ';
}

char lettreLaPlusFrequente(FILE *f){
	rewind(f);
	int nbr[26];
	for(int i=0;i<=25;++i){
		nbr[i]=0;
	}
	int id=0;
	char r;

	while(r !=' '){
		r=prochaineLettre(f);
		if(r!=' '){
			if(estMinuscule(r)){
				nbr[(r-'a')]++;
			}
			if(estMajuscule(r)){
				nbr[(r-'A')]++;
			}
		}
	}

	for(int i=0;i<=25;++i){
		if(nbr[i]>=nbr[id]){
			id=i;
	
		}
	}
	return 'a'+id;
}

void decodageCesar(FILE *f, FILE *g){
	char fr= lettreLaPlusFrequente(f);
	int d= ((('e'-fr)%26)+26)%26;
	printf("fr=%c\n",fr);
	printf("décalage de %d\n",d);
	char r;
	rewind(f);
	while( fscanf(f, "%c", &r)!= EOF ){
	printf("%c --> ",r);
		if(estMinuscule(r)==1){
			r= (r-'a'+d)%26+'a' ;
			fputc(r,g);
		}
		else if(estMajuscule(r)==1){
			r= (r-'A'+d)%26+'A';
			fputc(r,g);
		}
		else{
			fputc(r,g);
		}
		printf("%c %d\n", r, (int)r);
	}
}
//r-'A')+d)%26+'A'
















/*#include <stdio.h>
#include <stdlib.h>

int estMinuscule(char l);
int estMajuscule(char l);
char prochaineLettre(FILE* f);
char lettreLaPlusFrequente(FILE *f);
void decodageCesar(FILE *f, FILE *g);

int main(int argc, char *argv[]){
	FILE *f;
	FILE *g;
	char r;
	
	f = fopen(argv[1], "rb");
	g= fopen(argv[2], "w+");
	
//Si le fichier n’a pas ete ouvert correctement
	if( f == NULL || g == NULL ){
		fprintf(stderr, "Erreur : fichier mon_fichier.txt introuvable dans le repertoire courant\n");
//On quitte le programme
		return EXIT_FAILURE;
	}
	

	r=lettreLaPlusFrequente(f);
	
	printf("\nFin du fichier, lettre est: %c\n",r);
	
	decodageCesar(f,g);
	printf("fichier décodé !\n");
	fclose(f);
	fclose(g);
	
	return EXIT_SUCCESS;
	
}

int estMinuscule(char l){
	if( l >= 'a' && l <= 'z'){
		return 1;
	}
	else {
		return 0;
	}
}

int estMajuscule(char l){
	if( l >= 'A' && l <= 'Z'){
		return 1;
	}else {
		return 0;
	}
}

char prochaineLettre(FILE* f){
	char r;
	int fin=1;
	while(fscanf(f, "%c", &r)!=EOF){
		if(estMajuscule(r)==1 || estMinuscule(r)==1){
			return r;
		}
	}
	return ' ';
}

char lettreLaPlusFrequente(FILE *f){
	rewind(f);
	int nbr[26];
	for(int i=0;i<=25;++i){
		nbr[i]=0;
	}
	int id=0;
	char r;

	while(r !=' '){
		r=prochaineLettre(f);
		if(r!=' '){
			if(estMinuscule(r)){
				nbr[(r-'a')]++;
			}
			if(estMajuscule(r)){
				nbr[(r-'A')]++;
			}
		}
	}

	for(int i=0;i<=25;++i){
		if(nbr[i]>=nbr[id]){
			id=i;
	
		}
	}
	return 'a'+id;
}

void decodageCesar(FILE *f, FILE *g){
	char fr= lettreLaPlusFrequente(f);
	int d= -(fr-'e');
	printf("fr=%c\n",fr);
	printf("décalage de %d\n",d);
	char r;
	rewind(f);
	while( fscanf(f, "%c", &r)!= EOF ){
		if(estMinuscule(r)==1){
			fputc(((r-'a')+d)%26+'a',g);
		}
		else if(estMajuscule(r)==1){
			fputc(((r-'A')+d)%26+'A',g);
		}
		else{
			fputc(r,g);
		}
	}
}*/



























































