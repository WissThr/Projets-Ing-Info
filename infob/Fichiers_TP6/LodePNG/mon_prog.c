#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"
#include <time.h>
#include <stdbool.h>

typedef struct  { int width; int height; unsigned char* r; unsigned char* v ; unsigned char* b; unsigned char* a;} myimage;

void decodeOneStep(const char* filename);
void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height);
myimage LireImage(char* nom_fichier);
void EcrireImage(myimage img, char* filename);
void NoirEtBlanc(myimage img);


int main(int argc, char *argv[]){
	/*decodeOneStep("goats.png");*/
	myimage img = LireImage(argv[1]);
	NoirEtBlanc(img);
	EcrireImage(img,argv[2]);
	free(img.r);
	free(img.v);
	free(img.b);
	free(img.a);
	return EXIT_SUCCESS;
}

void decodeOneStep(const char* filename)
{
  unsigned error;
  unsigned char* image;
  unsigned width, height;

  error = lodepng_decode32_file(&image, &width, &height, filename);
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
  	int i=0;
  	srand(time(NULL));
  	int k;
     for(i=0;i<4*width*height;++i){
     
     if(i%4==0){
     k=rand()%200;
     }
     	
     	if(image[i]<255-50){
     		image[i]=k;
     	}
    }
	encodeOneStep("goats1.png", image, width, height); 
  /*use image here*/

  free(image);
}

void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height)
{
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename, image, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}


myimage LireImage(char* filename){
	unsigned error;
	unsigned char* image;
	unsigned width, height;
	myimage img;
	error = lodepng_decode32_file(&image, &width, &height, filename);
	printf("w=%d, h=%d\n",width,height);
	img.width=width;
	img.height=height;
	img.r=(unsigned char*)malloc((img.width*img.height)*sizeof(unsigned char));
	img.v=(unsigned char*)malloc((img.width*img.height)*sizeof(unsigned char));
	img.b=(unsigned char*)malloc((img.width*img.height)*sizeof(unsigned char));
	img.a=(unsigned char*)malloc((img.width*img.height)*sizeof(unsigned char));
	
	int i=0;
	int j=0;
	
	for(i=0;i<4*width*height;i+=4)
	{
		img.r[j]=image[i];
		img.v[j]=image[i+1];
		img.b[j]=image[i+2];
		img.a[j]=image[i+3];
		
		/*printf("%d\n",image[i]);
		printf("pixel%d= R:%d, V:%d, B:%d, A:%d \n",i-4 ,img.r[j], img.v[j], img.b[j], img.a[j]);*/
		j++;
	}
	

	return img;
	
}

void EcrireImage(myimage img, char* filename){
	unsigned char* image;
	image=(unsigned char*)malloc((4*img.width*img.height)*sizeof(unsigned char));
	int i=0;
	int j=0;
	for(i=0; i<img.width*img.height; ++i){
		image[j]=img.r[i];
		printf("r=%d ",image[j]);
		j++;
		image[j]=img.v[i];
		printf("v=%d ",image[j]);
		j++;
		image[j]=img.b[i];
		printf("b=%d ",image[j]);
		j++;
		image[j]=img.a[i];
		printf("a=%d\n",image[j]);
		j++;
	}
	encodeOneStep(filename, image, img.width, img.height);
	free(image);
}

void NoirEtBlanc(myimage img){
	int i=0;
	for(i=0; i<img.width*img.height;i++){
		int res=0;
		res=img.r[i]+img.v[i]+img.b[i];
		int aux = res/3;
		printf("%d\n", aux);
		img.r[i]=aux;
		img.v[i]=aux;
		img.b[i]=aux;
	}
	
}






























