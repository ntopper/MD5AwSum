#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Md5Hash.h"
#include "md5lib.h"

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
	if (isstr) this->handleString(inpstr);
	else this->file_path = inpstr;

	//this->checksum = md5lib::hash(this->file_path);
	md5lib hasher(this->file_path);
	this->checksum = hasher.get();

	if (isstr) this->cleanupString();
}

void Md5Hash::handleString(string s) throw(int) {
	ofstream f;
	f.open(TMPFILEPATH);
	f << s;
	f.close();
	this->file_path = TMPFILEPATH;
}

void Md5Hash::cleanupString() throw(int) {
	string s = "rm " + string(TMPFILEPATH);
	popen(s.c_str(), "r");
}

string Md5Hash::getChecksum() {
	return this->checksum;
}
