/*
Distributor ID:	Ubuntu
Description:	Ubuntu 16.04.2 LTS
Release:	16.04
Codename:	xenial
Building command: g++ -g -O2 -std=gnu++14 -static -o main main.cpp
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdint.h>
#include <stdlib.h>
#include <map>
#include <vector>

using namespace std;

typedef int32_t myint;
typedef uint32_t myuint;
typedef int8_t mychar;
typedef uint8_t myuchar;

const string sgen = "BDRQKPTVJI";
const string ngen = "0123456789";
const myuint i_val[4] = { 0x10325476u, 0x98badcfeu, 0xefcdab89u, 0x67452301u };
const myuint R1[8] = { 0xd1310ba6u, 0x98dfb5acu, 0x2ffd72dbu, 0xd01adfb7u, 0xb8e1afedu, 0x6a267e96u, 0xba7c9045u, 0xf12c7f99u };
const myuint R2[8] = { 0x00000000u, 0x77073096u, 0xee0e612cu, 0x990951bau, 0x076dc419u, 0x706af48fu, 0xe963a535u, 0x9e6495a3u };

const myuint startR3 = 0x404020u;
map<string, myint> ps1_ps2;
myuint R3[256];
FILE* keyFILE;

unsigned int hexToInt(char* s) {
	unsigned int res = 0;
	for (int i = 0, len = strlen(s); i < len; ++i) {
		res *= 16;
		if (s[i] >= '0' && s[i] <= '9')
			res += (s[i] - '0');
		else if (s[i] >= 'a' && s[i] <= 'f')
			res += (s[i] - 'a') + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			res += (s[i] - 'A') + 10;
	}
	return res;
}

void preProcess() {
	char buff[105];
	char s[4][5];
	FILE *fi = fopen("memory.txt", "r");
	FILE *fo = fopen("fixed_data.txt", "w");
	while (!feof(fi)) {
		fgets(buff, 102, fi);
		char* tok = strtok(buff, " \n");
		unsigned int address = hexToInt(tok);
		for (int t = 0; t < 2; ++t) {
			for (int i = 0; i < 4; ++i) {
				tok = strtok(NULL, " \n");
				memcpy(s + i, tok, sizeof(char) * 3);
			}
			fprintf(fo, "%x\t%s%s%s%s\n", address + t * 4, s[3], s[2], s[1], s[0]);
		}
	}
	fclose(fi);
	fclose(fo);
}

void readData() {
	FILE* f = fopen("fixed_data.txt", "r");
	for (myint i = 0; i < 256; ++i) {
		myuint x, y;
		fscanf(f, "%x %X", &x, &y);
		R3[i] = y;
	}
	fclose(f);
}

myuint calc(myuint eax) {
	mychar t[10];
	sprintf((char*)t, "%08X", eax);
	for (myint i = 0; i < 8; ++i)
		t[i] = (R1[i] - R2[i]) ^ myuint(t[i]);
	for (myint i = 0; i < 8; ++i) {
		myint temp = t[i], teax = t[i];
		t[i] = (teax << i) | temp;
	}

	myuint esi = 0xFFFFFFFF, edi;
	for (myint i = 0; i < 8; ++i) {
		eax = (unsigned char)t[i];
		edi = (unsigned char)esi;
		eax ^= edi;
		esi >>= 8;
		eax = R3[eax];
		esi ^= eax;
	}
	eax = ~esi;
	return eax;
}

myuint hardWorking(myuint mem[]) {
	myuint EAX = 0x98BADCFE, ECX = 0x67452301, EDX, EBX = 0x98BADCFE, EDI = 0xEFCDAB89, EBP_pos8, EBP_neg4, EBP_posC, EBP_neg8, ESI = 0x67452301, ESI_pos4 = 0xEFCDAB89, ESI_pos8 = 0x98BADCFE, ESI_posC = 0x10325476;
	EAX = EAX + mem[0];
	ECX = ECX + EAX;
	EAX = ECX;
	EAX = EAX >> 0x1D;
	ECX = ECX << 0x3;
	EAX = EAX | ECX;
	ECX = EDI;
	EDX = EAX;
	ECX = ECX & EAX;
	EDX = ~EDX;
	EDX = EDX & EBX;
	EBP_pos8 = EAX;
	EDX = EDX | ECX;
	ECX = 0x10325476;
	ECX = ECX + mem[1];
	ECX = ECX + EDX;
	EAX = ECX;
	EAX = EAX >> 0x19;
	ECX = ECX << 0x7;
	EAX = EAX | ECX;
	ECX = EAX;
	EDX = EAX;
	EDX = EDX & EBP_pos8;
	ECX = ~ECX;
	ECX = ECX & EDI;
	ECX = ECX | EDX;
	ECX = ECX + mem[2];
	EBX = EBX + ECX;
	ECX = EBX;
	ECX = ECX >> 0x15;
	EBX = EBX << 0xB;
	ECX = ECX | EBX;
	EBX = EAX;
	EDX = ECX;
	EBX = EBX & ECX;
	EDX = ~EDX;
	EDX = EDX & EBP_pos8;
	EDX = EDX | EBX;
	EBX = ECX;
	EDX = EDX + mem[3];
	EDI = EDI + EDX;
	EDX = EDI;
	EDX = EDX << 0x13;
	EDI = EDI >> 0xD;
	EDX = EDX | EDI;
	EDI = EDX;
	EBX = EBX & EDX;
	EDI = ~EDI;
	EDI = EDI & EAX;
	EBP_neg4 = EDX;
	EDI = EDI | EBX;
	EBX = EBP_pos8;
	EDI = EDI + mem[4];
	EBX = EBX + EDI;
	EDI = EBX;
	EDI = EDI >> 0x1D;
	EBX = EBX << 0x3;
	EDI = EDI | EBX;
	EBP_pos8 = EDI;
	EBX = EDI;
	EDX = EDX & EDI;
	EBX = ~EBX;
	EBX = EBX & ECX;
	EDI = EBP_neg4;
	EBX = EBX | EDX;
	EBX = EBX + mem[5];
	EAX = EAX + EBX;
	EDX = EAX;
	EDX = EDX >> 0x19;
	EAX = EAX << 0x7;
	EDX = EDX | EAX;
	EAX = EDX;
	EBX = EDX;
	EBX = EBX & EBP_pos8;
	EAX = ~EAX;
	EAX = EAX & EDI;
	EAX = EAX | EBX;
	EBX = EDX;
	EAX = EAX + mem[6];
	ECX = ECX + EAX;
	EAX = ECX;
	EAX = EAX >> 0x15;
	ECX = ECX << 0xB;
	EAX = EAX | ECX;
	ECX = EAX;
	EBX = EBX & EAX;
	ECX = ~ECX;
	ECX = ECX & EBP_pos8;
	ECX = ECX | EBX;
	EBX = EAX;
	ECX = ECX + mem[7];
	EDI = EDI + ECX;
	ECX = EDI;
	ECX = ECX << 0x13;
	EDI = EDI >> 0xD;
	ECX = ECX | EDI;
	EDI = ECX;
	EBX = EBX & ECX;
	EDI = ~EDI;
	EDI = EDI & EDX;
	EBP_neg4 = ECX;
	EDI = EDI | EBX;
	EBX = EBP_pos8;
	EDI = EDI + mem[8];
	EBX = EBX + EDI;
	EDI = EBX;
	EDI = EDI >> 0x1D;
	EBX = EBX << 0x3;
	EDI = EDI | EBX;
	EBX = EDI;
	ECX = ECX & EDI;
	EBX = ~EBX;
	EBX = EBX & EAX;
	EBP_pos8 = EDI;
	EBX = EBX | ECX;
	EDI = EBP_neg4;
	EBX = EBX + mem[9];
	EDX = EDX + EBX;
	ECX = EDX;
	ECX = ECX >> 0x19;
	EDX = EDX << 0x7;
	ECX = ECX | EDX;
	EDX = ECX;
	EBX = ECX;
	EBX = EBX & EBP_pos8;
	EDX = ~EDX;
	EDX = EDX & EDI;
	EDX = EDX | EBX;
	EBX = ECX;
	EDX = EDX + mem[10];
	EAX = EAX + EDX;
	EDX = EAX;
	EDX = EDX >> 0x15;
	EAX = EAX << 0xB;
	EDX = EDX | EAX;
	EAX = EDX;
	EBX = EBX & EDX;
	EAX = ~EAX;
	EAX = EAX & EBP_pos8;
	EAX = EAX | EBX;
	EAX = EAX + mem[11];
	EBX = EDX;
	EDI = EDI + EAX;
	EAX = EDI;
	EAX = EAX << 0x13;
	EDI = EDI >> 0xD;
	EAX = EAX | EDI;
	EDI = EAX;
	EBX = EBX & EAX;
	EDI = ~EDI;
	EDI = EDI & ECX;
	EBP_neg4 = EAX;
	EDI = EDI | EBX;
	EBX = EBP_pos8;
	EDI = EDI + mem[12];
	EBX = EBX + EDI;
	EDI = EBX;
	EDI = EDI >> 0x1D;
	EBX = EBX << 0x3;
	EDI = EDI | EBX;
	EBX = EDI;
	EAX = EAX & EDI;
	EBX = ~EBX;
	EBX = EBX & EDX;
	EBX = EBX | EAX;
	EBX = EBX + mem[13];
	ECX = ECX + EBX;
	EBX = ECX;
	EBX = EBX >> 0x19;
	ECX = ECX << 0x7;
	EBX = EBX | ECX;
	EAX = EBX;
	ECX = EBX;
	EAX = ~EAX;
	EAX = EAX & EBP_neg4;
	ECX = ECX & EDI;
	EAX = EAX | ECX;
	EAX = EAX + mem[14];
	EDX = EDX + EAX;
	EAX = EDX;
	EAX = EAX >> 0x15;
	EDX = EDX << 0xB;
	EAX = EAX | EDX;
	EDX = EBX;
	ECX = EAX;
	EDX = EDX & EAX;
	ECX = ~ECX;
	ECX = ECX & EDI;
	ECX = ECX | EDX;
	EDX = EBP_neg4;
	ECX = ECX + mem[15];
	EDX = EDX + ECX;
	ECX = EDX;
	ECX = ECX << 0x13;
	EDX = EDX >> 0xD;
	ECX = ECX | EDX;
	EDX = EAX;
	EBP_neg4 = ECX;
	EDX = EDX | ECX;
	ECX = EAX;
	EDX = EDX & EBX;
	ECX = ECX & EBP_neg4;
	EDX = EDX | ECX;
	EDX = EDX + mem[0];
	EDI = EDI + EDX + 0x5A826999;
	ECX = EDI;
	EDX = EDI;
	EDI = EBP_neg4;
	ECX = ECX >> 0x1D;
	EDX = EDX << 0x3;
	ECX = ECX | EDX;
	EBP_posC = EDI;
	EBP_posC = EBP_posC | ECX;
	EDI = EDI & ECX;
	EDX = EBP_posC;
	EDX = EDX & EAX;
	EDX = EDX | EDI;
	EDX = EDX + mem[4];
	EDX = EBX + EDX + 0x5A826999;
	EBX = EDX;
	EBX = EBX >> 0x1B;
	EDX = EDX << 0x5;
	EBX = EBX | EDX;
	EDX = EBP_posC;
	EDX = EDX & EBX;
	EBP_neg8 = EBX;
	EDX = EDX | EDI;
	EDX = EDX + mem[8];
	EDX = EAX + EDX + 0x5A826999;
	EAX = EDX;
	EAX = EAX >> 0x17;
	EDX = EDX << 0x9;
	EAX = EAX | EDX;
	EDX = EAX;
	EDI = EAX;
	EDX = EDX | ECX;
	EDI = EDI & ECX;
	EDX = EDX & EBX;
	EDX = EDX | EDI;
	EDI = EBP_neg4;
	EDX = EDX + mem[12];
	EDI = EDI + EDX + 0x5A826999;
	EDX = EDI;
	EDX = EDX >> 0x13;
	EDI = EDI << 0xD;
	EDX = EDX | EDI;
	EDI = EAX;
	EDI = EDI | EDX;
	EBP_neg4 = EDX;
	EDI = EDI & EBX;
	EBX = EAX;
	EBX = EBX & EDX;
	EDI = EDI | EBX;
	EBX = EBP_neg8;
	EDI = EDI + mem[1];
	ECX = ECX + EDI + 0x5A826999;
	EDI = ECX;
	EDI = EDI >> 0x1D;
	ECX = ECX << 0x3;
	EDI = EDI | ECX;
	ECX = EDX;
	EBP_neg4 = EBP_neg4 & EDI;
	ECX = ECX | EDI;
	EBP_pos8 = EDI;
	EDI = ECX;
	EDI = EDI & EAX;
	EDI = EDI | EBP_neg4;
	EDI = EDI + mem[5];
	EBX = EBX + EDI + 0x5A826999;
	EDI = EBX;
	EDI = EDI >> 0x1B;
	EBX = EBX << 0x5;
	EDI = EDI | EBX;
	ECX = ECX & EDI;
	ECX = ECX | EBP_neg4;
	ECX = ECX + mem[9];
	ECX = EAX + ECX + 0x5A826999;
	EAX = ECX;
	EAX = EAX >> 0x17;
	ECX = ECX << 0x9;
	EAX = EAX | ECX;
	ECX = EAX;
	EBX = EAX;
	ECX = ECX | EBP_pos8;
	EBX = EBX & EBP_pos8;
	ECX = ECX & EDI;
	ECX = ECX | EBX;
	EBX = EAX;
	ECX = ECX + mem[13];
	EDX = EDX + ECX + 0x5A826999;
	ECX = EDX;
	ECX = ECX >> 0x13;
	EDX = EDX << 0xD;
	ECX = ECX | EDX;
	EDX = EAX;
	EDX = EDX | ECX;
	EBX = EBX & ECX;
	EDX = EDX & EDI;
	EDX = EDX | EBX;
	EBX = EBP_pos8;
	EDX = EDX + mem[2];
	EBX = EBX + EDX + 0x5A826999;
	EDX = EBX;
	EBP_posC = ECX;
	EDX = EDX >> 0x1D;
	EBX = EBX << 0x3;
	EDX = EDX | EBX;
	EBP_neg4 = ECX;
	EBP_posC = EBP_posC | EDX;
	EBP_neg4 = EBP_neg4 & EDX;
	EBP_pos8 = EDX;
	EDX = EBP_posC;
	EDX = EDX & EAX;
	EDX = EDX | EBP_neg4;
	EDX = EDX + mem[6];
	EDI = EDI + EDX + 0x5A826999;
	EDX = EBP_posC;
	EBX = EDI;
	EBX = EBX >> 0x1B;
	EDI = EDI << 0x5;
	EBX = EBX | EDI;
	EDX = EDX & EBX;
	EBP_neg8 = EBX;
	EDX = EDX | EBP_neg4;
	EDX = EDX + mem[10];
	EDX = EAX + EDX + 0x5A826999;
	EAX = EDX;
	EAX = EAX >> 0x17;
	EDX = EDX << 0x9;
	EAX = EAX | EDX;
	EDX = EAX;
	EDI = EAX;
	EDX = EDX | EBP_pos8;
	EDI = EDI & EBP_pos8;
	EDX = EDX & EBX;
	EDX = EDX | EDI;
	EDI = EAX;
	EDX = EDX + mem[14];
	ECX = ECX + EDX + 0x5A826999;
	EDX = ECX;
	EDX = EDX >> 0x13;
	ECX = ECX << 0xD;
	EDX = EDX | ECX;
	ECX = EAX;
	ECX = ECX | EDX;
	EDI = EDI & EDX;
	ECX = ECX & EBX;
	EBP_posC = EDX;
	ECX = ECX | EDI;
	EDI = EBP_pos8;
	ECX = ECX + mem[3];
	EBP_neg4 = EDX;
	EDI = EDI + ECX + 0x5A826999;
	ECX = EDI;
	ECX = ECX >> 0x1D;
	EDI = EDI << 0x3;
	ECX = ECX | EDI;
	EBP_posC = EBP_posC | ECX;
	EBP_neg4 = EBP_neg4 & ECX;
	EDI = EBP_posC;
	EDI = EDI & EAX;
	EDI = EDI | EBP_neg4;
	EDI = EDI + mem[7];
	EDI = EBX + EDI + 0x5A826999;
	EBX = EDI;
	EBX = EBX >> 0x1B;
	EDI = EDI << 0x5;
	EBX = EBX | EDI;
	EDI = EBP_posC;
	EDI = EDI & EBX;
	EBP_neg8 = EBX;
	EDI = EDI | EBP_neg4;
	EDI = EDI + mem[11];
	EAX = EAX + EDI + 0x5A826999;
	EDI = EAX;
	EDI = EDI >> 0x17;
	EAX = EAX << 0x9;
	EDI = EDI | EAX;
	EAX = EDI;
	EAX = EAX | ECX;
	EAX = EAX & EBX;
	EBX = EDI;
	EBX = EBX & ECX;
	EAX = EAX | EBX;
	EBX = EBP_neg8;
	EAX = EAX + mem[15];
	EDX = EDX + EAX + 0x5A826999;
	EAX = EDX;
	EAX = EAX >> 0x13;
	EDX = EDX << 0xD;
	EAX = EAX | EDX;
	EDX = EBX;
	EDX = EDX ^ EDI;
	EDX = EDX ^ EAX;
	EDX = EDX + mem[0];
	ECX = ECX + EDX + 0x6ED9FBA1;
	EDX = ECX;
	EDX = EDX >> 0x1D;
	ECX = ECX << 0x3;
	EDX = EDX | ECX;
	ECX = EDI;
	ECX = ECX ^ EAX;
	ECX = ECX ^ EDX;
	ECX = ECX + mem[8];
	ECX = EBX + ECX + 0x6ED9FBA1;
	EBX = ECX;
	EBX = EBX >> 0x17;
	ECX = ECX << 0x9;
	EBX = EBX | ECX;
	ECX = EBX;
	EBP_pos8 = EBX;
	ECX = ECX ^ EAX;
	ECX = ECX ^ EDX;
	ECX = ECX + mem[4];
	ECX = EDI + ECX + 0x6ED9FBA1;
	EDI = ECX;
	EDI = EDI >> 0x15;
	ECX = ECX << 0xB;
	EDI = EDI | ECX;
	EBP_pos8 = EBP_pos8 ^ EDI;
	ECX = EBP_pos8;
	ECX = ECX ^ EDX;
	ECX = ECX + mem[12];
	ECX = EAX + ECX + 0x6ED9FBA1;
	EAX = ECX;
	EAX = EAX >> 0x11;
	ECX = ECX << 0xF;
	EAX = EAX | ECX;
	ECX = EBP_pos8;
	ECX = ECX ^ EAX;
	ECX = ECX + mem[2];
	EDX = EDX + ECX + 0x6ED9FBA1;
	ECX = EDX;
	ECX = ECX >> 0x1D;
	EDX = EDX << 0x3;
	ECX = ECX | EDX;
	EDX = EDI;
	EDX = EDX ^ EAX;
	EDX = EDX ^ ECX;
	EDX = EDX + mem[10];
	EBX = EBX + EDX + 0x6ED9FBA1;
	EDX = EBX;
	EDX = EDX >> 0x17;
	EBX = EBX << 0x9;
	EDX = EDX | EBX;
	EBX = EDX;
	EBP_pos8 = EDX;
	EBX = EBX ^ EAX;
	EBX = EBX ^ ECX;
	EBX = EBX + mem[6];
	EDI = EDI + EBX + 0x6ED9FBA1;
	EBX = EDI;
	EBX = EBX >> 0x15;
	EDI = EDI << 0xB;
	EBX = EBX | EDI;
	EBP_pos8 = EBP_pos8 ^ EBX;
	EDI = EBP_pos8;
	EDI = EDI ^ ECX;
	EDI = EDI + mem[14];
	EDI = EAX + EDI + 0x6ED9FBA1;
	EAX = EDI;
	EAX = EAX >> 0x11;
	EDI = EDI << 0xF;
	EAX = EAX | EDI;
	EDI = EBP_pos8;
	EDI = EDI ^ EAX;
	EDI = EDI + mem[1];
	EDI = ECX + EDI + 0x6ED9FBA1;
	ECX = EDI;
	ECX = ECX >> 0x1D;
	EDI = EDI << 0x3;
	ECX = ECX | EDI;
	EDI = EBX;
	EDI = EDI ^ EAX;
	EDI = EDI ^ ECX;
	EDI = EDI + mem[9];
	EDX = EDX + EDI + 0x6ED9FBA1;
	EDI = EDX;
	EDI = EDI >> 0x17;
	EDX = EDX << 0x9;
	EDI = EDI | EDX;
	EDX = EDI;
	EBP_pos8 = EDI;
	EDX = EDX ^ EAX;
	EDX = EDX ^ ECX;
	EDX = EDX + mem[5];
	EBX = EBX + EDX + 0x6ED9FBA1;
	EDX = EBX;
	EDX = EDX >> 0x15;
	EBX = EBX << 0xB;
	EDX = EDX | EBX;
	EBP_pos8 = EBP_pos8 ^ EDX;
	EBX = EBP_pos8;
	EBX = EBX ^ ECX;
	EBX = EBX + mem[13];
	EBX = EAX + EBX + 0x6ED9FBA1;
	EAX = EBX;
	EAX = EAX >> 0x11;
	EBX = EBX << 0xF;
	EAX = EAX | EBX;
	EBX = EBP_pos8;
	EBX = EBX ^ EAX;
	EBX = EBX + mem[3];
	EBX = ECX + EBX + 0x6ED9FBA1;
	ECX = EBX;
	ECX = ECX >> 0x1D;
	EBX = EBX << 0x3;
	ECX = ECX | EBX;
	EBX = EDX;
	EBX = EBX ^ EAX;
	ESI = ESI + ECX;
	EBX = EBX ^ ECX;
	EBX = EBX + mem[11];
	EDI = EDI + EBX + 0x6ED9FBA1;
	EBX = EDI;
	EBX = EBX >> 0x17;
	EDI = EDI << 0x9;
	EBX = EBX | EDI;
	EDI = EBX;
	ESI_posC = ESI_posC + EBX;
	EDI = EDI ^ EAX;
	EDI = EDI ^ ECX;
	EDI = EDI + mem[7];
	EDX = EDX + EDI + 0x6ED9FBA1;
	EDI = EDX;
	EDI = EDI >> 0x15;
	EDX = EDX << 0xB;
	EDI = EDI | EDX;
	EDX = EBX;
	EDX = EDX ^ EDI;
	ESI_pos8 = ESI_pos8 + EDI;
	EDX = EDX ^ ECX;
	EDX = EDX + mem[15];
	EAX = EAX + EDX + 0x6ED9FBA1;
	ECX = EAX;
	ECX = ECX >> 0x11;
	EAX = EAX << 0xF;
	ECX = ECX | EAX;
	ESI_pos4 = ESI_pos4 + ECX;
	return ESI ^ ESI_pos4 ^ ESI_pos8 ^ ESI_posC;
}

void findOtherPath(const mychar* first) {
	myuint dkey[4];
	memcpy(dkey, i_val, sizeof(myuint) * 4);
	myuchar mem[64];
	memset(mem, 0, sizeof(myuchar) * 64);
	for (myint i = 0; i < 5; ++i)
		mem[i] = first[i];
	mem[5] = 0x80;
	mem[56] = 0x28;
	myint eax = hardWorking((myuint*)mem);
	eax = calc(eax);
	ps1_ps2[(char*)first] = eax;
	fprintf(keyFILE, "%s %08X\n", first, eax);
}

void generateFiveFirst(string cur, myint n, myint m) {
	if (n + m == 5) {
		findOtherPath((mychar*)cur.c_str());
		return;
	}
	if (n < 3)
		for (myint i = 0, sz = sgen.length(); i < sz; ++i)
			generateFiveFirst(cur + sgen[i], n + 1, m);
	if (m < 2)
		for (myint i = 0, sz = ngen.length(); i < sz; ++i)
			generateFiveFirst(cur + ngen[i], n, m + 1);
}

void toUpper(char *s) {
	for (int i = 0; i < strlen(s); ++i)
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
}

int main() {
	preProcess();
	readData();
	keyFILE = fopen("output.txt", "w");
	generateFiveFirst("", 0, 0);
	fclose(keyFILE);
	cout << "Keygen 1_2" << endl;
	cout << "Do Thanh Nhon - 1512387" << endl;
	cout << "Nguyen Quoc Huy - 1512203" << endl;
	cout << "Chau Hoang Long - 1512292" << endl << endl << endl;
	do {
		puts("All keys were generated in file output.txt");
		puts("If you have already had first part of the key, you can search the other part by enter the first part here");
		char kk[10];
		printf("Enter the first part: "); scanf("%s", kk);
		toUpper(kk);
		if (ps1_ps2.find(kk) == ps1_ps2.end()) puts("Key not found.");
		else {
			printf("The full serial number: %s-%08X\n", kk, ps1_ps2[kk]);
		}
	} while (true);
	return 0;
}
