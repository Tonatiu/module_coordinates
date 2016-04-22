#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include "./image_processor/sceneprocessor.h"
#include "../calculator/transforms/basics_calculations.h"
#include "./image_processor/sceneprocessor.h"


/*La clase se encarga de administrar a todos los colectores de datos, es un hilo que se ejecutará de forma independiente*/
class ProcessingThread: public QThread
{
public:
    //La clase requiere de una cola de escenas y del path de origen
    ProcessingThread(SceneDataRelations *relations, string origin_path);
    //Devuelve el colector del procesador de escenas indicado por pos
private:
    void run();
    void CreateProcess();
    SceneDataRelations *relations;
    string origin_path;
};

#endif // PROCESSINGTHREAD_H
