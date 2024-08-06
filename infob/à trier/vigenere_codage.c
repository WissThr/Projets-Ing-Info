#include <stdio.h>
#include <stdlib.h>

int estMinuscule(char l);
int estMajuscule(char l);
int nbrMdp(char* argv);


int main(int argc, char *argv[]){

	FILE *f;
	FILE *g;
	unsigned char r;
	int d =0; 
	int n=nbrMdp(argv[2]);
	int* t=(int*)malloc(n*sizeof(int));
	
	if(t==NULL){
		return EXIT_FAILURE;
	}
	
	
	
	
	for(int i=0; i<n;++i){	
		char l=argv[2][i];
		if(estMinuscule(l)){
			t[i]=l-'a';
		}
		if(estMajuscule(l)){
			t[i]=l-'A';
		}
		t[i]++;

	}
	
	f = fopen(argv[1], "rb");
	g= fopen(argv[3], "w+");
	//Si le fichier n’a pas ete ouvert correctement
	if( f == NULL || g == NULL ){
		fprintf(stderr, "Erreur : fichier mon_fichier.txt introuvable dans le repertoire courant\n");
//On quitte le programme
		return EXIT_FAILURE;
	}



// Codage du fichier 
	int i=0;
	while( fscanf(f, "%c", &r)!= EOF ){
		d=t[i%n];
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

	fclose(f);
	fclose(g);
	free(t);


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

int nbrMdp(char* argv){
	int n=0;
	while(argv[n]!='\0'){
		n++;
	}
	return n;
}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



