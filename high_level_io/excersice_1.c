#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(void){
  int size;
  printf("What is the size of your name : ");
  scanf("%d",&size);

  char name[size];
  printf("What is your name : ");
  scanf("%s",name);

  char age[2];
  printf("What is your age");
  scanf("%s",age);

  FILE * fp1 = fopen("./doc1.txt","w+");

  if(fp1==NULL){
    printf("Doc1.txt could not be opened");
    perror("./doc1.txt");
    printf("Error number : %d",errno);
    exit(0);
  }
  else{
    printf("Doc1.txt opened succesfully");

    int written_bytes = fprintf(fp1,"My name is %s and my age is %s",name,age);
    if(written_bytes == -1){
      printf("Writting has been failed to file");
      perror("./doc1.txt");
      printf("Error number : %d",errno);
      exit(0);
    }else{
      printf("Bytes were written succesfully");
      fclose(fp1);
    }
  }
  return 0;
}