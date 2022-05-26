#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <regex.h>
#include <errno.h>
#include <string.h>

void find_dir(char* pathname, int curdepth, int max_depth, regex_t* reg) {
  DIR *dp;
  struct dirent *d;
  errno = 0;

  if (curdepth++ > max_depth)
    return;

  if ((dp = opendir(pathname)) == NULL) {
    if (errno == EACCES) {
      fprintf(stderr, "Permisson denied : %s", pathname);
      return;
    }

    else {
      perror("opendir");
      exit(EXIT_FAILURE);
    }
  }

  while ((d = readdir(dp)) != NULL) {
    char filepath[1024] = "";
    
    strncpy(filepath, pathname, strlen(pathname));
    strncat(filepath, "/", 1);
    strncat(filepath, d->d_name, strlen(d->d_name));

    if (strncmp(d->d_name, ".", 1) != 0 && strncmp(d->d_name, "..", 2) != 0) {
      if (reg == NULL || regexec(reg, d->d_name, 0, NULL, 0) != REG_NOMATCH) {
        printf("%s\n", filepath);
      }

      if (d->d_type == DT_DIR) {
        find_dir(filepath, curdepth, max_depth, reg);
      }
    }
  }

  closedir(dp);
}

int main(int argc, char *argv[])
{
    struct stat sb;
    int opt, max_depth = INT_MAX, curdepth = 1, pattern_enable = 0;
    char * pathname = ".";
    char * pattern = ".";
    regex_t reg;

    while ((opt = getopt(argc, argv, "d:n:")) != -1) {
        switch (opt) {
            case 'd':
                max_depth = atoi(optarg);
                
                if (max_depth < 0) {
                  fprintf(stderr, "Should input vaild depth\n");
                  exit(EXIT_FAILURE);
                }

                break;
            case 'n':
                pattern = optarg;
                pattern_enable = 1;
                break;
            default:
                break;
        }
    }

    if (argc > 3 && optind == 1) {
        fprintf(stderr, "Usage: %s -d <max depth> -n <pattern> <filepath>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (optind = argc - 1) {
        pathname = argv[optind];
    }

    if (pattern_enable && regcomp(&reg, pattern, 0) != 0) {
        perror("regcomp");
        exit(EXIT_FAILURE);
    }

    if (stat(pathname, &sb) == -1) {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    if (!pattern_enable || (pattern_enable && regexec(&reg, pathname, 0, NULL, 0)) != REG_NOMATCH) {
      printf("%s\n", pathname);
    }

    if (S_ISDIR(sb.st_mode)) {
      if (pattern_enable) {
        find_dir(pathname, curdepth, max_depth, &reg);
      }

      else {
        find_dir(pathname, curdepth, max_depth, NULL);
      }
    }

    exit(EXIT_SUCCESS);
}