#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE "Debe inicializar como ./a.out Número"
#define MAx 499979

int main(int argc, char **argv){

	int i = atoi(argv[1]);
	float P_1;
	float P_2;
	float div;
	FILE *in1;
	FILE *in2;
	char Primos[256] = "Primos.txt";
	char Mensaje [256] ="No se encontró producto de primos";

	/*errores*/
	if(argc!=2){
		printf("USAGE: %s\n", USAGE);
		exit(1);
	}
	if (i>1000000){
		printf("el argumento es mayor a 1 millon\n");
		exit(1);
	}
	if (!i){
		printf("El argumento no es entero\n");
		exit(1);
	}
	if(!(in1 = fopen(Primos,"r"))){
		printf("Problem opening file\n");
		exit(1);	
	}
	if(!(in2 = fopen(Primos,"r"))){
		printf("Problem opening file\n");
		exit(1);	
	}

	/*inicializa todo*/
	printf("AVISO, debido a la cantidad de números, el programa puede tardar\nSon Máximo 1724907024 iteraciones, tenga paciencia\n");
	P_1 = 0;
	P_2 = 0;
	do{
		fscanf(in1,"%f",&P_1);
		div = i/P_1;
		do{
			fscanf(in2,"%f",&P_2);
			if(P_2 == div){
				printf("%d %d\n", (int)P_1, (int)P_2);
				exit(0);
			}
		}while (P_2!=MAx);
		if(P_2 == MAx){
			rewind(in2);
		}
	}while (P_1 != MAx);
	fclose(in1);
	fclose(in2);
	printf("%s\n",Mensaje);
	return 0;
}
