/*
 * test_data.h
 *
 *  Created on: Feb 12, 2013
 *      Author: Oleksandr Kazymyrov
 *		Acknowledgments: Oleksii Shevchuk
 */

#ifndef TEST_DATA_H_
#define TEST_DATA_H_

#define TEST_VECTORS 2
#define MAX_MESSAGE_LENGTH 72 // in bytes

unsigned char Message[TEST_VECTORS][MAX_MESSAGE_LENGTH] = {
	{
		0x32,0x31,0x30,0x39,0x38,0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30,0x39,0x38,0x37,
		0x36,0x35,0x34,0x33,0x32,0x31,0x30,0x39,0x38,0x37,0x36,0x35,0x34,0x33,0x32,0x31,
		0x30,0x39,0x38,0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30,0x39,0x38,0x37,0x36,0x35,
		0x34,0x33,0x32,0x31,0x30,0x39,0x38,0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30
	},
	{
		0xfb,0xe2,0xe5,0xf0,0xee,0xe3,0xc8,0x20,0xfb,0xea,0xfa,0xeb,0xef,0x20,0xff,0xfb,
		0xf0,0xe1,0xe0,0xf0,0xf5,0x20,0xe0,0xed,0x20,0xe8,0xec,0xe0,0xeb,0xe5,0xf0,0xf2,
		0xf1,0x20,0xff,0xf0,0xee,0xec,0x20,0xf1,0x20,0xfa,0xf2,0xfe,0xe5,0xe2,0x20,0x2c,
		0xe8,0xf6,0xf3,0xed,0xe2,0x20,0xe8,0xe6,0xee,0xe1,0xe8,0xf0,0xf2,0xd1,0x20,0x2c,
		0xe8,0xf0,0xf2,0xe5,0xe2,0x20,0xe5,0xd1
	},
};

unsigned char Hash_512[TEST_VECTORS][64] = {
	{
		0x48,0x6f,0x64,0xc1,0x91,0x78,0x79,0x41,0x7f,0xef,0x08,0x2b,0x33,0x81,0xa4,0xe2,
		0x11,0xc3,0x24,0xf0,0x74,0x65,0x4c,0x38,0x82,0x3a,0x7b,0x76,0xf8,0x30,0xad,0x00,
		0xfa,0x1f,0xba,0xe4,0x2b,0x12,0x85,0xc0,0x35,0x2f,0x22,0x75,0x24,0xbc,0x9a,0xb1,
		0x62,0x54,0x28,0x8d,0xd6,0x86,0x3d,0xcc,0xd5,0xb9,0xf5,0x4a,0x1a,0xd0,0x54,0x1b
	},
	{
		0x28,0xfb,0xc9,0xba,0xda,0x03,0x3b,0x14,0x60,0x64,0x2b,0xdc,0xdd,0xb9,0x0c,0x3f,
		0xb3,0xe5,0x6c,0x49,0x7c,0xcd,0x0f,0x62,0xb8,0xa2,0xad,0x49,0x35,0xe8,0x5f,0x03,
		0x76,0x13,0x96,0x6d,0xe4,0xee,0x00,0x53,0x1a,0xe6,0x0f,0x3b,0x5a,0x47,0xf8,0xda,
		0xe0,0x69,0x15,0xd5,0xf2,0xf1,0x94,0x99,0x6f,0xca,0xbf,0x26,0x22,0xe6,0x88,0x1e
	},
};

unsigned char Hash_256[TEST_VECTORS][32] = {
	{
		0x00,0x55,0x7b,0xe5,0xe5,0x84,0xfd,0x52,0xa4,0x49,0xb1,0x6b,0x02,0x51,0xd0,0x5d,
		0x27,0xf9,0x4a,0xb7,0x6c,0xba,0xa6,0xda,0x89,0x0b,0x59,0xd8,0xef,0x1e,0x15,0x9d
	},
	{
		0x50,0x8f,0x7e,0x55,0x3c,0x06,0x50,0x1d,0x74,0x9a,0x66,0xfc,0x28,0xc6,0xca,0xc0,
		0xb0,0x05,0x74,0x6d,0x97,0x53,0x7f,0xa8,0x5d,0x9e,0x40,0x90,0x4e,0xfe,0xd2,0x9d
	},
};

// Message length in bits
unsigned long long MessageLength[TEST_VECTORS] = {
		504, 576
};



#endif /* TEST_DATA_H_ */
