#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USAGE "Debe inicializar como ./a.out file"

int main(int argc, char **argv){
	FILE *in;
	int N_a, N_e, N_i, N_o, N_u;
	int i;
	char filein[256];
	
	N_a = 0;
	N_e = 0;
	N_i = 0;
	N_o = 0;
	N_u = 0;

	//Error si los argumentos no son los necesitados
	if(argc!=2){
		fprintf(stderr, "USAGE: %s\n", USAGE);
		exit(1);
	}
	strcpy(filein, argv[1]);
	
	//abre archivo
	if(!(in=fopen(filein, "r"))){
		fprintf(stderr, "Problem opening file %s\n", filein);
		exit(1);
	}
	do{
		i = fgetc(in);
		if(i == 'a') N_a++;
		if(i == 'e') N_e++;
		if(i == 'i') N_i++;
		if(i == 'o') N_o++;
		if(i == 'u') N_u++;
		if(i == 'A') N_a++;
		if(i == 'E') N_e++;
		if(i == 'I') N_i++;
		if(i == 'O') N_o++;
		if(i == 'U') N_u++;
	}while (i != EOF);
	fclose(in);
	printf("a = %d\n", N_a);
	printf("e = %d\n", N_e);
	printf("i = %d\n", N_i);
	printf("o = %d\n", N_o);
	printf("u = %d\n", N_u);
	return 0;
}
