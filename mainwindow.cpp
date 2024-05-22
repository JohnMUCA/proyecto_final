#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::keyPressEvent(QKeyEvent *i)
{
    if(i->key() == Qt::Key_D)
    {
        prota->move(Qt::Key_D, 1);
    }
    else if(i->key() == Qt::Key_A)
    {
        prota->move(Qt::Key_A, 1);
    }
    else if(i->key() == Qt::Key_W)
    {
        prota->move(Qt::Key_W, 1);
    }
    else if(i->key() == Qt::Key_S)
    {
        prota->move(Qt::Key_S, 1);
    }

    if(prota->x()<(1000 * gameScaleFactor)  && prota->x()> (350 * gameScaleFactor)) set_focus_element(prota,16 * gameScaleFactor, 0, 1, 1);
    if(prota->y()<(1500 * gameScaleFactor) && prota->y()>(350 * gameScaleFactor)) set_focus_element(prota,0 , 16 * gameScaleFactor, 1, 1);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    escena = new QGraphicsScene;
    prota = new objetos(":/imagenes/caveMan.png", 16, 16, 4);
    keys = new unsigned int[4];
    fondoCompleto = new QPixmap();
    //centroFocus = new QPointF(25 * 16 * 4, 15 * 16 * 4);
    gradiante = new QRadialGradient();
    gradiante->setCenter(25 * 16 * gameScaleFactor, 15 * 16 * gameScaleFactor);
    gradiante->setRadius(32);
    brocha = new QBrush(*gradiante);

    fondoCompleto->load(":/imagenes/caves.png");
    brocha->setTexture(fondoCompleto->copy(0, 0, 468, 800).scaled(1024 * gameScaleFactor, 2048 * gameScaleFactor));
    //brocha->setTexture(fondoCompleto->scaled(2387 * gameScaleFactor, 982 * gameScaleFactor));
    brocha->setStyle(Qt::LinearGradientPattern);
    keys[0] = Qt::Key_A;
    keys[1] = Qt::Key_D;
    keys[2] = Qt::Key_W;
    keys[3] = Qt::Key_S;
    prota->set_keys(keys);
    ui->setupUi(this);
    ui->graphicsView->setGeometry(0, 0, 1024, 2048);
    ui->boton1->setText("Hello dear");
    ui->progressBar->setValue(0);
    ui->lcdNumber->display(0);
    escena->setSceneRect(0,0,ui->graphicsView->width() - 2,ui->graphicsView->height() - 2);
    escena->addItem(prota);
    set_focus_element(prota,16 * gameScaleFactor, 0, 1, 1);
    ui->graphicsView->setScene(escena);
    escena->setBackgroundBrush(*brocha);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete escena;
    delete prota;
}

void MainWindow::set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley, unsigned int x, unsigned int y)
{
    escena->setSceneRect(x * (item->x() + scalex - escena->width()/2), y * (item->y() + scaley - escena->height()/6) , escena->width(), escena->height());
    //scene->setSceneRect(item->x()+scalex-scene->width()/2,0,scene->width(),scene->height());
}

