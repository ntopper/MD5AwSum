#include <iostream>
#include <cstring>

using namespace std;

#define LOOKUP 0 
#define ADD 1
#define REMOVE 2
#define UPDATE 3
#define HELP 4
#define BAD_INPUT 5

/*
 * argv[0] is the name of the program
 * we want argv[1] assuming this is argv directly
 * from main. Will HELP and BAD_INPUT be the same
 * in the end because they result in printing the 
 * usage text? are we going to implement the usage 
 * text in this class? things to consider
 */

class inputParser{
	public:
		static int parseInput(int argc, char* argv[]){
			if(strcmp(argv[1], "--lookup") || strcmp(argv[1], "-l")) {
				if(argc != 3) return BAD_INPUT;			
				return LOOKUP;
			} else if(strcmp(argv[1], "--add") || strcmp(argv[1], "-a")) {
				if(argc != 3) return BAD_INPUT;			
				return ADD;
			} else if(strcmp(argv[1], "--remove") || strcmp(argv[1], "-r")){
				if(argc != 3) return BAD_INPUT;
				return REMOVE;
			} else if(strcmp(argv[1], "--update") || strcmp(argv[1], "-u")){
				if(argc != 3) return BAD_INPUT;
				return UPDATE;
			} else if(strcmp(argv[1], "--help") || strcmp(argv[1], "-h")){
				if(argc != 3) return BAD_INPUT;
				return HELP;
			} else return BAD_INPUT;
		}
};


  

