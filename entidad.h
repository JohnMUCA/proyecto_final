#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"
#include <QRect>
#include <QVector>

#define entidadSpeed 15

class Entidad : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Entidad(QVector<QRect> rectangulosAnimaciones, unsigned int* numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale);
    void move(unsigned int key, bool is_valid);
    void recibir_daño();
    //void establecer_posicion(Qpoint punto);
    void setAnimations(QVector<QRect> rectangulosAnimaciones, unsigned int* numsFotogramas);
    //void agregarAnimacion(QRect rentanguloAnimacion, unsigned int numFotogramas);
    void hacer_dagno();
    void setKeys(unsigned int* Keys);
    ~Entidad();

private:
    unsigned int velocidad;
    int salud;
    sprites* mainPixmap;
    unsigned int width;
    unsigned int height;
    unsigned int dagno;
    unsigned int scale;
    unsigned int keys[4];
    //recurso drop;

    QRect setCompleteSprites();
};

#endif // ENTIDAD_H
