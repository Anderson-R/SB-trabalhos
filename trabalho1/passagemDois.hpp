#ifndef PASSAGEMDOIS_HPP
#define PASSAGEMDOIS_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
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
                return true;
            }
            else throw 1;
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

std::vector<int> getOperands(std::string line){
    std::vector<int> ret;
    std::string inst = getInst(line);
    int instSize = inst.size();
    size_t pos = line.find(inst);
    std::string operand = line.substr(pos+instSize);
    trimWhiteSpace(operand);
    if(operand.size() == 0) throw 2;
    int nOperands = splitPUm(operand, ',').size();
    if(nOperands == 1){
        int op=-1;
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
    return ret;
}


void passagemDois(std::map<std::string, int> preFile, std::vector<std::string> program, std::string fileName){
    std::string line;
    std::ofstream obj;
    obj.open(fileName, std::fstream::out | std::fstream::trunc);
    for(int i=0; i<program.size(); i++){
        line = program.at(i);
        if(line == "SECTION TEXT" || line == "SECTION DATA"){
            i++;
            line = program.at(i);
        }
        std::string inst = getInst(line);
        if(verifyInst(inst)){
            std::vector<int> op;
            int opCode = INSTRUCTIONS.at(strCapitalize(inst));
            if(opCode != 14){
                try{
                    op = getOperands(strCapitalize(line));
                }catch(int e){
                    if(e == 1) 
                        cout<< "\33[1;31m"<< "ERRO8 semantico na linha do arquivo fonte: "<< preFile.at(line)<< " e linha do arquivo pre processado: "<< i+1 <<"\033[0m" << endl;
                    else if(e == 2)
                        cout<< "\33[1;31m"<< "ERRO9 lexico na linha do arquivo fonte: "<< preFile.at(line)<< " e linha do arquivo pre processado: "<< i+1 <<"\033[0m" << endl;
                };
                if(op.size() == 1) obj << opCode << " " << op.at(0) << " ";  
                else if(op.size() == 2 && opCode == 9) obj << opCode << " " << op.at(0) << " " << op.at(1) << " ";
                //else cout<< "\33[1;31m"<< "ERRO7 lexico na linha do arquivo fonte: "<< preFile.at(line)<< " e linha do arquivo pre processado: "<< i+1 <<"\033[0m" << endl;
            }
            else obj << opCode << " ";
            op.clear();
        }
        else if(verifyDir(strCapitalize(inst))){
            string rot;  
            containRot(line, &rot);
            obj << data.at(simbolTable.at(rot)) << " ";
        }
    }


    obj.close();
}


#endif