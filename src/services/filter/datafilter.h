#ifndef DATAFILTER_H
#define DATAFILTER_H

#include "../datafinder/mtl_data_collector.h"
#include "../../postgis/postgis/PostgisFunctions.h"
#include "../../postgis/postgis/entity/AreaObjetivo.h"
#include "../../postgis/geographic/BoundingBox.h"
#include "../../relations/scenedatarelations.h"

class DataFilter
{
public:
    DataFilter();
    //Filtra las escenas antes de ser copiadas. Las discrimina por: Son L1, Contienen ciudades
    //Recibe un objeto de relaciones, el path donde se almacenan las escenas
    void AplyFilter(SceneDataRelations* relations, string origin_path);
private:
    //Verifica que la escena esté preprocesada con ortorectificado y corrección geométrica
    bool IsL1Scene(MTL_Data_Collector* collector);
};

#endif // DATAFILTER_H
