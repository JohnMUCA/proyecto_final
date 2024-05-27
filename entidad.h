#ifndef ENTIDAD_H
#define ENTIDAD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "sprites.h"
#include <QRect>
#include <QVector>
#include <QString>
#include <QPoint>
#include <qvector2d.h>

#define entidadSpeed 15

class Entidad : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Entidad(QVector<QRect> rectangulosAnimaciones, unsigned int* numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale);
    ~Entidad();

    void move(unsigned int key, bool is_valid);
    void setAnimations(QVector<QRect> rectangulosAnimaciones, unsigned int* numsFotogramas);
    void setKeys(unsigned int* Keys);

    void recibir_dagno(int cantidad);
    void hacer_dagno(Entidad* otraEntidad);
    //void establecer_posicion(Qpoint punto);
    //void agregarAnimacion(QRect rentanguloAnimacion, unsigned int numFotogramas);

    void establecer_posicion(QPoint punto);
    QPoint obtenerPosicion() const;

    void establecerVelocidad(QVector2D nuevaVelocidad);
    QVector2D obtenerVelocidad() const;
    QRect obtenerRectangulo() const;


private:
    QString name;
    unsigned int velocidad;
    int salud;
    sprites* mainPixmap;
    unsigned int width;
    unsigned int height;
    unsigned int dagno;
    unsigned int scale;
    unsigned int keys[4];
    QPoint posicion;
    QVector2D velocidadVector;
    //recurso drop;

    QRect setCompleteSpritesProta();
    QRect setCompleteSpritesMurcielago();
};

#endif // ENTIDAD_H
