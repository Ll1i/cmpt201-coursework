// tokenize_loop.c
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>

int main(void) {
  char line[1024];

  while (1) {
    printf("Please enter some text: ");
    fflush(stdout);

    if (fgets(line, sizeof(line), stdin) == NULL) {
      putchar('\n');
      break;
    }

    line[strcspn(line, "\n")] = '\0';

    if (line[0] == '\0') {
      break;
    }

    printf("Tokens:\n");

    char *saveptr = NULL;
    char *token = strtok_r(line, " ", &saveptr);
    while (token != NULL) {
      printf("  %s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }

  return 0;
}
