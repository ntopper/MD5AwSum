#include "md5lib.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <cmath>

#define HASHERROR 1
#define HASHSIZE 33
#define BUFFSIZE 512

using namespace std;

string md5lib::hash(string file_path) throw(int) {
	//temporary implementation until hash function is written
	string t = "md5sum " + file_path;
	FILE *hashofpath = popen(t.c_str(), "r");
	if (!hashofpath) throw HASHERROR;

	char buffer[1024];
	char *inp = fgets(buffer, HASHSIZE, hashofpath);
	pclose(hashofpath);

	return inp;

	//this function will set up the constructor and return the result
	//makes it so we only need one static call to hash to hash a file
	//there will be a lot going on in the background.

	//return md5lib(file_path).get();
}

md5lib::md5lib(string path) {
	this->file_path = path;
	this->result = "\0";

	//need to read from path and pass on for processing

	this->initialize();
}

string md5lib::get() {
	return this->result;
}

void md5lib::initialize() {
	for(int i = 0; i < 64; i++) {
		this->K[i] = floor(abs(sin(i+1)) * pow(2,32));
	}

	this->a0 = 0x67452301;
	this->b0 = 0xefcdab89;
	this->c0 = 0x98badcfe;
	this->d0 = 0x10325476;
}

void md5lib::preprocess() {
	//preprocessing of input
	//padding

	ifstream inpreader(file_path, ios::binary);
	char buff[BUFFSIZE]; // this should be bits not bytes
	while(1) { //must signal end
		inpreader.read(buff, sizeof(buff) / sizeof(*buff));
		this->digest(buff);
	}
	//must add padding when the buffer is not filled
	inpreader.close();
}

int md5lib::leftrotate(int x, int c) {
	return (x << c) | (x >> (32-c));
}

void md5lib::digest(string input) {
	int M[16]; //break input into 32 bit chunks (16 of them)

	//initialize variables for this chunk
	int A = this->a0, B = this->b0, C = this->c0, D = this->d0;
	int F, g;

	//perform bitwise operations
	for(int j = 0; j < 64; j++) {
		if(j <= 15) {
			F = (B&C)|((~B)&D);
			g = j;
		} else if(j > 15 && j <= 31) {
			F = (D&B)|((~D)&C);
			g = (5*j + 1) % 16;
		} else if(j > 31 && j <= 47) {
			F = B^C^D;
			g = (3*j + 5) % 16;
		} else if(j > 47) {
			F = C^(B|(~D));
			g = (7*j) % 16;
		}

		int dTemp = D;
		D = C;
		C = B;
		B = B + leftrotate((A + F + this->K[j] + M[g]), s[j]);
		A = dTemp;
	}

	//finish up this chunk
	this->a0 = this->a0 + A;
	this->b0 = this->b0 + B;
	this->c0 = this->c0 + C;
	this->d0 = this->d0 + D;
}

void md5lib::finalize() {
	//put it all together
	char buff[HASHSIZE];
	sprintf(buff,"%x%x%x%x",this->a0,this->b0,this->c0,this->d0);
	this->result = string(buff);
}