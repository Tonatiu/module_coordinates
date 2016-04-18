#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include "../services/queue/pathqueue.h"
#include "./image_processor/sceneprocessor.h"

/*La clase se encarga de administrar a todos los colectores de datos, es un hilo que se ejecutará de forma independiente*/
class ProcessingThread: public QThread
{
public:
    //La clase requiere de una cola de escenas y del path de origen
    ProcessingThread(pathQueue *scene_path_queue, string origin_path);
    //Devuelve el colector del procesador de escenas indicado por pos
    MTL_Data_Collector *GetCollectorFrom(int pos);
private:
    void run();
    void ScenesMining();
    pathQueue *scene_path_queue;
    SceneProcessor **mining_threads;
    string origin_path;
};

#endif // PROCESSINGTHREAD_H
