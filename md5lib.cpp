#include "md5lib.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

#define HASHERROR 1

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

	//this function will have the calls to the various parts
	//of the md5 algorithm
}

void md5lib::initialize() {
	this->s = {7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,15,21,6,10,15,21,6,10,15,21};
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
}

void md5lib::digest() {
	//main processing of input
}

void md5lib::finalize() {
	//put it all together
}