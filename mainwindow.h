#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <string>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>
#include <QPushButton>
#include <fstream>

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

    void terminarNivel(char sigNivel);
private slots:

    void on_jugar_released();
    void on_continuar_released();
    void on_atras_released();
    void on_nivel1_released();
    void on_nivel2_released();
    void on_nivel3_released();
    void on_menuPrincipal_released();
    void on_botonPausa_released();
    void on_continuarNivel_released();
    void on_reiniciar_released();
    void on_menuPrincipalP_released();
    void on_siguienteNivel_released();
    void on_cargarPartida_released();
    void on_dificultSelector_valueChanged(int value);
    void on_salir_released();

private:
    Ui::MainWindow *ui;
    nivel *nivelActual;
    menu *menuActual;
    char numNivel;
    QString *puntuaciones;
    int dificultadJuego;

    void setup_nivel1();
    void setup_nivel2();
    void setup_nivel3();
    void setup_menuPrincipal();
    void setup_menuContinuar();
    void setup_menuFinNivel();
    void setup_menuPausa();

    void guardarPartida();
    void cargarPartida();

    QVector<QPushButton*> setup_botonesMenuP();
    QVector<QPushButton*> setup_botonesMenuContinuar();
    QVector<QPushButton*> setup_botonesMenuPasoNivel();
    QVector<QPushButton*> setup_botonesMenuPausa();

};
#endif // MAINWINDOW_H
