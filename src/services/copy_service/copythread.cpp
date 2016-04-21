#include "copythread.h"

CopyThread::CopyThread(string origin, string destiny, string filename)
{
    this->origin = origin;
    this->destiny = destiny;
    this->filename = filename;
}

void CopyThread::run(){
    string origin;
    //Inicialización del comando para copiar
    string command = "cp -r ";
    //Se concatena el path de origen con el nombre de la escena (la carpeta que la contiene)
    origin = this->origin + this->filename;
    string copy = command + origin + " " + this->destiny;
    //Copia la carpeta de origen al destino especificado
    //Se retorna false si hubo un error
    system(copy.c_str());
}
