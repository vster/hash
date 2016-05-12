#include <string.h>
#include "main.h"


void self_testing()
{
	unsigned char h512[64], h256[32];
	int i=0, j;

	for(i=0;i<TEST_VECTORS;i++)
	{
		hash_512(Message[i],MessageLength[i],h512);

		printf("Text for hashing = ");
		for(j=0; j<MessageLength[i]/8; j++) 
			printf("%02x ", ((unsigned int) Message[i][j])&0x00ff); 
		printf("\n\n");
		
		printf("Hash 512 = ");
		for(j=0; j<64; j++) 
			printf("%02x ", ((unsigned int) h512[j])&0x00ff); 
		printf("\n\n");
		

		if(memcmp(h512,Hash_512[i],sizeof(unsigned char)*64))
		{
			printf("  SelfTesting: Fail\n");
			printf("    Version: 512\n");
			printf("    Message: %d\n",i);
			printf("    Length: %lld\n",MessageLength[i]);
			return;
		}

		hash_256(Message[i],MessageLength[i],h256);

		printf("Hash 256 = ");
		for(j=0; j<32; j++) 
			printf("%02x ", ((unsigned int) h256[j])&0x00ff); 
		printf("\n\n");

		if(memcmp(h256,Hash_256[i],sizeof(unsigned char)*32))
		{
			printf("  SelfTesting: Fail\n");
			printf("    Version: 256\n");
			printf("    Message: %d\n",i);
			return;
		}
	}
	printf("  SelfTesting: Pass\n\n");
}

// It is not a cryptographic secure pseudorandom number generator
// 1 < bits < 64
unsigned long long get_random_number(unsigned long long bits)
{
	srand ((unsigned int)time(NULL));
	//  srand(__rdtsc());

    return ( (unsigned long long) ( (((unsigned long long)1<<bits)-(bits == 64 ? 2:1))  * ((long double)rand()/(long double)RAND_MAX) ) ) & ( ((unsigned long long)1<<bits) - (bits == 64 ? 2:1));
}

int main()
{
	unsigned char h512[64], h256[32];
	int i, j, len;

//	self_testing();

	for( i = 0; i < 9 ;i++ )
	{
		hash_512(TextToHashArray[i],MessageLength2[i],h512);

		printf("TEST %d\n\n", i+1);
		
		printf("Text for hashing = ");
		for(j = 0; j < MessageLength2[i]/8; j++) 
			printf("%02x ", ((unsigned int) TextToHashArray [i][j])&0x00ff); 
		printf("\n\n");
		
		printf("Hash 512 = ");
		for(j=0; j<64; j++) 
			printf("%02x ", ((unsigned int) h512[j])&0x00ff); 
		printf("\n\n");

		hash_256(TextToHashArray[i],MessageLength2[i],h256);

		printf("Hash 256 = ");
		for(j=0; j<32; j++) 
			printf("%02x ", ((unsigned int) h256[j])&0x00ff); 
		printf("\n\n\n");
	}
	return 0;
}
