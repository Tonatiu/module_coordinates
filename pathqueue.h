#ifndef PATHQUEUE_H
#define PATHQUEUE_H
#include <string>
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <fstream>
//La estructura almacena la información de los paths(En general puede almacenar cualquier string)
typedef struct node{
    char* data;
    struct node* next;
}Node;

class pathQueue
{
public:
    pathQueue();
    //Métodos propios de una cola
    void enqueue(std::string data);
    std::string dequeue();
    int getLength();
    //El método permite leer datos sin necesidad de eliminar el nodo
    std::string getNext();
private:
    Node *makeNode(std::string Data);
    //Estructura para manipular la cola
    typedef struct queue{
        Node* header;
        Node* end;
        //Puntero que recorre la cola de forma circular
        Node* reader;
        //Permite saber el número de elementos en la cola
        int counter;
    }Queue;
    Queue path_queue;
};

#endif // PATHQUEUE_H
