#include <iostream>
#include <regex>
#include <fstream>
#include <streambuf>
#include <functional>
#include <map>


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
    	std::regex e ("<[A-Za-z0-9_\"\\.\\s]+>[\\s]*(\\[[A-Za-z0-9_\"\\.\\s]+\\][\\s]*\\{[A-Za-z0-9_\"\\.\\s]+\\})*");
	  	std::regex_iterator<std::string::iterator> rit ( file_str.begin(), file_str.end(), e );
    	std::regex_iterator<std::string::iterator> rend;
   		// while (rit!=rend)
    	// {
    		input_string=rit->str();


    		// std::cout << rit->str() << std::endl;
   			// ++rit;
   		// }
	}
	if (argc>2)
	{
		cout<<"Given too many input files, only one please"<<endl;
	}
	return 0;
}
