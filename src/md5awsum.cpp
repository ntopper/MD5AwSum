#include "headers/md5awsum.h"
#include "headers/rainbow_table.h"
#include "headers/md5hash.h"
#include "headers/RepositoryManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <libgen.h>


using namespace std;

void md5awsum::lookup(string inString, bool isFile){
	string hash;
	if (isFile) {
	
		//make sure the file exists
		ifstream infile(inString);
		if(!infile.good()) {
			cerr << inString << ": No such file or directory" << endl;
			return;
		}
		
		try {
			Md5Hash fHash(inString);
        	hash =  fHash.getChecksum();
        	cout << "checksum: " << hash << endl;
		} catch (int e){
        	cerr << "Error reading from file" << endl;
       		return;
		}
	 } else hash = inString;
	
    searchTable(hash);
}

void md5awsum::searchTable(string hash){
	RainbowTable table;
	try{
		table.parse();
	}catch(int e){
		if(e == RainbowTable::ERROR_READING_FILE){
			cerr << "error parsing the repository" << endl;
		}
	} 
	table.search(hash);
}

void md5awsum::add(string url){
	RepositoryManager repoMan;
	repoMan.add(url);
}

void md5awsum::remove(string url){
	RepositoryManager repoMan;
	repoMan.remove(url);
	cout << "Removed " << url << " from local table." << endl;
}

void md5awsum::download(string url){
	cout << "Download from -> " << url << endl;

	//download file
	string wget = "wget -nv " + url + " 2>&1";
	FILE *wgetOutput = popen(wget.c_str(), "r");
	if(!wgetOutput) throw "wget fail";

	//read in output
	char buff[256];
	fgets(buff, 255, wgetOutput);
	pclose(wgetOutput);

	//find filename
	string filename = string(buff);
	size_t found = filename.find("-> \"");
	filename.erase(0,found+4);
	found = filename.find("\" ");
	filename.erase(found);

	//pass to lookup
	cout << "Download complete -> " << filename << endl;
	lookup(filename, true);
}

void md5awsum::addFromFile(string filename) {
	ifstream f(filename);
	char url[256];

	while (true) {
		f.getline(url,256);
		if(f.fail()) break;
		add(url);
	}
	f.close();
}

void md5awsum::addEntry(string filename) {
	try{
		Md5Hash h(filename);
		string hash = h.getChecksum();

		string file = string(basename(&filename[0]));

		RepositoryManager repoMan;
		repoMan.addEntry(file, hash);
	} catch(exception e) {
		cerr << "Error reading from file." << endl;
		return;
	}
}

void md5awsum::addEntry(string name, string hash) {
	RepositoryManager repoMan;
	repoMan.addEntry(name,hash);
}

void md5awsum::update(string url){
	RepositoryManager repoMan;
	repoMan.update(url);
}

void md5awsum::update() {
	RepositoryManager repoMan;
	repoMan.update();
}
