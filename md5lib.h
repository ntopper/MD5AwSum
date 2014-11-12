#include <string>
using namespace std;

class md5lib {
	private:
		int[64] s;
		int[64] K;
		int a0, b0, c0, d0;

	public:
		static string hash(string) throw(int);
		static void initialize();
		static void preprocessing(); // these will be modified either to be not static
		static void digest(); // or to take in parameters
		static void finalize(); // should probably be instantiation but idk
};