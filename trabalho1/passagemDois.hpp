#include <iostream>
#include <vector>
#include <string>
#include "passagemUm.hpp"

bool verifyOperands(string line){
    string inst = getInst(line);
    int instSize = inst.size();
    size_t pos = line.find(inst);
    string operands = line.substr(pos+instSize);
    vector<string> separatedOp = split(operands, ',');
    if(separatedOp.size() == 1 && separatedOp[0].size() == 0 && INSTRUCTIONS.at(inst) == 14)
        return true;
    if(separatedOp.size() == 1 && separatedOp[0].size() > 1 && INSTRUCTIONS.at(inst) != 14) 
        return true;
    if(separatedOp.size() == 2 && separatedOp[0].size() > 1 && separatedOp[1].size() > 1 && INSTRUCTIONS.at(inst) == 9) 
        return true;

    return false;
}


