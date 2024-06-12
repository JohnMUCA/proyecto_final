#ifndef MENU_H
#define MENU_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include <QPushButton>
#include <QGroupBox>

class menu
{
public:
    menu(QGraphicsView *graphicsV, QString imageBackground, float nivelScale, unsigned int height,
         unsigned int width,unsigned int x, unsigned int y, QVector<QPushButton*> botones, QGroupBox *grupoBotones,
         char tipoMenu);
    ~menu();
private:
    QGraphicsView *graph;
    QGraphicsScene *escena;
    QBrush *brocha;
    QPixmap *fondoCompleto;
    QVector<QPushButton*> botones;
    QGroupBox *grupoBotones;

    void setup_scene(QString image_Background, float nivel_Scale, unsigned int _heightMap, unsigned int _widthMap,
                     unsigned int _x, unsigned int _y);
};

#endif // MENU_H
