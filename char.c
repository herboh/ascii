#include <stdio.h>

void print_row(char c) {
  char symbol[8];
  char binary[9];
  int i;

  for (i = 7; i >= 0; i--) {
    binary[7 - i] = ((c >> i) & 1) ? '1' : '0';
  }
  binary[8] = '\0';

  if (c == ' ') {
    snprintf(symbol, sizeof(symbol), "space");
  } else if (c == '\n') {
    snprintf(symbol, sizeof(symbol), "\\n");
  } else if (c == '\t') {
    snprintf(symbol, sizeof(symbol), "\\t");
  } else if (c >= 33 && c <= 126) {
    symbol[0] = c;
    symbol[1] = '\0';
  } else {
    snprintf(symbol, sizeof(symbol), "0x%02X", c);
  }

  printf("%-8s %-5u 0x%02X   %s\n", symbol, c, c, binary);
}

int main(int argc, char *argv[]) {
  int i;

  if (argc > 2) {
    printf("usage: ./char [text]\n");
    return 1;
  }

  printf("%-8s %-5s %-6s %s\n", "symbol", "value", "hex", "binary");

  if (argc == 1) {
    for (i = 0; i <= 127; i++) {
      print_row((char)i);
    }
  } else {
    for (i = 0; argv[1][i] != '\0'; i++) {
      print_row((char)argv[1][i]);
    }
  }

  return 0;
}
