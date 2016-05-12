#include <cstdio>
#include "hash.h"

//Если параметр не задан, то программа считает, что входной файл есть хэшируемые данные
//Иначе она считает длину текста в байтах и сам текст в шестнадцатеричном виде
// #define INPUT_HEX

int hexDig(char ch) {
  if ((ch >= '0') && (ch <= '9')) return ch - '0';
  if ((ch >= 'A') && (ch <= 'F')) return ch - 'A' + 10;
  if ((ch >= 'a') && (ch <= 'f')) return ch - 'a' + 10;
  return -1;
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  byte buf[1024]; int len;
  byte hashed[32];

#ifdef INPUT_HEX
  while (scanf("%d", &len) != EOF) {
    for (int i = len - 1; i >= 0; i--) {
      char c1 = 0, c2 = 0;
      while (hexDig(c1) < 0) scanf("%c", &c1);
      while (hexDig(c2) < 0) scanf("%c", &c2);
      buf[i] = hexDig(c1) * 16 + hexDig(c2);
    }
#else
    len = 0; while (scanf("%c", &buf[len]) != EOF) len++;
#endif
    hash(buf, len, hashed);
    printf("0x");
    for (int i = 31; i >= 0; i--)
      printf("%02X", hashed[i]);
    printf("\n");
#ifdef INPUT_HEX
  }
#endif
  return 0;
}
