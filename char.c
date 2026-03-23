#include <stdio.h>

static const char *ASCII_CONTROL_NAMES[] = {
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ",  "ACK", "BEL", "BS",
    "HT",  "LF",  "VT",  "FF",  "CR",  "SO",   "SI",  "DLE", "DC1",
    "DC2", "DC3", "DC4", "NAK", "SYN", "ETB",  "CAN", "EM",  "SUB",
    "ESC", "FS",  "GS",  "RS",  "US",  "SPACE"};

static void print_binary(unsigned char c) {
  for (int i = 7; i >= 0; i--) {
    putchar(((c >> i) & 1u) + '0');
  }
}

static const char *symbol_label(unsigned char c, char symbol[8]) {
  if (c <= 32) {
    return ASCII_CONTROL_NAMES[c];
  }

  if (c == 127) {
    return "DEL";
  }

  if (c <= 126) {
    symbol[0] = (char)c;
    symbol[1] = '\0';
  } else {
    snprintf(symbol, 8, "0x%02X", (unsigned)c);
  }

  return symbol;
}

static void print_row(unsigned char c) {
  char symbol[8];
  unsigned value = c;

  printf("%-8s %-5u 0x%02X   ", symbol_label(c, symbol), value, value);
  print_binary(c);
  putchar('\n');
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    fprintf(stderr, "usage: %s [text]\n", argv[0]);
    return 1;
  }

  printf("%-8s %-5s %-6s %s\n", "symbol", "value", "hex", "binary");

  if (argc == 1) {
    for (int i = 0; i < 128; i++) {
      print_row((unsigned char)i);
    }
  } else {
    for (int i = 0; argv[1][i] != '\0'; i++) {
      print_row((unsigned char)argv[1][i]);
    }
  }

  return 0;
}
