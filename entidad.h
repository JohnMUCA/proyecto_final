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
    Entidad(QVector<QRect> rectangulosAnimaciones, unsigned int* numsFotogramas, QString name, unsigned int ancho, unsigned int alto,
            unsigned int scale, bool tipoSprite);
    ~Entidad();

    void move(unsigned int key, bool is_valid);
    void setAnimations(QVector<QRect> rectangulosAnimaciones, unsigned int* numsFotogramas);
    void setKeys(unsigned int* Keys);
    void setDagno(short int _dagno);
    void setSalud(int _salud);

    void recibir_dagno(short int cantidad);
    QRect obtenerRectangulo() const;
    int obtenerSalud() const ;
    unsigned int obtenerUltimaTecla() const;
    int getVelocidad();
    short int getdagno();

private:
    int salud;
    sprites* mainPixmap;
    unsigned int width;
    unsigned int height;
    short int dagno;
    unsigned int scale;
    unsigned int keys[4];
    unsigned int ultimaTecla;

    QRect getCompleteSpritesProta();
    QRect getCompleteSpritesMurcielago();
    QRect getCompleteSpritesMamut();
    QRect getCompleteSpritesTigre();
    QRect getCompleteSpritesLobo();
};

#endif // ENTIDAD_H
