#include <iostream>
#include <string.h>
#include <stdint.h>
#include "md5lib.h"

#define PATH1 "/tmp/.testfile"
#define PATH2 "/tmp/.emptyfile"

void hexdump1(unsigned char* buff) {
	cout << endl;
	for(unsigned int i = 0; i < 64; i++) {
		printf("0x%2.2x\t", buff[i]);
		if (!((i+1)%8)) printf("\n");
	}
	cout << endl;
}

int main(int argc, char *argv[]) {
	cout << "testing: " << PATH1 << endl;
	md5lib test1(PATH1);
	cout << "the result is:\t[" << test1.get() << "]" << endl;
	cout << "  compared to:\t[" << md5lib::hash(PATH1) << "]" << endl;
	cout << "\ntesting: " << PATH2 << endl;
	md5lib test2(PATH2);
	cout << "the result is:\t[" << test2.get() << "]" << endl;
	cout << "  compared to:\t[" << md5lib::hash(PATH2) << "]" << endl;

	//this works for filling buff with 0x00 but idk why not for md5lib
	uint8_t buff[64];
	memset(buff,0,63);
	return 0;
}