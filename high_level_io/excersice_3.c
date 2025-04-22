#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(void){
  FILE * fp1 = fopen("./doc3.txt","w");

  if(fp1==NULL){
    printf("Doc3.txt could not be opened");
    perror("./doc3.txt");
    printf("Error number : %d",errno);
    exit(0);
  }else{
    fclose(fp1);
  }

  chmod("./doc3.txt",S_IRUSR|S_IRGRP|S_IROTH);

  FILE * fp2 = fopen("./doc3.txt","r");

  if(fp2==NULL){
    printf("Doc3.txt could not be opened");
    perror("./doc3.txt");
    printf("Error number : %d",errno);
    exit(0);
  }

  char buffer[] = "Hello this new world";

  int bytes_written = fprintf(fp2,"%s",buffer);

  if(bytes_written==-1){
    printf("Data could not be written");
    perror("./doc3.txt");
    printf("Error number : %d",errno);
    exit(0);
  }

  fclose(fp2);

  return 0;
}