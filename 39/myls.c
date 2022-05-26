#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_file_info(struct stat sb) {
  printf("%5lo  ", (unsigned long) sb.st_mode);
  printf("%3lo  ", (long) sb.st_nlink);
  printf("%3ld  %3ld  ", (long) sb.st_uid, (long)sb.st_gid);
  printf("%4lld  ", (long long) sb.st_size);

  char time_str[1024] = "";

  strftime(time_str, 1024, "%b %d %H:%M", localtime(&sb.st_mtime));
  printf("%s ", time_str);
}

int main(int argc, char *argv[])
{
    struct stat sb;
    int opt;
    char * pathname = ".";
    bool list = false;
    DIR *dp;
    opterr = 0;    // disable getopt() error message

    while ((opt = getopt(argc, argv, "l:")) != -1) {
        switch (opt) {
            case 'l':
                pathname = optarg;
                list = true;
                break;
            default:
                break;
        }
    }

    if (!list && argc > 1) {
        pathname = argv[1];
    }

    if (stat(pathname, &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(sb.st_mode)) {
      if ((dp = opendir(pathname)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
      }

      struct dirent *d;

      while ((d = readdir(dp)) != NULL) {
        if (list) {
          char filepath[1024] = "";

          strncpy(filepath, pathname, strlen(pathname));
          strncat(filepath, "/", 1);
          strncat(filepath, d->d_name, strlen(d->d_name));

          if (stat(filepath, &sb) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
          }
        }

        if (list)
          print_file_info(sb);
        printf("%s\n", d->d_name);
      }

      closedir(dp);
    }

    else {
      if (list)
        print_file_info(sb);

      printf("%s\n", pathname);
    }

    exit(EXIT_SUCCESS);
}