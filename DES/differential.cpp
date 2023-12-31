#include <iostream>
#include <fstream>
	//#include <conio.h>
#include <string>
using namespace std;

int main()
{

	ifstream ifile1, ifile2;
	ofstream input_xor, output_xor, reversefinalperm, alpha;
	int k, i, j, l;
	int cipher1[8][8], cipher2[8][8], c1_after_invperm[8][8], c2_after_inverperm[8][8], e[8][8], f[8][6], g[8][4], h, m, n, o;
	int invrfp[8][8] = { 57, 49, 41, 33, 25, 17, 9, 1,
		59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5,
		63, 55, 47, 39, 31, 23, 15, 7,
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6,
		64, 56, 48, 40, 32, 24, 16, 8
	};
	int ex[8][6] = { 32, 1, 2, 3, 4, 5,
		4, 5, 6, 7, 8, 9,
		8, 9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1
	};
	int invp[8][4] = { 9, 17, 23, 31,
		13, 28, 2, 18,
		24, 16, 30, 6,
		26, 20, 10, 1,
		8, 14, 25, 3,
		4, 29, 11, 19,
		32, 12, 22, 7,
		5, 27, 15, 21,
	};

	ifile2.open("output_1.txt");
	input_xor.open("betaxor.txt");	// input XOR
	output_xor.open("gammaxor.txt");	// output XOR
	reversefinalperm.open("reversefinalperm.txt");	// lr XOR l'r' 
	alpha.open("alpha.txt");
	string str1, str2;
	while (getline(ifile2, str1))
	{
		getline(ifile2, str2);
		k = 0;
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				cipher1[i][j] = str1[k] - '0';
				k++;
			}
		}

		k = 0;
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				cipher2[i][j] = str2[k] - '0';
				k++;
			}
		}

		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				k = (invrfp[i][j] - 1) / 8;
				l = (invrfp[i][j] - 1) % 8;
				c1_after_invperm[i][j] = cipher1[k][l];
				reversefinalperm << c1_after_invperm[i][j];
			}
		}
		reversefinalperm << '\n';
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				k = (invrfp[i][j] - 1) / 8;
				l = (invrfp[i][j] - 1) % 8;
				c2_after_inverperm[i][j] = cipher2[k][l];
				reversefinalperm << c2_after_inverperm[i][j];
			}
		}
		reversefinalperm << '\n';
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				e[i][j] = c1_after_invperm[i][j] ^ c2_after_inverperm[i][j];
			}
		}
		for (i = 0; i < 8; i++){

			for (j = 0; j < 6; j++){
				k = (ex[i][j] - 1) / 8;
				l = (ex[i][j] - 1) % 8;
				h = e[k][l];
				input_xor << h;
			}
		}
		
        e[4][5] = e[4][5] ^ 1;	// output xor after permutation operation 
		
        input_xor << '\n';
		
        
        for (i = 0; i < 8; i++){
			for (j = 0; j < 4; j++){
				k = (invp[i][j] - 1) / 8;
				l = (invp[i][j] - 1) % 8;
				g[i][j] = e[k + 4][l];
				output_xor << g[i][j];
			}
		}
		output_xor << '\n';
		for (i = 0; i < 8; i++){
            for (j = 0; j < 6; j++){
				k = (ex[i][j] - 1) / 8;
				l = (ex[i][j] - 1) % 8;
				h = c1_after_invperm[k][l];
				alpha << h;
			}
		}
		alpha << '\n';
	}
	ifile1.close();
	ifile2.close();
	input_xor.close();
	output_xor.close();
	reversefinalperm.close();
	return 0;
}