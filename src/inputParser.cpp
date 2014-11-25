#include <iostream>
#include <cstring>

using namespace std;

#define LOOKUP 0 
#define ADD 1
#define REMOVE 2
#define UPDATE 3
#define HELP 4
#define CHECKSUM 5

class inputParser{
	public:
		static int parseInput(int argc, char* argv[]){

			//not enough arguments, return help
			if(argc < 2) return HELP;
		
			//lookup flag, return LOOKUP if 3 arguments given
			if(!strcmp(argv[1], "--lookup") || !strcmp(argv[1], "-l")) {
				if(argc != 3) return HELP;			
				return LOOKUP;
			} 
			
			//add flag, return ADD if 3 arguments given
			else if(!strcmp(argv[1], "--add") || !strcmp(argv[1], "-a")) {
				
				if(argc != 3) return HELP;			
				return ADD;
			} 
			
			//remove flag, return REMOVE if 3 arguments given
			else if(!strcmp(argv[1], "--remove") || !strcmp(argv[1], "-r")){
				if(argc != 3) return HELP;
				return REMOVE;
			} 
			
			//update flag, return UPDATE if less than 4 arguments given
			else if(!strcmp(argv[1], "--update") || !strcmp(argv[1], "-u")){
				if(argc > 3) return HELP;
				return UPDATE;
			} 
			
			//two arguments and no flags, the given argument must be a filepath
			else if (argc == 2){
				return CHECKSUM;
			} 
			
			//default instruction to print usage
			else return HELP;
		}

		static void usage() {
			cout << " __  __ ____  ____    _            ____                  " << endl;
			cout << "|  \\/  |  _ \\| ___|  / \\__      __/ ___| _   _ _ __ ___  " << endl;
			cout << "| |\\/| | | | |___ \\ / _ \\ \\ /\\ / /\\___ \\| | | | '_ ` _ \\ " << endl;
			cout << "| |  | | |_| |___) / ___ \\ V  V /  ___) | |_| | | | | | |" << endl;
			cout << "|_|  |_|____/|____/_/   \\_\\_/\\_/  |____/ \\__,_|_| |_| |_|" << endl;
			cout << endl;
			cout << "Usage: MD5AwSum [options]" << endl;
			cout << "\nOptions: " << endl;
			cout << "\t-h, --help\t\tshow this information" << endl;
			cout << "\t-v, --verbose\t\tverbose output (default quiet)" << endl;
			//modify the following to be correct and more helpful
			cout << "\t-l, --lookup\t\tlookup text" << endl;
			cout << "\t-a, --add\t\tadd text" << endl;
			cout << "\t-r, --remove\t\tremove text" << endl;
			cout << "\t-u, --update\t\tupdate text" << endl;
		}
};



  

