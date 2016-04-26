#include "cutter.h"
/*Esta es la función de LUIS, para localizar los pixeles de un área objetivo*/
InfoObjetivo *CoorsToPixel(BoundingBox targetAux, int img_high, int img_width, BoundingBox container){
    // tomamos los valores actuales del área objetivo
   double UL_Lat = targetAux.getLeftTop().getLat();
   double UL_Long = targetAux.getLeftTop().getLng();
   double DR_Lat = targetAux.getRightBottom().getLat();
   double DR_Long = targetAux.getRightBottom().getLng();
   // los modificaremos de salirse de rango
   if(targetAux.getLeftTop().getLat() > container.getLeftTop().getLat())
      UL_Lat = container.getLeftTop().getLat();
   if(targetAux.getLeftTop().getLng() < container.getLeftTop().getLng()) // aqui es el simbolo menor debido a los signos de las longitudes
      UL_Long = container.getLeftTop().getLng();
   if(targetAux.getRightBottom().getLat() < container.getRightBottom().getLat())
      DR_Lat = container.getRightBottom().getLat();
   if(targetAux.getRightBottom().getLng() > container.getRightBottom().getLng())
      DR_Long = container.getRightBottom().getLng();
   // asignamos nuevamente
   Coords Up_Left2(UL_Lat, UL_Long);
   Coords Down_Right2(DR_Lat, DR_Long);
   BoundingBox target;
   target.setLeftTop(Up_Left2);
   target.setRightBottom(Down_Right2);

   double difLatitudesImagenBound_Up = container.getLeftTop().getLat() - target.getLeftTop().getLat();
   // lo escribo alrevez para obtener un valor positivo
   double difLongitudesImagenBound_Up = target.getLeftTop().getLng() - container.getLeftTop().getLng();

   double difLatitudesImagen = container.getLeftTop().getLat() - container.getRightBottom().getLat();
   // lo escribo alrevez para obtener un valor positivo
   double difLongitudesImagen = container.getRightBottom().getLng() - container.getLeftTop().getLng();

   double relacionLats = difLatitudesImagenBound_Up / difLatitudesImagen;
   double relacionLongs = difLongitudesImagenBound_Up / difLongitudesImagen;

   int Up_y = img_high * relacionLats;
   int Up_x = img_width * relacionLongs;

   double difLatitudesImagenBound_Down = container.getLeftTop().getLat() - target.getRightBottom().getLat();
   // lo escribo alrevez para obtener un valor positivo
   double difLongitudesImagenBound_Down = target.getRightBottom().getLng() - container.getLeftTop().getLng();

   relacionLats = difLatitudesImagenBound_Down / difLatitudesImagen;
   relacionLongs = difLongitudesImagenBound_Down / difLongitudesImagen;

   int Down_y = img_high * relacionLats;
   int Down_x = img_width * relacionLongs;

   InfoObjetivo *pixel_pos_target = new InfoObjetivo(
               Up_x,
               Up_y,
               Down_x,
               Down_y,
               (Down_x - Up_x),
               (Down_y - Up_y)
               );

   return pixel_pos_target;
}
