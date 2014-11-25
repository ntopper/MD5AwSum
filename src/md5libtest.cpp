#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "headers/md5lib.h"

#define PATH1 "/tmp/.testfile"
#define PATH2 "/tmp/.emptyfile"
#define PATH3 "/tmp/.THISISATEMPORARYFILE"

int main(int argc, char *argv[]) {
	string hash;

	cout << "testing: " << PATH1 << endl;
	clock_t start1 = clock();
	md5lib test1(PATH1);
	clock_t stop1 = clock();
	cout << "the result is:\t[" << test1.get() << "] in " << float(stop1 - start1) / CLOCKS_PER_SEC << "s" << endl;
	clock_t start2 = clock();
	hash = md5lib::hash(PATH1);
	clock_t stop2 = clock();
	cout << "  compared to:\t[" << hash << "] in " << float(stop2 - start2) / CLOCKS_PER_SEC << "s" << endl;
	
	cout << "\ntesting: " << PATH2 << endl;
	clock_t start3 = clock();
	md5lib test2(PATH2);
	clock_t stop3 = clock();
	cout << "the result is:\t[" << test2.get() << "] in " << float(stop3 - start3) / CLOCKS_PER_SEC << "s" << endl;
	clock_t start4 = clock();
	hash = md5lib::hash(PATH2);
	clock_t stop4 = clock();
	cout << "  compared to:\t[" << hash << "] in " << float(stop4 - start4) / CLOCKS_PER_SEC << "s" << endl;

	cout << "\nFinal Test Phase..." << endl;
	srand(time(0));
	for(int i = 0; i < 1000; i++) {
		char buff[52];
		memset(buff,0,52);
		for(int j = 0; j < 50; j++) {
			buff[j] = (char)(rand()%77 + 48);
		}
		
		ofstream f(PATH3);
		f << buff;
		f.close();

		string a1 = md5lib::hash(PATH3);
		string a2 = md5lib(PATH3).get();

		printf("\r#%03d",i);
		if (strcmp(a1.c_str(),a2.c_str())) cerr << " [FAILED] " << buff << endl;
	}
	cout << endl;
	return 0;
}