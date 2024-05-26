#ifndef PLAYER_H
#define PLAYER_H

#include "entidad.h"
#include "QVector"

class player : public Entidad
{
public:
    player(QVector<QRect> rectangulosAnimaciones, unsigned int* numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale);
    //void setKeys(unsigned int* keys);
    void recolectarItem();
private:
    int puntaje;

};

#endif // PLAYER_H
