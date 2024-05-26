#include "player.h"

player::player(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale) :
    Entidad(rectangulosAnimaciones,numsFotogramas, name, ancho, alto, scale)
{
    puntaje = 0;
    //setKeys(keys);
}

/*void player::setKeys(unsigned int *keys)
{
    for(unsigned int i=0;i<4;i++) this->keys[i] = keys[i];
}*/

