#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    struct stat sb;
    int fd, n, line_cnt;
    char * pathname = "";

    if (argc != 3 || strlen(argv[1]) < 0 || argv[1][0] != '-') {
        fprintf(stderr, "Usage: %s -<offset> <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    line_cnt = -(atoi(argv[1]));
    pathname = argv[2];

    if (stat(pathname, &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if ((fd = open(pathname, O_RDONLY)) == -1) {
      perror("open");
      exit(EXIT_FAILURE);
    }

    if (lseek(fd, -1, SEEK_END) == -1) {
      perror("lseek");
      exit(EXIT_FAILURE);
    }

    char buf[sb.st_size];

    while (line_cnt > 0) {
      if (read(fd, buf, 1) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
      }

      if (buf[0] == '\n')
        line_cnt--;

      n = lseek(fd, -2, SEEK_CUR);

      if (n == -1)
        break;
    }

    if (n > 0 || line_cnt == 0) {
      if (lseek(fd, 2, SEEK_CUR) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
      }
    }
    
    else {
      if (lseek(fd, 0, SEEK_CUR) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
      }
    }

    memset(buf, 0, sb.st_size);

    if (read(fd, buf, sb.st_size) == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    printf("%s", buf);
    close(fd);

    exit(EXIT_SUCCESS);
}