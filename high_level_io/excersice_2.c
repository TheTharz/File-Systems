#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(void){
  FILE * fp1 = fopen("./doc1.txt","r");

  if(fp1==NULL){
    printf("Doc1.txt could not be opened");
    perror("./doc1.txt");
    printf("Error number : %d",errno);
    exit(0);
  }

  FILE * fp2 = fopen("./doc2.txt","w");

  if(fp2==NULL){
    printf("Doc2.txt could not be opened");
    perror("./doc2.txt");
    printf("Error number : %d",errno);
    exit(0);
  }

  char buffer[20];

  while(fscanf(fp1,"%s",buffer) != EOF){
    int bytes_written = fprintf(fp2,"%s ",buffer);

    if(bytes_written==-1){
      printf("Failed to write file");
      perror("./doc2.txt");
      printf("Error number : %d",errno);
      exit(0);
    }
  }

  printf("Content copied succesfully");
  fclose(fp1);
  fclose(fp2);
  return 0;
}