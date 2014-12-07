#ifndef MD5LIB_H
#define MD5LIB_H

#include <string>
#include "rainbow_table.h"

using namespace std;

class RepositoryManager {
	public:
		RainbowTable master;
		RepositoryManager();
		void add(string url);
		void remove(string url);
		void update(string url);
		void update();
		void print();
		void addEntry(string,string);
	private:
		
};
#endif
