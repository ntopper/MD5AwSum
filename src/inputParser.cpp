#include "headers/md5awsum.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

#define LOOKUP 0 
#define ADD 1
#define REMOVE 2
#define UPDATE 3
#define HELP 4
#define CHECKSUM 5
#define DOWNLOAD 6
#define SOURCES 7
#define QUIET 8
#define ADDFROMFILE 9
#define ENTRY 10
#define GENERATE 11

class inputParser{
	public:
		int mainFlag = 0;
		vector<int> subFlag;
		vector<string> params;
		md5awsum prog;

		inputParser(int argc, char* argv[], md5awsum p) {
			prog = p;
			if(argc < 2) mainFlag = HELP;
			else if(argc == 2) mainFlag = CHECKSUM;
			for(int i = 1; i < argc; i++) {
				parseInput(argv[i]);
			}
		}

		void parseInput(char *input){

			//MAINFLAGS
			//lookup flag, return LOOKUP if 3 arguments given
			if(!strcmp(input, "--lookup") || !strcmp(input, "-l")) {
				if(mainFlag != 0) mainFlag = HELP;			
				mainFlag = LOOKUP;
			} 
			
			//add flag, return ADD if 3 arguments given
			else if(!strcmp(input, "--add") || !strcmp(input, "-a")) {
				if(mainFlag != 0) mainFlag = HELP;				
				mainFlag = ADD;
			} 
			
			//remove flag, return REMOVE if 3 arguments given
			else if(!strcmp(input, "--remove") || !strcmp(input, "-r")) {
				if(mainFlag != 0) mainFlag = HELP;	
				mainFlag = REMOVE;
			} 
			
			//update flag, return UPDATE if less than 4 arguments given
			else if(!strcmp(input, "--update") || !strcmp(input, "-u")) {
				if(mainFlag != 0) mainFlag = HELP;	
				mainFlag = UPDATE;
			}

			//download flag, return DOWNLOAD if 3 arguments are given
			else if(!strcmp(input, "--download") || !strcmp(input, "-d")) {
				if(mainFlag != 0) mainFlag = HELP;	
				mainFlag = DOWNLOAD;
			}

			//sources flag, returns SOURCES
			else if(!strcmp(input, "--sources") || !strcmp(input, "-s")) {
				if(mainFlag != 0) mainFlag = HELP;	
				mainFlag = SOURCES;
			}

			//addfromfile flag, returns ADDFROMFILE
			else if(!strcmp(input, "--add-from-file") || !strcmp(input, "-aff")) {
				if(mainFlag != 0) mainFlag = HELP;
				mainFlag = ADDFROMFILE;
			}

			else if(!strcmp(input, "--entry") || !strcmp(input, "-e")) {
				if(mainFlag != 0) mainFlag = HELP;
				mainFlag = ENTRY;
			}

			else if(!strcmp(input, "--generate") || !strcmp(input, "-g")) {
				if(mainFlag != 0) mainFlag = HELP;
				mainFlag = GENERATE;
			}
			
			//SUBFLAGS
			//quiet flag, adds to subFlag
			else if(!strcmp(input, "--quiet") || !strcmp(input, "-q")) {
				subFlag.push_back(QUIET);
			}

			//PARAMETERS
			else params.push_back(input);
		}

		void analyze() {
			string argument_string;

			head();

			switch(mainFlag) {
				case LOOKUP: //reverse lookup from given hash string
					if(!params.size()) usage();
					else {
						argument_string = params.front();
						prog.lookup(argument_string, false);
					}
					break;
					
				case ADD: //add a repository given a url
					if(!params.size()) usage();
					else {
						argument_string = params.front();
						prog.add(argument_string);
					}
					break;
					
				case REMOVE: //remove a repository given a url
					if(!params.size()) usage();
					else {
						argument_string = params.front();
						prog.remove(argument_string);
					}
					break;
					
				case UPDATE: //update one (given a url) or all of the stored repositories
					//if no url argument is given, update all
					if (!params.size()) { prog.update(); }
					
					//otherwize update the given URL
					else {
						argument_string = params.front();
						prog.update(argument_string);
					}
					break;
				
				case DOWNLOAD:
					if(!params.size()) usage();
					else {
						argument_string = params.front();
						prog.download(argument_string);
					}
					break;

				case CHECKSUM://hash file at a given filepath and lookup the resulting cecksum
					argument_string = params.front();
					prog.lookup(argument_string, true);
					break;

				case SOURCES: //search for all entires labeld as "repository"
					argument_string = "repository";
					prog.lookup(argument_string, false);
					break;

				case ADDFROMFILE:
					if(!params.size()) usage();
					else {
						argument_string = params.front();
						prog.addFromFile(argument_string);
					}
					break;

				case ENTRY:
					if(!params.size()) usage();
					if((!subFlag.size() || subFlag.front() == QUIET) && params.size() == 1) {
						argument_string = params.front();
						prog.addEntry(argument_string);
					} else {
						argument_string = params[0];
						string hash = params[1];
						prog.addEntry(argument_string, hash);
					}
					break;
					
				case GENERATE: {
					//determine directory
					if(!params.size()) {
						argument_string = "./"; //current dir
					} else {
						argument_string = params.front();
					}

					//variables
					vector<string> files;
					getDir(argument_string, files);

					//pass to add entry
					printf("Found %d files!\n",(int)files.size());
					for(unsigned int i = 0; i < files.size(); i++) {
						cout << "-> " << files[i] << endl;
						prog.addEntry(files[i]);
					}
					break;
				}

				case HELP:
					usage();
					break;
			}
		}

		static void getDir(string directory, vector<string> &files) {
			DIR *d;
			struct dirent *df;
			struct stat ds;

			if((d = opendir(directory.c_str())) != NULL) {
				while((df = readdir(d)) != NULL) {
					//ignore directories
					if(df->d_name[0] == '.') continue;
					if(directory.back() != '/') directory += "/";
					stat((directory + string(df->d_name)).c_str(), &ds);
					if(S_ISDIR(ds.st_mode)) continue;

					//push to files
					files.push_back(directory + string(df->d_name));
				}
			}

			closedir(d);
		}

		static void head() {
			cout << " __  __ ____  ____    _            ____                  " << endl;
			cout << "|  \\/  |  _ \\| ___|  / \\__      __/ ___| _   _ _ __ ___  " << endl;
			cout << "| |\\/| | | | |___ \\ / _ \\ \\ /\\ / /\\___ \\| | | | '_ ` _ \\ " << endl;
			cout << "| |  | | |_| |___) / ___ \\ V  V /  ___) | |_| | | | | | |" << endl;
			cout << "|_|  |_|____/|____/_/   \\_\\_/\\_/  |____/ \\__,_|_| |_| |_|" << endl;
			cout << endl;
		}

		static void usage() {
			cout << "Usage: MD5AwSum [options] <input>" << endl;
			cout << "\nOptions: " << endl;
			cout << "\t-h, --help\t\tshow this information" << endl;
			//cout << "\t-q, --quiet\t\tsupress output (default verbose)" << endl;
			//modify the following to be correct and more helpful
			cout << "\t-l, --lookup\t\tlookup the given hash" << endl;
			cout << "\t-a, --add\t\tadd the given url to the local table" << endl;
			cout << "\t-r, --remove\t\tremove the given url from the local table" << endl;
			cout << "\t-s, --sources\t\tshow repositories that are locally stored" << endl;
			cout << "\t-d, --download\t\tdownload the given url and lookup" << endl;
			cout << "\t-u, --update\t\tupdate the local table, updates\n\t\t\t\tall urls if it is not specified" << endl;
			cout << "\t-aff, --add-from-file\treads a file where each line is a url\n\t\t\t\teach url is added to the table" << endl;
			cout << "\t-e, --entry\t\twill read the file, hash and add to local\n\t\t\t\trepo or will take the given name and\n\t\t\t\thash and add it to the local repo" << endl;
			cout << "\t-g, --generate\t\tgiven a directory will hash and store\n\t\t\t\tall files in that directory, defaults\n\t\t\t\tto current directory if not given." << endl;
		}


};



  

