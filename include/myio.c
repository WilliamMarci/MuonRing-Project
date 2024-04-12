//save any data to csv file of dat file
// #include "myio.h"
// #include <iostream>
#include <stdio.h>
#include <string.h>
#include <TFile.h>
#include "myio.h"

static char *THEFILE;

/*
Initiate output file
---
- filename: name of file to save data
- header: header of file
*/
void PrintVector(Float_t *vector){
    Size_t dimension = 3; // sizeof(vector);
    printf("[ ");
    for (size_t i = 0; i < dimension; i++)
    {
        printf("%g ", vector[i]);
    }
    printf("]\n");
}

// static char* THEFILE;

void InitOutput(char* filename, char* headline)
{
 THEFILE=filename;
 if(strlen(THEFILE)==0) printf(headline);
 else 
 {
   FILE* f=fopen(THEFILE, "w");
   if (!f)
   {
     printf("File cannot be opened!\n");
     THEFILE[0]=0;
   }
   else {
    fprintf(f,headline);
    fclose(f);
   }
 }
}

void AddIntToOutput(int n){
    if(strlen(THEFILE)==0) printf("%d ", n);
    else{
        FILE* fp = fopen(THEFILE, "a");
        if(!fp){
            printf("Error: cannot open file\n");
            THEFILE[0]=0;
        }

        fprintf(fp, "%d ", n);
        fclose(fp);
    }
}

void AddToOutput(Float_t n){
    if(strlen(THEFILE)==0)printf("%g\n", n);
    else{
        FILE* fp = fopen(THEFILE, "a");
        if(!fp){
            printf("Error: cannot open file %s\n", THEFILE);
        }
        fprintf(fp, "%g", n);
        fclose(fp);
    }
}

void AddToOutput2(Float_t n1,Float_t n2){
    if(strlen(THEFILE)==0)printf("%g %g\n", n1, n2);
    else{
        FILE* fp = fopen(THEFILE, "a");
        if(!fp){
            printf("Error: cannot open file %s\n", THEFILE);
        }
        fprintf(fp, "%g %g\n", n1, n2);
        fclose(fp);
    }
}

void AddToOutput3(Float_t n1,Float_t n2,Float_t n3){
    if(strlen(THEFILE)==0)printf("%g %g %g\n", n1, n2, n3);
    else{
        FILE* fp = fopen(THEFILE, "a");
        if(!fp){
            printf("Error: cannot open file %s\n", THEFILE);
        }
        fprintf(fp, "%g %g %g\n", n1, n2, n3);
        fclose(fp);
    }
}

void AddToOutput4(Float_t n1,Float_t n2,Float_t n3,Float_t n4){
    if(strlen(THEFILE)==0)printf("%g %g %g %g\n", n1, n2, n3, n4);
    else{
        FILE* fp = fopen(THEFILE, "a");
        if(!fp){
            printf("Error: cannot open file %s\n", THEFILE);
        }
        fprintf(fp, "%g %g %g %g\n", n1, n2, n3, n4);
        fclose(fp);
    }
}

void MatrixOutput(Float_t *matrix, int nrow, int ncol){
    if(strlen(THEFILE)==0){
        for(int i=0; i<nrow; i++){
            for(int j=0; j<ncol; j++){
                printf("%g ", matrix[i*ncol+j]);
            }
            printf("\n");
        }
    }
    else{
        FILE* fp = fopen(THEFILE, "a");
        if(!fp){
            printf("Error: cannot open file %s\n", THEFILE);
        }
        for(int i=0; i<nrow; i++){
            for(int j=0; j<ncol; j++){
                fprintf(fp, "%g ", matrix[i*ncol+j]);
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
    }
}