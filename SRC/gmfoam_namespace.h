/********************************************************************************************************
* File:              gmfoam_namespace.h                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-02-26 20:45:17                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-02-27 20:43:28                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#ifndef GMFOAM_NAMESPACE_H
#define GMFOAM_NAMESPACE_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <functional>
#include <map>
#include <fstream>
#include <streambuf>


using namespace::std;

extern string project_name;
string project_name="";
#ifdef _WIN32 
    #include <direct.h>
    #define GetCurrentDir _getcwd
    #define slash "\\"
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
	#define slash "/"
#endif

namespace gmfoam_ns
{
	// ####################define some file directory#######################################################
	// std::map<std::string, std::string> system_dir_mapping;
	// system_dir_mapping["contr"]


};
#endif