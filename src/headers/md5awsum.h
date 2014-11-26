#ifndef MD5AWSUM_H
#define MD5AWSUM_H

#include <string>
using namespace std;

class md5awsum {
	public:
		void lookup(string, bool);
		void add(string);
		void remove(string);
		void update(string);
		void update();
		void searchTable(string);
		void download(string);
};

#endif
