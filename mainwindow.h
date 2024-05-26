#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QGraphicsScene>
#include <objetos.h>
#include <QKeyEvent>
#include <QTimer>
#include "player.h"
#include <QVector>

#define gameScaleFactor 8
#define alturaProta 16
#define anchoProta 16

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void keyPressEvent(QKeyEvent* i);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private slots:



private:
    Ui::MainWindow *ui;
    QGraphicsScene* escena;
    player* prota;
    unsigned int* keys;
    QBrush *brocha;
    QPixmap *fondoCompleto;
    //QPointF* centroFocus;
    //QRadialGradient* gradiante;
    void set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley);
    QVector<QRect> completeAnimationsProta();
    unsigned int* numsFotogramasProta;

};
#endif // MAINWINDOW_H
