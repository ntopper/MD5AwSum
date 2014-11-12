#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "Md5Hash.h"

#define HASHERROR 1
#define STRINGFILEERROR 2
#define HASHSIZE 33
#define TMPFILEPATH "/tmp/.tmpstringtohash.txt"

using namespace std;

Md5Hash::Md5Hash(string inpstr, bool isstr) {
	this->checksum = "\0";
	if (isstr) this->handleString(inpstr);
	else this->file_path = inpstr;

	this->Digest();

	if (isstr) this->cleanupString();
}

void Md5Hash::Digest() throw(int) {
	//temporary implementation until hash function is written
	string t = "md5sum " + this->file_path;
	FILE *hashofpath = popen(t.c_str(), "r");
	if (!hashofpath) throw HASHERROR;

	char buffer[1024];
	char *inp = fgets(buffer, HASHSIZE, hashofpath);
	pclose(hashofpath);

	this->checksum = inp;
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
