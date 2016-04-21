#ifndef INFOOBJETIVO_H
#define INFOOBJETIVO_H


class InfoObjetivo
{
public:
    InfoObjetivo(int Up_Left_X, int Up_Left_Y, int Down_Right_X, int Down_Right_Y, int Ancho, int Alto);
    int GetUL_X();
    int GetUL_Y();
    int GetDR_X();
    int GetDR_Y();
    int GetAncho();
    int GetAlto();
private:
     int Up_Left_X;
     int Up_Left_Y;
     int Down_Right_X;
     int Down_Right_Y;
     int Ancho;
     int Alto;
};

#endif // INFOOBJETIVO_H
