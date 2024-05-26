#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::keyPressEvent(QKeyEvent *i)
{

        if((i->key() == Qt::Key_D) && prota->x() <= 403 * gameScaleFactor)
        {
            prota->move(Qt::Key_D, 1);
        }
        else if((i->key() == Qt::Key_A) && prota->x() >=  100 * gameScaleFactor)
        {
            prota->move(Qt::Key_A, 1);
        }
        else if((i->key() == Qt::Key_W) && prota->y() >= 70 * gameScaleFactor)
        {
            prota->move(Qt::Key_W, 1);
        }
        else if((i->key() == Qt::Key_S) && prota->y() <= 665 * gameScaleFactor)
        {
            prota->move(Qt::Key_S, 1);
        }
    if(prota->y()<(700) || prota->y()>(30)) set_focus_element(prota,16, 16 * 4);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    escena = new QGraphicsScene;
    keys = new unsigned int[4];
    keys[0] = Qt::Key_A;
    keys[1] = Qt::Key_D;
    keys[2] = Qt::Key_W;
    keys[3] = Qt::Key_S;
    //animationsProta = new QVector();
    numsFotogramasProta = new unsigned int[4];
    numsFotogramasProta[0] = 3;
    numsFotogramasProta[1] = 3;
    numsFotogramasProta[2] = 3;
    numsFotogramasProta[3] = 3;

    prota = new player(completeAnimationsProta(), numsFotogramasProta ,keys, ":/imagenes/caveMan.png", 16, 16, 4);
    fondoCompleto = new QPixmap();
    //centroFocus = new QPointF(25 * 16 * 4, 15 * 16 * 4);
    //gradiante = new QRadialGradient();
    //gradiante->setCenter(25 * 16 * gameScaleFactor, 15 * 16 * gameScaleFactor);
    //gradiante->setRadius(32);
    brocha = new QBrush();

    fondoCompleto->load(":/imagenes/caves.png");
    brocha->setTexture(fondoCompleto->copy(0, 0, 468, 800).scaled(468 * gameScaleFactor, 800 * gameScaleFactor));

    //brocha->setTexture(fondoCompleto->scaled(2387 * gameScaleFactor, 982 * gameScaleFactor));
    //brocha->setStyle(Qt::LinearGradientPattern);

    ui->graphicsView->setGeometry(0, 0, 1000, 700);
    escena->setSceneRect(0,0,ui->graphicsView->width() - 2,ui->graphicsView->height() - 2);
    escena->addItem(prota);
    set_focus_element(prota,16 * 4, 16 * 4);
    ui->graphicsView->setScene(escena);
    escena->setBackgroundBrush(*brocha);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete escena;
    delete prota;
    delete[] keys;
    delete fondoCompleto;
    delete brocha;
    delete[] numsFotogramasProta;
}

void MainWindow::set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley)
{
    escena->setSceneRect(item->x() + (scalex / 2) - (escena->width() / 2),
                         item->y() + (scaley / 2) - (escena->height() / 2) ,
                         escena->width(),
                         escena->height());
}

QVector<QRect> MainWindow::completeAnimationsProta()
{
    QVector<QRect> animations;
    QRect dimLeft;
    QRect dimRight;
    QRect dimUp;
    QRect dimDown;

    dimLeft.setX(0);
    dimLeft.setY(1 * alturaProta);
    dimLeft.setHeight(1 * alturaProta);
    dimLeft.setWidth(3 * anchoProta);

    dimRight.setX(3 * anchoProta);
    dimRight.setY(1 * alturaProta);
    dimRight.setHeight(1 * alturaProta);
    dimRight.setWidth(3 * anchoProta);

    dimUp.setX(0);
    dimUp.setY(0);
    dimUp.setHeight(1 * alturaProta);
    dimUp.setWidth(3 * anchoProta);

    dimDown.setX(3 * anchoProta);
    dimDown.setY(0);
    dimDown.setHeight(1 * alturaProta);
    dimDown.setWidth(3 * anchoProta);

    animations.push_back(dimLeft);
    animations.push_back(dimRight);
    animations.push_back(dimUp);
    animations.push_back(dimDown);
    return animations;
}
