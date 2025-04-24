#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void){
  int fd1 = open("./doc3.txt",O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IXUSR);
  if(fd1==-1){
    perror("./doc3.txt");
    printf("Error while opening the file doc3 %d",errno);
    exit(0);
  }else{
    close(fd1);
  }

  chmod("./doc3.txt",S_IRUSR);

  int fd2 = open("./doc3.txt",O_RDONLY,S_IRUSR);
  if(fd2==-1){
    perror("./doc3.txt");
    printf("Error while opening the file doc3 %d",errno);
    exit(0);
  }else{
    char data[5]="hello";
    int bytes_written = write(fd1,data,5);

    if(bytes_written==-1){
      perror("./doc3.txt");
      printf("Error while writing the file doc3 %d",errno);
      exit(0);
    }else{
      close(fd2);
    }
  }
  
}
