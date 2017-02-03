#ifndef STRING_OPERATOR_H
#define STRING_OPERATOR_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class string_operator
{
	public:
		string_operator();
		~string_operator();
		string_operator(const string& str);
		string get_command();

	private:
		string s;

};
#endif