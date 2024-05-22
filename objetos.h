#ifndef OBJETOS_H
#define OBJETOS_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>
#include "sprites.h"
#define objectSpeed 15

class objetos : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    objetos(QString name, unsigned int ancho, unsigned int alto, unsigned int scale);
    QRect set_complete_sprites();
    move(unsigned int key, bool is_valid);
    void set_keys(unsigned int *keys);
private:
    void set_animations();
    void set_left_animation();
    void set_right_animation();
    void set_up_animation();
    void set_down_animation();
    void set_death_animation();

    unsigned int width;
    unsigned int height;
    unsigned int keys[4];
    sprites *mainPixmap;
};

#endif // OBJETOS_H
