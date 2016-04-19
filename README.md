# module_coordinates
Las carpetas contienen el código que compone el proyecto, en include encontrarás todas las cabeceras y en src el resto del código.

El proyecto usa funciones como to_string() que no vienen en el compilador normal de GCC en la versión 4.8, pero si vienen en el cross compiler de MINGW, y también a partir de la versión 11 de C++ son un estandar esas funciones, entonces solamente se estipuló en el proyecto que se trabajaría con la version 11 de C++ :)

Se usa boost para las fechas:
sudo apt-get install libboost-all-dev

La copia de las escenas satelitales se realiza en la siguiente ruta:
/home/tu_nombre_de_usuario/LandsatScenes
de no existir esta ruta, la crea :)

- Se requiere la instalacion de Boost 
sudo apt-get install libboost-all-dev

se tiene que instalar postGIS, la version usada fue la 9.4, aqui hay un link de ayuda:
https://trac.osgeo.org/postgis/wiki/UsersWikiPostGIS21UbuntuPGSQL93Apt

tambien el conector de QT con POSTGRES
sudo apt-get install libqt5sql5-psql

tambien la siguiente librería:
http://installion.co.uk/ubuntu/trusty/universe/l/libpqxx-dev/install/index.html

