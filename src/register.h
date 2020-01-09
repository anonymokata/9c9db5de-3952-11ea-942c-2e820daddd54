#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class Register {
private:
	unordered_map<string, int> quantity;
public:
	inline int getQuantity(string s) { return 0; }
	void scanItem(string);

};

#endif
