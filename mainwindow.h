#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>

#include "nivel.h"

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

private slots:



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    nivel *nivelActual;

    void setup_nivel1();
    void setup_nivel2();
    void setup_nivel3();

};
#endif // MAINWINDOW_H
