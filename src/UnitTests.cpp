#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "headers/RainbowTable.h"
#include "headers/RepositoryManager.h"
#include "headers/Md5Hash.h"

using namespace std;

int main(int argc, char* argv[]) {

	cout << "removing local repository" << endl;
	system("rm -r ~/.md5awsum");

	RepositoryManager man;

	//Add Hashes
	cout << "Adding ubuntu hashes" << endl;
	try {man.add("http://md5awsumdev.appspot.com/ubuntu");}
	catch (int e) {
		if(e == RainbowTable::ERROR_READING_FILE)
			{cout << "error adding remote repository (ubuntu)" <<endl;}
	}

	cout << "Adding 'foo/bar' hashes" << endl;
	try {man.add("http://md5awsumdev.appspot.com/testrepo");}
	catch (int e) {
		if(e == RainbowTable::ERROR_READING_FILE)
			{cout << "error adding remote repository (foo/bar)" <<endl;}
	}

	//check if hashes were added
	cout << "Contents of ~/.md5awsum/hashes.xml" << endl;
	system("cat ~/.md5awsum/hashes.xml");

	cout << "*********************************" << endl;

	//remove ubuntu hashes
	cout << "Removing ubuntu hashes" << endl;
	try {man.remove("http://md5awsumdev.appspot.com/ubuntu");}
	catch (int e) {
		if(e == RainbowTable::ERROR_READING_FILE)
			{cout << "error reading local repository" <<endl;}
	}

	cout << "Contents of ~/.md5awsum/hashes.xml" << endl;
	system("cat ~/.md5awsum/hashes.xml");

	//add ubuntu hashes
	cout << "adding ubuntu hashes" << endl;
	try {man.add("http://md5awsumdev.appspot.com/ubuntu");}
	catch (int e) {
		if(e == RainbowTable::ERROR_READING_FILE)
			{cout << "error adding remote repository (ubuntu)" <<endl;}
	}

	cout << "updating ubuntu hashes" << endl;
	try {man.update("http://md5awsumdev.appspot.com/ubuntu");}
	catch (int e) {
		if(e == RainbowTable::ERROR_READING_FILE)
			{cout << "error adding remote repository (ubuntu)" <<endl;}
	}

	cout << "*********************************" << endl;

	//calculate a checksum
	string file = argv[1];
	cout << "calculating checksum of "  << file << endl;
	string checksum;
	try {Md5Hash hash(file); checksum = hash.getChecksum();}
	catch (int e) {
			{cout << "error hashing file" <<endl;}
	}
	cout << "checksum: " << checksum << endl;

	//creating rainbow table instance
	RainbowTable table;
	try {
		table.parse();
	}
	catch(int e) {
		if(e == RainbowTable::ERROR_READING_FILE)
			{cout << "error parsing local repository" << endl;}
	}

	cout << "searching repository" << endl;
	table.search(checksum);

	cout << "updating all" << endl;

	man.update();
}
