/********************************************************************************************************
* File:              gmFoamTranslator.h                                              
* Author:            Hexiang                                     | Boris Jeremic,                       *
* Date:              2017-02-04 20:15:35                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-02-04 20:26:35                                     *            
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

using namespace::std;

class gmFoamtranslator{
	
	public:
		gmFoamtranslator();
		~gmFoamtranslator();
		gmFoamtranslator(const string& input_command);
		void load_mesh();
		void set_command(const string& str);
		void set_keyword(const std::vector<string>& str);
		void set_parameter(const std::vector<string>& str);

	private:
		string command;
		std::vector<string> keyword;
		std::vector<string> parameter;		


};

#endif