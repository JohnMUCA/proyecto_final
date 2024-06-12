#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    nivelActual->key_event(event);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->BotMenuPrincipal->setVisible(false);
    ui->BotonesCargarNivel->setVisible(false);
    ui->BotonesFinNivel->setVisible(false);
    nivelActual = nullptr;
    menuActual = nullptr;
    setup_menuPrincipal();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (nivelActual != nullptr) delete nivelActual;
    if (menuActual != nullptr) delete menuActual;
}

void MainWindow::setup_nivel1()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    nivelActual = new nivel(ui->graphicsView, ":/imagenes/caves.png", ":/imagenes/caves_reference.png", 8, 800, 468, 0, 0, 1, 1, ui->salud);
}

void MainWindow::setup_nivel2()
{

    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    nivelActual = new nivel(ui->graphicsView, ":/imagenes/Yermo.png", ":/imagenes/Yermo_reference.png", 1, 982, 2387, 0, 0, 2, 0, ui->salud);
}

void MainWindow::setup_nivel3()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    nivelActual = new nivel(ui->graphicsView, ":/imagenes/savannah.png", ":/imagenes/savannah_reference.png", 1.5, 544, 574, 0, 939, 3, 0, ui->salud);
}

void MainWindow::setup_menuPrincipal()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    menuActual = new menu(ui->graphicsView, ":/imagenes/menuPrincipal.png", 1, 800, 1500, 0, 0, setup_botonesMenuP(),
                          ui->BotMenuPrincipal, 'P');
}

void MainWindow::setup_menuCargarPartida()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
}

void MainWindow::setup_menuFinNivel()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
}

QVector<QPushButton*> MainWindow::setup_botonesMenuP()
{
    QVector<QPushButton*> botones;
    botones.push_back(ui->Play);
    botones.push_back(ui->cargarPartida);
    return botones;
}

QVector<QPushButton*> MainWindow::setup_botonesMenuCargarNivel()
{
    QVector<QPushButton*> botones;
    botones.push_back(ui->nivel1);
    botones.push_back(ui->nivel2);
    botones.push_back(ui->nivel3);
    botones.push_back(ui->atras);
    return botones;
}

QVector<QPushButton*> MainWindow::setup_botonesMenuPasoNivel()
{
    QVector<QPushButton*> botones;
    botones.push_back(ui->siguienteNivel);
    botones.push_back(ui->menuPrincipal);
    return botones;
}

void MainWindow::on_pushButton_released()
{
    setup_nivel2();
}


void MainWindow::on_pushButton_2_released()
{
    setup_nivel3();
}


void MainWindow::on_Play_released()
{
    setup_nivel1();
}

