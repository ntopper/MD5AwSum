#ifndef MD5LIB_H
#define MD5LIB_H

#include <string>
using namespace std;

class RepositoryManager {
	public:
		RainbowTable master;
		RepositoryManager();
		void add(string url);
		void remove(string url);
		void update(string url);
		
	private:
		
};

#endif