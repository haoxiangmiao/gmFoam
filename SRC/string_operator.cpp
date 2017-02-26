/********************************************************************************************************
* File:              string_operator.cpp                                              
* Author:            Hexiang                                     | Boris Jeremic,                       *
* Date:              2017-02-04 20:16:04                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-02-04 20:27:17                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include "string_operator.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>
#include <streambuf>
using namespace std;

string_operator::string_operator(){}
string_operator::string_operator(const string& str):s{str} {}
string_operator::~string_operator(){}

// this is for no nested openning flag and closing flag
vector<string> string_operator::string_extractor(string& s1, string opening_flag, string closing_flag)
{
	int index=0;
	vector<string> ret;
	string::iterator it=s1.begin();
	string::iterator opening_flag_it=s1.end();
	string temp_string;
	for (; it!=s1.end(); ++it)
	{
	// convert a char to string
		// stringstream ss;
		// string temp;
		// ss<<(*it);
		// ss>>temp;	
		string temp=get_string_component(it);
	//####################### 
		if(temp==opening_flag)
		{
			index=index+1;
			opening_flag_it=it;
			
		}
		if((it>opening_flag_it)&&(temp!=closing_flag))
		{
			temp_string=temp_string+temp;

		}
		if(temp==closing_flag)
		{
			temp_string=delete_space(temp_string);    // this line means our extraction output without spaces.
			ret.push_back(temp_string);
			temp_string="";
			opening_flag_it=s1.end();
		}
	}

	return ret;
}

string string_operator::delete_space(string& s2)
{
	string ret;
	string::iterator it=s2.begin();
	for(; it<s2.end(); ++it)
	{
		string temp=get_string_component(it);
		if(temp!=" ")
			ret=ret+temp;
	}
	return ret;

}

string string_operator::get_string_component(string::iterator it)
{
	string ret;
	stringstream ss;
	ss<<(*it);
	ss>>ret;
	return ret;
}

std::regex_iterator<std::string::iterator> string_operator::search_reg(std::regex e)
{
	std::regex_iterator<std::string::iterator> rit ( (this->s).begin(), (this->s).end(), e );
	return rit;
}

string string_operator::get_string()
{
	return (this->s);
}


void string_operator::replace_reg(std::regex e, string& replace_str)
{
	string replaced_string=std::regex_replace((this->s), e, replace_str);
	this->s=replaced_string;
}

void string_operator::readfile2string(string Dir)
{
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
		this->s=temp_s;
	};
}