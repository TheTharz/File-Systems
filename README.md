# C File I/O Operations Guide

A comprehensive guide to file operations in C, covering both high-level (buffered) and low-level (unbuffered) I/O operations.

## Table of Contents

- [Required Headers](#required-headers)
- [High-Level I/O Operations](#high-level-io-operations)
- [Low-Level I/O Operations](#low-level-io-operations)
- [File Permissions](#file-permissions)
- [Error Handling](#error-handling)
- [Examples](#examples)

## Required Headers

```c
#include <stdio.h>    // For high-level I/O
#include <stdlib.h>   // For exit()
#include <unistd.h>   // For low-level I/O
#include <fcntl.h>    // For file control options
#include <errno.h>    // For error handling
#include <sys/stat.h> // For file permissions
```

## High-Level I/O Operations

### Opening and Closing Files

1. `FILE* fopen(const char* filename, const char* mode)`

   - Modes:
     - "r" - read only
     - "w" - write (create/truncate)
     - "a" - append
     - "r+" - read and write
     - "w+" - read and write (create/truncate)
     - "a+" - read and append

   ```c
   FILE* fp = fopen("./doc1.txt", "w+");
   if (fp == NULL) {
       perror("./doc1.txt");
       exit(0);
   }
   ```

2. `int fclose(FILE* stream)`
   ```c
   if (fclose(fp) != 0) {
       perror("Error closing file");
   }
   ```

### Reading and Writing

1. `int fprintf(FILE* stream, const char* format, ...)`

   ```c
   int bytes = fprintf(fp, "My name is %s and my age is %s", name, age);
   if (bytes == -1) {
       perror("Write failed");
   }
   ```

2. `int fscanf(FILE* stream, const char* format, ...)`
   ```c
   char buffer[100];
   while (fscanf(fp, "%s", buffer) != EOF) {
       // Process buffer
   }
   ```

## Low-Level I/O Operations

### Opening and Creating Files

1. `int open(const char* pathname, int flags, mode_t mode)`

   - Flags (can be combined with |):
     - O_RDONLY - read only
     - O_WRONLY - write only
     - O_RDWR - read and write
     - O_CREAT - create if doesn't exist
     - O_TRUNC - truncate if exists
     - O_APPEND - append mode

   ```c
   int fd = open("./doc1.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
   if (fd == -1) {
       perror("./doc1.txt");
       exit(0);
   }
   ```

2. `int close(int fd)`
   ```c
   if (close(fd) == -1) {
       perror("Close failed");
   }
   ```

### Reading and Writing

1. `ssize_t read(int fd, void* buf, size_t count)`

   ```c
   char buffer[25];
   ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
   if (bytes_read == -1) {
       perror("Read failed");
   }
   ```

2. `ssize_t write(int fd, const void* buf, size_t count)`
   ```c
   char data[] = "Hello World";
   ssize_t bytes_written = write(fd, data, strlen(data));
   if (bytes_written == -1) {
       perror("Write failed");
   }
   ```

### File Positioning

1. `off_t lseek(int fd, off_t offset, int whence)`

   - whence options:
     - SEEK_SET - from start
     - SEEK_CUR - from current position
     - SEEK_END - from end

   ```c
   // Move 14 bytes from start
   off_t new_pos = lseek(fd, 14, SEEK_SET);

   // Move 9 bytes forward from current position
   new_pos = lseek(fd, 9, SEEK_CUR);
   ```

## File Permissions

### Permission Flags

- S_IRUSR (0400) - owner read
- S_IWUSR (0200) - owner write
- S_IXUSR (0100) - owner execute
- S_IRGRP (0040) - group read
- S_IWGRP (0020) - group write
- S_IXGRP (0010) - group execute
- S_IROTH (0004) - others read
- S_IWOTH (0002) - others write
- S_IXOTH (0001) - others execute

### Changing Permissions

1. `int chmod(const char* pathname, mode_t mode)`
   ```c
   // Set read-only for owner
   if (chmod("./doc3.txt", S_IRUSR) == -1) {
       perror("chmod failed");
   }
   ```

## Error Handling

1. Using errno and perror:
   ```c
   if (fd == -1) {
       perror("./doc1.txt");
       printf("Error number: %d\n", errno);
       exit(0);
   }
   ```

## Examples

### High-Level File Copy

```c
FILE *source = fopen("source.txt", "r");
FILE *dest = fopen("dest.txt", "w");
char buffer[1024];

while (fscanf(source, "%s", buffer) != EOF) {
    fprintf(dest, "%s ", buffer);
}

fclose(source);
fclose(dest);
```

### Low-Level File Copy

```c
int src_fd = open("source.txt", O_RDONLY);
int dst_fd = open("dest.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
char buffer[1024];
ssize_t bytes_read;

while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
    write(dst_fd, buffer, bytes_read);
}

close(src_fd);
close(dst_fd);
```

## Key Differences

1. High-Level I/O (stdio.h):

   - Buffered operations
   - Better performance for small operations
   - More portable
   - Easier to use
   - Higher memory overhead

2. Low-Level I/O (unistd.h):
   - Unbuffered operations
   - Direct system calls
   - More control
   - Better for large files
   - Platform-specific features

## Project Structure

```
.
├── high_level_io/
│   ├── exercise_1.c  // Basic file operations
│   ├── exercise_2.c  // File copying
│   └── exercise_3.c  // Permission handling
├── low_level_io/
│   ├── read_and_write_to_file.c
│   ├── copy_from_file.c
│   ├── change_the_permissions_mode.c
│   └── lseek.c
└── README.md
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
