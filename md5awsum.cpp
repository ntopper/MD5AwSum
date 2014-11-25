#include <iostream>
#include <string>
#include "md5awsum.h"
#include "RainbowTable.h"
#include "src/headers/Md5Hash.h"
#include "inputParser.cpp"
#include "RepositoryManager.h"

using namespace std;

//please use the included header file :)

int main (int argc, char* argv[]) {
	md5awsum prog;
	string hashOrUrl = 0;
	switch(inputParser::parseInput(argc, argv)) {		//depending on what parseInput returns...(0,1,2,3,4, or 5)
		case 0:
			//parseInput returns 0 if it parsed the argument "lookup"
			//so we do a lookup on the argument in argv[2], presumably the hash of the program
			hashOrUrl = argv[2];
			prog.lookup(hashOrUrl, false);
			break;
		case 1:
			//parseInput returns 1 if it parsed the argument "add"
			//so we add the url in argv[2], presumably the url of a new repository
			hashOrUrl = argv[2];
			prog.add(hashOrUrl);
			break;
		case 2:
			//parseInput returns 2 if it parsed the argument "remove"
			//so we remove the url in argv[2], presumably the url of an existing repository
			hashOrUrl = argv[2];
			prog.remove(hashOrUrl);
			break;
		case 3:
			//parseInput returns 3 if it parsed the argument "update"
			//so we update the url in argv[2], presumably the url of an existing repository
			hashOrUrl = argv[2];
			prog.remove(hashOrUrl);
			break;
		case 5:
			cerr << "Error bad input." << endl;
		case 4:
			//handles case 4 and 5
			//print help/readme
			inputParser::usage();
			break;
		case 6:
			//parseInput returns 6 if it parsed only one argument after the program name
			//so we do a lookup on the url in argv[1], presumably the filepath of the program name
			string filepath = argv[1];
			prog.lookup(filepath, true);
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
	
    //finds hash table location in config class singleton instance
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
	//wiki says config.initialize(). What do?
	RepositoryManager repoMan;
	repoMan.add(url);
}

void md5awsum::remove(string url){
	//wiki says config.initialize(). What do?
	RepositoryManager repoMan;
	repoMan.remove(url);
}

void md5awsum::update(string url){
	RepositoryManager repoMan;
	repoMan.update(url);
}

/*
 * THERE IS NO FUNCTION IN REPOSITORYMANAGER TO UPDATE ALL WTF MAN
void update(){
	RepositoryManager repoMan;
	repoMan.update(ALL);
}
*/
