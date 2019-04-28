#ifndef PASSAGEMUM_HPP
#define PASSAGEMUM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <map>

using namespace std;

map<string, int> INSTRUCTIONS = {{"ADD", 1},
                                {"SUB", 2},
                                {"MULT", 3},
                                {"DIV", 4},
                                {"JMP", 5},
                                {"JMPN", 6},
                                {"JMPP", 7},
                                {"JMPZ", 8},
                                {"COPY", 9},
                                {"LOAD", 10},
                                {"STORE", 11},
                                {"INPUT", 12},
                                {"OUTPUT", 13},
                                {"STOP", 14}};

//separa a string in em uma ou mais strings usando o token como ponto de separação
vector<string> split(string in, char token){
    vector<string> vec;
    int j = 0;
    vec.push_back("");
    for(int i = 0; i < in.length(); i++){
        if(in[i] == token){ 
            j++;
            vec.push_back("");
        }
        else vec[j].append(in, i, 1);
    }
    return vec;
}

//caso haja rotulo o salva em rot e retorna 0, caso contrario retorna 1, erro retorna 2
int containRot(string line, string *rot){
    vector<string> vec;
    vec = split(line, ':');
    if(vec.size() == 1 && vec[0] != "") return 1;

    if(vec.size() == 2 && vec[0] != "" && vec[1] != ""){
        if(vec[0].back() == ' ') vec[0].pop_back();    
        *rot = vec[0];
        return 0;
    }
    return 2;
}

//retorna a instrução da linha
string getInst(string line){
    string inst;
    string rot;
    int ctnRot = containRot(line, &rot);
    if(ctnRot == 1)
        inst = split(line, ' ')[0];
    else if(ctnRot == 0){
        line.erase(0, rot.size()+1);
        if(line.at(0) == ' ') line.erase(0, 1);
        inst = split(line, ' ')[0];
    }
    locale loc;
    for(int i=0; i< inst.length(); i++){
        inst[i] = toupper(inst[i], loc);
    }
    return inst;
}

//verifica se a instrução inst existe
bool verifyInst(string inst){
    locale loc;
    for(int i=0; i< inst.length(); i++){
        inst[i] = toupper(inst[i], loc);
    }
    map<string,int>::iterator it;
    it = INSTRUCTIONS.find(inst);
    if(it != INSTRUCTIONS.end()) return true;

    return false;
}





#endif