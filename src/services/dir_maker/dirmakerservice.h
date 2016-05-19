#ifndef DIRMAKERSERVICE_H
#define DIRMAKERSERVICE_H

#include <stdlib.h>
#include <pwd.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>

using namespace std;

class DirMakerService
{
public:
    DirMakerService();
    string scenes_path;
    string minis_path;
};

#endif // DIRMAKERSERVICE_H
