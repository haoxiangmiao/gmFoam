/********************************************************************************************************
* File:              gmFoamTranslator.cpp                                              
* Author:            Hexiang                                     | Boris Jeremic,                       *
* Date:              2017-02-04 20:25:37                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-03-10 12:33:20                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include <iostream>
#include "gmFoamTranslator.h"
#include "string_operator.h"
#include <stdio.h>
#include <string.h>
#include <vector>
#include <regex>
#include <functional>
#include <map>
#include "gmfoam_namespace.h"
#include <fstream>
#include <streambuf>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include "boundary_type.h"

using namespace std;


// using namespace gmfoam_ns;


gmFoamTranslator::gmFoamTranslator(){}
gmFoamTranslator::gmFoamTranslator(const string& input_command)
{
	this->input_string=input_command;

}  

gmFoamTranslator::~gmFoamTranslator(){}

void gmFoamTranslator::set_command()
{
	string_operator so=string_operator(input_string);
	vector<string> vs=so.string_extractor(input_string,"<",">");
	vector<string>::size_type sz=vs.size();
	if(sz>1)
	{
		cout<<"Syntax error:command by command, please!"<<endl;
		exit(EXIT_FAILURE);
	}

	this->command=vs[0];
}
void gmFoamTranslator::set_keyword()
{
	string_operator so=string_operator(input_string);
	this->keyword=so.string_extractor(input_string,"[","]");	
}
void gmFoamTranslator::set_parameter()
{
	string_operator so=string_operator(input_string);
	this->parameter=so.string_extractor(input_string,"{","}");
}

string gmFoamTranslator::get_command()
{
	string ret=this->command;
	return ret;
}

vector<string> gmFoamTranslator::get_keyword()
{
	std::vector<string> ret=this->keyword;
	return ret;
}

vector<string> gmFoamTranslator::get_parameter()
{
	vector<string> ret=this->parameter;
	return ret;
}

// ###################Note this function should be dynamically updated when new commands added. To build the mapping between string command and member function pointer.

void gmFoamTranslator::set_funcMap()
{
	this->funcMap["load_fluid_mesh"]=&gmFoamTranslator::load_fluid_mesh;
	this->funcMap["define_transportProperties"]=&gmFoamTranslator::define_transportProperties;
	this->funcMap["define_boundaryGeometry"]=&gmFoamTranslator::define_boundaryGeometry;
	this->funcMap["set_system"]=&gmFoamTranslator::set_system;
	this->funcMap["set_boundary_condition"]=&gmFoamTranslator::set_boundary_condition;
	this->funcMap["add_fluid_phase"]=&gmFoamTranslator::add_fluid_phase;
	this->funcMap["define_model_name"]=&gmFoamTranslator::define_model_name;
	this->funcMap["add_solid_phase"]=&gmFoamTranslator::add_solid_phase;

}
// ##################################################################################################################################################### 


void gmFoamTranslator::set_all()
{
	set_command();
	set_keyword();
	set_parameter();
	set_funcMap();
}

std::map<std::string,  void (gmFoamTranslator::* )()> gmFoamTranslator::get_map()
{
	return this->funcMap;
}

void gmFoamTranslator::load_fluid_mesh()
{
	int FLAG=-1;

	extern string project_name;
	string s=project_name;
	s=s+"_fluid_simulation";
	// string temp_str=(this->parameter)[0];            //note the calling of components here, first () then []
	// string_operator so=string_operator((this->parameter)[0]);
	// string::iterator it=temp_str.begin();
	// for(; it!=temp_str.end(); ++it)
	// {
	// 	if(so.get_string_component(it)!=".")
	// 		project_name=project_name+so.get_string_component(it);
	// 	else break;
	// }
	string SPACE=" ";
	string bash_call_string="gmsh_conversion"+SPACE+s;
	system(bash_call_string.c_str());
	
	FLAG=0;
	bug_information(FLAG);
}

void gmFoamTranslator::define_transportProperties()   
{
	int FLAG=-1;

	extern string project_name;
	string s= project_name+"_fluid_simulation";
	string Dir=getFilePath();
	Dir=Dir+"/"+s+"/constant/transportProperties";
	std::ifstream input(Dir);
	if (!input) 
	{
		std::cerr << "Could not open the file!" << std::endl;
		bug_information(FLAG);
		return;
	}
	else
	{
		string temp_s;
		input.seekg(0, std::ios::end);
		temp_s.reserve(input.tellg()); 
		input.seekg(0, std::ios::beg);
		temp_s.assign((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
		if((this->parameter).size()!=3)
		{
			std::cerr << "lack parameters in define_transportProperties" << std::endl;
			bug_information(FLAG);
			return;
		}
		else
		{
			string unit="";
			string continuous_unit=(this->parameter)[1];
			for(string::iterator it=continuous_unit.begin(); it<continuous_unit.end(); ++it)
			{
				// unit=unit+(*it)+" ";
				if((*it)!='-')                     //in order to avoid separation between negative sign and numbers
				{
					unit=unit+(*it)+" ";
				}
				else
				{
					unit=unit+(*it);
				}
			}
			temp_s=temp_s+(this->parameter)[0]+"      ["+unit+"] "+(this->parameter)[2]+";\n";
			std::ofstream out(Dir);
			out<<temp_s;
			out.close();
		}
	
	};



	FLAG=0;
	bug_information(FLAG);
}

void gmFoamTranslator::define_boundaryGeometry()
{
	int FLAG=-1;

	extern string project_name;
	string s= project_name+"_fluid_simulation";
	string Dir=getFilePath();
	Dir=Dir+"/"+s+"/constant/polyMesh/boundary";
	std::ifstream input(Dir);
	if (!input)
	{
		std::cerr << "Could not open the file!" << std::endl;
		bug_information(FLAG);
		return;
	}
	else
	{
		string temp_s;
		input.seekg(0, std::ios::end);
		temp_s.reserve(input.tellg()); 
		input.seekg(0, std::ios::beg);
		temp_s.assign((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
		string_operator so=string_operator(temp_s);
		for(int i=0; i<(this->keyword).size(); ++i)
		{
			// std::regex e ("<[A-Za-z0-9_\"\\.\\s]+>[\\s]*(\\[[A-Za-z0-9_\"\\.\\s]+\\][\\s]*\\{[A-Za-z0-9_\"\\.\\s]+\\})*");
			string replace_str="";
			string keyword_i=(this->keyword)[i];
			string reg_string=keyword_i+"\n[\\s]*\\{[\\s]*\n[\\s]*type[\\s]*"+"patch;"+"\n[\\s]*"+"physicalType[\\s]*patch;";
			std::regex e (reg_string);
			replace_str=keyword_i+"\n    {\n        type            "+(this->parameter)[i]+";\n        inGroups     1("+(this->parameter)[i]+");";
			so.replace_reg(e,replace_str);
		}
		temp_s=so.get_string();
		std::ofstream out(Dir);
		out<<temp_s;
		out.close();
	};



	FLAG=0;
	bug_information(FLAG);
}

void gmFoamTranslator::execute_command()
{
	(this->*(this->funcMap[this->command]))();   
}

// ###########this function can be used to return current running directory as string#######################
string gmFoamTranslator::getFilePath()
{

	char filePath[256];	
	if(!GetCurrentDir(filePath, sizeof(filePath)))
	{

		cout<<"** ERROR - Something went wrong, exiting...\n";
		return " ";
	}
	
	string FilePath(filePath);
	return FilePath;

}

void gmFoamTranslator::set_system()
{
	
	int FLAG=-1;


	extern string project_name;
	string s= project_name+"_fluid_simulation";
	string Dir=getFilePath();
	Dir=Dir+"/"+s+"/"+"system/"+(this->parameter)[0];
	string_operator so;
	so.readfile2string(Dir);
	int No_parameter=(this->parameter).size();
	string opening_flag="{";
	string closing_flag="}";

	std::vector<string> original_string;
	original_string.push_back(so.get_string());


	for(int i=0; i<No_parameter-3; ++i)
	{
		string temp_s=so.balanced_extractor((this->parameter)[1+i],opening_flag,closing_flag);
		original_string.push_back(temp_s);
		so.set_string(temp_s);
	}

	int No_original_string=original_string.size();
	string reg_str=(this->parameter)[No_parameter-2]+"[\\s]*[a-zA-Z0-9]+;";
	string replace_str=(this->parameter)[No_parameter-2]+"\t"+(this->parameter)[No_parameter-1]+";";
	std::regex e (reg_str);
	so.replace_reg(e,replace_str);
	string new_string=so.get_string();

	for(int j=0; j<No_original_string-1; ++j)
	{
		string_operator so_temp=string_operator(original_string[No_original_string-2-j]);
		so_temp.balanced_replace(new_string,(this->parameter)[No_parameter-3-j],opening_flag, closing_flag);
		new_string=so_temp.get_string();
	}

	std::ofstream out(Dir);
	out<<new_string;
	out.close();



	FLAG=0;
	bug_information(FLAG);

}


void gmFoamTranslator::set_boundary_condition()
{
	int FLAG=-1;

	extern string project_name;
	string s= project_name+"_fluid_simulation";
	string Dir=getFilePath();

	// First we need to get startTime
	Dir=Dir+"/"+s+"/"+"system/controlDict";
	string_operator so;
	so.readfile2string(Dir);
	string temp=so.get_string();

	std::regex e("startTime[\\s]*([0-9\\.]+);");
	std::regex_iterator<std::string::iterator> rit ( temp.begin(), temp.end(), e );
	string temp_str=rit->str();

	std::smatch sm;
	std::regex_match(temp_str,sm,e);    //sm[1] is the starttime extract from syatem file

	string Boundary_file=sm[1];
	std::map<std::string, std::string> file_map { {"U",U_header},{"p",P_header} };

	string Dir_temp=getFilePath()+"/"+s+"/"+Boundary_file+"/"+(this->parameter)[0];
	string file_dir=getFilePath()+"/"+s+"/"+Boundary_file;

	std::ifstream input(Dir_temp);
	if (!input)   //initial boundary file does not exist...
	{
		//###################test if initial boundary condition file exists or not ##########################################
		struct stat st;
		if(stat(file_dir.c_str(),&st)!=0)
		{
			// cout<<"directory does not exist"<<endl;
			string mk_str="mkdir  "+file_dir;
			system(mk_str.c_str());
		}

		//###################################################################################################################
		
		string temp_str=header+file_map[(this->parameter)[0]];
	
		if((this->parameter)[1]=="dimensions")
		{
			string continuous_unit=(this->parameter)[2];
			string unit="";
			for(string::iterator it=continuous_unit.begin(); it<continuous_unit.end(); ++it)
			{
				if((*it)!='-')
				{
					unit=unit+(*it)+" ";
				}
				else
				{
					unit=unit+(*it);
				}
				
			}
			temp_str=temp_str+"\ndimensions      ["+unit+"];\n";
			// Dir_temp=Dir_temp+"/"+(this->parameter)[0];
			std::ofstream out(Dir_temp);
			out<<temp_str;
			out.close();
		}
		else
		{
			cout<<"please specify the dimensions for boundary condition field "<<(this->parameter)[0]<<endl;
			bug_information(FLAG);
			return;
		}
	}

	else
	{
		string_operator so1;
		so1.readfile2string(Dir_temp);
		string original_string=so1.get_string();
		int No_parameter=(this->parameter).size();
		boundary_type bt=boundary_type((this->parameter)[No_parameter-1]);

		// cout<<bt.get_string()<<endl;

		string value=bt.generateBC();

		// cout<<value<<endl;

		string opening_flag="{";
		string closing_flag="}";

		if((this->parameter)[1]=="internalField")
		{
			original_string=original_string+"\ninternalField   "+value;
		}
		if((this->parameter)[1]=="boundaryField")
		{
			string boundary_temp=so1.balanced_extractor((this->parameter)[1],opening_flag,closing_flag);
			if(boundary_temp=="NOT FOUND")
			{
				original_string=original_string+"boundaryField\n{\n    "+(this->parameter)[2]+"\n    {\n        "+(this->parameter)[3]+"            "+value+"    }\n\n}";

			}
			else
			{
				boundary_temp=boundary_temp+"\n    "+(this->parameter)[2]+"\n    {\n        "+(this->parameter)[3]+"            "+value+"\n    }\n";
				so1.balanced_replace(boundary_temp,(this->parameter)[1],opening_flag,closing_flag);
				original_string=so1.get_string();
			}

		}
		std::ofstream out(Dir_temp);
		out<<original_string;
		out.close();
	};




	FLAG=0;
	bug_information(FLAG);
}




void gmFoamTranslator::define_model_name()
{
	int FLAG=-1;


	extern string project_name;
	project_name=(this->parameter)[0];


	FLAG=0;
	bug_information(FLAG);
}


void gmFoamTranslator::add_fluid_phase()
{
	int FLAG=-1;



	string Dir=getFilePath();
	Dir=Dir+"/"+(this->parameter)[0];

	extern string project_name;
	string s= project_name;

	ifstream mesh_file(Dir);
	string current_line;
	string output_string="";

	string_operator so1=string_operator((this->parameter)[1]);
	string_operator so2=string_operator((this->parameter)[2]);
	string separator1=";";
	

	std::vector<string> physical_volume=so1.string_separator((this->parameter)[1],separator1);

	std::vector<string> physical_boundary=so2.string_separator((this->parameter)[2],separator1);

	// ##########################try to concatenate two string vector#################################################
	std::vector<string> physical_element=physical_boundary;
	physical_element.insert(physical_element.end(),physical_volume.begin(),physical_volume.end());

	// cout<<physical_element[5]<<physical_element[6]<<physical_element[7]<<endl;

	// ##################################end concatenating#############################################################
	std::map<int, std::vector<string>> NODE;		//node map: the first component is node index; the second component is whole node line.
	std::map<int, std::vector<string>> ELEMENT;   //element map: the firsr component is element index, the second component is whole element line .msh file.

	if(mesh_file.is_open())
	{
		int flag=0;
		int index=-1;
		
		while(std::getline(mesh_file,current_line))
		{

			if(current_line=="$MeshFormat")
			{
				flag=1;
			}
			if(current_line=="$Nodes")
			{
				flag=2;
				index=0;
			}
			if(current_line=="$Elements")
			{
				flag=3;
				index=0;
			}
			if(current_line=="$PhysicalNames")
			{
				flag=4;
				index=0;
				output_string=output_string+"$PhysicalNames\n"+std::to_string(physical_element.size())+"\n";
			}
			if(flag==1)
			{
					if(current_line!="$PhysicalNames")
					{
						output_string=output_string+current_line+"\n";
						// cout<<"I am here"<<endl;
					}
					else
					{
						flag=0;
						// cout<<output_string<<endl;
					}
				// cout<<current_line;
			}
			if(flag==2)
			{
				if(index!= 2)
				{
					index=index+1;   //just to skip fisrt two lines
				}
				else
				{
					if(current_line!="$EndNodes")
					{
						string_operator so=string_operator(current_line);
						string separator=" ";
						std::vector<string> string_component=so.string_separator(current_line,separator);   //parse nodes information: 4 numbers: 1 index 3 coordinates
						int node_index=std::stoi(string_component[0]);
						NODE[node_index]=string_component;

					}
					else
					{
						flag=0;
						index=-1;
					}					
				
				}
			}
			if(flag==3)
			{
				if(index!=2)
				{
					index=index+1;
				}
				else
				{
					if(current_line!="$EndElements")
					{
						string_operator so=string_operator(current_line);
						string separator=" ";
						std::vector<string> string_component=so.string_separator(current_line,separator);
						int element_index=std::stoi(string_component[0]);
						ELEMENT[element_index]=string_component;
						// cout<<ELEMENT[element_index][2]<<endl;
					}
					else
					{
						flag=0;
						index=-1;
					}
				}
			}
			if(flag==4)
			{
				if(index!=2)
				{
					index=index+1;
				}
				else
				{
					if(current_line!="$EndPhysicalNames")
					{
						string_operator so=string_operator(current_line);
						string separator=" ";
						std::vector<string> string_component=so.string_separator(current_line,separator);
						for (int i3 = 0; i3 < physical_element.size(); ++i3)
						{
							if(string_component[1]==physical_element[i3])
							{
								output_string=output_string+current_line+"\n";
								// cout<<output_string<<endl;
							}
						}
					}
					else
					{
						flag=0;
						index=-1;
					}
				}
			}

		}

	}
	else
	{
		cout<<"Cannot open file"<<endl;
		return;
	}

	int No_nodes=0;
	int No_elements=0;
	int No_physical_surfaces=0;
	std::vector<int> nodelist;
	string element_information="";
	string node_information="";



	for(int i=0; i<physical_element.size(); ++i)
	{
		for(std::map<int, std::vector<string>>::iterator it=ELEMENT.begin(); it!=ELEMENT.end(); ++it)
		{
			if((it->second)[3]==physical_element[i])   //the 4th component is physical group number
			{
				for (int k = 0; k < (it->second).size(); ++k)
				{
					element_information=element_information+(it->second)[k]+" ";
				}
				element_information=element_information+"\n";

				// cout<<element_information<<endl;

				No_elements=No_elements+1;
				for(int l=5; l < (it->second).size(); ++l)
				{
					int temp=std::stoi((it->second)[l]);
					nodelist.push_back(temp);
				}	
			}
		}
	}


	sort(nodelist.begin(),nodelist.end());
	nodelist.erase(unique(nodelist.begin(),nodelist.end()),nodelist.end());

	// for(std::vector<int>::iterator it2=nodelist.begin(); it2!=nodelist.end(); ++it2)
	// {
	// 	cout<<(*it2)<<endl;
	// 	cout<<"i AM HAPPY DOWN"<<endl;
	// }

	// for(std::map<int, std::vector<string>>::iterator it3=NODE.begin(); it3!=NODE.end(); ++it3)
	// {
	// 	cout<<(it3->first)<<endl;
	// 	cout<<"finish output node information"<<endl;
	// }

	for (int i1 = 0; i1 < nodelist.size(); ++i1)
	{
		for(std::map<int, std::vector<string>>::iterator it1=NODE.begin(); it1!=NODE.end(); ++it1)
		{
			if(nodelist[i1]==std::stoi((it1->second)[0]))
			{
				for(int k1=0; k1<(it1->second).size(); ++k1)
				{
					node_information=node_information+(it1->second)[k1]+" ";
				}
				node_information=node_information+"\n";
				No_nodes=No_nodes+1;
			}
		}
	}


	output_string=output_string+"$EndPhysicalNames\n$Nodes\n"+std::to_string(No_nodes)+"\n"+node_information+"$EndNodes\n$Elements\n"+std::to_string(No_elements)+"\n"+element_information+"$EndElements\n";

	string file_dir=getFilePath()+"/"+s+"_fluid_simulation";
	struct stat st;
	if(stat(file_dir.c_str(),&st)!=0)
	{
		// cout<<"directory does not exist"<<endl;
		string mk_str="mkdir  "+file_dir;
		system(mk_str.c_str());
	}
	else
	{
		// ########################## terminal commands can be executed inside c++ using system function ############################################ 
		cout<<s<<"_fluid already exists!!! clearing inside..."<<endl;
		string rm_str="rm -r "+file_dir;
		string mk_str="mkdir  "+file_dir;
		system(rm_str.c_str());
		system(mk_str.c_str());
		// ###########################################################################################################################################
	}



	string output_dir=file_dir+"/"+project_name+"_fluid.msh";
	std::ofstream out(output_dir);
	out<<output_string;
	out.close();

	

	FLAG=0;
	bug_information(FLAG);

}

void gmFoamTranslator::add_solid_phase()
{
	int FLAG=-1;


	string calling_gmessy="gmessy "+(this->parameter)[0];
	system(calling_gmessy.c_str());


	FLAG=0;
	bug_information(FLAG);
}


void gmFoamTranslator::bug_information(int FLAG)
{
	if(FLAG==0)
	{
		cout<<"Successfully converted "<<(this->input_string)<<"\n"<<endl;
	}
	else
	{
		cout<<"ATTENTION:Failed to converted "<<(this->input_string)<<"!!!"<<"\n"<<endl;
	}
	
}
//###########################################################################################################