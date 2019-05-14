#ifndef PASSAGEMUM_HPP
#define PASSAGEMUM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <map>

using namespace std;

//Map of all valid instructions
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
                                {"STOP", 14}
};

vector<string> DIRETIVAS = {{"CONST"}, {"SPACE"}};

//<posCounter, value>
map<int, int> data;

//Map for the simbol table
map<string, int> simbolTable;

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

//verifies if label exists in simbol table. if exists(error) returns 1, if not add label to table and returns 0
int validateLabel(string label, int posCounter){

    if(simbolTable.find(label) != simbolTable.end()) return 1;
    
    simbolTable.insert(pair<string, int>(label, posCounter));
    return 0;
}

//returns the value of the label, if it doesn't exists in simbolTable returns -1
int labelValue(string label){
    map<string,int>::iterator it;
    it = simbolTable.find(label);
    if(it == simbolTable.end()) return -1;
    return it->second;
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

    return it != INSTRUCTIONS.end();
}

bool verifyDir(string dir){
    for(int i=0; i<DIRETIVAS.size(); i++)
        if(dir == DIRETIVAS.at(i)) return true;

    return false;
}

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

int constDir(int posCounter, string line){
    int b = line.find("CONST");
    int value = stoi(line.substr(b+6, 100));
    data.insert(posCounter, value);
    return 1;
}

//Faz a primeira passagem em todo o código fonte pre-processado
void passagemUm(map<string, int> pre, vector<string> program){

    string line, label;
    int posCounter=0, lineCounter=1;
    bool inText=false, inData=false;
    for(int i=0; i<program.size(); i++){
        line = program.at(i);
        
        //section
        if(line == "SECTION TEXT") {
            inText = true;
            inData = false;
            i++;
            line = program.at(i);
        }
        else if(line == "SECTION DATA"){
            inText = false;
            inData = true;
            i++;
            line = program.at(i);
        }
        if(inText){
            //rotulo
            if(containRot(line, &label) == 0){
                if(validateLabel(label, posCounter) == 1)
                    cout<< "\33[1;31m"<< "ERRO semantico na linha: "<< pre.at(line)<< "\033[0m"<< endl;
            };

            //instrução e diretiva
            string inst = getInst(line);
            if(!verifyInst(inst) && !verifyDir(inst)){
                cout<< "\33[1;31m"<< "ERRO sintatico/lexico na linha: "<< pre.at(line)<< "\033[0m"<< endl;
            }
            else{
                if(inst == "COPY") posCounter += 3;
                else if(inst == "STOP") posCounter += 1;
                //else if(inst == "CONST") posCounter += constDir(posCounter, );
                else if(inst == "SPACE"){}
                else posCounter += 2;
            }
            lineCounter++;
        }
    }
}




#endif