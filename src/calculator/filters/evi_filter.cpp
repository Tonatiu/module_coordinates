#include "evi_filter.h"

EVI_Filter::EVI_Filter(MTL_Data_Collector *collector): Filter(collector)
{
}
//Para calcular el promedio se requiere de la entrada de dos filas, una perteneciente al rojo visible (vis) la otra al NIR (Near Infra Red)
//Para landsat de 4 hasta 7 las bandas son la 3 y 4, para landsat 8 es la 4 y 5
/*float EVI_Filter::EVI_Vector_Prom(vector<uchar> vis_row, vector<uchar> nir_row){
    int row_size = vis_row.size();
    float prom = 0.0;
    float EVI;
    //Se calcula el promedio de EVI en una fila de la escena.
    for(int i = 0; i < row_size; i++){
        //Se calcula el EVI de un pixel
        EVI = this->EVI_Calc(vis_row[i], nir_row[i]);
        //Cálculo del promedio. Se divide antes para no lidiar con números muy grandes
        prom += EVI / row_size;
    }

    return prom;
}*/

float EVI_Filter::EVI_Calc(uchar vis_pixel, uchar nir_pixel, uchar blue_pixel){
    float vis_refl;
    float NIR_refl;
	float blue_refl;
    //En caso de ser escena del landsat 8
    if(this->isL8){
        vis_refl = this->basicCalcs->RefelctanceCalc(vis_pixel, (RED_BAND + 1));
        NIR_refl = this->basicCalcs->RefelctanceCalc(nir_pixel, (NIR_BAND + 1));
		blue_refl = this->basicCalcs->RefelctanceCalc(blue_pixel, (BLU_BAND + 1));
    }
    //en caso de ser escena de landsat < 8
    else{
        vis_refl = this->basicCalcs->RefelctanceCalc(vis_pixel, (RED_BAND));
        NIR_refl = this->basicCalcs->RefelctanceCalc(nir_pixel, (NIR_BAND));
		blue_refl = this->basicCalcs->RefelctanceCalc(blue_pixel, (BLU_BAND));
    }

    return 2.5 * ((NIR_refl - vis_refl)/(1 + NIR_refl + 6 * vis_refl - 7.2 * blue_refl));
}
