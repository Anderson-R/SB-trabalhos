#include <fstream>
#include <iostream>
#include "passagemZero.hpp"
#include "passagemUm.hpp"

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
    main_reader.open(argv[1]);
    std::ofstream preWriter(split(argv[1], '.').front() + ".pre");

	if(! main_reader) {
		std::cout << "Error opening file!" << std::endl;
		return 0;
	}

    passagemZero(main_reader, preWriter);

    return 0;  
}