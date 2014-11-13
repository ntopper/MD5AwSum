#include <iostream>
#include "md5lib.h"

#define PATH "/tmp/.testfile"

int main(int argc, char *argv[]) {
	cout << "testing: " << PATH << endl;
	md5lib test(PATH);
	cout << "the result is:\t[" << test.get() << "]" << endl;
	cout << "  compared to:\t[" << md5lib::hash(PATH) << "]" << endl;
	return 0;
}