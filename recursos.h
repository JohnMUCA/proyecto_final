#ifndef RECURSOS_H
#define RECURSOS_H

#include <QObject>
#include <QPixmap>
#include <QRect>
#include <QGraphicsPixmapItem>

#include "sprites.h"

class recursos : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    recursos(QRect rectanguloAnimacion, unsigned int numFotogramas, unsigned int width,
             unsigned int height, unsigned int scale, bool type, QString name, char tipoCultivo);
    ~recursos();

    QRect obtenerRectangulo() const;
    void setAnimation(QRect rectangulosAnimaciones, unsigned int numsFotogramas);

private:
    sprites* mainPixmap;
    unsigned int width;
    unsigned int height;
    unsigned int scale;
    bool type;
    void set_type_recurso(QString name, char tipoCultivo);
    QRect getCompleteSpritesFuego();
    QRect getCompleteSpritesComida();
    QRect getCompleteSpritesLanza();
    QRect getCompleteSpritesTrigo();
    QRect getCompleteSpritesZanahoria();
    QRect getCompleteSpritesTomate();
};
#endif // RECURSOS_H
