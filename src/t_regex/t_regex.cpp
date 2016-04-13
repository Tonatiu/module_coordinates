#include "t_regex.h"
//Encuentra coincidencias en input de acuerdo a la expresión regular reg_ex
bool matches(string input, string reg_ex){
    regex_t re;
    //Compilación de la expresión
    if(regcomp(&re, reg_ex.c_str(), REG_EXTENDED) != 0)
        return false;
    //Comparación con la cadena de entrada
    if(regexec(&re, input.c_str(), (size_t)0, NULL, 0) == 0){
        regfree(&re);
        return true;
    }
    //Se libera el compilador para volverlo a usar
    regfree(&re);

    return false;
}
