#include "cutter.h"

InfoObjetivo *CoorsToPixel(BoundingBox target, int img_high, int img_width, BoundingBox container){
   double difLatitudesImagenBound_Up = container.getLeftTop().getLat() - target.getLeftTop().getLat();
   // lo escribo alrevez para obtener un valor positivo
   double difLongitudesImagenBound_Up = target.getLeftTop().getLng() - container.getLeftTop().getLng();

   double difLatitudesImagen = container.getLeftTop().getLat() - target.getRightBottom().getLat();
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



   InfoObjetivo *pixel_pos_target = new InfoObjetivo(Up_x, Up_y, Down_x, Down_y, (Down_x - Up_y), (Down_y - Up_y));

   return pixel_pos_target;
}
