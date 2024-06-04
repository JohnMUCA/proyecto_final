#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>

#include "nivel.h"

#define gameScaleFactor 4
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
    void keyPressEvent(QKeyEvent* event);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

private slots:



private:
    Ui::MainWindow *ui;
    nivel *nivelActual;
    //QGraphicsScene* escena;
    //player* prota;
    //unsigned int* keys;
    //QBrush *brocha;
    //QPixmap *fondoCompleto;
    //unsigned int* numsFotogramasProta;
    //QPointF* centroFocus;
    //QRadialGradient* gradiante;

    //void set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley);
    //QVector<QRect> completeAnimationsProta();
    void setup_nivel();

};
#endif // MAINWINDOW_H
