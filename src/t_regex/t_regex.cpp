#include "./include/t_regex/t_regex.h"

bool matches(string input, string reg_ex){
    regex_t re;

    if(regcomp(&re, reg_ex.c_str(), REG_EXTENDED) != 0)
        return false;

    if(regexec(&re, input.c_str(), (size_t)0, NULL, 0) == 0){
        regfree(&re);
        return true;
    }
    regfree(&re);
    return false;
}
