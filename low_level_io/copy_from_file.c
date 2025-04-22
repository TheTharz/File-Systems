#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(void){
  int fd1 = open("./doc1.txt",O_RDONLY | O_CREAT | O_APPEND,S_IRUSR);
  char data_read[25];
  if(fd1==-1){
    perror("./doc1.txt");
    printf("\nError occured when opening the file %d",errno);
    exit(0);
  }else{
    int bytes_read = read(fd1,(void *)data_read,25);

    if(bytes_read==-1){
      perror("doc1.txt");
      printf("\nError occured when reading the file %d",errno);
      exit(0);
    }else{
      int fd2 = open("./doc2.txt",O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
      if(fd2==-1){
        perror("./doc2.txt");
        printf("\nError occured when opening the file %d",errno);
        exit(0);
      }else{
        int bytes_written = write(fd2,(void *)data_read,25);
        if(bytes_written==-1){
          perror("./doc2.txt");
          printf("\nError occured when writing to file %d",errno);
          exit(0);
        }else{
          printf("\n Written to file successfully.");
          close(fd1);
          close(fd2);
        }
      }
    }
  }
  return 0;
}