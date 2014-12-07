#include "headers/md5awsum.h"
#include "input_parser.cpp"

int main(int argc, char *argv[]) {
	md5awsum prog;
	inputParser parser(argc,argv,prog);
	parser.analyze();
	return 0;
}
