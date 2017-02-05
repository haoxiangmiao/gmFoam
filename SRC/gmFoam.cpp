/********************************************************************************************************
* File:              gmFoam.cpp                                              
* Author:            Hexiang                                     | Boris Jeremic,                       *
* Date:              2017-02-04 20:15:47                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-02-04 20:27:50                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include <regex>
#include <fstream>
#include <streambuf>


using namespace std;


int main(int argc, char const *argv[])
{
	if (argc==1)
	{
		cout<<"cannot find input files"<<endl;
	}
	if (argc==2)
	{
		// ################################read the file into string#########################
		std::ifstream t(argv[1]);
		std::string file_str;
		t.seekg(0, std::ios::end);   
		file_str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);
		file_str.assign((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
		// ###################################end of reading file################################
    	std::regex e ("<[A-Za-z0-9_\"\\.\\s]+>[\\s]*\\[[A-Za-z0-9_\"\\.\\s]+\\][\\s]*\\{[A-Za-z0-9_\"\\.\\s]+\\}");
	  	std::regex_iterator<std::string::iterator> rit ( file_str.begin(), file_str.end(), e );
    	std::regex_iterator<std::string::iterator> rend;
   		while (rit!=rend)
    	{
    		
    		std::cout << rit->str() << std::endl;
   			++rit;
   		}
	}
	if (argc>2)
	{
		cout<<"Given too many input files, only one please"<<endl;
	}
	return 0;
}
