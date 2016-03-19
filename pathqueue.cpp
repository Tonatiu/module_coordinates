#include "pathqueue.h"
//Constructor de la clase. Inicializa todos los punteros y el contador
pathQueue::pathQueue()
{
    this->path_queue.header = NULL;
    this->path_queue.end = NULL;
    this->path_queue.reader = NULL;
    this->path_queue.counter = 0;
}
//Genera un nodo con su respectiva información
Node* pathQueue::makeNode(std::string Data){
    Node* newNode =(Node*) malloc(sizeof(Node));
    //Verificación de memoria ram
    if(newNode == NULL){
        std::cout << "Error!! memory out\n";
        exit(0);
    }
    //Copiado de la información de interés
    newNode->data = (char*) malloc(Data.length());
    strcpy(newNode->data, Data.c_str());
    newNode->next = NULL;
    //Data = NULL;
    return newNode;
}
//Permite agregar un nodo a la cola
void pathQueue::enqueue(std::string data){
    Node* newNode = this->makeNode(data);
    //Acciones si la cola está vacía
    if(this->path_queue.header == NULL){
        this->path_queue.header = newNode;
        this->path_queue.end = newNode;
        this->path_queue.reader = newNode;
    }
    //Acciónes si la cola no estpa vacía
    else{
        this->path_queue.end->next = newNode;
        this->path_queue.end = newNode;
    }
    //Incrementa el numero de elementos en uno
    this->path_queue.counter++;
}
//Permite sacar el primer nodo de la cola
std::string pathQueue::dequeue(){
    std::string to_return;
    Node* aux;
    //Recuperación de la información a regresar
    to_return = this->path_queue.header->data;
    //Eliminación del nodo
    aux = this->path_queue.header;
    this->path_queue.header = aux->next;
    this->path_queue.reader = aux->next;
    aux->next = NULL;
    //Decremento del número de elementos
    this->path_queue.counter--;

    return to_return;
}
//Permite conocer el número actual de elementos en la cola
int pathQueue::getLength(){
    return this->path_queue.counter;
}
//Permite leer el contenido del siguiente nodo sin expulsarlo de la cola
std::string pathQueue::getNext(){
    std::string to_return;
    //Verifica que la cola no esté vacía
    if(this->path_queue.counter <= 0)
        return "_empty_";
    //Recuperación de la información
    to_return = this->path_queue.reader->data;
    //Verifica que el siguiente nodo no sea nulo, si es así regresa al inicio de la cola
    if(this->path_queue.reader->next != NULL)
        this->path_queue.reader = this->path_queue.reader->next;
    else
        this->path_queue.reader = this->path_queue.header;

    return to_return;

}
