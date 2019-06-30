#ifndef IA32DATA_HPP
#define IA32DATA_HPP

#include <iostream>
#include <string>
#include <vector>

std::string dataNotInit(std::string var, int size){
    std::string val;
    for(int i=0; i<size-1; i++) val.append("0, ");
    val.append("0");
    return var + " dd " + val + "\n";
}

std::string dataInit(std::string var, int val){
    return var + " dd " + std::to_string(val) + "\n";
}

#endif