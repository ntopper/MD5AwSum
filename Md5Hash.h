#include <iostream>
#include <string>

using namespace std;

class Md5Hash {
	private:
		string file_path;
		string checksum;

	public:
		Md5Hash(string,bool = false);
		void Digest() throw(int);
		void handleString(string) throw(int);
		void cleanupString() throw(int);
		string getChecksum();
};
