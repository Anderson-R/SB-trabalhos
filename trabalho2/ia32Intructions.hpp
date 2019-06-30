#ifndef IA32INSTRUCTIONS_HPP
#define IA32INSTRUCTIONS_HPP

#include <iostream>
#include <string>

//retorna string da tradução da instrução add
std::string add(std::string op){
    return "add eax, [" + op + "]\n";
}

//retorna string da tradução da instrução sub
std::string sub(std::string op){
    return "sub eax, [" + op + "]\n";
}

//retorna string da tradução da instrução mult
std::string mult(std::string op){
    return "imul [" + op + "]\n";
}

//retorna string da tradução da instrução div
std::string div(std::string op){
    return "idiv [" + op + "]\n";
}

//retorna string da tradução da instrução jmp
std::string jmp(std::string label){
    return "jmp " + label + "\n";
}

//retorna string da tradução da instrução jmpn
std::string jmpn(std::string label){
    std::string ret;
    ret.append("cmp eax, 0\n");
    ret.append("jl ");
    ret.append(label);
    ret.append("\n");
    return ret;
}

//retorna string da tradução da instrução jmpp
std::string jmpp(std::string label){
    std::string ret;
    ret.append("cmp eax, 0\n");
    ret.append("jg ");
    ret.append(label);
    ret.append("\n");
    return ret;
}

//retorna string da tradução da instrução jmpz
std::string jmpz(std::string label){
    std::string ret;
    ret.append("cmp eax, 0\n");
    ret.append("jz ");
    ret.append(label);
    ret.append("\n");
    return ret;
}

//retorna string da tradução da instrução copy
std::string copy(std::string op1, std::string op2){
    std::string ret;
    ret.append("push eax\n");
    ret.append("mov eax, ["); ret.append(op1); ret.append(+"]\n");
    ret.append("mov dword ["); ret.append(op2); ret.append("], eax\n");
    ret.append("pop eax\n");
    return ret;
}

//retorna string da tradução da instrução load
std::string load(std::string mem){
    return "mov eax, [" + mem + "]\n";
}

//retorna string da tradução da instrução store
std::string store(std::string mem){
    return "mov dword [" + mem + "], eax\n";
}

//retorna string da tradução da instrução stop
std::string stop(){
    std::string ret;
    ret.append("mov eax, 1\n");
    ret.append("mov ebx, 0\n");
    ret.append("int 80h\n");
    return ret;
}

//retorna string da tradução da instrução stop
std::string c_output(std::string mem){
    std::string ret;
    ret.append("push "); ret.append(mem); ret.append("\n");
    ret.append("call escreverChar");
}

//retorna a linha a ser inserida no arquivo de saída (arquivo.s)
std::string callFunc(int inst, std::vector<std::string> op = {""}){
    switch (inst){
        case 1:
            return add(op.at(0));
            break;
        case 2:
            return sub(op.at(0));
            break;
        case 3:
            return mult(op.at(0));
            break;
        case 4:
            return div(op.at(0));
            break;
        case 5:
            return jmp(op.at(0));
            break;
        case 6:
            return jmpn(op.at(0));
            break;
        case 7:
            return jmpp(op.at(0));
            break;
        case 8:
            return jmpz(op.at(0));
            break;
        case 9:
            return copy(op.at(0), op.at(1));
            break;
        case 10:
            return load(op.at(0));
            break;
        case 11:
            return store(op.at(0));
            break;
        case 14:
            return stop();
            break;
        case 16:
            return c_output(op.at(0));
            break;
        default:
            throw -1;
            break;
    }
}

//retorna string com todas as subrotinas de input e output do assembly inventado
std::string utilFunc(){
    std::string ret;
    //escreverChar
    ret.append("escreverChar:\n");
    ret.append("push ebp\n");
    ret.append("mov ax, 1\n");
    ret.append("mov ebp, esp\n");
    ret.append("mov eax, 4\n");
    ret.append("mov ebx, 1\n");
    ret.append("mov ecx, [ebp+8]\n");
    ret.append("mov edx, 1\n");
    ret.append("int 80h\n");
    ret.append("pop ebp\n");
    ret.append("ret 4\n");

}

#endif