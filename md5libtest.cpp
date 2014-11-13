#include <iostream>
#include "md5lib.h"

#define PATH1 "/tmp/.testfile"
#define PATH2 "/home/mark/dmesg-1739-10142014.txt"

int main(int argc, char *argv[]) {
	cout << "testing: " << PATH1 << endl;
	md5lib test1(PATH1);
	cout << "the result is:\t[" << test1.get() << "]" << endl;
	cout << "  compared to:\t[" << md5lib::hash(PATH1) << "]" << endl;
	cout << "\ntesting: " << PATH2 << endl;
	md5lib test2(PATH2);
	cout << "the result is:\t[" << test2.get() << "]" << endl;
	cout << "  compared to:\t[" << md5lib::hash(PATH2) << "]" << endl;
	return 0;
}