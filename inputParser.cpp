#define LOOKUP 0 
#define ADD 1
#define REMOVE 2
#define UPDATE 3
#define HELP 4
#define BAD_INPUT 5
#include<iostream>
#include <cstring>
using namespace std;

class inputParser{
public:
	static int parseInput(int argc, char* argv[]){
	if(strcmp(argv[0], "--lookup") || strcmp(argv[0], "-l")) {
		if(argc != 3){
		return BAD_INPUT;
		}			
		return ADD;
	}
	if(strcmp(argv[0], "--add") || strcmp(argv[0], "-a")) {
		if(argc != 3){
		return BAD_INPUT;
		}			
		return ADD;
	}
	if(strcmp(argv[0], "--remove") || strcmp(argv[0], "-r")){
		if(argc != 3){
		return BAD_INPUT;
		}
		return REMOVE;
	}
	if(strcmp(argv[0], "--update") ||strcmp(argv[0], "-u")){
		if(argc != 3){
		return BAD_INPUT;
		}
		return UPDATE;
	}
	if(strcmp(argv[0], "--help") ||strcmp(argv[0], "-h")){
		if(argc != 3){
		return BAD_INPUT;
		}
		return HELP;
	}
	return BAD_INPUT;
	}
};


  

