#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(void){
  int size;
  printf("What is the size of your name : ");
  scanf("%d",&size);

  char name[size];
  printf("\nWhat is your name : ");
  scanf("%s",name);

  char age[2];
  printf("\nWhat is your age : ");
  scanf("%s",age);

  int fd1 = open("./doc1.txt",O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR);

  if(fd1==-1){
    perror("./doc1.txt");
    printf("Error occured when opening the file doc1.txt %d",errno);
    exit(0);
  }else{
    int bytes_written1 = write(fd1,(void *)name,size);
    char buf1[4] = " is ";
    int bytes_written2 = write(fd1,(void *)buf1,4);
    int bytes_written3 = write(fd1,(void *)age,2);
    char buf2[11] = " years old.";
    int bytes_written4 = write(fd1,(void *)buf2,11);

    if(bytes_written1==-1 || bytes_written2==-1 || bytes_written3==-1 || bytes_written4==-1){
      perror("doc1.txt");
      printf("Error occured when writting to the file doc1.txt %d",errno);
      exit(0);
    }else{
      printf("Written tp the file successfully");
      close(fd1);
    }
  }

  return 0;
}