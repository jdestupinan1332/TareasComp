#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define USAGE "Debe inicializar como ./a.out archivo.dat"


int main(int argc, char **argv){

	int lmax = 0; //lineas máximas
	int l1; //linea actual
	int l2;
	float cp; //potencial prueba
	float cm; //potencial menor
	float x,y,z;
	float xi,yi,zi; 
	float xj,yj,zj;
	FILE *in0;
	FILE *in1;
	FILE *in2;
	char filein[256];
	int i;
	
	//Error si los argumentos no son los necesitados
	if(argc!=2){
		printf("USAGE: %s\n", USAGE);
		exit(1);
	}
	strcpy(filein, argv[1]);
	
	
	//abre archivo
	if(!(in0=fopen(filein, "r"))){
		printf("Problem opening file %s\n", filein);
		exit(1);
	}
	if(!(in1=fopen(filein, "r"))){
		printf("Problem opening file %s\n", filein);
		exit(1);
	}
	if(!(in2=fopen(filein, "r"))){
		printf("Problem opening file %s\n", filein);
		exit(1);
	}
	
	//cuenta el número de lineas
	do{
		i = fgetc(in0);
		if (i == '\n') lmax++;
	}while (i != EOF);

	//inicialización de valores
	
	l1 = 0;
	cm = 0.0;
	printf("Este programa demora un poquito\n");
	do{
		cp = 0.0;
		l2 = 0;
		l1 = l1 + 1;
		fscanf(in1,"%f %f %f\n",&xi, &yi, &zi);
		do{
			l2 = l2 + 1;
			fscanf(in2,"%f %f %f\n",&xj, &yj, &zj);
			if(xi !=xj && yi !=yj && zi !=zj){
				cp = cp - 1/(sqrt(pow(xi-xj,2)+pow(yi-yj,2)+pow(zi-zj,2)));
			}
		}while (l2 < lmax);
		if (l2 == lmax){
			rewind(in2);
		}
		if (cp < cm){
			cm = cp;
			x = xi;
			y = yi;
			z = zi;
		}
	}while (l1 < lmax);
	fclose(in2);
	fclose(in1);
	printf ("%f %f %f\n", x, y, z);
	return 0;
}

