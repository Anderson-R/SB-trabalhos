#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Needed for istringstream
#include <sstream>

// Needed for find_if function template
#include <algorithm>

// Needed for toupper()
#include <cctype>

// Splits a string into a vector of strings
std::vector<std::string> split(const std::string& s, char delimiter){
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter)){
      tokens.push_back(token);
   }
   return tokens;
}

// For strNotBlank
bool isNotSpace(char c){
	return ! isspace(c);
}

// Returns true if passed string contains non-whitespace character
bool strNotBlank(const std::string &str){
    return std::find_if(str.begin(), str.end(), isNotSpace) != str.end();
}

// Removes spaces and tabulations in each line of code
std::vector<std::string> intoTokens(const std::string& s){
	std::vector<std::string> tokens;
	std::vector<std::string> tokens1 = split(s, ' ');
	for(std::vector<std::string>::iterator it = tokens1.begin(); it != tokens1.end(); it++){
		std::vector<std::string> additionalTokens = split(*it, '\t');
		for(int i = 0; i < additionalTokens.size(); i++){
			if(strNotBlank(additionalTokens[i]))
				tokens.push_back(additionalTokens[i]);
		}
	}
	return tokens;
}

// Capitalizes all text in a string
std::string strCapitalize(const std::string str){
	std::string capitalized = str;
    for(auto& x: capitalized)
        x = toupper(x);
    return capitalized;
}

int passagemZero(std::ifstream& main_reader, std::ofstream& preWriter){

	bool newLine = true;
	bool EQUfound; // Flag for EQU directive
	std::string token;
	std::vector<std::string> tokens;
	std::vector<std::string> EQUtable;
	std::string rawLine;
	int origLineNum = 1; // Line number in the original .asm file
	int iEQU; // For indexing the EQUATE table
	int machineState = 0; // FSM which controls the 

	// Iterate through the lines in the .asm code for pre-processing
	while(std::getline(main_reader, rawLine)){
		if(strNotBlank(rawLine)){

			tokens = intoTokens(rawLine);

			switch(machineState){
				case 0:
					if(strCapitalize(rawLine) == "SECTION TEXT"){
						machineState = 1;
					}
					else if(strCapitalize(tokens[1]) == "EQU"){
						tokens.front().pop_back();
						EQUtable.push_back(tokens.front());
						EQUtable.push_back(tokens.back());
					}
					else{
						std::cout << "Error! Code outside of text section in line no. " << origLineNum << std::endl;
						return 0;
					}
					break;

				case 1:
					newLine = true;
					// Iterate through individual tokens in the .asm code
					for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++){
						if(strNotBlank(*it)){

							// Ignore comments
							if(it->front() == ';')
								break;

							// Place spaces between tokens and enumerates lines according to .asm
							if(newLine == true){
								preWriter << origLineNum << ' ';
								newLine = false;
							}
							else
								preWriter << ' ';

							EQUfound = false;
							for(iEQU = 0; iEQU < EQUtable.size(); iEQU += 2){
								if(*it == EQUtable[iEQU]){
									EQUfound = true;
									break;
								}
								iEQU++;
							}

							if(EQUfound == true)
								preWriter << EQUtable[iEQU+1];
							else
								preWriter << *it;
						}
					}
					if(newLine == false)
						preWriter << std::endl;
					break;
				default:
					break;
			}
		}
		origLineNum++;
	}

	main_reader.close();
	preWriter.close();

	return 0;

}