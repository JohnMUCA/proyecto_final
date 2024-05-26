#include "nivel.h"

nivel::nivel(QGraphicsView *graphicsV, QString imageBackground)
{
    graph = graphicsV;
    setup_scene(imageBackground);
    setup_player();
}

nivel::~nivel()
{
    delete graph;
    delete escena;
    delete prota;
    delete numsFotogramasProta;
    delete fondoCompleto;
    delete brocha;

}

void nivel::key_event(QKeyEvent *event)
{
    prota->move(event->key(), 1);
    if(prota->y()<(700) || prota->y()>(30)) set_focus_element(prota,16, 16 * 4);
}

void nivel::setProta_keys()
{
    prota_keys;
    prota_keys[0] = Qt::Key_A;
    prota_keys[1] = Qt::Key_D;
    prota_keys[2] = Qt::Key_W;
    prota_keys[3] = Qt::Key_S;
}

void nivel::setNumsFotogramasProta()
{
    numsFotogramasProta = new unsigned int[4];
    numsFotogramasProta[0] = 3;
    numsFotogramasProta[1] = 3;
    numsFotogramasProta[2] = 3;
    numsFotogramasProta[3] = 3;
}

void nivel::setup_scene(QString image_Background)
{
    //------------------------------------------Creacion escena-----------------------------------------------
    graph->setGeometry(0, 0, 1000, 700);
    escena = new QGraphicsScene;
    escena->setSceneRect(0,0,graph->width() - 2,graph->height() - 2);
    graph->setScene(escena);
    //----------------------------------------------------------------------------------------------

    //------------------------------------------creacion fondoCompleto-----------------------------------------------
    fondoCompleto = new QPixmap();
    fondoCompleto->load(image_Background);
    //----------------------------------------------------------------------------------------------

    //------------------------------------------creacion brocha-----------------------------------------------
    brocha = new QBrush();
    brocha->setTexture(fondoCompleto->copy(0, 0, 468, 800).scaled(468 * gameScaleFactor, 800 * gameScaleFactor));
    //----------------------------------------------------------------------------------------------

    escena->setBackgroundBrush(*brocha);

}

void nivel::setup_player()
{
    setProta_keys();
    setNumsFotogramasProta();
    prota = new player(completeAnimationsProta(), numsFotogramasProta, ":/imagenes/caveMan.png", anchoProta, alturaProta, scaleProta);
    prota->setKeys(prota_keys);
    escena->addItem(prota);
}


void nivel::set_focus_element(QGraphicsPixmapItem *item, unsigned int scalex, unsigned int scaley)
{
    escena->setSceneRect(item->x() + (scalex / 2) - (escena->width() / 2),
                         item->y() + (scaley / 2) - (escena->height() / 2) ,
                         escena->width(),
                         escena->height());
}

QVector<QRect> nivel::completeAnimationsProta()
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
