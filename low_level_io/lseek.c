#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(void){
  int fd1 = open("./doc1.txt",O_RDONLY|O_CREAT|O_APPEND,S_IRUSR);
  printf("File opened succesfully for reading");
  if(fd1==-1){
    perror("./doc1.txt");
    printf("Error occured while opening the file %d",errno);
    exit(0);
  }else{
    char data_read1[16];
    lseek(fd1,14,SEEK_SET);
    int bytes_read1 = read(fd1,data_read1,16); //now the file offset is 30 so next byte is 31

    char data_read2[11];
    lseek(fd1,9,SEEK_CUR);

    int bytes_read2 = read(fd1,data_read2,11);

    if(bytes_read1==-1 || bytes_read2==-1){
      perror("./doc1.txt");
      printf("Error occured while reading from the file %d",errno);
      exit(0);
    }else{
      printf("Read from the file successfully");
      close(fd1);
    }

    int fd2 = open("./doc2.txt",O_RDWR|O_CREAT|O_TRUNC,S_IWUSR);
    if(fd2==-1){
      perror("./doc2.txt");
      printf("Error while opening the file %d",errno);
      exit(0);
    }

    printf("File opened for writting successfully");

    int bytes_written1 = write(fd2,(void *)data_read1,16);
    int bytes_written2 = write(fd2,(void *)data_read2,11);

    if(bytes_written1==-1 || bytes_written2==-1){
      perror("./doc2.txt");
      printf("Error occured when writing to the file %d",errno);
      exit(0);
    }

    close(fd2);
    printf("Bytes were written successfully to file");
  }

  return 0;
}