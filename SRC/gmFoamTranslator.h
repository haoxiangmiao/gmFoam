#ifndef GMFOAMTRANSLATOR_H
#define GMFOAMTRANSLATOR_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <functional>
#include <map>
#include <regex>
#include "gmfoam_namespace.h"
#include <fstream>
#include <streambuf>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include "string_operator.h"

using namespace::std;
using namespace gmfoam_ns;


class gmFoamTranslator{
	
	public:
		gmFoamTranslator();
		~gmFoamTranslator();
		gmFoamTranslator(const string& input_command);
		void set_command();
		void set_keyword();
		void set_parameter();
		void set_all();
		void set_funcMap();
		string get_command();
		vector<string> get_keyword();
		vector<string> get_parameter();
		std::map<std::string, void (gmFoamTranslator::* )()> get_map();
		void load_mesh();
		void define_transportProperties();
		void define_boundaryGeometry();
		void execute_command();
		string getFilePath();
		void set_boundary_condition_U();



	private:
		string command;
		std::vector<string> keyword;
		std::vector<string> parameter;	
		string input_string;
		std::map<std::string, void (gmFoamTranslator::* )()> funcMap;


};

#endif