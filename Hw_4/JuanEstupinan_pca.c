#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_eigen.h>

#define dim 24
#define recon 10

int count_lines (char *filename);
void print_matrix(double *M, int n_x, int n_y);
double calc_prom_v(double *M, int n,int nlines);
double calc_sigma(double *M, double *Vprom, int coli, int colj, int nlines);
void print_matrixf(double *M, int n_x, int n_y);
double calc_chi(int n,double *M,gsl_matrix *reconst, int nlines);

int main (int argc, char **argv){
  FILE *in;
  FILE *in2;
  char filename[256];
  double *M, *Vprom, *Sigma;
  int nlines;
  float d1; //measurements
  int n, j, pos;
  gsl_matrix_view sigma;
  double var;
  
  
  /*get arguments*/
  strcpy(filename, argv[1]);
  if(!(in=fopen(filename, "r"))){
    printf("problem opening file %s\n", filename);
    exit(1);
  }
  nlines = count_lines(filename);
  
  /*errors*/
  if (argc!=2){
    printf("Start the program as ./a.out data\n");
      }   
  /*memory allocation*/
  if (!(M = malloc(nlines * dim * sizeof(double)))){
    fprintf(stderr, "Problem with memory allocation\n");
    exit(1);
  }
  if (!(Vprom = malloc(nlines * sizeof(double)))){
    fprintf(stderr, "Problem with memory allocation\n");
    exit(1);
  }
  if (!(Sigma = malloc(nlines*nlines * sizeof(double)))){
    fprintf(stderr, "Problem with memory allocation\n");
    exit(1);
  }

   
  /*the Matrix*/
  for(n=0; n<nlines*dim; n++){
    fscanf(in,"%f", &d1);
    M[n] = d1;
  }
  

  /*calculate the mean value*/
  var = 0.0;
  for (n=0;n<nlines;n++){
    var = calc_prom_v(M,n,nlines);
    Vprom[n] = var; 
  }
  
  
  /*calculate Sigma*/
  var = 0.0;
  for(n=0;n<nlines;n++){
    for(j=0;j<nlines;j++){
      var = calc_sigma(M,Vprom,n,j,nlines);
      pos = j + (nlines * n);
      Sigma[pos] = var;
    }
  }




  /*eigenvalues and eigenvectors*/
  sigma = gsl_matrix_view_array (Sigma, nlines, nlines);
  gsl_vector *eval = gsl_vector_alloc (nlines);
  gsl_matrix *evec = gsl_matrix_alloc (nlines, nlines);
  gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (nlines);
  gsl_eigen_symmv (&sigma.matrix, eval, evec, w);
  gsl_eigen_symmv_free (w);
  gsl_eigen_symmv_sort (eval, evec, 
			GSL_EIGEN_SORT_VAL_ASC);

  double *Evec = malloc(nlines * recon * sizeof(double));
  for(n=0;n<nlines;n++){
    for(j=0;j<recon;j++){
      var = gsl_matrix_get(evec,n,j);
      Evec[j + (recon*n)]=var;
    }
  }

  /*writes Eigenvectors*/
  print_matrixf(Evec,nlines,recon);
  /*writes eigenvalues*/
  in2 = fopen("JuanEstupinan_eigenvalues.dat","w"); 
  if(!in2){
    printf("problems opening the file %s\n", filename);
    exit(1);
  }
  for(n=0;n<nlines;n++){
    var = gsl_vector_get(eval,n);
    fprintf(in2,"%f\n",var);
  } 
  fclose(in2);


  gsl_vector_free (eval);
  gsl_matrix_free(evec);

  /*reconstruction*/
  gsl_matrix_view m = gsl_matrix_view_array(M,nlines,dim);
  gsl_matrix_view red = gsl_matrix_view_array(Evec,nlines,recon);
  gsl_matrix *reconstruct = gsl_matrix_alloc(dim,recon);
  gsl_blas_dgemm (CblasTrans, CblasNoTrans,1.0,&m.matrix,&red.matrix,0.0,reconstruct);
  

  /*calculate chi2*/
  for(n=0;n<dim;n++){ 
    in2 = fopen("JuanEstupinan_pca_chisquare.dat","a");
    var = calc_chi(n,M,reconstruct,nlines);
    fprintf(in2,"Chi_%d %f\n",n,var);
  }
  fclose(in2); 
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

 double calc_prom_v(double *M, int n,int nlines){
    gsl_vector_view v;
    gsl_matrix_view m;
    int i;
    double num,prom;

    m = gsl_matrix_view_array(M,nlines,dim);
    v = gsl_matrix_row(&m.matrix,n);
    prom = 0.0;
    for (i=0;i<dim;i++){
      num = gsl_vector_get(&v.vector,i);
      prom = prom + num;
    }	
    prom = prom/dim;
    return prom;
 }

double calc_sigma(double *M, double *Vprom, int fili, int filj, int nlines){
  double numi,numj,promi,promj, sigm;
  gsl_vector_view v1,v2;
  gsl_vector_view vp;
  gsl_matrix_view m;
  int i;
  m = gsl_matrix_view_array(M,nlines,dim);
  v1 = gsl_matrix_row(&m.matrix,fili);
  v2 = gsl_matrix_row(&m.matrix,filj);
  vp = gsl_vector_view_array(Vprom, nlines);
  promi=gsl_vector_get(&vp.vector,fili);
  promj=gsl_vector_get(&vp.vector,filj);
  sigm = 0;
  
  for(i=0;i<dim;i++){
    numi=gsl_vector_get(&v1.vector,i);
    numj=gsl_vector_get(&v2.vector,i);
 
    sigm = sigm + (numi - promi)*(numj - promj);
  }
  sigm = sigm/(dim-1);
  return sigm;
}

void print_matrixf(double * m, int n_x, int n_y){
  int i,j,pos;
  FILE *in;
  
  in = fopen("JuanEstupinan_eigenvectors.dat","w"); 
    if(!in){
      printf("problems opening the file\n");
      exit(1);
    }
  fprintf(in, "\n");
  /*Prints to screen*/
  for(i=0;i<n_x;i++){
    for(j=0;j<n_y;j++){
      pos = j + (n_y * i);/*position in the array*/
      fprintf(in," %f ",m[pos]);
    }
    fprintf(in,"\n");
  }
  fprintf(in,"\n");
  fclose(in);
}

double calc_chi(int n,double *M,gsl_matrix *reconst,int nlines){
  int i;
  gsl_vector_view rec = gsl_matrix_row(reconst,n);

  double varm,varr;
  double chi=0.0;
  for(i=0;i<recon;i++){
    varm = M[i+(n*nlines)];
    varr = gsl_vector_get(&rec.vector, i);
    chi = chi + pow(varr - varm,2);
  }
  chi = chi/(recon-1);
  return chi;
}

