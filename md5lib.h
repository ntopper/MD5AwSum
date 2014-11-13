#include <string>
using namespace std;

class md5lib {
	private:
		string file_path;
		string result;
		int s[64] = {7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,15,21,6,10,15,21,6,10,15,21};
		int K[64];
		int a0, b0, c0, d0;

		void initialize();
		void preprocess();
		int leftrotate(int,int);
		void digest(string);
		void finalize();
	public:
		static string hash(string) throw(int);

		md5lib(string);
		string get();
};