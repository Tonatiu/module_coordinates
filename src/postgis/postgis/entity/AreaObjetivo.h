#include <string>

#include "../../geographic/GeoPolygon.h"
#include "../../geographic/BoundingBox.h"

#ifndef _POSTGIS_ENTITY_AREA_OBJETIVO_H_
    
    #define _POSTGIS_ENTITY_AREA_OBJETIVO_H_
    
    class AreaObjetivo{
        
        GeoPolygon geometry;
        
        std::string id;
        std::string dateAcquired;
        std::string sceneCenterTime;
        
        /**
         * properties
         * */
        float porcentajeContaminacion;
        float porcentajeVegetacion;
        float calidad;
        float nubosidad;
        
        std::string entidad;
        std::string municipio;
        std::string localidad;
        
        public:
            void setId(std::string id){
                this->id = id;
            }
            void setDateAcquired(std::string dateAcquired){
                this->dateAcquired = dateAcquired;
            }
            void setSceneCenterTime(std::string sceneCenterTime){
                this->sceneCenterTime = sceneCenterTime;
            }
            void setPorcentajeContaminacion(float porcentajeContaminacion){
                this->porcentajeContaminacion = porcentajeContaminacion;
            }
            void setporcentajeVegetacion(float porcentajeVegetacion){
                this->porcentajeVegetacion = porcentajeVegetacion;
            }
            void setCalidad(float calidad){
                this->calidad = calidad;
            }
            void setNubosidad(float nubosidad){
                this->nubosidad = nubosidad;
            }
            void setGeometry(GeoPolygon geometry){
                this->geometry = geometry;
            }
            void setEntidad(std::string entidad){
                this->entidad = entidad;
            }
            void setMunicipio(std::string municipio){
                this->municipio = municipio;
            }
            void setLocalidad(std::string localidad){
                this->localidad = localidad;
            }
            

            float getPorcentajeContaminacion(){
                return porcentajeContaminacion;
            }
            float getPorcentajeVegetacion(){
                return porcentajeVegetacion;
            }
            float getCalidad(){
                return calidad;
            }
            float getNubosidad(){
                return nubosidad;
            }
            GeoPolygon getGeometry(){
                return geometry;
            }
            std::string getEntidad(){
                return entidad;
            }
            std::string getMunicipio(){
                return municipio;
            }
            std::string getLocalidad(){
                return localidad;
            }
            std::string getId(){
                return id;
            }
            std::string getDateAcquired(){
                return dateAcquired;
            }
            std::string getSceneCenterTime(){
                return sceneCenterTime;
            }
            BoundingBox getBounds(){
                return geometry.getBounds();
            }
    };
    
#endif