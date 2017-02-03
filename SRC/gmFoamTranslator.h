#ifndef GMFOAMTRANSLATOR_H
#define GMFOAMTRANSLATOR_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace::std;

class gmFoamtranslator{
	
	public:
		gmFoamtranslator();
		~gmFoamtranslator();
		gmFoamtranslator(const string& input_command);
		void load_mesh();
		void set_command(const string& str);
		void set_keyword(const std::vector<string>& str);
		void set_parameter(const std::vector<string>& str);

	private:
		string command;
		std::vector<string> keyword;
		std::vector<string> parameter;		


};

#endif