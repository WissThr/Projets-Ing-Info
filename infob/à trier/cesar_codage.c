#include <stdio.h>
#include <stdlib.h>

int estMinuscule(char l);
int estMajuscule(char l);

int main(int argc, char *argv[]){


	int d=atoi(argv[2]);
	d=d%26;
	printf("décalage de %d\n",d);
	
	if(d<0){
		d+=26;
	}
	FILE *f;
	FILE *g;
	char r;
	
	f = fopen(argv[1], "rb");
	g= fopen(argv[3], "w+");

//Si le fichier n’a pas ete ouvert correctement
	if( f == NULL ){
		fprintf(stderr, "Erreur : fichier mon_fichier.txt introuvable dans le repertoire courant\n");
//On quitte le programme
		return EXIT_FAILURE;
	}
//Sinon, on lit chaque caractere du fichier

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
		
		/*printf("%c\n min:%d; maj:%d\n", r,estMinuscule(r),estMajuscule(r));*/
	} 
	
	printf("\n");
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


