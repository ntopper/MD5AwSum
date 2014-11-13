#include "md5lib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <cmath>

#define HASHERROR 1
#define HASHSIZE 33
#define MESSAGESIZE 64

//http://stackoverflow.com/questions/7656219/c-c-function-for-generating-a-hash-for-passwords-using-md5-or-another-algorit
//http://bobobobo.wordpress.com/2010/10/17/md5-c-implementation/
//needs -std=c++11 to run as of now

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

	this->initialize();
	cout << "initialized... ";
	this->process();
	cout << "processed... ";
	this->finalize();
	cout << "finalized." << endl << endl;
}

string md5lib::get() {
	return this->result;
}

void md5lib::initialize() {
	for(uint32_t i = 0; i < 64; i++) {
		this->K[i] = floor(abs(sin(i+1)) * pow(2,32));
	}

	this->a0 = 0x67452301;
	this->b0 = 0xefcdab89;
	this->c0 = 0x98badcfe;
	this->d0 = 0x10325476;
}

void md5lib::process() {
	ifstream inpreader(file_path, ios::binary);
	uint32_t length = 0;
	uint32_t new_length;
	bool alive = true;
	char buff[MESSAGESIZE];
	while(alive) {
		inpreader.read(buff, MESSAGESIZE);
		if (inpreader.eof()) {
			//padding should be implemented here
			char output[2048];
			uint32_t tmplength = length;

			length += strlen(buff)*8;
			for(new_length = length+1; new_length%512 != 448; new_length++);

			memcpy(output, buff, strlen(buff));
			output[strlen(buff)] = 128;

			memcpy(output + (new_length - tmplength)/8, &length,4);

			alive = false;

			this->digest((uint32_t *)output);
		} else {
			this->digest((uint32_t *)buff);
		}
		length += 512;
	}
	inpreader.close();
}

uint32_t md5lib::leftrotate(uint32_t x, uint32_t c) {
	return (x << c) | (x >> (32-c));
}

void md5lib::digest(uint32_t *M) {
	//initialize variables for this chunk
	uint32_t A = this->a0, B = this->b0, C = this->c0, D = this->d0;
	uint32_t F, g;

	//perform bitwise operations
	for(uint32_t j = 0; j < 64; j++) {
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

		uint32_t dTemp = D;
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