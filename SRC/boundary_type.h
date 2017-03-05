#ifndef BOUNDARY_TYPE_H
#define BOUNDARY_TYPE_H
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <streambuf>
#include "string_operator.h"


using namespace std;
class boundary_type
{
	public:
		boundary_type();
		~boundary_type();
		boundary_type(const string& str);
		string generateBC();
		string get_string();
	private:
		string s;
};
#endif