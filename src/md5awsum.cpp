#include "headers/md5awsum.h"
#include "headers/RainbowTable.h"
#include "headers/Md5Hash.h"
#include "headers/RepositoryManager.h"
#include "inputParser.cpp"
#include <iostream>
#include <string>
#include <stdio.h>

#define LOOKUP 0 
#define ADD 1
#define REMOVE 2
#define UPDATE 3
#define HELP 4
#define CHECKSUM 5
#define DOWNLOAD 6

using namespace std;


int main (int argc, char* argv[]) {
	md5awsum prog;
	string argument_string;

	inputParser::head();
	
	//return value of parseInput determines what the user would like to do
	int choice = inputParser::parseInput(argc, argv);
	
	switch(choice) {
		case LOOKUP: //reverse lookup from given hash string
			argument_string = argv[2];
			prog.lookup(argument_string, false);
			break;
			
		case ADD: //add a repository given a url
			argument_string = argv[2];
			prog.add(argument_string);
			break;
			
		case REMOVE: //remove a repository given a url
			argument_string = argv[2];
			prog.remove(argument_string);
			break;
			
		case UPDATE: //update one (given a url) or all of the stored repositories

			//if no url argument is given, update all
			if (argc < 2) {prog.update();}
			
			//otherwize update the given URL
			else {
				argument_string = argv[2];
				prog.update(argument_string);
			}
			break;
		
		case DOWNLOAD:
			argument_string = argv[2];
			prog.download(argument_string);
			break;

		case CHECKSUM://hash file at a given filepath and lookup the resulting cecksum
			argument_string = argv[1];
			prog.lookup(argument_string, true);
			break;
			
		case HELP:
			inputParser::usage();
			break;
	}
	return 0;
}

void md5awsum::lookup(string inString, bool isFile){
	string hash;
	if (isFile) {
		try {
			Md5Hash fHash = Md5Hash(inString);
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
}

void md5awsum::download(string url){
	cout << "Download from -> " << url << endl;

	//download file
	string wget = "wget --content-disposition -nv " + url + " 2>&1";
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

void md5awsum::update(string url){
	RepositoryManager repoMan;
	repoMan.update(url);
}

void md5awsum::update() {
	RepositoryManager repoMan;
	repoMan.update();
}
