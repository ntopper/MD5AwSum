#include <string>
#include <stdint.h>
using namespace std;

class md5lib {
	private:
		string file_path;
		string result;
		unsigned char padd[64];
		uint32_t s[64] = {7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21};
		uint32_t K[64];
		uint32_t a0, b0, c0, d0;

		void initialize();
		void process();
		uint32_t leftrotate(uint32_t,uint32_t);
		void digest(uint32_t*);
		void finalize();
	public:
		static string hash(string) throw(int);

		md5lib(string);
		string get();
};