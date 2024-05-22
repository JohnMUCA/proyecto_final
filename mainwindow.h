#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QGraphicsScene>
#include <objetos.h>
#include <QKeyEvent>
#include <QTimer>

#define gameScaleFactor 4

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
    objetos* prota;
    unsigned int* keys;
    QBrush *brocha;
    QPixmap *fondoCompleto;
    //QPointF* centroFocus;
    QRadialGradient* gradiante;
    void set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley, unsigned int x, unsigned int y);

};
#endif // MAINWINDOW_H
