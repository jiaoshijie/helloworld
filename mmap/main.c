#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
  struct stat sb;
  const char *file_path = "./hello.o";
  size_t file_size = 0;

  if (stat(file_path, &sb)) {
    fprintf(stderr, "stat() occurs error: %s\n", strerror(errno));
    return errno;
  }
  file_size = sb.st_size;
  if (file_size == 0) {
    fprintf(stderr, "file size must be not zero\n");
    return -1;
  }

  int fd = open(file_path, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "open() occurs error: %s\n", strerror(errno));
    return errno;
  }

  void *file_mem = mmap(NULL, file_size, PROT_EXEC, MAP_PRIVATE, fd, 0);
  if (file_mem == MAP_FAILED) {
    close(fd);
    fprintf(stderr, "mmap() occurs error: %s\n", strerror(errno));
    return errno;
  }

  ((void(*)(void))(file_mem))();

  close(fd);
  munmap(file_mem, file_size);
  return 0;
}
