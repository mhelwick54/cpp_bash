#include "../include/funcs.h"

std::string tokenizer(std::string::iterator prev, std::string* str, std::string delims) {
	auto tok_end = str->end(), temp = prev;
	for(auto delim : delims) {
		temp = prev;
		while(temp != str->end()) {
			if(*temp == delim && temp < tok_end) {
				tok_end = temp;
				break;
			}
			++temp;
		}
	}
	if(tok_end == str->end()) {
		return std::string(prev, tok_end);
	}
	return std::string(prev, tok_end);
}


void test() {
	std::string str = "this-is/a;tests-";
	std::string delims = "-/;";
	std::string ret = "begin";
	auto it = str.begin();
	while(it != str.end()) {
		ret = tokenizer(it, &str, delims);
		it += ret.length() + 1;
		debug(ret);
	}
}
