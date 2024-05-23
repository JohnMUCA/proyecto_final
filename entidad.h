#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"
#include <QRect>

class Entidad : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Entidad(QString name, unsigned int ancho, unsigned int alto, unsigned int scale);
    void recibir_daño();
    //void establecer_posicion(Qpoint punto);
    void set_left_animation(QRect rentanguloAnimacion);
    void set_right_animation(QRect rentanguloAnimacion);
    void set_down_animation(QRect rentanguloAnimacion);
    void set_death_animation(QRect rentanguloAnimacion);

private:
    unsigned int velocidad;
    int salud;
    sprites mainPixmap;
    unsigned int width;
    unsigned int height;
    unsigned int dagno;
    //recurso drop;
};

#endif // ENTIDAD_H
