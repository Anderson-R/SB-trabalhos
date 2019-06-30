#ifndef IA32INSTRUCTIONS_HPP
#define IA32INSTRUCTIONS_HPP

#include <iostream>
#include <string>

std::string add(std::string op){
    return "add eax, [" + op + "]\n";
}

std::string sub(std::string op){
    return "sub eax, [" + op + "]\n";
}

std::string mult(std::string op){
    return "imul [" + op + "]\n";
}

std::string div(std::string op){
    return "idiv [" + op + "]\n";
}

#endif