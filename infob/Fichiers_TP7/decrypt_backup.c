#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct{double qt[26][26][26][26]; } quadgram_tab;

double valeur_quadgram(quadgram_tab quad_tab ,char c, char h, char a, char r);
double compute_score(char *input, quadgram_tab tabquad);
char* permute(char* password );
void decrypt(char *input, char *output, char *password);


int main(int argc, char *argv[]){
	srand( time( NULL ) );
	quadgram_tab quad_tab;
	FILE *f;
	f = fopen(argv[1], "rb");
	int n=0;

	
	char c=0;
	char h=0;
	char a=0;
	char r=0;
	double score;
	
	
	for(int i=0;i<26;++i){
		for(int j=0;j<26;++j){
			for(int k=0;k<26;++k){
				for(int l=0;l<26;++l){
					quad_tab.qt[i][j][k][l]=0;
				}
			}
		}
	}
	while(feof(f) == 0)
	{
		fscanf(f,"%c %c %c %c %lf\n", &c, &h, &a, &r, &score);
		quad_tab.qt[c-'a'][h-'a'][a-'a'][r-'a']+=score;
	}
	printf("ok");

	valeur_quadgram(quad_tab,c,h,a,r);
	/*char M[26]="abcdefghijklmnopqrstuvwxyz";
	pas_mieux=0;
	while(pas_mieux<1000){
		char Mp[26]=permute(M);
		double s=(decrypt())
	}*/
	fclose(f);
	
	return EXIT_SUCCESS;
	
	
}


double valeur_quadgram(quadgram_tab quad_tab,char c,char h, char a, char r){
	/*printf("score de %c%c%c%c=%lf\n",c,h,a,r,quad_tab.qt[c-'a'][h-'a'][a-'a'][r-'a']);*/
	double score;
	if(quad_tab.qt[c-'a'][h-'a'][a-'a'][r-'a']==0){
		score=1;
	}
	else{
		score=quad_tab.qt[c-'a'][h-'a'][a-'a'][r-'a'];
	}
	return score;
}

double compute_score(char *input, quadgram_tab tabquad){
	double st=0;
	int i=0;
	while(input[i]!='\0'){
		st+=valeur_quadgram(tabquad,input[i],input[i+1],input[i+2],input[i+3]);
	}
	return st;
}

char* permute(char* password ){
	int i = 0;
	int r=rand()%26;
	char aux;
	aux=password[i];
	password[i] = password[r];
	password[r]=aux;
	 return password;
}

void decrypt(char *input, char *output, char *password){
	int i=0;
	while(input[i]!='\0'){
		output[i]=password[input[i]-'a'];
	}
}





























