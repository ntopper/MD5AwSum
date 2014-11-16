#include <iostream>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "md5lib.h"

#define PATH1 "/tmp/.testfile"
#define PATH2 "/tmp/.emptyfile"

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
	return 0;
}