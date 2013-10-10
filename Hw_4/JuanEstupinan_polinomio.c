#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_matrix.h>
int count_lines(char *filename);
void print_matrix(double * m, int n_x, int n_y); 

int main (int argc, char **argv){
  FILE *in;
  char filename[265];
  double *M;
  double *M_T;
  double *Y, *X;
  float x,y;
  double valx, valy, num, fx, chi;
  int pos;
  int j,n;
  int nlines, degree;


  /*get arguments*/
  strcpy(filename, argv[1]);
  if(!(in=fopen(filename, "r"))){
    printf("problem opening file %s\n", filename);
    exit(1);
  }
  nlines = count_lines(filename);
  degree = atoi(argv[2]) + 1;

  /*errors*/
  if (degree<=1){
    printf("The program needs a degree greater that 0\n");
    exit(1);
  }
  if (argc!=3){
    printf("Start the program as ./a.out data degree\n");
  }

  /*memory allocation*/
  if (!(M = malloc(nlines * degree * sizeof(double)))){
    fprintf(stderr, "Problem with memory allocation\n");
      exit(1);
  }
  if (!(Y = malloc(nlines * sizeof(double)))){
    fprintf(stderr, "Problem with memory allocation\n");
    exit(1);
  }
  if (!(X = malloc(nlines * sizeof(double)))){
    fprintf(stderr, "Problem with memory allocation\n");
    exit(1);
    }


  /* the Matrix and Y vector*/
  for(n=0; n<nlines; n++){
    fscanf(in,"%f %f\n", &x, &y);
    X[n] = x; //X vector
    Y[n] = y; //Y vector;
    for(j=0;j<degree;j++){
      pos = j + (degree * n);
      M[pos] = pow(x,j); //matrix
    }
  }
  
 
  /*GSL matrix*/
  gsl_matrix_view m = gsl_matrix_view_array (M, nlines, degree);
  gsl_matrix *c = gsl_matrix_alloc(degree,degree);
  gsl_blas_dgemm (CblasTrans, CblasNoTrans,
		  1.0, &m.matrix, &m.matrix,
                  0.0, c);

  
  /*inverse c by LU decomposition*/
  int s=0;
  gsl_permutation *p = gsl_permutation_alloc(degree);
  gsl_linalg_LU_decomp (c,p,&s);
  gsl_matrix *inv = gsl_matrix_alloc(degree,degree);
  gsl_linalg_LU_invert (c,p,inv);


 /*compute inv * m_t*/
  gsl_matrix *b = gsl_matrix_alloc(degree,nlines);
  gsl_blas_dgemm (CblasNoTrans, CblasTrans,
		  1.0, inv, &m.matrix,
                  0.0, b);
  

  /*compute b*Y*/
  gsl_vector *res = gsl_vector_alloc(degree);
  gsl_vector_view yv = gsl_vector_view_array (Y, nlines);
  gsl_blas_dgemv (CblasNoTrans,
		  1.0, b, &yv.vector,
                  0.0, res);

  for(n=0;n<degree;n++){
    num = gsl_vector_get(res,n);
    printf("a_%d %f\n",n,num);
  }

  /*chi-squared calculation*/

  chi = 0.0;
  for(n=0;n<nlines;n++){
    fx = 0.0;
    valx = X[n];
    valy = Y[n];
    for(j=0;j<degree;j++){
      num = gsl_vector_get (res,j);
      fx = fx + pow(valx,j)*num;
    }
    chi = chi + pow(valy-fx,2);
  }
  chi = chi/nlines;
  printf("chi2 %f\n",chi);
  fclose(in);
  return 0;
}




  
int count_lines(char *filename){
  FILE *in;
  int n_lineas;
  int c;
  if(!(in=fopen(filename,"r"))){
    printf("problem opening file %s\n", filename);
    exit(1);
  }
  
  n_lineas=0;
  do{
    c=fgetc(in);
    if(c=='\n'){
      n_lineas++;
      
    }
  }while (c !=EOF);
  
  fclose(in);
  return n_lineas;
}


void print_matrix(double * m, int n_x, int n_y){
  int i,j,pos;
  fprintf(stdout, "\n");
  /*Prints to screen*/
  for(i=0;i<n_x;i++){
    for(j=0;j<n_y;j++){
      pos = j + (n_y * i);/*position in the array*/
      printf(" %f ",m[pos]);
    }
    printf("\n");
  }
  printf("\n");
}
