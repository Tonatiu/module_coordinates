#include "datafilter.h"

DataFilter::DataFilter()
{
}

void DataFilter::AplyFilter(SceneDataRelations *relations, string origin_path){
    PostgisFunctions functions;
    int num_scenes = relations->GetFilesCount();
    MTL_Data_Collector *collector;
    vector<AreaObjetivo> results;

    for(int i = 0; i < num_scenes; i++){
        collector = new MTL_Data_Collector();
        //Se genera la ruta hacia el MTL
        string scene_name = relations->GetFileNameByID(i);
        string MTL_path = origin_path + scene_name + "/" + scene_name + "_MTL.txt";
        //Apertura del MTL
        if(collector->OpenMTLFile(MTL_path)){
            //Obtención de datos
            collector->ObtainData();
            //Creación de bounds para búsqueda
            BoundingBox bounds(collector->GetCoors());
            //Búsqueda en base de datos para obtener coincidencias
            results = functions.getAreasObjetivo(bounds);
            //Verificación de que la escena cumpla con los requisitos
            if(!IsL1Scene(collector) || results.empty()){
                cout << scene_name << " rejected\n";
                relations->EraseFileByID(i);
                collector = NULL;
                num_scenes--;
                i--;
            }else{
                cout<<"Accepted " << results.size() <<"\n";
                relations->PushCollector(*collector);
                relations->PushSceneTargets(results);
            }
        }
        else{
            cout << scene_name << " rejected\n";
            relations->EraseFileByID(i);
            collector = NULL;
            num_scenes--;
            i--;
        }
    }
    collector = NULL;
}

bool DataFilter::IsL1Scene(MTL_Data_Collector *collector){
    return matches(collector->GetDataType(), "(L1)([A-Z]*)");
}

