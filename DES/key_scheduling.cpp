
#define BYTE unsigned char
#define INT unsigned int
#include <iostream>
#include <fstream>
#include<vector>
	//#include <conio.h>
#include <string>
#include <math.h>
using namespace std;

/********************************************************************
 *UNPACK8()  Unpack 8 bytes at 8bits/byte into 64 bytes at 1 bit/byte
 ********************************************************************/

void unpack8(BYTE *packed, BYTE *binary)
/*BYTE * packed;
 BYTE * binary; */
{
	 INT i, j, k;

	for (i = 0; i < 8; i++)
	{
		k = *packed++;
		for (j = 0; j < 8; j++) *binary++ = (k >> (7 - j)) &01;
	}
}

/********************************************************************
 *PACK8() Pack 64 bytes at 1 bits/byte into 8 bytes at 8 bit/byte
 ********************************************************************/

void pack8(BYTE *packed, BYTE *binary)
/* BYTE * packed;
  BYTE * binary; */
{
	 INT i, j, k;

	for (i = 0; i < 8; i++)
	{
		k = 0;
		for (j = 0; j < 8; j++) k = (k << 1) + *binary++;
		*packed++ = k;
	}
}
INT S[8][64] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
	0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
	4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
	15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
	15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
	3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
	0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
	13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
	10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
	13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
	13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
	1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
	7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
	13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
	10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
	3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
	2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
	14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
	4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
	11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
	12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
	10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
	9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
	4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
	4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
	13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
	1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
	6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
	13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
	1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
	7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
	2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};

/*PERMUTED CHOICE  PC1 */
INT PC1[] = { 57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

/*Shedule og the left shifts for C and D blocks
unsigned short shifts[] = { 2, 13, 13 };
*/
unsigned short shifts[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

/*PERMUTED CHOICE 2 (PC@) */

INT PC2[] = { 14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};
// 
// key[i] = CD[PC2[i]-1];

/*Key Scedule of 16 498-bit subkey generated from 64-bit key */

BYTE KS[16][48];

int main()
{
	ofstream ofile, allkeys;
	ofile.open("scheduledkey.txt");	// file will store keys for brute force 
	 INT i, j, k, t1, t2, z;
	int CD[56];
	for (int q = 0; q < 56; q++)
	{
		CD[q] = -1;
	}
	int key6[48];
	int blocks[8] = { 45,59,-1,7,46,57,17,48 };	// bytewise round key of 6th round obtained from sbox.cpp
	int p = 0;
	for (int i = 0; i < 8; i++)
	{
		// storing key bitwise 
		int x = blocks[i];
		if (x == -1)
		{
			for (int q = 1; q <= 6; q++)
			{
				key6[p] = -1;
				p++;
			}
		}
		else
		{
			for (int q = 1; q <= 6; q++)
			{
				key6[p] = (x >> (6 - q)) &1;
				p++;
			}
		}
	}
  ofile<<"42 bits 6 the round subkey\n";
	for (z = 0; z < 48; z++)
		ofile << key6[z] << ' ';
	ofile << '\n';

	int r = 6;
	for (int i = 0; i < 48; i++)
	{
		// going to CD before generation of 6th round subkey 
		CD[PC2[i] - 1] = key6[i];
	}
  ofile<<"CD used to generate 6th round subkey\n";
	for (z = 0; z < 56; z++)
		ofile << CD[z] << ' ';
	ofile << '\n';

	for (i = 0; i < r; i++)
	{
		                                 // rightshifting CD 6 times corresponding to left shifts that were done 
		for (j = 0; j < shifts[5 - i]; j++)
		{
			                             //  before reaching CD of 6th round in key generation, so we get the 
			t1 = CD[27];	               // CD used for key generation of first round and we will brute force on it.
			t2 = CD[55];
			for (k = 27; k >= 1; k--)
			{
				CD[k] = CD[k - 1];
				CD[k + 28] = CD[k + 27];
			}
			CD[0] = t1;
			CD[28] = t2;
		}
	}

	int c = 0;
  ofile<<"CD for generating first round subkey aka our main key\n";
	for (z = 0; z < 56; z++)
	{
		ofile << int(CD[z]) << ' ';
		if (CD[z] == -1)
		{
			c++;
		}
	}
  ofile<<"\n no of missing bits in 56 bits of DES key\n";
	ofile <<c << endl;
	allkeys.open("key_output.txt");
	for (int i = 0; i < (1 << 14); i++)
	{
		// generating all possible keys for brute force (2^14)
		vector<int> x;
		for (int j = 0; j < 14; j++)
		{
			x.push_back(((i >> (13 - j)) &1));
		}
		int j = 0;
		for (int k = 0; k < 56; k++)
		{
			if (CD[k] == -1)
			{
				allkeys << x[j++];
			}
			else
			{
				allkeys << CD[k];
			}
		}
		allkeys << "\n";
	}

	return 0;
}