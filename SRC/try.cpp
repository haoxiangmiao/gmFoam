/********************************************************************************************************
* File:              try.cpp                                              
* Author:            hexiang6666                                 | Boris Jeremic,                       *
* Date:              2017-02-27 20:48:08                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-03-10 01:28:01                                     *            
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
// using namespace gmfoam_ns;


int main(int argc, char const *argv[])
{
	string s0="<define_model_name>[name]{test_model}";
	gmFoamTranslator tr0=gmFoamTranslator(s0);
	tr0.set_all();
	tr0.execute_command();


	string s1="<add_fluid_phase>[mesh_file]{test_model.msh}[volumn_physical_group]{1;2;3;5}[boundary_physical_group]{10;11;12;13;14;15}";
	gmFoamTranslator tr1=gmFoamTranslator(s1);
	tr1.set_all();
	tr1.execute_command();

	string s2="<add_solid_phase>[gmessi_file]{test_model_imposed_motion.gmessi}";
	gmFoamTranslator tr2=gmFoamTranslator(s2);
	tr2.set_all();
	tr2.execute_command();

	string s3="<load_fluid_mesh> [filename]{test_model_fluid.msh}";
	gmFoamTranslator tr3=gmFoamTranslator(s3);
	tr3.set_all();
	tr3.execute_command();

	string s4="<define_transportProperties> [property_name]{nu}[property_dimensions]{0 2 -1 0 0 0 0}[property_value]{0.01}";
	gmFoamTranslator tr4=gmFoamTranslator(s4);
	tr4.set_all();
	tr4.execute_command();



	string s5="<define_boundaryGeometry> [top_fluid_surface]{wall}[bottom_fluid_surface]{wall}[lateral_surface_4]{wall}[lateral_surface_3]{wall}[lateral_surface_2]{wall}[lateral_surface_1]{wall}";
	gmFoamTranslator tr5=gmFoamTranslator(s5);
	tr5.set_all();
	tr5.execute_command();


	// #####################examples to set system values##########################################################################


	// string s4="<set_system>[system_file]{fvSolution}[variable]{solvers}{p}{solver}[value]{hexiangwang}";
	// gmFoamTranslator tr4=gmFoamTranslator(s4);
	// tr4.set_all();
	// tr4.execute_command();

	// string s5="<set_system>[system_file]{fvSolution}[variable]{PISO}{pRefCell}[value]{hexiangwang}";
	// gmFoamTranslator tr5=gmFoamTranslator(s5);
	// tr5.set_all();
	// tr5.execute_command();

	// string s6="<set_system>[system_file]{controlDict}[variable]{startTime}[value]{2.3}";
	// gmFoamTranslator tr6=gmFoamTranslator(s6);
	// tr6.set_all();
	// tr6.execute_command();

	// ##################################################################################################################################


	string s7="<set_boundary_condition>[boundary_file]{U}[variable]{dimensions}[value]{0 1 -1 0 0 0 0}";
	gmFoamTranslator tr7=gmFoamTranslator(s7);
	tr7.set_all();
	tr7.execute_command();
	
	string s8="<set_boundary_condition>[boundary_file]{U}[variable]{internalField}[value]{uniform; (0 0 0)}";
	gmFoamTranslator tr8=gmFoamTranslator(s8);
	tr8.set_all();
	tr8.execute_command();


	string s9="<set_boundary_condition>[boundary_file]{U}[variable]{boundaryField}{top_fluid_surface}{type}[value]{fixedValue;uniform;(1 0 0)}";
	gmFoamTranslator tr9=gmFoamTranslator(s9);
	tr9.set_all();
	tr9.execute_command();

	string s10="<set_boundary_condition>[boundary_file]{U}[variable]{boundaryField}{bottom_fluid_surface}{type}[value]{noSlip}";
	gmFoamTranslator tr10=gmFoamTranslator(s10);
	tr10.set_all();
	tr10.execute_command();

	string s11="<set_boundary_condition>[boundary_file]{U}[variable]{boundaryField}{lateral_surface_4}{type}[value]{noSlip}";
	gmFoamTranslator tr11=gmFoamTranslator(s11);
	tr11.set_all();
	tr11.execute_command();

	string s12="<set_boundary_condition>[boundary_file]{U}[variable]{boundaryField}{lateral_surface_3}{type}[value]{noSlip}";
	gmFoamTranslator tr12=gmFoamTranslator(s12);
	tr12.set_all();
	tr12.execute_command();

	string s13="<set_boundary_condition>[boundary_file]{U}[variable]{boundaryField}{lateral_surface_2}{type}[value]{noSlip}";
	gmFoamTranslator tr13=gmFoamTranslator(s13);
	tr13.set_all();
	tr13.execute_command();

	string s14="<set_boundary_condition>[boundary_file]{U}[variable]{boundaryField}{lateral_surface_1}{type}[value]{noSlip}";
	gmFoamTranslator tr14=gmFoamTranslator(s14);
	tr14.set_all();
	tr14.execute_command();

	string s15="<set_boundary_condition>[boundary_file]{p}[variable]{dimensions}[value]{0 2 -2 0 0 0 0}";
	gmFoamTranslator tr15=gmFoamTranslator(s15);
	tr15.set_all();
	tr15.execute_command();

	string s16="<set_boundary_condition>[boundary_file]{p}[variable]{internalField}[value]{uniform;0}";
	gmFoamTranslator tr16=gmFoamTranslator(s16);
	tr16.set_all();
	tr16.execute_command();

	string s17="<set_boundary_condition>[boundary_file]{p}[variable]{boundaryField}{top_fluid_surface}{type}[value]{zeroGradient}";
	gmFoamTranslator tr17=gmFoamTranslator(s17);
	tr17.set_all();
	tr17.execute_command();


	string s18="<set_boundary_condition>[boundary_file]{p}[variable]{boundaryField}{bottom_fluid_surface}{type}[value]{zeroGradient}";
	gmFoamTranslator tr18=gmFoamTranslator(s18);
	tr18.set_all();
	tr18.execute_command();

	string s19="<set_boundary_condition>[boundary_file]{p}[variable]{boundaryField}{lateral_surface_4}{type}[value]{zeroGradient}";
	gmFoamTranslator tr19=gmFoamTranslator(s19);
	tr19.set_all();
	tr19.execute_command();

	string s20="<set_boundary_condition>[boundary_file]{p}[variable]{boundaryField}{lateral_surface_3}{type}[value]{zeroGradient}";
	gmFoamTranslator tr20=gmFoamTranslator(s20);
	tr20.set_all();
	tr20.execute_command();

	string s21="<set_boundary_condition>[boundary_file]{p}[variable]{boundaryField}{lateral_surface_2}{type}[value]{zeroGradient}";
	gmFoamTranslator tr21=gmFoamTranslator(s21);
	tr21.set_all();
	tr21.execute_command();

	string s22="<set_boundary_condition>[boundary_file]{p}[variable]{boundaryField}{lateral_surface_1}{type}[value]{zeroGradient}";
	gmFoamTranslator tr22=gmFoamTranslator(s22);
	tr22.set_all();
	tr22.execute_command();
	
	return 0;
}
