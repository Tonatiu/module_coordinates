#include "infoobjetivo.h"

InfoObjetivo::InfoObjetivo(int Up_Left_X, int Up_Left_Y, int Down_Right_X, int Down_Right_Y, int Ancho, int Alto)
{
    this->Alto = Alto;
    this->Ancho = Ancho;
    this->Up_Left_X = Up_Left_X;
    this->Up_Left_Y = Up_Left_Y;
    this->Down_Right_X = Down_Right_X;
    this->Down_Right_Y = Down_Right_Y;
}

int InfoObjetivo::GetAlto(){
    return this->Alto;
}

int InfoObjetivo::GetAncho(){
    return this->Ancho;
}

int InfoObjetivo::GetDR_X(){
    return this->Down_Right_X;
}

int InfoObjetivo::GetDR_Y(){
    return this->Down_Right_Y;
}

int InfoObjetivo::GetUL_X(){
    return this->Up_Left_X;
}

int InfoObjetivo::GetUL_Y(){
    return this->Up_Left_Y;
}
