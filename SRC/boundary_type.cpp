/********************************************************************************************************
* File:              boundary_type.cpp                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-03-10 01:32:47                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-03-10 01:35:03                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <streambuf>
#include "string_operator.h"
#include "boundary_type.h"

using namespace std;
boundary_type::boundary_type(){}
boundary_type::~boundary_type(){}
boundary_type::boundary_type(const string& str):s{str}{}


//##########################Note:: This function handles all knids of Bundary condition output; should be updated if using new boundary conditions ########################################

string boundary_type::generateBC()
{
	string ret;
	string_operator so=string_operator(this->s);
	string separator=";";
	std::vector<string> vs=so.string_separator(this->s,separator);    // in our syntax we use ; to separate string
	// cout<<vs.size()<<endl;
	// cout<<vs[0]<<endl<<vs[1]<<endl;
	if(vs[0]=="uniform")
	{
		if(vs.size()!=2)
		{
			cout<<"lack parameters about uniform field"<<endl;
		}
		else
		{
			string value="";
			string continuous_value=vs[1];
			for(string::iterator it=continuous_value.begin(); it<continuous_value.end(); ++it)
				value=value+(*it)+" ";// ret="uniform    "
			ret="uniform "+value+";\n\n";
		}
	}
	if(vs[0]=="fixedValue")
	{
		if(vs.size()!=3)
		{
			cout<<"lack parameters about fixedValue boundary condition"<<endl;
		}
		else
		{
			string vs12=vs[1]+";"+vs[2];
			boundary_type bt=boundary_type(vs12);
			string part_ret=bt.generateBC();

			ret="fixedValue;\n        value           "+part_ret;
		}
	}
	if(vs[0]=="noSlip")
	{
		if(vs.size()!=1)
		{
			cout<<"syntax error"<<endl;
		}
		else
		{
			ret=vs[0]+";\n";
		}
	}
	if(vs[0]=="zeroGradient")
	{
		if(vs.size()!=1)
		{
			cout<<"syntax error"<<endl;
		}
		else
		{
			ret=vs[0]+";\n";
		}
	}

	return ret;
}


// ###############################################################################################################################################################################


string boundary_type::get_string()
{
	return (this->s);
}