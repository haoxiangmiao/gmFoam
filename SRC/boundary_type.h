/********************************************************************************************************
* File:              boundary_type.h                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-03-10 01:31:06                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-03-10 01:32:39                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/



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