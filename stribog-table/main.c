/*
 * main.c
 *
 *  Created on: Feb 15, 2013
 *      Author: Oleksandr Kazymyrov
 *		Acknowledgments: Oleksii Shevchuk
 */

#include "main.h"

#define SELF_TESTING

#ifdef SELF_TESTING
void self_testing()
{
//	unsigned char h512[64]={}, h256[32] = {};
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

	printf("  SelfTesting: Pass\n");
}
#endif
// It is not a cryptographic secure pseudorandom number generator
// 1 < bits < 64
unsigned long long get_random_number(unsigned long long bits)
{
//    srand(__rdtsc());
	srand ((unsigned int)time(NULL));

    return ( (unsigned long long) ( (((unsigned long long)1<<bits)-(bits == 64 ? 2:1))  * ((long double)rand()/(long double)RAND_MAX) ) ) & ( ((unsigned long long)1<<bits) - (bits == 64 ? 2:1));
}

void test_permofance(unsigned long long n_tests, unsigned long long n_blocks)
{
	unsigned long long i = 0, message_length = 0, block_length = 0;
	long double perfomance_rate = 0, block_rate = 0, nseconds = 0;
	unsigned char *h512 = NULL;
	clock_t begin = 0, end = 0;

	unsigned long long block_size_bits = 512, block_size_bytes;

	char cipher_name[]="Stribog";

	if (n_blocks  == 1)
		block_size_bits = 511;

	block_size_bytes = block_size_bits/8;

	h512 = calloc(sizeof(unsigned char),(size_t)(n_blocks*block_size_bytes));

	for(i=0;i<n_blocks*block_size_bytes;i++)
	{
		h512[i]=(unsigned char)get_random_number(8);
	}

	hash_512(h512,n_blocks*block_size_bits,h512); 

	begin = clock();
	//////////////////////////
	for(i=0; i<n_tests; i++)
		hash_512(h512,n_blocks*block_size_bits,h512);
	//////////////////////////
	end = clock();

	nseconds =  (long double)(end - begin) / CLOCKS_PER_SEC;

	message_length = n_tests*n_blocks*block_size_bits; // input message in bits
	block_length = n_tests;

	block_rate = (long double)block_length/nseconds;
	perfomance_rate = (long double)message_length/nseconds;

	perfomance_rate /= (1024*1024); // rate in Mbit/s

	printf("  Number of blocks: %lld Number of tests: %lld\n",n_blocks,n_tests);
	printf("  Hash = %s\n",cipher_name);
	printf("  Perfomance: %.2Lf Blk/s = %.3Lf MBit/s \n\n",block_rate, perfomance_rate);

	if(h512)
		free(h512);
}

int main()
{
//#ifdef SELF_TESTING
//	self_testing();
//#endif
	
	int i = 0;
	self_testing();

	for(i=0;i<23;i++)
	{
//		test_permofance(1<<(22-i),1<<i);
	}

	return 0;
}
