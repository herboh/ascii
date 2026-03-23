#include <stdio.h>

int main(int argc, char *argv[]) {
  int c;

  c = getchar();

  if (c != EOF) {
    printf("%c\n", c);
  }

  return 0;
}
