
#include <fstream>
#include "parser/ophandlers.h"

int main(int argc, char **argv)
{
	if (argc<2) {
		fprintf(stderr,"Error: no input file given\n");
		return 1;
	}
	std::fstream infile(argv[1],std::ios::in);
	std::string buf;
	operation *op;
	while (!infile.eof()) {
		getline(infile,buf);
		strip_comments(buf);
		strip_trailing_whitespace(buf);
		if (!buf.empty()) {
			printf("%s\n",buf.c_str());
			op = assembly_to_op(buf);
			if (op) {
				binaryprint(op->instruction(),false);
				delete op;
			}
		}
	}
	infile.close();
	return 0;
}
