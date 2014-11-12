#include "md5lib.h"
#include <iostream>
#include <string>
#include <stdio.h>

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