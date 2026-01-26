#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
  char *line = NULL;
  size_t cap = 0;

  while (1) {
    printf("Enter programs to run.\n> ");
    fflush(stdout);

    ssize_t nread = getline(&line, &cap, stdin);
    if (nread == -1) {
      putchar('\n');
      break;
    }

    if (nread > 0 && line[nread - 1] == '\n') {
      line[nread - 1] = '\0';
    }

    if (line[0] == '\0') {
      continue;
    }

    pid_t pid = fork();
    if (pid < 0) {
      perror("fork");
      continue;
    }

    if (pid == 0) {
      execl(line, line, (char *)NULL);

      printf("Exec failure\n");
      _exit(127);
    } else {
      int status = 0;
      if (waitpid(pid, &status, 0) < 0) {
        perror("waitpid");
      }
    }
  }

  free(line);
  return 0;
}
