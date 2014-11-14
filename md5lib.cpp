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

//debug purposes
void hexdump(char*);
void hexdump(unsigned char*);

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
	this->process();
	this->finalize();
}

string md5lib::get() {
	return this->result;
}

void md5lib::initialize() {
	this->padd[1] = 0x80;
	for(int i = 1; i < 64; i++) {
		this->padd[i] = 0x00;
	}

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
	bool alive = true;
	char buff[MESSAGESIZE];
	memset(buff, 0, MESSAGESIZE);
	while(alive) {
		inpreader.read(buff, MESSAGESIZE);
		if (inpreader.eof()) {
			char output[256]; //changing this value changes the amount of values in output
			uint32_t new_length;
			uint32_t tmplength = length;

			length += strlen(buff);
			for(new_length = (length*8)+1; (new_length%512) != 448; new_length++);
			new_length = new_length/8;

			cout << "length: " << length << endl;
			cout << "newlength: " << new_length << endl;

			memcpy(output, buff, strlen(buff));

			char *first = output + new_length - length - tmplength;
			char *last = output + new_length - tmplength - 1;
			fill(first, last, 0);
			*first = 0x80;

			//*last = (char)length; //this makes the output change each time :(
			memcpy(last, &length, 8);

			//debug
			hexdump(output);

			cout << "\n[DEBUG] length of output: " << strlen(output) << endl << endl; //the lengths are not 64 or a multiple of 64 as needed :(

			int chunk = strlen(output)/64;
			for(int i = 0; i <= chunk; i++) {
				char tmp[MESSAGESIZE];
				memcpy(tmp, output+i*MESSAGESIZE, MESSAGESIZE);
				this->digest((uint32_t *)tmp);
			}

			alive = false;
		} else {
			this->digest((uint32_t *)buff);
			length += 64;
		}
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
	sprintf(buff,"%8.8x%8.8x%8.8x%8.8x",this->a0,this->b0,this->c0,this->d0);
	this->result = string(buff);
}

void hexdump(char* buff) {
	cout << endl;
	for(unsigned int i = 0; i < strlen(buff); i++) {
		printf("0x%2.2x\t", buff[i]);
		if (!((i+1)%8)) printf("\n");
	}
	cout << endl;
}

void hexdump(unsigned char* buff) {
	cout << endl;
	for(unsigned int i = 0; i < strlen((char*)buff); i++) {
		printf("0x%2.2x\t", buff[i]);
		if (!((i+1)%8)) printf("\n");
	}
	cout << endl;
}