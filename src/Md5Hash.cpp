#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "headers/Md5Hash.h"
#include "headers/md5lib.h"

#define HASHERROR 1
#define STRINGFILEERROR 2
#define HASHSIZE 33
#define TMPFILEPATH "/tmp/.tmpstringtohash.txt"

using namespace std;

/*
 * This class is a wrapper class for the md5 hashing
 * algorithm. It holds relevant information on the currently
 * generated hash.
 */

Md5Hash::Md5Hash(string inpstr, bool isstr) {
	this->checksum = "\0";
	this->isstr = isstr;

	if (this->isstr) this->handleString(inpstr);
	else this->file_path = inpstr;

	//this->checksum = md5lib::hash(this->file_path);
	md5lib hasher(this->file_path);
	this->checksum = hasher.get();
}

Md5Hash::~Md5Hash() {
	this->cleanupString();
}

void Md5Hash::handleString(string s) throw(int) {
	ofstream f;
	f.open(TMPFILEPATH);
	f << s;
	f.close();
	this->file_path = TMPFILEPATH;
}

void Md5Hash::cleanupString() throw(int) {
	if(this->isstr) remove(TMPFILEPATH);
}

string Md5Hash::getChecksum() {
	return this->checksum;
}
