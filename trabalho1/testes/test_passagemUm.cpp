#include <iostream>
#include "../passagemUm.hpp"
#include <vector>
#include <string>

using namespace std;

int main(){
    vector<string> vec;
    //-split-test 1
    vec.push_back("string qualquer");
    if(vec != split("string qualquer", ':') )
        cout<<"\33[1;31m Split-Test 1 FAILED"<<endl;
    else
        cout<<"\33[1;32m Split-Test 1 SUCCEEDED"<<endl;
    vec.clear();
    
    //-Split-test 2
    vec.push_back("string ");
    vec.push_back(" qualquer");
    if(vec != split("string : qualquer", ':') )
        cout<<"\33[1;31m Split-Test 2 FAILED"<<endl;
    else
        cout<<"\33[1;32m Split-Test 2 SUCCEEDED"<<endl;
    vec.clear();

    //-Split-test 3
    vec.push_back("");
    if(vec != split("", ':') )
        cout<<"\33[1;31m Split-Test 3 FAILED"<<endl;
    else
        cout<<"\33[1;32m Split-Test 3 SUCCEEDED"<<endl;
    vec.clear();

    string rot = "";
    //-containRot-test 1
    if(containRot("string : qualquer", &rot) == 0 && rot == "string")
        cout<<"\33[1;32m containRot-Test 1 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m containRot-Test 1 FAILED"<<endl;

    //-containRot-test 2
    rot = "";
    if(containRot("string qualquer", &rot) == 1 && rot == "")
        cout<<"\33[1;32m containRot-Test 2 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m containRot-Test 2 FAILED"<<endl;

    //-getInst-test 1
    if(getInst("COPY N2, N3") == "COPY" )
        cout<<"\33[1;32m getInst-Test 1 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m getInst-Test 1 FAILED"<<endl;

    //-getInst-test 2
    if(getInst("label: coPy N2, N3") == "COPY" )
        cout<<"\33[1;32m getInst-Test 2 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m getInst-Test 2 FAILED"<<endl;

    //-verifyInst-test 1
    if(!verifyInst("Addd"))
        cout<<"\33[1;32m verifyInst-Test 1 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyInst-Test 1 FAILED"<<endl;
    
    //-verifyInst-test 2
    if(verifyInst("Add"))
        cout<<"\33[1;32m verifyInst-Test 2 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyInst-Test 2 FAILED"<<endl;

    //-validateLabel-test 1
    if(validateLabel("l1", 7) == 0 && simbolTable.at("l1") == 7)
        cout<<"\33[1;32m validateLabel-Test 1 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m validateLabel-Test 1 FAILED"<<endl;

    //-validateLabel-test 2
    if(validateLabel("l1", 7) == 1)
        cout<<"\33[1;32m validateLabel-Test 2 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m validateLabel-Test 2 FAILED"<<endl;

    //-labelValue-test 1
    if(labelValue("l1") == 7)
        cout<<"\33[1;32m labelValue-Test 1 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m labelValue-Test 1 FAILED"<<endl;

    //-labelValue-test 2
    if(labelValue("l2") == -1)
        cout<<"\33[1;32m labelValue-Test 2 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m labelValue-Test 2 FAILED"<<endl;

    //-verifyOperands-test 1
    if(verifyOperands("STOP") == true)
        cout<<"\33[1;32m verifyOperands-Test 1 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 1 FAILED"<<endl;

    //-verifyOperands-test 2
    if(verifyOperands("STOP l1") == false)
        cout<<"\33[1;32m verifyOperands-Test 2 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 2 FAILED"<<endl;

    //-verifyOperands-test 3
    if(verifyOperands("COPY l1,") == false)
        cout<<"\33[1;32m verifyOperands-Test 3 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 3 FAILED"<<endl;

    //-verifyOperands-test 4
    if(verifyOperands("COPY l1, l2") == true)
        cout<<"\33[1;32m verifyOperands-Test 4 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 4 FAILED"<<endl;

    //-verifyOperands-test 5
    if(verifyOperands("ADD l1, l2") == false)
        cout<<"\33[1;32m verifyOperands-Test 5 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 5 FAILED"<<endl;

    //-verifyOperands-test 6
    if(verifyOperands("ADD l1") == true)
        cout<<"\33[1;32m verifyOperands-Test 6 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 6 FAILED"<<endl;

    //-verifyOperands-test 7
    if(verifyOperands("ADD l1, ") == false)
        cout<<"\33[1;32m verifyOperands-Test 7 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 7 FAILED"<<endl;

    //-verifyOperands-test 8
    if(verifyOperands("COPY l1, ") == false)
        cout<<"\33[1;32m verifyOperands-Test 8 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 8 FAILED"<<endl;

    //-verifyOperands-test 9
    if(verifyOperands("COPY , l1") == false)
        cout<<"\33[1;32m verifyOperands-Test 9 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 9 FAILED"<<endl;

    //-verifyOperands-test 10
    if(verifyOperands("L1: DIV DOIS") == true)
        cout<<"\33[1;32m verifyOperands-Test 10 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyOperands-Test 10 FAILED"<<endl;

    //-verifyDir-test 1
    if(verifyDir("CONST") == true)
        cout<<"\33[1;32m verifyDir-Test 1 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyDir-Test 1 FAILED"<<endl;

    //-verifyDir-test 2
    if(verifyDir("SPACE") == true)
        cout<<"\33[1;32m verifyDir-Test 2 SUCCEEDED"<<endl;
    else
        cout<<"\33[1;31m verifyDir-Test 2 FAILED"<<endl;

    return 0;
}