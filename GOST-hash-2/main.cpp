// Тесты алгоритма хеширования ГОСТ Р 34.11-94
// Используются узлы замен из процедуры проверок
// самого ГОСТ Р 34.11-94

#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

using namespace std;

const int HSB = 32;

/*
GOST ("This is message, length=32 bytes") = B1C466D37519B82E8319819FF32595E047A28CB6F83EFF1C6916A815A637FFFA
GOST ("Suppose the original message has length = 50 bytes") = 471ABA57A60A770D3A76130635C1FBEA4EF14DE51F78B4AE57DD893B62F55208
GOST ("") = CE85B99CC46752FFFEE35CAB9A7B0278ABB4C2D2055CFF685AF4912C49490F8D
GOST ("a") = D42C539E367C66E9C88A801F6649349C21871B4344C6A573F849FDCE62F314DD
GOST ("abc") = F3134348C44FB1B2A277729E2285EBB5CB5E0F29C975BC753B70497C06A4D51D
GOST ("message digest") = AD4434ECB18F2C99B60CBE59EC3D2469582B65273F48DE72DB2FDE16A4889A4D
GOST ("The quick brown fox jumps over the lazy dog") = 77B7FA410C9AC58A25F49BCA7D0468C9296529315EACA76BD1A10F376D1F4294
GOST (128 символов "U") = 53A3A3ED25180CEF0C1D85A074273E551C25660A87062A52D926A9E8FE5733A4
GOST (1000000 символов "a") = 5C00CCC2734CDD3332D3D4749576E3C1A7DBAF0E7EA74E9FA602413C90A129FA
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

		hash((byte*)TextToHashArray[j], len, hashed);

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

	hash(buf, len, hashed);

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

	hash(buf, len, hashed);

	cout << "TEST 9" << endl;
	cout << "Text to hash = 1000000 x \"a\" " << endl;

	for( int i = 0; i<HSB; ++i )
			cout << hex << setfill('0') << setw(2) <<(int)hashed[i];

	cout << endl << endl;

	return 0;
}
