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
#include "gmFoamTranslator.h"
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;
ert
erttjei

gmFoamTranslator::gmFoamTranslator(){}
gmFoamTranslator::gmFoamTranslator(const string& input_command)
{
 
 }  
gmFoamTranslator::~gmFoamTranslator(){}

void gmFoamTranslator::load_mesh()
{

}
void gmFoamTranslator::set_command(const string& str)
{
	this->command=str;
}
void gmFoamTranslator::set_keyword(const std::vector<string>& str)
{
	this->keyword=str;
}
void gmFoamTranslator::set_parameter(const std::vector<string>& str)
{
	this->parameter=str;
}

