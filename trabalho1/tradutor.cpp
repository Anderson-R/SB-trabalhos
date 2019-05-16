#include <fstream>
#include <iostream>
#include "passagemUm.hpp"

int main(int argc, char** argv){

    if(argc < 2){
		std::cout << "No filename was passed to be translated!" << std::endl;
		return 0;
	}

	else if(split(argv[1], '.').back() != "asm"){
		std::cout << "Filename isn't an assembly source code!" << std::endl;
		return 0;
	}

	std::ifstream main_reader(argv[1]);

	if(! main_reader) {
		std::cout << "Error opening file!" << std::endl;
		return 0;
	}

    return 0;  
}