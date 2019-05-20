#include <fstream>
#include <iostream>
#include "passagemZero.hpp"
#include "passagemUm.hpp"
#include "passagemDois.hpp"

int main(int argc, char** argv){

    if(argc < 2){
		std::cout << "No filename was passed to be translated!" << std::endl;
		return 0;
	}

	else if(splitPUm(argv[1], '.').back() != "asm"){
		std::cout << "Filename isn't an assembly source code!" << std::endl;
		return 0;
	}

	std::ifstream main_reader;
	std::string objName = splitPUm(argv[1], '.').front();
	objName.append(".obj");
    main_reader.open(argv[1]);
    std::fstream preWriter;
	preWriter.open(split(argv[1], '.').front() + ".pre", std::fstream::in | std::fstream::out | std::fstream::trunc);
	
	if(! main_reader) {
		std::cout << "Error opening file!" << std::endl;
		return 0;
	}

	std::map<std::string, int> preFile;
	std::vector<std::string> program;
    passagemZero(main_reader, preWriter, preFile, program);
	std::map<std::string, int> st = passagemUm(preFile, program);
	std::map<std::string, int>::iterator it = st.begin();
	cout<<"=============="<<endl;
	for(; it != st.end(); it++)
		cout<<it->first<<" "<<it->second<<endl;
	cout<<"=============="<<endl;
	passagemDois(preFile, program, objName);
    
    main_reader.close();
	preWriter.close();

    return 0;  
}