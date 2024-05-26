#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QVector>

#include "player.h"

#define alturaProta 16
#define anchoProta 16
#define scaleProta 4
#define gameScaleFactor 8

class nivel
{
public:
    nivel(QGraphicsView *graphicsV, QString imageBackground);
    ~nivel();
    void key_event(QKeyEvent *event);
private:
    QGraphicsView *graph;
    QGraphicsScene *escena;
    player *prota;
    unsigned int prota_keys[4];
    unsigned int* numsFotogramasProta;
    QBrush *brocha;
    QPixmap *fondoCompleto;

    void setProta_keys();
    void setNumsFotogramasProta();

    void setup_scene(QString image_Background);
    void setup_prota();
    bool left_movement_is_valid(QGraphicsPixmapItem *item);
    bool right_movement_is_valid(QGraphicsPixmapItem *item);
    bool up_movement_is_valid(QGraphicsPixmapItem *item);
    bool down_movement_is_valid(QGraphicsPixmapItem *item);
    void set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley);
    QVector<QRect> completeAnimationsProta();
};

#endif // NIVEL_H
