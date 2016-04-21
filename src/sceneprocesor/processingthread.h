#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include "./image_processor/sceneprocessor.h"
#include "../relations/scenedatarelations.h"
#include "../calculator/transforms/basics_calculations.h"
#include "../calculator/filters/ndvi_filter.h"
#include "../calculator/filters/pm10filter.h"

/*La clase se encarga de administrar a todos los colectores de datos, es un hilo que se ejecutará de forma independiente*/
class ProcessingThread: public QThread
{
public:
    //La clase requiere de una cola de escenas y del path de origen
    ProcessingThread(SceneDataRelations *relations, string origin_path);
    //Devuelve el colector del procesador de escenas indicado por pos
private:
    void run();
    void ScenesMining();
    vector<string> *scene_path_queue;
    SceneProcessor **mining_threads;
    string origin_path;
    SceneDataRelations* relations;
};

#endif // PROCESSINGTHREAD_H
