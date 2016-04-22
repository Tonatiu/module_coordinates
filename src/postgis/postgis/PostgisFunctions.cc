#include "PostgisFunctions.h"


/**
 * @bounds -> esquinas de la escena satelital
 * 
 * @return
 *  Objeto Vector con todas las Areas Objetivo contenidas en la escena satelital.
 * */
vector<AreaObjetivo> PostgisFunctions::getAreasObjetivo(BoundingBox bounds){
    vector<AreaObjetivo> results;
    
    try{
        
        /* Creamos la conexión  */
        connection C( POSTGIS_QUERY_CONNECTION );
        
        if (C.is_open()) {
            
            /*    Creamos consulta  */
            string sql = "SELECT ST_AsText(ST_Envelope(ST_Intersection(";
            
            //bounds
            sql.append("ST_GeomFromText('");
            sql.append(bounds.getPolygonWKT());
            sql.append("',4326)");
            
            //cierre
            sql.append(",geom))),cve_ent,cve_mun,nom_loc FROM municipios ");
            
            //condicion
            sql.append("WHERE NOT ST_isEmpty(ST_Intersection(");
            
            sql.append("ST_GeomFromText('");
            sql.append(bounds.getPolygonWKT());
            sql.append("',4326), geom))");
            /*    Creamos un objeto non-transactional    */
            nontransaction N(C);
            
            /*    Ejecutamos el query     */
            result R( N.exec(sql) );
            
            
            /*    Manejo de resultado    */
            /*    El valor del registro dentro del for esta en el array c */
            for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                GeoPolygon polygon(c[0].as<string>(), "4326");
                polygon.setBounds( parseBoundingBox(polygon.getGeomText()) );
                
                AreaObjetivo areaObjetivo;
                areaObjetivo.setGeometry(polygon);
                areaObjetivo.setEntidad(c[1].as<string>());
                areaObjetivo.setMunicipio(c[2].as<string>());
                areaObjetivo.setLocalidad(c[3].as<string>());
                
                results.push_back(areaObjetivo);
            }
            
            /*      Reducimos el tamaño del vector      */
            //results.shrink_to_fit();
            
            //Cerramos la conexión
            C.disconnect();
        } else {
            //No se creo la conexión
            cout << "Error en la conexión" << endl;
        }
        
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
    }
    
    return results;
}



/**
 * @table_name -> nombre de la tabla.
 * @geometry_column -> nombre de la columna geografica.
 * 
 * @return
 *  Regresa el srid de la tabla especificada
 * */
string PostgisFunctions::getTableSrid(string table_name, string geometry_column){
    string srid;
    try{
        
        /* Creamos la conexión  */
        connection C( POSTGIS_QUERY_CONNECTION );
        
        if (C.is_open()) {
            
            /*    Creamos consulta  */
            string sql = "SELECT Find_SRID('public',";
            
            sql.append("'");
            sql.append(table_name);
            sql.append("'");
            
            sql.append(",");
            
            sql.append("'");
            sql.append(geometry_column);
            sql.append("'");
            
            
            //cierre de la consulta
            sql.append(")");
            
            /*    Creamos un objeto non-transactional    */
            nontransaction N(C);
            
            /*    Ejecutamos el query     */
            result R( N.exec(sql) );
            
            
            /*    Manejo de resultado    */
            /*    El valor del registro dentro del for esta en el array c */
            
            if( R.size() > 0 ){
                srid = R[0][0].as<string>();
            }
            
        
            //Cerramos la conexión
            C.disconnect();
        } else {
            //No se creo la conexión
            cout << "Error en la conexión" << endl;
        }
        
    }catch (const std::exception &e){
        cerr << e.what() << endl;
    }
    
    return srid;
}



/*
* @p1 -> esquina superior izquierda
* @p2 -> esquina inferior derecha
* 
* @return
*   Regresa un GeoPolygon que contiene a los dos puntos.
*   Si el SRID del objeto es -1 significa que hubo un error.
*/
GeoPolygon PostgisFunctions::getBounds(GeoPoint p1, GeoPoint p2){
    GeoPolygon g_polygon;
    
    try{
        
        /* Creamos la conexión  */
        connection C( POSTGIS_QUERY_CONNECTION );
        
        if (C.is_open()) {
            
            /*    Creamos consulta  */
            string sql = "SELECT ST_AsText( ST_Envelope( ST_Collect(";
            
            //p1
            sql.append("ST_GeomFromText('");
            sql.append(p1.asText());
            sql.append("')");
            
            sql.append(",");
            
            //p2
            sql.append("ST_GeomFromText('");
            sql.append(p2.asText());
            sql.append("')");
            
            //cierre
            sql.append(")))");
            
            /*    Creamos un objeto non-transactional    */
            nontransaction N(C);
            
            /*    Ejecutamos el query     */
            result R( N.exec(sql) );
            
            
            /*    Manejo de resultado    */
            /*    El valor del registro dentro del for esta en el array c */
            if( R.size() > 0 ){
                g_polygon.setGeomText(R[0][0].as<string>());
                g_polygon.setSrid(p1.getSrid());
            }
        
            //Cerramos la conexión
            C.disconnect();
        } else {
            //No se creo la conexión
            cout << "Error en la conexión" << endl;
        }
        
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
    }
    
    return g_polygon;
}


/**
 * Persistencia de la información del areaObjetivo
 * */
bool PostgisFunctions::insertAreaObjetivo(AreaObjetivo areaObjetivo){
    
    try{
        mutex.lock();
            /* Creamos la conexión  */
            connection C( POSTGIS_QUERY_CONNECTION );

            if( !C.is_open() ){
                return false;
            }

            string sql = "INSERT INTO transition(data,the_geom) VALUES ('";
            sql.append("{");

            sql.append( propertyToString("entidad", areaObjetivo.getEntidad()));
            sql.append( propertyToString("municipio", areaObjetivo.getMunicipio()));
            sql.append( propertyToString("localidad", areaObjetivo.getLocalidad()));

            sql.append( propertyToString("calidad", areaObjetivo.getCalidad()));
            sql.append( propertyToString("nubosidad", areaObjetivo.getNubosidad()));
            sql.append( propertyToString("vegetacion", areaObjetivo.getPorcentajeVegetacion()));
            sql.append( propertyToString("contaminacion", areaObjetivo.getPorcentajeContaminacion()));

            sql.append( propertyToString("scene_id", areaObjetivo.getId()));
            sql.append( propertyToString("scene_date_temp", areaObjetivo.getDateAcquired()));
            sql.append( propertyToString("scene_time", areaObjetivo.getSceneCenterTime(), true));

            sql.append("}");
            sql.append("',ST_GeomFromText('");
            sql.append(areaObjetivo.getGeometry().getGeomText());
            sql.append("',4326))");

            /* Create a transactional object. */
            work W(C);

            /* Execute SQL query */
            W.exec( sql );
            W.commit();
            C.disconnect ();
        mutex.unlock();
        return true;
    }catch (const std::exception &e){
        cerr << e.what() << std::endl;
        return false;
    }
}


std::string propertyToString(string key, string value, bool last){
    string aux = "\"";
    aux.append(key);
    aux.append("\": ");
    aux.append("\"");
    aux.append(value);
    aux.append("\"");
    
    if(!last){
        aux.append(",");
    }
    
    return aux;
}


string propertyToString(string key, float value, bool last){
    string value_aux = to_string(value);
    
    string aux = "\"";
    aux.append(key);
    aux.append("\": ");
    aux.append(value_aux);
    
    if(!last){
        aux.append(",");
    }
    
    return aux;
}


BoundingBox parseBoundingBox(string geomText){
    string prefix = "POLYGON((";
    string suffix = "))";
    
    string coordsText = geomText.substr( prefix.length(), (geomText.length() - suffix.length() - prefix.length()) );
    
    char *cstr = new char[coordsText.length() + 1];
    strcpy(cstr, coordsText.c_str());
    
    return parseBoundingBox(cstr);
}


BoundingBox parseBoundingBox(char *coords){
    double lat;
    double lng;
    
    Coords left_bottom;
    Coords left_top;
    Coords right_top;
    Coords right_bottom;
    
    char *lineCoords = strtok(coords, ",");
    char *endPointer;
    for( int i = 0; i < 4; i++ ){
        lng = strtod(lineCoords, &endPointer);
        lat = strtod(endPointer, NULL);
        
        switch(i){
            case 0:{
            right_bottom.setLat(lat);
            right_bottom.setLng(lng);
                break;
            }
            case 1:{
                left_top.setLat(lat);
                left_top.setLng(lng);
                break;
            }
            case 2:{
                right_top.setLat(lat);
                right_top.setLng(lng);
                break;
            }
            case 3:{
                left_bottom.setLat(lat);
                left_bottom.setLng(lng);
                break;
            }
        }
        lineCoords = strtok(NULL, ",");
    }
    
    
    BoundingBox bounds(left_top,right_top,right_bottom,left_bottom);
    return bounds;
}
