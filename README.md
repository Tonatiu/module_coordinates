# module_coordinates
Las carpetas contienen el código que compone el proyecto, en include encontrarás todas las cabeceras y en src el resto del código.

El proyecto usa funciones como to_string() que no vienen en el compilador normal de GCC en la versión 4.8, pero si vienen en el cross compiler de MINGW, y también a partir de la versión 11 de C++ son un estandar esas funciones, entonces solamente se estipuló en el proyecto que se trabajaría con la version 11 de C++ :)

Se usa boost para las fechas:
sudo apt-get install libboost-all-dev

La copia de las escenas satelitales se realiza en la siguiente ruta:
/home/tu_nombre_de_usuario/LandsatScenes
de no existir esta ruta, la crea :)
