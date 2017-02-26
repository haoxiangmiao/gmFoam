#ifndef STRING_OPERATOR_H
#define STRING_OPERATOR_H
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <streambuf>

using namespace std;
class string_operator
{
	public:
		string_operator();
		~string_operator();
		string_operator(const string& str);
		std::vector<string> string_extractor(string& s1, string opening_flag, string closing_flag);
		string delete_space(string& s2);
		string get_string_component(string::iterator it);
		string get_string();
		std::regex_iterator<std::string::iterator> search_reg(std::regex e);
		void replace_reg(std::regex e, string& replace_str);
		void readfile2string(string Dir);
	private:
		string s;

};
#endif