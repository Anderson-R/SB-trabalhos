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

std::string jmp(std::string label){
    return "jmp " + label + "\n";
}

//retorna a linha a ser inserida no arquivo de saída (arquivo.s)
std::string callFunc(int inst, std::string op){
    switch (inst){
        case 1:
            return add(op);
            break;
        case 2:
            return sub(op);
            break;
        case 3:
            return mult(op);
            break;
        case 4:
            return div(op);
            break;
        case 5:
            return div(op);
            break;
        default:
            throw -1;
            break;
    }
}

#endif