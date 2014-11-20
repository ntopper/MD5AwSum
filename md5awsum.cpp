#include <iostream>
#include "RainbowTable.h"
#include "Md5Hash.h"
#include <string>
#include "inputParser.cpp"
#include "RepositoryManager.h"

void lookup(string, bool);
void add(string);
void remove(string);
void update(string);
void searchTable(string);


using namespace std;
int main (int argc, char* argv[]){
		inputParser parser;							//instance of inputParser
		switch(parser.parseInput(argc, argv)){		//depending on what parseInput returns...(0,1,2,3,4, or 5)
			case 0:{
				//parseInput returns 0 if it parsed the argument "lookup"
				//so we do a lookup on the argument in argv[2], presumably the hash of the program
				string hash = argv[2];
				lookup(hash, false);
				break;
			}
			
			case 1:{ 
				//parseInput returns 1 if it parsed the argument "add"
				//so we add the url in argv[2], presumably the url of a new repository
				string url = argv[2];
				add(url);
				break;}
			
			case 2:{ 
				//parseInput returns 2 if it parsed the argument "remove"
				//so we remove the url in argv[2], presumably the url of an existing repository
				string url = argv[2];
				remove(url);
				break;}
					
			case 3:{ 
				//parseInput returns 3 if it parsed the argument "update"
				//so we update the url in argv[2], presumably the url of an existing repository
				string url = argv[2];
				remove(url);
				break;}
					
				
			case 4:{
				//print help/readme
				break;}
				
			case 5:{
				//bad input
				cout<<"BAD INPUT"<<endl;
				//print help/readme
				break;}
			case 6:{
				//parseInput returns 6 if it parsed only one argument after the program name
				//so we do a lookup on the url in argv[1], presumably the filepath of the program name
				string filepath = argv[1];
				lookup(filepath, true);
				break;}
		}
		return 0;
}

void lookup(string inString, bool isFile){
	string hash;
	if (isFile){
		try{
		Md5Hash fHash = Md5Hash(inString);
        hash =  fHash.getChecksum();
        cout << "checksum: " << hash << endl;
		} catch (int e){
        cout<<"Error reading from file"<<endl;
       return;
		}
	 } else {hash = inString;}
	
    //finds hash table location in config class singleton instance
    searchTable(hash);
}

void searchTable(string hash){
	RainbowTable table;
	try{
		table.parse();
	}catch(int e){
			if(e == RainbowTable::ERROR_READING_FILE){
					cout<<"error parsing the repository"<<endl;
			}
	} 
	table.search(hash);
}

void add(string url){
	//wiki says config.initialize(). What do?
	RepositoryManager repoMan;
	repoMan.add(url);
}

void remove(string url){
	//wiki says config.initialize(). What do?
	RepositoryManager repoMan;
	repoMan.remove(url);
}

void update(string url){
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
