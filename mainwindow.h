#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>
#include <QPushButton>

#include "nivel.h"
#include "menu.h"

#define nivel1Scale
#define nivel2Scale
#define nivel3Scale

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

    void terminarNivel();
private slots:

    void on_pushButton_released();
    void on_pushButton_2_released();

    void on_Play_released();

private:
    Ui::MainWindow *ui;
    nivel *nivelActual;
    menu *menuActual;

    void setup_nivel1();
    void setup_nivel2();
    void setup_nivel3();
    void setup_menuPrincipal();
    void setup_menuCargarPartida();
    void setup_menuFinNivel();

    QVector<QPushButton*> setup_botonesMenuP();
    QVector<QPushButton*> setup_botonesMenuCargarNivel();
    QVector<QPushButton*> setup_botonesMenuPasoNivel();

};
#endif // MAINWINDOW_H
