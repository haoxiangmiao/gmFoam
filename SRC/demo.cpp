/********************************************************************************************************
* File:              demo.cpp                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-02-27 20:46:20                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-02-27 20:46:38                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <functional>
#include <map>
#include <regex>
#include "gmfoam_namespace.h"
#include "string_operator.h"
#include <fstream>
#include <streambuf>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
using namespace std;



int main(int argc, char const *argv[])
{
	string Dir="/home/hexiang/git/gmFoam/SRC/Openfoam_translator/cavity_final_can_run/system/controlDict";
	string_operator so;
	so.readfile2string(Dir);
	string c=so.get_string();
	cout<<c;
	// string d=("startTime       0;");
	// std::regex e("(startTime)[\\s]*([a-zA-Z0-9]+);");

	std::regex e("(startTime)[\\s]*([0-9A-Za-z]+)(;)");
	std::regex_iterator<std::string::iterator> rit ( c.begin(), c.end(), e );
	
	string tem=rit->str();
	cout<<tem<<endl;

	std::smatch sm;
	std::regex_match (tem,sm,e);

	cout<<sm[0]<<endl;
	cout<<sm[1]<<endl;
	cout<<sm[2]<<endl;
	cout<<sm[3]<<endl;
	cout<<"hekooo world"<<endl;

	std::ofstream out("see this");
	out<<c;
	out.close();




	return 0;
}
