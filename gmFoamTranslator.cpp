#include <isotream>
#include "gmFoamTranslator.h"
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

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

