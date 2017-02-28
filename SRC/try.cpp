/********************************************************************************************************
* File:              try.cpp                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-02-27 20:48:08                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-02-27 20:48:52                                     *            
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
#include "string_operator.h"
#include "gmFoamTranslator.h"
#include "gmfoam_namespace.h"


using namespace std;
using namespace gmfoam_ns;


int main(int argc, char const *argv[])
{
	string s="<load_mesh> [filename]{test_model.msh}";
	// string s1="<define_transportProperties> [property_name]{nu}[property_unit]{0 2 -1 0 0 0 0}[property_value]{0.1}";
	gmFoamTranslator tr=gmFoamTranslator(s);
	tr.set_all();
	tr.execute_command();
	string s1="<define_transportProperties> [property_name]{nu}[property_unit]{0 2 -1 0 0 0 0}[property_value]{0.1}";
	gmFoamTranslator tr1=gmFoamTranslator(s1);
	tr1.set_all();
	tr1.execute_command();
	string s2="<define_boundaryGeometry> [top_surface]{wall}[bottom_surface]{wall}[lateral_surface_4]{wall}[lateral_surface_3]{wall}[lateral_surface_2]{wall}[lateral_surface_1]{wall}";
	gmFoamTranslator tr2=gmFoamTranslator(s2);
	tr2.set_all();
	tr2.execute_command();


	string s4="<set_system>[system_file]{fvSolution}[variable]{solvers}{p}{solver}[value]{hexiangwang}";
	gmFoamTranslator tr4=gmFoamTranslator(s4);
	tr4.set_all();
	tr4.execute_command();

	string s5="<set_system>[system_file]{fvSolution}[variable]{PISO}{pRefCell}[value]{hexiangwang}";
	gmFoamTranslator tr5=gmFoamTranslator(s5);
	tr5.set_all();
	tr5.execute_command();

	string s6="<set_system>[system_file]{controlDict}[variable]{application}[value]{Heeeeee}";
	gmFoamTranslator tr6=gmFoamTranslator(s6);
	tr6.set_all();
	tr6.execute_command();

	// string s3="<set_system>[system_file]{controlDict}[variable_name]{startTime}[value]{0}";

	// string s3="<set_boundary> [variable]{U}[boundary_name]{top_surface}[type]{fixedValue}[value}[uniform(1 0 0)]";
	
	// string s4="<set_boundary_condition_U> [boundary_name]{bottom_surface}[type]{noslip}[value}[]";
	// string s5="<set_boundary_condition_U> [boundary_name]{lateral_surface_4}[type]{noslip}[value}[]";
	// string s6="<set_boundary_condition_U> [boundary_name]{lateral_surface_3}[type]{noslip}[value}[]";
	// string s7="<set_boundary_condition_U> [boundary_name]{lateral_surface_2}[type]{noslip}[value}[]";
	// string s8="<set_boundary_condition_U> [boundary_name]{lateral_surface_1}[type]{noslip}[value}[]";
	
	return 0;
}
