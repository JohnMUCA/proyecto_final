#ifndef NIVEL_H
#define NIVEL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QVector>
#include <QTimer>
#include <QObject>
#include <qlabel.h>

#include "entidad.h"
#include "enemigo.h"


#define alturaProta 16
#define anchoProta 16
#define alturaMurcielago 32
#define anchoMurcielago 32
#define alturaTigre 65
#define anchoTigre 33
#define alturaLobo 65
#define anchoLobo 24
#define alturaMamut 65
#define anchoMamut 75

#define scaleMurcielago 3
#define scaleProta 4
#define scaleMamut 3
#define scaleTigre 2
#define scaleLobo 2

class nivel : public QObject
{
    Q_OBJECT
public:
    nivel(QGraphicsView *graphicsV, QString imageBackground, QString imageReference, float nivelScale, unsigned int height,
          unsigned int width,unsigned int x, unsigned int y, unsigned short numNivel, bool setFocus, QLabel* salud);
    ~nivel();
    void key_event(QKeyEvent *event);

signals:
    void heTerminado();
    void renaudarEnemigo();
    void pausarEnemigo();
public slots:
    void detectarAtaque();
    void recuperaEscena();
    void pausarNivel();
private:
    QGraphicsView *graph;
    QGraphicsScene *escena;
    Entidad *prota;
    Enemigo **murcielagos;
    Enemigo *mamut;
    Enemigo **tigres;
    Enemigo **lobos;

    //Enemigo *Mamut;
    unsigned int prota_keys[5];
    unsigned int mamut_keys[8];
    unsigned int tigre_keys[8];
    unsigned int* numsFotogramasProta;
    unsigned int* numsFotogramasMurcielago;
    unsigned int* numsFotogramasMamut;
    unsigned int* numsFotogramasTigre;
    unsigned int* numsFotogramasLobo;

    QBrush *brocha;
    QPixmap *fondoCompleto;
    QImage *fondoReferencia;
    QColor *colorTope;
    bool focus;
    bool pausaN;
    QLabel* salud;
    QTimer* timeColision;

    void setProta_keys();
    void setMamut_keys();
    void setTigre_keys();
    void setNumsFotogramasProta();
    void setNumsFotogramasMurcielago();
    void setNumsFotogramasMamut();
    void setNumsFotogramasTigre();
    void setNumsFotogramasLobo();

    void setup_scene(QString image_Background, QString image_Reference, float nivel_Scale, unsigned int _heightMap, unsigned int _widthMap,
                     unsigned int _x, unsigned int _y);
    void setup_prota(unsigned short _numNivel);
    void setup_murcielago(unsigned short _numNivel);
    void setup_Mamut(unsigned short _numNivel);
    void setup_Tigre(unsigned short _numNivel);
    void setup_Lobo(unsigned short _numNivel);

    bool left_movement_is_valid(Entidad *item);
    bool right_movement_is_valid(Entidad *item);
    bool up_movement_is_valid(Entidad *item);
    bool down_movement_is_valid(Entidad *item);

    void set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley);
    QVector<QRect> completeAnimationsProta();
    QVector<QRect> completeAnimationsMurcielago();
    QVector<QRect> completeAnimationsTigre();
    QVector<QRect> completeAnimationsLobo();
    QVector<QRect> completeAnimationsMamut();
};

#endif // NIVEL_H
