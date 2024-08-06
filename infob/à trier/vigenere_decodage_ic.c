#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int estMinuscule(char l);
int estMajuscule(char l);
char prochaineLettre(FILE* f);
char lettreLaPlusFrequente(FILE *f);
void decodageVigenere(FILE *f, FILE *g, int n, unsigned char* mdp);
void normaliserTexte(FILE *f, FILE *g);
void decouperFichier(FILE *in, FILE *out, int longueur, int debut);
double IndiceCoincidence(FILE *in);
int longueurMotPasseVigenere(FILE *in);


int main(int argc, char *argv[]){
	FILE *f;
	FILE *g;
	FILE *h;
	FILE *k;
	printf("ok1");
	fflush(NULL);
	f = fopen(argv[1], "rb");
	g= fopen(argv[2], "w+");
	h= fopen("inter.txt", "wb+");
	printf("ok1");
	fflush(NULL);
/*Si le fichier n’a pas ete ouvert correctement*/
	if( f == NULL || g == NULL ){
		fprintf(stderr, "Erreur : fichier mon_fichier.txt introuvable dans le repertoire courant\n");
/*On quitte le programme*/
		return EXIT_FAILURE;
	}
	printf("ok1");
	fflush(NULL);
	normaliserTexte(f,h);
	printf("ok4");
	fflush(NULL);
	int n=longueurMotPasseVigenere(h);
	printf("ok5");
	fflush(NULL);
	int i=0;
	unsigned char mdp[n];
	for(i=0;i<n;i++){
		mdp[i]='a';
	}
	
	for(i=0;i<n;i++){
		k= fopen("inter2.txt", "wb");
		decouperFichier(h,k,n,i);
		fclose(k);
		k= fopen("inter2.txt", "rb");
		mdp[i]=lettreLaPlusFrequente(k);
		fclose(k);
	}
	
	decodageVigenere(f,g,n,mdp);
	/*printf("fichier décodé !\n le mdp est: ");
	for(int i =0; i<n; i++){
		printf("%c ",mdp[i]-4);
	}*/
	printf("\n");
	fclose(f);
	fclose(g);
	fclose(h);
	
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
	int i;
	for(i=0;i<=25;++i){
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
	for(i=0;i<=25;++i){
		if(nbr[i]>=nbr[id]){
			id=i;
	
		}
	}
	/*printf("%c, %d\n", 'a'+id, nbr[id]);*/
	return 'a'+id;
}

void normaliserTexte(FILE *f, FILE *g){
	char r;
	rewind(f);
	while( fscanf(f, "%c", &r)!= EOF ){
	/*printf("%c --> ",r);*/
		if(estMinuscule(r)==1){
			fputc(r,g);
		}
		else if(estMajuscule(r)==1){
			r= (r-'A')%26+'a';
			fputc(r,g);
		}
		/*printf("%c %d\n", r, (int)r);*/
	}
}

void decouperFichier(FILE *f, FILE *g, int longueur, int debut){
	char r;
	rewind(f);
	rewind(g);
	fseek(f, debut, SEEK_SET);
	if(fscanf(f, "%c", &r)!= EOF){
		fputc(r,g);
	}
	while(fscanf(f, "%c", &r)!= EOF){
		fseek(f, longueur-2, SEEK_CUR);
		fscanf(f, "%c", &r);
		fputc(r,g);
	}
}

void decodageVigenere(FILE *f, FILE *g, int n, unsigned char*t){
	rewind(f);
	rewind(g);
	int i=0;
	char r;
	while( fscanf(f, "%c", &r)!= EOF ){
		int d=((('e'-t[i%n] )%26)+26)%26;
		if(estMinuscule(r)==1){
			fputc(((r-'a')+d)%26+'a',g);
		}
		else if(estMajuscule(r)==1){
			fputc(((r-'A')+d)%26+'A',g);
		}
		else{
			fputc(r,g);
			--i;
		}
		++i;
	}
}

double IndiceCoincidence(FILE *in){
	rewind(in);
	double nbr[27];
	int i;
	for(i=0;i<=26;++i){
		nbr[i]=0;
	}
	char r;

	while(r !=' '){
		r=prochaineLettre(in);
		if(r!=' '){
			if(estMinuscule(r)){
				nbr[(r-'a')]++;
			}
			if(estMajuscule(r)){
				nbr[(r-'A')]++;
			}
			++nbr[26];
		}
	}
	double aux=0;
	for(i=0;i<=25;++i){
		aux+=nbr[i]*(nbr[i]-1);
	}
	aux= aux/(nbr[26]*(nbr[26]-1));
	return aux;
}

int longueurMotPasseVigenere(FILE *in){
	rewind(in);
	int i = 0;
	for(i = 1; i <= 30; ++i){
		FILE* x = fopen("inter3.txt", "wb+");
		if(x == NULL){
			fprintf(stderr, "Erreur : fichier inter3.txt introuvable dans le répertoire courant\n");
			return EXIT_FAILURE;
		}
		decouperFichier(in, x, i, 0); 
		fclose(x);
		printf("ok2");
		fflush(NULL);
		x = fopen("inter3.txt", "rb");
		printf("indice=%f\n", IndiceCoincidence(x));
		fflush(NULL);
		if(IndiceCoincidence(x) >= 0.07){
			fclose(x);
			printf("i=%d", i);
			fflush(NULL);
			return i;
		}
		fclose(x);
	}
	return 0;
}





