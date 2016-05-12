#include <cstdio>
#include <memory.h>
#include "hash.h"

typedef byte Block[32]; // Block - массив из 32х байтов (256 бит)
typedef byte Block32[4]; // Block32 - массив из 4х байтов (32 бита)

/*
// ГОСТ 28147-89
byte S[8][16] = { // S-блоки, используемые ЦБ РФ
{ 4, 10,  9,  2, 13,  8,  0, 14,  6, 11,  1, 12,  7, 15,  5,  3},
{14, 11,  4, 12,  6, 13, 15, 10,  2,  3,  8,  1,  0,  7,  5,  9},
{ 5,  8,  1, 13, 10,  3,  4,  2, 14, 15, 12,  7,  6,  0,  9, 11},
{ 7, 13, 10,  1,  0,  8,  9, 15, 14,  4,  6, 12, 11,  2,  5,  3},
{ 6, 12,  7,  1,  5, 15, 13,  8,  4, 10,  9, 14,  0,  3, 11,  2},
{ 4, 11, 10,  0,  7,  2,  1, 13,  3,  6,  8,  5,  9, 12, 15, 14},
{13, 11,  4,  1,  3, 15,  5,  9,  0, 10, 14,  7,  6,  8,  2, 12},
{ 1, 15, 13,  0,  5,  7, 10,  4,  9,  2,  3, 14,  6, 11,  8, 12},
};
*/


byte S[8][16] = { // S-блоки компании CryptoPro
{	10,	4,	5,	6,	8,	1,	3,	7,	13,	12,	14,	0,	9,	2,	11,	15},	//1
{	5,	15,	4,	0,	2,	13,	11,	9,	1,	7,	6,	3,	12,	14,	10,	8},		//2
{	7,	15,	12,	14,	9,	4,	1,	0,	3,	11,	5,	2,	6,	10,	8,	13},	//3
{	4,	10,	7,	12,	0,	15,	2,	8,	14,	1,	6,	5,	13,	11,	9,	3},		//4
{	7,	6,	4,	11,	9,	12,	2,	10,	1,	8,	0,	14,	15,	13,	3,	5},		//5
{	7,	6,	2,	4,	13,	9,	15,	0,	10,	1,	5,	11,	8,	14,	12,	3},		//6
{	13,	14,	4,	1,	7,	0,	5,	10,	3,	12,	8,	15,	6,	2,	9,	11},	//7
{	1,	3,	10,	9,	5,	11,	4,	15,	8,	6,	7,	14,	13,	0,	2,	12},	//8
};


/*
byte S[8][16] = { // Тестовая таблица Инфотекс, похожа на ЦБ РФ, только 
				  // S-блоки в обратном порядке
	 {0x1, 0xf, 0xd, 0x0, 0x5, 0x7, 0xa, 0x4, 0x9, 0x2, 0x3, 0xe, 0x6, 0xb, 0x8, 0xc},	// 8
     {0xd, 0xb, 0x4, 0x1, 0x3, 0xf, 0x5, 0x9, 0x0, 0xa, 0xe, 0x7, 0x6, 0x8, 0x2, 0xc},	// 7
     {0x4, 0xb, 0xa, 0x0, 0x7, 0x2, 0x1, 0xd, 0x3, 0x6, 0x8, 0x5, 0x9, 0xc, 0xf, 0xe},	// 6
     {0x6, 0xc, 0x7, 0x1, 0x5, 0xf, 0xd, 0x8, 0x4, 0xa, 0x9, 0xe, 0x0, 0x3, 0xb, 0x2},	// 5
     {0x7, 0xd, 0xa, 0x1, 0x0, 0x8, 0x9, 0xf, 0xe, 0x4, 0x6, 0xc, 0xb, 0x2, 0x5, 0x3},	// 4
     {0x5, 0x8, 0x1, 0xd, 0xa, 0x3, 0x4, 0x2, 0xe, 0xf, 0xc, 0x7, 0x6, 0x0, 0x9, 0xb},	// 3
     {0xe, 0xb, 0x4, 0xc, 0x6, 0xd, 0xf, 0xa, 0x2, 0x3, 0x8, 0x1, 0x0, 0x7, 0x5, 0x9},	// 2
     {0x4, 0xa, 0x9, 0x2, 0xd, 0x8, 0x0, 0xe, 0x6, 0xb, 0x1, 0xc, 0x7, 0xf, 0x5, 0x3}	// 1
     };
*/


void E_f(byte A[], byte K[], byte R[]) { // Функция f в ГОСТ 28147-89
  int c = 0; //Складываем по модулю 2^32. c - перенос  в следующий разряд
  for (int i = 0; i < 4; i++) {
    c += A[i] + K[i];
    R[i] = c & 0xFF;
    c >>= 8;
  }

  for (int i = 0; i < 8; i++) {                  // Заменяем 4х-битные кусочки согласно S-блокам
    int x = R[i >> 1] & ((i & 1) ? 0xF0 : 0x0F);   // x - 4х-битный кусочек
    R[i >> 1] ^= x;                                // Обнуляем соответствующие биты
    x >>= (i & 1) ? 4 : 0;                         // сдвигаем x либо на 0, либо на 4 бита влево
    x = S[i][x];                                   // Заменяем согласно S-блоку 
    R[i >> 1] |= x << ((i & 1) ? 4 : 0);           //
  }

  int tmp = R[3]; // Сдвигаем на 8 бит (1 байт) влево
  R[3] = R[2];
  R[2] = R[1];
  R[1] = R[0];
  R[0] = tmp;

  tmp = R[0] >> 5; // Сдвигаем еще на 3 бита влево
  for (int i = 1; i < 4; i++) {
    int nTmp = R[i] >> 5;
    R[i] = (R[i] << 3) | tmp;
    tmp = nTmp;
  }
  R[0] = (R[0] << 3) | tmp;
}

void E(byte  D[], byte K[], byte R[]) { // ГОСТ 28147-89
  Block32 A, B;                                //Инициализация блоков A и B
  for (int i = 0; i < 4; i++) A[i] = D[i];
  for (int i = 0; i < 4; i++) B[i] = D[i + 4];

  for (int step = 0; step < 3; step++)         // K1..K24 идут в прямом порядке - три цикла K1..K8
    for (int i = 0; i < 32; i += 4) {
      Block32 tmp; E_f(A, K + i, tmp);              // (K + i) - массив K с i-го элемента
      for (int i = 0; i < 4; i++) tmp[i] ^= B[i];
      memcpy(B, A, sizeof A); memcpy(A, tmp, sizeof tmp);
    }
  for (int i = 28; i >= 0; i -= 4) { // А K25..K32 идут в обратном порядке
    Block32 tmp; E_f(A, K + i, tmp);
    for (int i = 0; i < 4; i++) tmp[i] ^= B[i];
    memcpy(B, A, sizeof A); memcpy(A, tmp, sizeof tmp);
  }
  for (int i = 0; i < 4; i++) R[i] = B[i];      //Возвращаем результат
  for (int i = 0; i < 4; i++) R[i + 4] = A[i];
}

// GOST R 34.11-94
void A(byte Y[], byte R[]) {
  for (int i = 0; i < 24; i++) R[i] = Y[i + 8];
  for (int i = 0; i < 8; i++) R[i + 24] = Y[i] ^ Y[i + 8];
}

int fi(int arg) { // Функция фи. Отличие от функции в статье - нумерация не 1..32, а 0..31
  int i = arg & 0x03;
  int k = arg >> 2; k++;
  return (i << 3) + k - 1;
}
void P(byte Y[], byte R[]) {
  for (int i = 0; i < 32; i++) R[i] = Y[fi(i)];
}

void psi(byte arr[]) {
  byte y16[] = {0, 0};
  y16[0] ^= arr[ 0]; y16[1] ^= arr[ 1];
  y16[0] ^= arr[ 2]; y16[1] ^= arr[ 3];
  y16[0] ^= arr[ 4]; y16[1] ^= arr[ 5];
  y16[0] ^= arr[ 6]; y16[1] ^= arr[ 7];
  y16[0] ^= arr[24]; y16[1] ^= arr[25];
  y16[0] ^= arr[30]; y16[1] ^= arr[31];
  for (int i = 0; i < 30; i++) arr[i] = arr[i + 2];
  arr[30] = y16[0]; arr[31] = y16[1];
}
void psi(byte arr[], int p) {
  while (p--) psi(arr);
}

void f(byte H[], byte M[], byte newH[]) { // Функция f
  Block C[4];
  memset(C, 0, sizeof C);
  C[2][ 0] = 0x00;
  C[2][ 1] = 0xFF;
  C[2][ 2] = 0x00;
  C[2][ 3] = 0xFF;
  C[2][ 4] = 0x00;
  C[2][ 5] = 0xFF;
  C[2][ 6] = 0x00;
  C[2][ 7] = 0xFF;
  C[2][ 8] = 0xFF;
  C[2][ 9] = 0x00;
  C[2][10] = 0xFF;
  C[2][11] = 0x00;
  C[2][12] = 0xFF;
  C[2][13] = 0x00;
  C[2][14] = 0xFF;
  C[2][15] = 0x00;
  C[2][16] = 0x00;
  C[2][17] = 0xFF;
  C[2][18] = 0xFF;
  C[2][19] = 0x00;
  C[2][20] = 0xFF;
  C[2][21] = 0x00;
  C[2][22] = 0x00;
  C[2][23] = 0xFF;
  C[2][24] = 0xFF;
  C[2][25] = 0x00;
  C[2][26] = 0x00;
  C[2][27] = 0x00;
  C[2][28] = 0xFF;
  C[2][29] = 0xFF;
  C[2][30] = 0x00;
  C[2][31] = 0xFF;

  Block U, V, W, K[4], tmp;
  memcpy(U, H, sizeof U);
  memcpy(V, M, sizeof V);
  for (int i = 0; i < 32; i++) W[i] = U[i] ^ V[i];
  P(W, K[0]);

  for (int step = 1; step < 4; step++) {
    A(U, tmp); for (int i = 0; i < 32; i++) U[i] = tmp[i] ^ C[step][i];
    A(V, tmp); A(tmp, V);
    for (int i = 0; i < 32; i++) W[i] = U[i] ^ V[i];
    P(W, K[step]);
  }

  Block S;
  for (int i = 0; i < 32; i += 8)
    E(H + i, K[i >> 3], S + i);

  psi(S, 12); for (int i = 0; i < 32; i++) S[i] ^= M[i];
  psi(S, 1 ); for (int i = 0; i < 32; i++) S[i] ^= H[i];
  psi(S, 61);
  memcpy(newH, S, sizeof S);
}

void hash(byte buf[], int len, byte result[]) {
  Block block, Sum, L, H, newH;
  int pos = 0, posIB = 0;

  memset(Sum, 0, sizeof Sum);
  memset(H, 0, sizeof H);

  while ((posIB < len) || pos) {
    if (posIB < len) block[pos++] = buf[posIB++];
    else block[pos++] = 0;
    if (pos == 32) {
      pos = 0;

      int c = 0;
      for (int i = 0; i < 32; i++) {
        c += block[i] + Sum[i];
        Sum[i] = c & 0xFF;
        c >>= 8;
      }

      f(H, block, newH); memcpy(H, newH, sizeof newH);
    }
  }

  memset(L, 0, sizeof L);
  int c = len << 3;
  for (int i = 0; i < 32; i++) {
    L[i] = c & 0xFF;
    c >>= 8;
  }
  f(H, L, newH); memcpy(H, newH, sizeof newH);
  f(H, Sum, newH); memcpy(result, newH, sizeof newH);
}
