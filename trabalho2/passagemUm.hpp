#ifndef PASSAGEMUM_HPP
#define PASSAGEMUM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <map>
#include "passagemZero.hpp"

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
                                {"STOP", 14},
                                {"C_INPUT", 15},
                                {"C_OUTPUT", 16},
                                {"H_INPUT", 17},
                                {"H_OUTPUT", 18},
                                {"S_INPUT", 19},
                                {"S_OUTPUT", 20}
};

vector<string> DIRETIVAS = {{"CONST"}, {"SPACE"}};

//<posCounter, value>
map<int, int> data;

//Map for the simbol table
map<string, int> simbolTable;

//separa a string in em uma ou mais strings usando o token como ponto de separação
vector<string> splitPUm(string in, char token){
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
    bool found = line.find(":") != string::npos;
    vec = splitPUm(line, ':');
    if(vec.size() == 1 || vec.size() == 2){
        if(found) {
            *rot = vec[0];
            return 0;
        }
    }
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
    string lineCopy = line.substr(0, 100);
    int ctnRot = containRot(lineCopy, &rot);
    if(ctnRot == 1)
        inst = splitPUm(lineCopy, ' ')[0];
    else if(ctnRot == 0){
        lineCopy.erase(0, rot.size()+1);
        if(lineCopy.size() > 0 && lineCopy.at(0) == ' ') lineCopy.erase(0, 1);
        inst = splitPUm(lineCopy, ' ')[0];
    }
    else if(ctnRot == 2) throw 1;
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
    it = INSTRUCTIONS.find(strCapitalize(inst));

    return it != INSTRUCTIONS.end();
}

bool verifyDir(string dir){
    for(int i=0; i<DIRETIVAS.size(); i++)
        if(dir == DIRETIVAS.at(i)) return true;

    return false;
}

int constDir(int posCounter, string line){
    string capLine = strCapitalize(line);
    int pos = capLine.find("CONST");
    if(capLine.length() == (pos+5)) return -1;
    int value = stoi(capLine.substr(pos+6, 100), NULL, 0);
    data.insert(pair<int, int>(posCounter, value));
    //if(simbolTable.find(line.substr(0,pos-2)) != simbolTable.end())
        //simbolTable.find(line.substr(0,pos-2))->second = value;
    return 1;
}

int spaceDir(int posCounter, string line){
    string capLine = strCapitalize(line);
    int pos = line.find("SPACE");
    if(pos == string::npos) pos = line.find("space");
    string rot;
    containRot(line, &rot);
    if(line.length() == (pos+5)){
        data.insert(pair<int, int>(posCounter, 0));
        validateLabel(rot, posCounter);
        return 1;
    }
    int value = stoi(line.substr(pos+6, 100));
    for(int i=0; i<value; i++)
        data.insert(pair<int, int>(posCounter+i, 0));
    validateLabel(rot, posCounter);
    return value;
}

//Faz a primeira passagem em todo o código fonte pre-processado
map<string, int> passagemUm(map<string, int> pre, vector<string> program){
    simbolTable.clear();
    string line, label;
    int posCounter=0, lineCounter=1;
    bool inText=false, inData=false;
    for(int i=0; i<program.size(); i++){
        line = program.at(i);
        //section
        if(i == 0 && strCapitalize(line) != "SECTION TEXT")
            cout<< "\33[1;31m"<< "ERRO semantico na linha do aqruivo fonte: "<< pre.at(line)<< " e linha do aquivo pre processado: " << lineCounter << "\033[0m"<< endl;
        if(strCapitalize(line) == "SECTION TEXT") {
            inText = true;
            inData = false;
            i++;
            line = program.at(i);
            lineCounter++;
        }
        else if(strCapitalize(line) == "SECTION DATA"){
            inText = false;
            inData = true;
            i++;
            line = program.at(i);
            lineCounter++;
        }
        

        if((inText || inData) && (line != "")){
            //rotulo
            if(containRot(line, &label) == 0){
                if(validateLabel(label, posCounter) == 1)
                    cout<< "\33[1;31m"<< "ERRO semantico na linha do aqruivo fonte: "<< pre.at(line)<< " e linha do aquivo pre processado: " << lineCounter << "\033[0m"<< endl;
            };
            label.erase();

            //instrução e diretiva
            string inst;
            try{
                inst = getInst(line);
            }catch(int e){
                if(e==1){
                    i++;
                    lineCounter++;
                    line = program.at(i);
                    inst = getInst(line);
                }
            }
            
            if(!verifyInst(inst) && !verifyDir(inst) && !inst.empty()){
                cout<< "\33[1;31m"<< "ERRO lexico na linha do aqruivo fonte: "<< pre.at(line)<< " e linha do aquivo pre processado: " << lineCounter << "\033[0m"<< endl;
            }
            else{
                if(strCapitalize(inst) == "COPY" && inText) posCounter += 3;
                else if(strCapitalize(inst) == "COPY" && inData)
                    cout<< "\33[1;31m"<< "ERRO semantico na linha do aqruivo fonte: "<< pre.at(line)<< " e linha do aquivo pre processado: " << lineCounter << "\033[0m"<< endl;
                else if(strCapitalize(inst) == "STOP" && inText) posCounter++;
                else if(strCapitalize(inst) == "STOP" && inData)
                    cout<< "\33[1;31m"<< "ERRO semantico na linha do aqruivo fonte: "<< pre.at(line)<< " e linha do aquivo pre processado" << lineCounter << "\033[0m"<< endl;
                else if(strCapitalize(inst) == "CONST" && inData) {
                    if(constDir(posCounter, line) == -1)
                        cout<< "\33[1;31m"<< "ERRO sintatico na linha do aqruivo fonte: "<< pre.at(line)<< " e linha do aquivo pre processado: " << lineCounter << "\033[0m"<< endl;
                    else
                        posCounter++;
                }
                else if(strCapitalize(inst) == "CONST" && inText)
                    cout<< "\33[1;31m"<< "ERRO semantico na linha do aqruivo fonte: "<< pre.at(line)<< " e linha do aquivo pre processado: " << lineCounter << "\033[0m"<< endl;
                else if(strCapitalize(inst) == "SPACE" && inData) posCounter += spaceDir(posCounter, line);
                else if(strCapitalize(inst) == "SPACE" && inText)
                    cout<< "\33[1;31m"<< "ERRO semantico na linha do aqruivo fonte: "<< pre.at(line)<< " e linha do aquivo pre processado: " << lineCounter << "\033[0m"<< endl;
                else if(inText) posCounter += 2;
            }
        }

        lineCounter++;
    }

    return simbolTable;
}




#endif