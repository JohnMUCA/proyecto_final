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
    //ui->graphicsView->setGeometry(0, 0, 1000, 700);
    setup_nivel1();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete nivelActual;
}

void MainWindow::setup_nivel1()
{
    nivelActual = new nivel(ui->graphicsView, ":/imagenes/caves.png", ":/imagenes/caves_reference.png", 8, 800, 468, 0, 0, 1, 1);
}

void MainWindow::setup_nivel2()
{
    delete nivelActual;
    nivelActual = new nivel(ui->graphicsView, ":/imagenes/Yermo.png", ":/imagenes/Yermo_reference.png", 1, 982, 2387, 0, 0, 2, 0);
}

void MainWindow::setup_nivel3()
{
    delete nivelActual;
    nivelActual = new nivel(ui->graphicsView, ":/imagenes/savannah.png", ":/imagenes/savannah_reference.png", 1.5, 544, 574, 0, 939, 3, 0);
}



void MainWindow::on_pushButton_clicked()
{
    setup_nivel2();
}


void MainWindow::on_pushButton_2_clicked()
{
    setup_nivel3();
}

