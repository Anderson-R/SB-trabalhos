#include <iostream>
#include <vector>
#include <string>
#include "passagemUm.hpp"

//returns number of operands, if wrong number of operands for the instruction in line return -1
uint8_t verifyOperands(string line){
    string inst = getInst(line);
    int instSize = inst.size();
    size_t pos = line.find(inst);
    string operands = line.substr(pos+instSize);
    vector<string> separatedOp = splitPUm(operands, ',');
    if(separatedOp.size() == 1 && separatedOp[0].size() == 0 && INSTRUCTIONS.at(inst) == 14)
        return 0;
    if(separatedOp.size() == 1 && separatedOp[0].size() > 1 && INSTRUCTIONS.at(inst) != 14) 
        return 1;
    if(separatedOp.size() == 2 && separatedOp[0].size() > 1 && separatedOp[1].size() > 1 && INSTRUCTIONS.at(inst) == 9) 
        return 2;

    return -1;
}

bool isNumber(std::string s){
    std::string::iterator it5 = s.begin();
    while (it5 != s.end() && std::isdigit(*it5)) ++it5;
    return (!s.empty() && it5 == s.end());
}

void trimWhiteSpace(std::string& s){
    for(uint8_t i=0; i< s.size(); i++){
        if(s.at(i) == ' ') s.erase(i, 1);
    }
}

bool getOperand(std::string op, int* ret){
    trimWhiteSpace(op);
    std::vector<std::string> sum = splitPUm(op, '+');
    if(sum.size() == 1){
        if(isNumber(sum.at(0))) {
            *ret = stoi(sum.at(0));
            return true;
        }
        else{
            std::map<std::string, int>::iterator it = simbolTable.find(sum.at(0));
            if(it != simbolTable.end()) {
                *ret = it->second;
                std::cout<<it->first<<"=>"<<it->second<<endl;
                return true;
            }
        }
    }
    if(sum.size() == 2){
        std::map<std::string, int>::iterator it = simbolTable.find(sum.at(0));
        if(it != simbolTable.end() && isNumber(sum.at(1))){
            *ret = it->second + stoi(sum.at(1));
            return true;
        } 
    }
    return false;
}

std::vector<int> getOperands(std::string line, uint8_t nOperands){
    std::vector<int> ret;
    std::string inst = getInst(line);
    int instSize = inst.size();
    size_t pos = line.find(inst);
    std::string operand = line.substr(pos+instSize);
    if(nOperands == 1){
        int op;
        if(getOperand(operand, &op)) ret.push_back(op);
        return ret;
    }
    else if(nOperands == 2){
        std::vector<std::string> ops = splitPUm(operand, ',');
        int op1, op2;
        if(getOperand(ops.at(0), &op1) && getOperand(ops.at(1), &op2)){
            ret.push_back(op1);
            ret.push_back(op2);
        }
        return ret;

    }
}

bool operands(string line){
    string inst = getInst(line);
    if(!verifyInst(inst)) return false;
    uint8_t nOperands = verifyOperands(line);
    if(nOperands == -1) return false;


}


