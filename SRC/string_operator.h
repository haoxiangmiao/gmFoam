/********************************************************************************************************
* File:              string_operator.h                                              
* Author:            Hexiang                                     | Boris Jeremic,                       *
* Date:              2017-02-02 18:56:11                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-02-04 20:28:06                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#ifndef STRING_OPERATOR_H
#define STRING_OPERATOR_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class string_operator
{
	public:
		string_operator();
		~string_operator();
		string_operator(const string& str);
		string get_command();

	private:
		string s;

};
#endif