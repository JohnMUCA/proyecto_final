#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QVector>
#include <QTimer>
#include <QObject>

#include "entidad.h"
#include "enemigo.h"
#include "qlabel.h"

#define alturaProta 16
#define anchoProta 16
#define alturaMurcielago 32
#define anchoMurcielago 32
#define alturaTigre 32
#define anchoTigre 32
#define alturaLobo 32
#define anchoLobo 32
#define alturaMamutdFrente 65
#define anchoMamutdFrente 65
#define alturaMamutdLado 66
#define anchoMamutdLado 89

#define scaleMurcielago 3
#define scaleProta 4
//#define gameScaleFactor 8

class nivel : public QObject
{
    Q_OBJECT
public:
    nivel(QGraphicsView *graphicsV, QString imageBackground, QString imageReference, float nivelScale, unsigned int height, unsigned int width, unsigned int x, unsigned int y, unsigned short numNivel, bool setFocus, QLabel* salud);
    ~nivel();
    void key_event(QKeyEvent *event);

public slots:
    void detectarAtaque();
private:
    QGraphicsView *graph;
    QGraphicsScene *escena;
    Entidad *prota;
    Enemigo *murcielago;
    //Enemigo *Mamut;
    unsigned int prota_keys[4];
    unsigned int* numsFotogramasProta;
    unsigned int* numsFotogramasMurcielago;
    unsigned int* numsFotogramasMamut;
    QBrush *brocha;
    QPixmap *fondoCompleto;
    QImage *fondoReferencia;
    QColor *colorTope;
    bool focus;
    bool colision;
    QLabel* salud;
    QTimer* timeColision;

    void setProta_keys();
    void setNumsFotogramasProta();
    void setNumsFotogramasMurcielago();
    void setNumsFotogramasMamut();

    void setup_scene(QString image_Background, QString image_Reference, float nivel_Scale, unsigned int _heightMap, unsigned int _widthMap, unsigned int _x, unsigned int _y);
    void setup_prota(unsigned short _numNivel);
    void setup_murcielago(unsigned short _numNivel);
    void setup_Mamut();


    bool left_movement_is_valid(Entidad *item);
    bool right_movement_is_valid(Entidad *item);
    bool up_movement_is_valid(Entidad *item);
    bool down_movement_is_valid(Entidad *item);
    void set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley);
    QVector<QRect> completeAnimationsProta();
    QVector<QRect> completeAnimationsMurcielago();
    //QVector<QRect> completeAnimationsTigre();
    //QVector<QRect> completeAnimationsLobo();
    QVector<QRect> completeAnimationsMamut();
};

#endif // NIVEL_H
