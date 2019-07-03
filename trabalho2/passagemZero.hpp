#ifndef PASSAGEMZERO_HPP
#define PASSAGEMZERO_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

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

//passes the .pre file to a map with its original file line number
std::map<std::string, int> preToMap(std::fstream& preWriter, std::vector<int> lines, std::vector<std::string>& program){
	std::map<std::string, int> ret;
	preWriter.seekp(0);
	for(int i=0; i<lines.size(); i++){
		std::string line;
		std::getline(preWriter, line);
		program.push_back(strCapitalize(line));
		ret.insert(std::pair<std::string, int>(strCapitalize(line), lines.at(i)));
	}
	return ret;
}

int passagemZero(std::ifstream& main_reader, std::fstream& preWriter, std::map<std::string, int>& mapRet, std::vector<std::string>& vecRet){

	std::vector<int> lines;

	bool newLine = true;
	bool EQUfound; // Flag for EQU directive
	bool MACROfound; // Flag for MACRO directive
	std::string token;
	std::string macrodef; // For constructing MACROs
	std::vector<std::string> tokens;
	std::vector<std::string> EQUtable;
	std::vector<std::string> MACROtable;
	std::string rawLine;
	int origLineNum = 1; // Line number in the original .asm file
	int iEQU; // For indexing the EQUATE table
	int iMACRO; // For indexing the MACRO table
	int machineState = 0; // FSM which controls the translator. 0 - pre-SECTION TEXT, 1 - post-SECTION TEXT, 2 - IF directive, 3 - MACRO definition

	// Iterate through the lines in the .asm code for pre-processing
	while(std::getline(main_reader, rawLine)){
		if(strNotBlank(rawLine)){
			newLine = true;
			tokens = intoTokens(rawLine);

			switch(machineState){
				case 0:
					if(strCapitalize(rawLine) == "SECTION TEXT"){
						preWriter<< "SECTION TEXT"<<std::endl;
						lines.push_back(origLineNum);
						machineState = 1;
					}
					else if(strCapitalize(tokens[1]) == "EQU"){
						tokens.front().pop_back();
						EQUtable.push_back(tokens.front());
						EQUtable.push_back(tokens.back());
					}
					else{
						std::cout << "Semantic error! Code outside of text section in line no. " << origLineNum << std::endl;
						return 0;
					}
					break;

				case 1:
					if(strCapitalize(tokens[0]) == "IF"){
						machineState = 2;
						EQUfound = false;
						for(iEQU = 0; iEQU < EQUtable.size(); iEQU += 2){
							if(tokens[1] == EQUtable[iEQU]){
								EQUfound = true;
								break;
							}
						}
						break;
					}

					if(tokens.size() > 1){
						if(strCapitalize(tokens[1]) == "MACRO"){
							machineState = 3;
							if(tokens[0].back() == ':')
								tokens[0].pop_back();
							else{
								std::cout << "Syntactic error! Expecting ':' after label in line no. " << origLineNum << std::endl;
								return 0;
							}
							MACROtable.push_back(tokens[0]);
							iMACRO = MACROtable.size();
							//parameters
							break;
						}
					}

					// Iterate through individual tokens in the .asm code
					for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++){
						if(strNotBlank(*it)){

							// Ignore comments
							if(it->front() == ';')
								break;

							// Place spaces between tokens
							if(newLine == true){
								lines.push_back(origLineNum);
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
							}

							MACROfound = false;
							for(iMACRO = 0; iMACRO < MACROtable.size(); iMACRO += 2){
								if(*it == MACROtable[iMACRO]){
									MACROfound = true;
									break;
								}
							}

							if(EQUfound == true)
								preWriter << EQUtable[iEQU+1];
							else if(MACROfound == true)
								preWriter << MACROtable[iMACRO+1];
							else
								preWriter << *it;
						}
					}
					if(newLine == false && MACROfound == false)
						preWriter << std::endl;
					break;

				case 2:
					if(EQUfound == true){
						for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++){
							if(strNotBlank(*it)){

								// Ignore comments
								if(it->front() == ';')
									break;

								// Place spaces inbetween tokens
								if(newLine == true){
									lines.push_back(origLineNum);
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
								}

								if(EQUfound == true)
									preWriter << EQUtable[iEQU+1];
								else
									preWriter << *it;
							}
						}
						if(newLine == false)
							preWriter << std::endl;
					}
					else
						EQUfound = false;
					machineState = 1;
					break;
				case 3:
					if(strCapitalize(tokens[0]) == "END"){
						MACROtable.push_back(macrodef);
						macrodef.clear();
						machineState = 1;
						break;
					}

					MACROfound = false;
					for(iMACRO = 0; iMACRO < MACROtable.size(); iMACRO += 2){
						if(tokens[0] == MACROtable[iMACRO]){
							MACROfound = true;
							break;
						}
					}
					if(MACROfound)
						macrodef.append(MACROtable[iMACRO+1]);
					else{
						for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++){
							if(newLine == true){
								newLine = false;
								lines.push_back(origLineNum);
							}
							else
								macrodef.push_back(' ');
							macrodef.append(*it);
						}
						if(newLine == false){
							macrodef.push_back('\n');
						}
					}
					break;
				default:
					break;
			}
		}
		origLineNum++;
	}
	mapRet = preToMap(preWriter, lines, vecRet);

	return 0;

}

#endif