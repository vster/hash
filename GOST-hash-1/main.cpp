// Тесты алгоритма хеширования ГОСТ Р 34.11-94
// Используются узлы замен из документа RFC 4357.
// Продукты компаний Верба-О, КриптоПро, ИнфоТеКС.

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

using namespace std;

const int HSB = 32;

/*
GOST("This is message, length=32 bytes") = 2CEFC2F7B7BDC514E18EA57FA74FF357E7FA17D652C75F69CB1BE7893EDE48EB
GOST("Suppose the original message has length = 50 bytes") = C3730C5CBCCACF915AC292676F21E8BD4EF75331D9405E5F1A61DC3130A65011
GOST("") = 981E5F3CA30C841487830F84FB433E13AC1101569B9C13584AC483234CD656C0
GOST("a") = E74C52DD282183BF37AF0079C9F78055715A103F17E3133CEFF1AACF2F403011
GOST("abc") = B285056DBF18D7392D7677369524DD14747459ED8143997E163B2986F92FD42C
GOST("message digest") = BC6041DD2AA401EBFA6E9886734174FEBDB4729AA972D60F549AC39B29721BA0
GOST("The quick brown fox jumps over the lazy dog") =  9004294A361A508C586FE53D1F1B02746765E71B765472786E4770D565830A76
GOST(128 символов "U") = 1C4AC7614691BBF427FA2316216BE8F10D92EDFD37CD1027514C1008F649C4E8
GOST(1000000 символов "a") = 8693287AA62F9478F7CB312EC0866B6C4E4A0F11160441E8F4FFCD2715DD554F
*/

static char *TextToHashArray[7] = {
		"This is message, length=32 bytes",
		"Suppose the original message has length = 50 bytes",
		"",
		"a",
		"abc",
		"message digest",
		"The quick brown fox jumps over the lazy dog"
		};


int main()
{

	byte *buf;
	int len;
	byte hashed[HSB];
	int i;

	for (int j = 0; j < 7; j++)
	{
 		len = (int)strlen((char*)TextToHashArray[j]);

        hash_g94((byte*)TextToHashArray[j], len, hashed);

		cout << "TEST " << j+1 << endl;
		cout << "Text to hash = " << "\"" << TextToHashArray[j] << "\"" << endl;

		for( int i=0; i<HSB; ++i )

			cout << hex << setfill('0') << setw(2)<< (int)hashed[i];
		cout << endl << endl;
		}

	buf = (byte*)malloc(129*sizeof(byte));

	for ( i = 0; i<128; i++ )
		buf[i] = 'U';
	buf[i] = 0x00;
 	len = strlen((char*)buf);

    hash_g94(buf, len, hashed);

	cout << "TEST 8" << endl;
	cout << "Text to hash = 128 x \"U\" " << endl;

	for( int i = 0; i<HSB; ++i )
			cout << hex << setfill('0') << setw(2) <<(int)hashed[i];

	cout << endl << endl;
	buf = (byte*)realloc(buf,1000001*sizeof(byte));

	for ( i = 0; i<1000000; i++ )
		buf[i] = 'a';
	buf[i] = '\0';
 	len = strlen((char*)buf);

    hash_g94(buf, len, hashed);

	cout << "TEST 9" << endl;
	cout << "Text to hash = 1000000 x \"a\" " << endl;

	for( int i = 0; i<HSB; ++i )
			cout << hex << setfill('0') << setw(2) <<(int)hashed[i];

	cout << endl << endl;

	return 0;
}
