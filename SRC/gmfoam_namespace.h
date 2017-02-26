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
	namespace transportProperties
	{
		string reserved_template="";
	}



};
#endif