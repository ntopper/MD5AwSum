#ifndef MD5LIB_H
#define MD5LIB_H

#include <string>
#include "RainbowTable.h"

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
