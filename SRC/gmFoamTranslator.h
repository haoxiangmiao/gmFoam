/********************************************************************************************************
* File:              gmFoamTranslator.h                                              
* Author:            Hexiang                                     | Boris Jeremic,                       *
* Date:              2017-02-04 20:15:35                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-03-10 00:22:52                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
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
#include "boundary_type.h"

using namespace::std;
// using namespace gmfoam_ns;


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
		void load_fluid_mesh();
		void define_transportProperties();
		void define_boundaryGeometry();
		void execute_command();
		void set_system();
		void set_boundary_condition();
		string getFilePath();
		void add_fluid_phase();
		void define_model_name();
		void add_solid_phase();
		void bug_information(int FLAG);


	private:
		string command;
		std::vector<string> keyword;
		std::vector<string> parameter;	
		string input_string;
		std::map<std::string, void (gmFoamTranslator::* )()> funcMap;


};

#endif