#include <iostream>
#include <string>

using namespace std;

class Md5Hash {
	private:
		string file_path;
		string checksum;

		void handleString(string) throw(int);
		void cleanupString() throw(int);
	public:
		Md5Hash(string,bool = false);
		string getChecksum();
};
