
/********************************************************************************************************
* File:              gmFoamTranslator.cpp                                              
* Author:            Hexiang                                     | Boris Jeremic,                       *
* Date:              2017-02-04 20:25:37                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-02-04 20:27:34                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include "gmFoamTranslator.h"
#include "string_operator.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <regex>
#include <functional>
#include <map>
#include "gmfoam_namespace.h"
#include <fstream>
#include <streambuf>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;


using namespace gmfoam_ns;


gmFoamTranslator::gmFoamTranslator(){}
gmFoamTranslator::gmFoamTranslator(const string& input_command)
{
	this->input_string=input_command;

}  

gmFoamTranslator::~gmFoamTranslator(){}

void gmFoamTranslator::set_command()
{
	string_operator so=string_operator(input_string);
	vector<string> vs=so.string_extractor(input_string,"<",">");
	vector<string>::size_type sz=vs.size();
	if(sz>1)
	{
		cout<<"Syntax error:command by command, please!"<<endl;
		exit(EXIT_FAILURE);
	}

	this->command=vs[0];
}
void gmFoamTranslator::set_keyword()
{
	string_operator so=string_operator(input_string);
	this->keyword=so.string_extractor(input_string,"[","]");	
}
void gmFoamTranslator::set_parameter()
{
	string_operator so=string_operator(input_string);
	this->parameter=so.string_extractor(input_string,"{","}");
}

string gmFoamTranslator::get_command()
{
	string ret=this->command;
	return ret;
}

vector<string> gmFoamTranslator::get_keyword()
{
	std::vector<string> ret=this->keyword;
	return ret;
}

vector<string> gmFoamTranslator::get_parameter()
{
	vector<string> ret=this->parameter;
	return ret;
}

// ###################Note this function should be dynamically updated when new commands added. To build the mapping between string command and member function pointer.

void gmFoamTranslator::set_funcMap()
{
	this->funcMap["load_mesh"]=&gmFoamTranslator::load_mesh;
	this->funcMap["define_transportProperties"]=&gmFoamTranslator::define_transportProperties;
	this->funcMap["define_boundaryGeometry"]=&gmFoamTranslator::define_boundaryGeometry;
	// this->funcMap["set_boundary_condition_U"]=&gmFoamTranslator::set_boundary_condition_U;
}
// ##################################################################################################################################################### 


void gmFoamTranslator::set_all()
{
	set_command();
	set_keyword();
	set_parameter();
	set_funcMap();
}

std::map<std::string,  void (gmFoamTranslator::* )()> gmFoamTranslator::get_map()
{
	return this->funcMap;
}

void gmFoamTranslator::load_mesh()
{
	extern string project_name;
	string temp_str=(this->parameter)[0];            //note the calling of components here, first () then []
	string_operator so=string_operator((this->parameter)[0]);
	string::iterator it=temp_str.begin();
	for(; it!=temp_str.end(); ++it)
	{
		if(so.get_string_component(it)!=".")
			project_name=project_name+so.get_string_component(it);
		else break;
	}
	string SPACE=" ";
	string bash_call_string="gmsh_conversion"+SPACE+project_name;
	system(bash_call_string.c_str());
}

void gmFoamTranslator::define_transportProperties()   
{
	extern string project_name;
	string s= project_name;
	string Dir=getFilePath();
	Dir=Dir+"/"+s+"/constant/transportProperties";
	std::ifstream input(Dir);
	if (!input) 
		std::cerr << "Could not open the file!" << std::endl;
	else
	{
		string temp_s;
		input.seekg(0, std::ios::end);
		temp_s.reserve(input.tellg()); 
		input.seekg(0, std::ios::beg);
		temp_s.assign((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
		if((this->parameter).size()!=3)
			std::cerr << "lack parameters in define_transportProperties" << std::endl;
		else
		{
			string unit="";
			string continuous_unit=(this->parameter)[1];
			for(string::iterator it=continuous_unit.begin(); it<continuous_unit.end(); ++it)
				unit=unit+(*it)+" ";
			temp_s=temp_s+(this->parameter)[0]+"      ["+unit+"] "+(this->parameter)[2]+";\n";
			std::ofstream out(Dir);
			out<<temp_s;
			out.close();
		}
	
	};
}

void gmFoamTranslator::define_boundaryGeometry()
{
	extern string project_name;
	string s= project_name;
	string Dir=getFilePath();
	Dir=Dir+"/"+s+"/constant/polyMesh/boundary";
	std::ifstream input(Dir);
	if (!input) 
		std::cerr << "Could not open the file!" << std::endl;
	else
	{
		string temp_s;
		input.seekg(0, std::ios::end);
		temp_s.reserve(input.tellg()); 
		input.seekg(0, std::ios::beg);
		temp_s.assign((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
		string_operator so=string_operator(temp_s);
		for(int i=0; i<(this->keyword).size(); ++i)
		{
			// std::regex e ("<[A-Za-z0-9_\"\\.\\s]+>[\\s]*(\\[[A-Za-z0-9_\"\\.\\s]+\\][\\s]*\\{[A-Za-z0-9_\"\\.\\s]+\\})*");
			string replace_str="";
			string keyword_i=(this->keyword)[i];
			string reg_string=keyword_i+"\n[\\s]*\\{[\\s]*\n[\\s]*type[\\s]*"+"patch;"+"\n[\\s]*"+"physicalType[\\s]*patch;";
			std::regex e (reg_string);
			replace_str=keyword_i+"\n    {\n        type            "+(this->parameter)[i]+";\n        inGroups     1("+(this->parameter)[i]+");";
			so.replace_reg(e,replace_str);
		}
		temp_s=so.get_string();
		std::ofstream out(Dir);
		out<<temp_s;
		out.close();
	};
}

void gmFoamTranslator::execute_command()
{
	(this->*(this->funcMap[this->command]))();   
}

// ###########this function can be used to return current running directory as string#######################
string gmFoamTranslator::getFilePath()
{
	char filePath[256];	
	if(!GetCurrentDir(filePath, sizeof(filePath)))
	{

		cout<<"** ERROR - Something went wrong, exiting...\n";
	}
	
	string FilePath(filePath);
	return FilePath;
}

// void gmFoamTranslator::set_boundary_condition_U()
// {
// 	extern string project_name;
// 	string s= project_name;
// 	string Dir=getFilePath();
// 	Dir=Dir+"/"+s+"//";
// }
//###########################################################################################################