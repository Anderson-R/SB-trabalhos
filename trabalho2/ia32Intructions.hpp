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
    return "imul dword [" + op + "]\n";
}

//retorna string da tradução da instrução div
std::string div(std::string op){
    return "idiv dword [" + op + "]\n";
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

//retorna string da tradução da instrução c_output
std::string c_output(std::string mem){
    std::string ret;
    ret.append("push "); ret.append(mem); ret.append("\n");
    ret.append("call escreverChar\n");
    return ret;
}

//retorna string da tradução da instrução c_intput
std::string c_input(std::string mem){
    std::string ret;
    ret.append("push "); ret.append(mem); ret.append("\n");
    ret.append("call lerChar\n");
    return ret;
}

std::string s_output(std::string mem, std::string size){
    std::string ret;
    ret.append("push "); ret.append(size); ret.append("\n");
    ret.append("push "); ret.append(mem); ret.append("\n");
    ret.append("call escreverString\n");
    return ret;
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
        case 15:
            return c_input(op.at(0));
            break;
        case 16:
            return c_output(op.at(0));
            break;
        case 20:
            return s_output(op.at(0), op.at(1));
            break;
        default:
            throw -1;
            break;
    }
}

//retorna string com todas as subrotinas de input e output do assembly inventado
std::string utilFunc(){
    std::string ret;
    ret.append(";Util functions\n");

    //escreverChar
    ret.append("escreverChar:\n");
    ret.append("push ebp\n");
    ret.append("mov ebp, esp\n");
    ret.append("push ebx\n");
    ret.append("push ecx\n");
    ret.append("push edx\n");
    ret.append("mov eax, 4\n");
    ret.append("mov ebx, 1\n");
    ret.append("mov ecx, [ebp+8]\n");
    ret.append("mov edx, 1\n");
    ret.append("int 80h\n");
    ret.append("pop edx\n");
    ret.append("pop ecx\n");
    ret.append("pop ebx\n");
    ret.append("pop ebp\n");
    ret.append("mov ax, 1\n");
    ret.append("ret 4\n\n");

    //lerChar
    ret.append("lerChar:\n");
    ret.append("push ebp\n");
    ret.append("mov ebp, esp\n");
    ret.append("push ebx\n");
    ret.append("push ecx\n");
    ret.append("push edx\n");
    ret.append("mov eax, 3\n");
    ret.append("mov ebx, 0\n");
    ret.append("mov ecx, [ebp+8]\n");
    ret.append("mov edx, 1\n");
    ret.append("int 80h\n");
    ret.append("pop edx\n");
    ret.append("pop ecx\n");
    ret.append("pop ebx\n");
    ret.append("pop ebp\n");
    ret.append("mov ax, 1\n");
    ret.append("ret 4\n\n");


    //escreverString
    ret.append("escreverString:\n");
    ret.append("push ebp\n");
    ret.append("mov ebp, esp\n");
    ret.append("push ebx\n");
    ret.append("push ecx\n");
    ret.append("push edx\n");
    ret.append("mov eax, 4\n");
    ret.append("mov ebx, 1\n");
    ret.append("mov ecx, [ebp+8]\n");
    ret.append("mov edx, [ebp+12]\n");
    ret.append("int 80h\n");
    ret.append("pop edx\n");
    ret.append("pop ecx\n");
    ret.append("pop ebx\n");
    ret.append("pop ebp\n");
    ret.append("mov ax, [ebp+12]\n");
    ret.append("ret 8\n\n");

    //lerString
    ret.append("lerString:\n");
    ret.append("push ebp\n");
    ret.append("mov ebp, esp\n");
    ret.append("push ebx\n");
    ret.append("push ecx\n");
    ret.append("push edx\n");
    ret.append("mov eax, 3\n");
    ret.append("mov ebx, 0\n");
    ret.append("mov ecx, [ebp+8]\n");
    ret.append("mov edx, [ebp+12]\n");
    ret.append("int 80h\n");
    ret.append("push edx\n");
    ret.append("push ecx\n");
    ret.append("call countTillEnter\n");
    ret.append("pop edx\n");
    ret.append("pop ecx\n");
    ret.append("pop ebx\n");
    ret.append("pop ebp\n");
    ret.append("mov ax, 1\n");
    ret.append("ret 8\n\n");


    //conta quantos caracteres foram lidos
    ret.append("countTillEnter: push ebp\n");
    ret.append("mov ebp, esp\n");
    ret.append("push ebx\n");
    ret.append("mov ebx, [ebp+8]\n");
    ret.append("mov eax, -1\n");
    ret.append("compare: cmp eax, [ebp+12]\n");
    ret.append("je end\n");
    ret.append("inc eax\n");
    ret.append("cmp byte [ebx+eax], 0x0A\n");
    ret.append("jne compare\n");
    ret.append("end: pop ebx\n");
    ret.append("pop ebp\n");
    ret.append("ret 8\n\n");
    ret.append("\n\n");
    return ret;
}

#endif