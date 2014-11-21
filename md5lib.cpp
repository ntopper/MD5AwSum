#include "md5lib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <cmath>
#include <sys/ioctl.h>
#include <unistd.h>

#define HASHERROR 1
#define HASHSIZE 33
#define MESSAGESIZE 64

//http://stackoverflow.com/questions/7656219/c-c-function-for-generating-a-hash-for-passwords-using-md5-or-another-algorit
//http://bobobobo.wordpress.com/2010/10/17/md5-c-implementation/

//consider removing for loops in digest to speed up algorithm?
//sacrifice readability?

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

	//return md5lib(file_path).get();
}

md5lib::md5lib(string path) {
	this->file_path = path;
	this->result = "\0";

	//determine size of the file
	streampos start, end;
	ifstream f(this->file_path, ios::binary);
	start = f.tellg();
	f.seekg(0,ios::end);
	end = f.tellg();
	this->size = (end-start);

	//determine what breaks should be for progress bar
	if(!(this->size) || this->size < 100) this->sizebreak = 1;
	else this->sizebreak = this->size/100;

	//begin hash progress
	this->initialize();
	this->process();
	this->finalize();
}

string md5lib::get() {
	return this->result;
}

void md5lib::initialize() {
	//populate K
	for(uint32_t i = 0; i < 64; i++) {
		this->K[i] = floor(abs(sin(i+1)) * pow(2,32));
	}

	//initialization values
	this->a0 = 0x67452301;
	this->b0 = 0xefcdab89;
	this->c0 = 0x98badcfe;
	this->d0 = 0x10325476;
}

void md5lib::process() {
	//initialize variables
	ifstream inpreader(this->file_path, ios::binary);
	uint64_t length = 0;
	bool alive = true;
	char buff[MESSAGESIZE+1];

	while(alive) {
		//clean buffer and read 512 bits
		memset(buff, 0, MESSAGESIZE+1);
		inpreader.read(buff, MESSAGESIZE);

		if (inpreader.eof()) {
			//set up buffers/variables and clean memory
			uint8_t output[256];
			memset(output, 0, 255);
			uint64_t new_length;
			uint64_t tmplength = length;

			//calculate new length after padding
			length += strlen(buff);
			for(new_length = length+1; new_length%64 != 56; new_length++);

			//copy bits that were read to the buffer to be padded
			memcpy(output, buff, strlen(buff));

			//append '1' bit and 0's to new length
			uint8_t *first = output + length - tmplength;
			uint8_t *last = output + new_length - tmplength + 7; //- 1 + 8;
			fill(first, last, 0);
			*first = 0x80;

			//append length in bits, converted to little endian
			uint64_t bits = length*8;
			uint8_t *rev = reinterpret_cast<uint8_t*>(&bits);
			for (int i=0, j=7; j>=0; ++i, --j) {
				*(last - i) = *(rev + j);
			}

			//push to digest algorithm
			int chunk = (new_length-tmplength+64)/64;
			for(int i = 0; i < chunk; i++) {
				uint8_t tmp[MESSAGESIZE];
				memset(tmp,0,MESSAGESIZE);
				memcpy(tmp, output+i*MESSAGESIZE, MESSAGESIZE);
				this->digest((uint32_t *)tmp);
			}

			alive = false;
		} else {
			this->digest((uint32_t *)buff);
			length += 64;
		}
		if(!(length%this->sizebreak)) this->progress(length);
	}
	inpreader.close();
	if(this->size >= 100) cout << endl;
}

uint32_t md5lib::leftrotate(uint32_t x, uint32_t c) {
	return (x << c) | (x >> (32-c));
}

void md5lib::digest(uint32_t *M) {
	//hexdump((uint8_t*)M,64);

	//initialize variables for this chunk
	uint32_t A = this->a0, B = this->b0, C = this->c0, D = this->d0;
	uint32_t F, g;

	//perform bitwise operations
	for(uint32_t j = 0; j < 64; j++) {
		if(j <= 15) {
			//round 1
			F = (B&C)|((~B)&D);
			g = j;
		} else if(j <= 31) {
			//round 2
			F = (D&B)|((~D)&C);
			g = (5*j + 1) % 16;
		} else if(j <= 47) {
			//round 3
			F = B^C^D;
			g = (3*j + 5) % 16;
		} else {
			//round 4
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
	uint8_t *temp;

	//convert to little endian
	temp = (uint8_t *)&(this->a0);
	sprintf(buff,"%2.2x%2.2x%2.2x%2.2x", temp[0], temp[1], temp[2], temp[3]);
	this->result += string(buff);
	temp = (uint8_t *)&(this->b0);
	sprintf(buff,"%2.2x%2.2x%2.2x%2.2x", temp[0], temp[1], temp[2], temp[3]);
	this->result += string(buff);
	temp = (uint8_t *)&(this->c0);
	sprintf(buff,"%2.2x%2.2x%2.2x%2.2x", temp[0], temp[1], temp[2], temp[3]);
	this->result += string(buff);
	temp = (uint8_t *)&(this->d0);
	sprintf(buff,"%2.2x%2.2x%2.2x%2.2x", temp[0], temp[1], temp[2], temp[3]);
	this->result += string(buff);
}

void md5lib::hexdump(uint8_t* buff, uint64_t size) {
	//debug function to examine bytes being digested
	cout << endl;
	for(unsigned int i = 0; i < size; i++) {
		printf("0x%2.2x\t", buff[i]);
		if (!((i+1)%8)) printf("\n");
	}
	cout << endl;
}

void md5lib::progress(uint64_t prog) {
	//get terminal columns
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	uint8_t c = (3*w.ws_col/4)-2;

	//check progress
	if(!(this->size) || this->size < 100) return;
	float pos = (float)prog/(float)(this->size);

	//create bar
	cout << "[";
	for(int i = 0; i < c; i++) {
		if(i < pos*c) cout << "=";
		else cout << " ";
	}
	cout << "]" << int(pos*100 + 1) << "%\r";
	cout.flush();
}