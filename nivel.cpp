#include "nivel.h"
#include "qlabel.h"

nivel::nivel(QGraphicsView *graphicsV, QString imageBackground, QString imageReference, float nivelScale,
             unsigned int heightMap, unsigned int widthMap, unsigned int x, unsigned int y, unsigned short numNivel,
             bool setFocus, QLabel* salud)
{
    focus = setFocus;
    graph = graphicsV;
    setup_scene(imageBackground, imageReference, nivelScale, heightMap, widthMap, x, y);
    setup_prota(numNivel);
    setup_murcielago(numNivel);
    setup_Mamut(numNivel);
    setup_Tigre(numNivel);
    setup_Lobo(numNivel);

    this->salud = salud;
    timeColision = new QTimer;
    QObject::connect(timeColision,SIGNAL(timeout()),this,SLOT(detectarAtaque()));
    timeColision->start(200);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

nivel::~nivel()
{
    delete prota;
    delete murcielago;
    delete mamut;
    delete tigre;
    delete lobo;
    delete[] numsFotogramasProta;
    delete[] numsFotogramasMurcielago;
    delete[] numsFotogramasMamut;
    delete brocha;
    delete fondoReferencia;
    delete fondoCompleto;
    delete colorTope;
    delete timeColision;
    delete escena;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void nivel::key_event(QKeyEvent *event)
{
    bool isValid = 1;

    if(unsigned(event->key()) == prota_keys[0]) isValid = left_movement_is_valid(prota);
    else if(unsigned(event->key()) == prota_keys[1]) isValid = right_movement_is_valid(prota);
    else if(unsigned(event->key()) == prota_keys[2]) isValid = up_movement_is_valid(prota);
    else if(unsigned(event->key()) == prota_keys[3]) isValid = down_movement_is_valid(prota);

    if(prota->y()>= 2000 && prota->y()<2100) murcielago->empezarPerseguir();
    prota->move(event->key(), isValid);

    if(focus && (prota->y()<(700) || prota->y()>(30))) set_focus_element(prota,16, 16 * 4);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void nivel::detectarAtaque()
{
    salud->setText(QString::number(prota->obtenerSalud()));
    if (prota->obtenerRectangulo().intersects(murcielago->obtenerRectangulo())) {
        prota->recibir_dagno(murcielago->getdagno());

        int diffX = prota->x() - murcielago->x();
        int diffY = prota->y() - murcielago->y();

        if (abs(diffX) > abs(diffY)) {
            // Rebote horizontal
            if (diffX > 0) {
                for (int i = 0; i < 9; ++i) {
                    prota->move(Qt::Key_D, up_movement_is_valid(prota));
                    if(focus && (prota->y()<(700) || prota->y()>(30))) set_focus_element(prota,16, 16 * 4);
                }
            } else {
                for (int i = 0; i < 9; ++i) {
                    prota->move(Qt::Key_A, up_movement_is_valid(prota));
                    if(focus && (prota->y()<(700) || prota->y()>(30))) set_focus_element(prota,16, 16 * 4);
                }
            }
        } else {
            // Rebote vertical
            if (diffY > 0) {
                for (int i = 0; i < 9; ++i) {
                    prota->move(Qt::Key_S, up_movement_is_valid(prota));
                    if(focus && (prota->y()<(700) || prota->y()>(30))) set_focus_element(prota,16, 16 * 4);
                }
            } else {
                for (int i = 0; i < 9; ++i) {
                    prota->move(Qt::Key_W, up_movement_is_valid(prota));
                    if(focus && (prota->y()<(700) || prota->y()>(30))) set_focus_element(prota,16, 16 * 4);
                }
            }
        }
    }
}
void nivel::setProta_keys()
{
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

void nivel::setNumsFotogramasMurcielago()
{
    numsFotogramasMurcielago = new unsigned int;
    *numsFotogramasMurcielago = 3;

}

void nivel::setNumsFotogramasMamut()
{
    numsFotogramasMamut = new unsigned int[4];
    numsFotogramasMamut[0] = 8;
    numsFotogramasMamut[1] = 8;
    numsFotogramasMamut[2] = 8;
    numsFotogramasMamut[3] = 8;
}

void nivel::setNumsFotogramasTigre()
{
    numsFotogramasTigre = new unsigned int[4];
    numsFotogramasTigre[0] = 4;
    numsFotogramasTigre[1] = 4;
    numsFotogramasTigre[2] = 4;
    numsFotogramasTigre[3] = 4;
}

void nivel::setNumsFotogramasLobo()
{
    numsFotogramasLobo = new unsigned int[4];
    numsFotogramasLobo[0] = 4;
    numsFotogramasLobo[1] = 4;
    numsFotogramasLobo[2] = 4;
    numsFotogramasLobo[3] = 4;
}

void nivel::setup_scene(QString image_Background, QString image_Reference, float nivel_Scale, unsigned int _heightMap,
                        unsigned int _widthMap, unsigned int _x, unsigned int _y)
{
    //------------------------------------------Creacion escena-----------------------------------------------
    graph->setGeometry(0, 0, 1500, 800);
    escena = new QGraphicsScene;
    escena->setSceneRect(0, 0, graph->width() - 2, graph->height() - 2);
    graph->setScene(escena);
    //----------------------------------------------------------------------------------------------

    //------------------------------------------creacion fondoCompleto-----------------------------------------------
    fondoCompleto = new QPixmap();
    fondoCompleto->load(image_Background);
    //----------------------------------------------------------------------------------------------

    //------------------------------------------creacion brocha-----------------------------------------------
    brocha = new QBrush();
    brocha->setTexture(fondoCompleto->copy(_x, _y, _widthMap, _heightMap).scaled(_widthMap * nivel_Scale, _heightMap * nivel_Scale));
    //----------------------------------------------------------------------------------------------

    //------------------------------------------creacion fondoReferencia -----------------------------------------------
    fondoReferencia = new QImage;
    fondoReferencia->load(image_Reference);
    *fondoReferencia = fondoReferencia->copy(_x, _y, _widthMap, _heightMap).scaled(_widthMap * nivel_Scale, _heightMap * nivel_Scale);
    //------------------------------------------------------------------------------------------------------------------

    //-------------------------------------------creacion colorTope-----------------------------------------------------
    colorTope = new QColor("white");
    //------------------------------------------------------------------------------------------------------------------
    escena->setBackgroundBrush(*brocha);

}

void nivel::setup_prota(unsigned short _numNivel)
{
    setProta_keys();
    setNumsFotogramasProta();
    prota = new Entidad(completeAnimationsProta(), numsFotogramasProta, ":/imagenes/caveMan.png", anchoProta, alturaProta, scaleProta,1);
    if (_numNivel == 1)
    {
        prota->setX(28 * anchoProta * scaleProta);
        prota->setY(14 * alturaProta * scaleProta);
    }
    else if(_numNivel == 2)
    {
        prota->setX(2 * anchoProta * scaleProta);
        prota->setY(2 * alturaProta * scaleProta);
    }
    else if(_numNivel == 3)
    {
        prota->setX(8 * anchoProta * scaleProta);
        prota->setY(8 * alturaProta * scaleProta);
    }
    prota->setDagno(50);
    prota->setSalud(100);
    prota->setKeys(prota_keys);
    escena->addItem(prota);
    if (focus) set_focus_element(prota, anchoProta * scaleProta, alturaProta * scaleProta);

}

void nivel::setup_murcielago(unsigned short _numNivel)
{
    setNumsFotogramasMurcielago();
    murcielago = new Enemigo(completeAnimationsMurcielago(), numsFotogramasMurcielago, ":/imagenes/murcielago.png",
                             anchoMurcielago, alturaMurcielago, scaleMurcielago,1,1);

    if(_numNivel == 1)
    {
        murcielago->setX(18.5 * anchoMurcielago * scaleMurcielago);
        murcielago->setY(15 * alturaMurcielago * scaleMurcielago);
    }
    else if(_numNivel == 2)
    {
        murcielago->setX(2 * anchoMurcielago * scaleMurcielago);
        murcielago->setY(2 * alturaMurcielago * scaleMurcielago);
    }
    else if(_numNivel == 3)
    {
        murcielago->setX(8 * anchoMurcielago * scaleMurcielago);
        murcielago->setY(8 * alturaMurcielago * scaleMurcielago);
    }
    murcielago->setDagno(20);
    murcielago->setSalud(60);
    murcielago->set_mov_acelerado(murcielago->x(),murcielago->y(),3,-7,-3,0.1);
    murcielago->set_perseguir(prota,100,0.1);
    murcielago->set_mov_circular_parametros(80, 3 , 0.1, murcielago->x(), murcielago->y());
    escena->addItem(murcielago);
}
void nivel::setup_Mamut(unsigned short _numNivel)
{
    setNumsFotogramasMamut();
    mamut = new Enemigo(completeAnimationsMamut(), numsFotogramasMamut, ":/imagenes/mamut.png",
                        anchoMamut, alturaMamut, scaleMamut,1,1);
    if(_numNivel == 1)
    {
        mamut->setX(10 * anchoMamut * scaleMamut);
        mamut->setY(10 * alturaMamut * scaleMamut);
    }
    else if(_numNivel == 2)
    {
        mamut->setX(1 * anchoMamut * scaleMamut);
        mamut->setY(1 * alturaMamut * scaleMamut);
    }
    else if(_numNivel == 3)
    {
        mamut->setX(1 * anchoMamut * scaleMamut);
        mamut->setY(1 * alturaMamut * scaleMamut);
    }
    mamut->setDagno(20);
    mamut->setSalud(100);
    escena->addItem(mamut);
    //murcielago->set_mov_acelerado(murcielago->x(),murcielago->y(),3,-7,-3,0.1);
    //murcielago->set_perseguir(prota,100,0.1);
    //murcielago->set_mov_circular_parametros(80, 3 , 0.1, murcielago->x(), murcielago->y());
    //escena->addItem(murcielago);
}

void nivel::setup_Tigre(unsigned short _numNivel)
{
    setNumsFotogramasTigre();
    tigre = new Enemigo(completeAnimationsTigre(), numsFotogramasTigre, ":/imagenes/kati-eloranta-tiger.png",
                        anchoTigre, alturaTigre, scaleTigre,1,0);
    if(_numNivel == 1)
    {
        tigre->setX(10 * anchoTigre * scaleTigre);
        tigre->setY(10 * alturaTigre * scaleTigre);
    }
    else if(_numNivel == 2)
    {
        tigre->setX(1 * anchoTigre * scaleTigre);
        tigre->setY(1 * alturaTigre * scaleTigre);
    }
    else if(_numNivel == 3)
    {
        tigre->setX(1 * anchoTigre * scaleTigre);
        tigre->setY(1 * alturaTigre * scaleTigre);
    }
    tigre->setDagno(20);
    tigre->setSalud(60);
    escena->addItem(tigre);
    //murcielago->set_mov_acelerado(murcielago->x(),murcielago->y(),3,-7,-3,0.1);
    //murcielago->set_perseguir(prota,100,0.1);
    //murcielago->set_mov_circular_parametros(80, 3 , 0.1, murcielago->x(), murcielago->y());
    //escena->addItem(murcielago);
}

void nivel::setup_Lobo(unsigned short _numNivel)
{
    setNumsFotogramasLobo();
    lobo = new Enemigo(completeAnimationsLobo(), numsFotogramasLobo, ":/imagenes/wolfsheet6.png",
                        anchoLobo, alturaLobo, scaleLobo,1,0);
    if(_numNivel == 1)
    {
        lobo->setX(10 * anchoLobo * scaleLobo);
        lobo->setY(10 * alturaLobo * scaleLobo);
    }
    else if(_numNivel == 2)
    {
        lobo->setX(3 * anchoLobo * scaleLobo);
        lobo->setY(3 * alturaLobo * scaleLobo);
    }
    else if(_numNivel == 3)
    {
        lobo->setX(1 * anchoLobo * scaleLobo);
        lobo->setY(1 * alturaLobo * scaleLobo);
    }
    lobo->setDagno(20);
    lobo->setSalud(60);
    escena->addItem(lobo);
}


bool nivel::left_movement_is_valid(Entidad *item)
{
    int xf1,yf1,xf2,yf2;
    bool is_valid1, is_valid2;

    xf1 = item->x()-item->getVelocidad();
    yf1 = item->y();
    xf2 = item->x()-item->getVelocidad();
    yf2 = item->y()+(alturaProta*scaleProta)-1;

    is_valid1 = fondoReferencia->pixelColor(xf1, yf1) != *colorTope;
    is_valid2 = fondoReferencia->pixelColor(xf2, yf2) != *colorTope;

    return is_valid2 && is_valid1;
}

bool nivel::right_movement_is_valid(Entidad *item)
{
    int xf1,yf1,xf2,yf2;
    bool is_valid1, is_valid2;

    xf1 = item->x()+(anchoProta * scaleProta) - 1 + item->getVelocidad();
    yf1 = item->y();
    xf2 = item->x()+(anchoProta * scaleProta) - 1 + item->getVelocidad();
    yf2 = item->y()+(alturaProta * scaleProta) - 1;



    is_valid1 = fondoReferencia->pixelColor(xf1, yf1) != *colorTope;
    is_valid2 = fondoReferencia->pixelColor(xf2, yf2) != *colorTope;


    return is_valid2 && is_valid1;
}

bool nivel::up_movement_is_valid(Entidad *item)
{
    int xf1,yf1,xf2,yf2;
    bool is_valid1, is_valid2;

    xf1 = item->x();
    yf1 = item->y() - item->getVelocidad();
    xf2 = item->x() + (anchoProta * scaleProta) - 1;
    yf2 = item->y() - item->getVelocidad();

    is_valid1 = fondoReferencia->pixelColor(xf1, yf1) != *colorTope;
    is_valid2 = fondoReferencia->pixelColor(xf2, yf2) != *colorTope;

    return is_valid2 && is_valid1;
}

bool nivel::down_movement_is_valid(Entidad *item)
{
    int xf1,yf1,xf2,yf2;
    bool is_valid1, is_valid2;

    xf1 = item->x();
    yf1 = item->y() + item->getVelocidad() + (alturaProta * scaleProta) - 1;
    xf2 = item->x() + (anchoProta * scaleProta) - 1;
    yf2 = item->y() + (alturaProta * scaleProta) - 1 + item->getVelocidad();

    is_valid1 = fondoReferencia->pixelColor(xf1, yf1) != *colorTope;
    is_valid2 = fondoReferencia->pixelColor(xf2, yf2) != *colorTope;

    return is_valid2 && is_valid1;
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

QVector<QRect> nivel::completeAnimationsMurcielago()
{
    QVector<QRect> animations;
    QRect dimFlotar;

    dimFlotar.setX(1 * anchoMurcielago);
    dimFlotar.setY(0);
    dimFlotar.setHeight(1 * alturaMurcielago);
    dimFlotar.setWidth(3 * anchoMurcielago);

    animations.push_back(dimFlotar);
    return animations;
}

QVector<QRect> nivel::completeAnimationsTigre()
{
    QVector<QRect> animations;
    QRect dimLeft;
    QRect dimRight;
    QRect dimUp;
    QRect dimDown;

    dimLeft.setX(0 * anchoTigre);
    dimLeft.setY(2 * alturaTigre);
    dimLeft.setHeight(1 * anchoTigre);
    dimLeft.setWidth(4 * alturaTigre);

    dimRight.setX(4 * alturaTigre);
    dimRight.setY(2 * alturaTigre);
    dimRight.setHeight(1 * anchoTigre);
    dimRight.setWidth(4 * alturaTigre);

    dimUp.setX(4 * anchoTigre);
    dimUp.setY(0 * alturaTigre);
    dimUp.setHeight(1 * alturaTigre);
    dimUp.setWidth(4 * anchoTigre);

    dimDown.setX(0 * anchoTigre);
    dimDown.setY(0 * alturaTigre);
    dimDown.setHeight(1 * alturaTigre);
    dimDown.setWidth(4 * anchoTigre);

    animations.push_back(dimLeft);
    animations.push_back(dimRight);
    animations.push_back(dimUp);
    animations.push_back(dimDown);
    return animations;
}

QVector<QRect> nivel::completeAnimationsLobo()
{
    QVector<QRect> animations;
    QRect dimLeft;
    QRect dimRight;
    QRect dimUp;
    QRect dimDown;

    dimLeft.setX(0 * anchoLobo);
    dimLeft.setY(2 * alturaLobo);
    dimLeft.setHeight(1 * anchoLobo);
    dimLeft.setWidth(4 * alturaLobo);

    dimRight.setX(4 * alturaLobo);
    dimRight.setY(2 * alturaLobo);
    dimRight.setHeight(1 * anchoLobo);
    dimRight.setWidth(4 * alturaLobo);

    dimUp.setX(4 * anchoLobo);
    dimUp.setY(0 * alturaLobo);
    dimUp.setHeight(1 * alturaLobo);
    dimUp.setWidth(4 * anchoLobo);

    dimDown.setX(0 * anchoLobo);
    dimDown.setY(0 * alturaLobo);
    dimDown.setHeight(1 * alturaLobo);
    dimDown.setWidth(4 * anchoLobo);

    animations.push_back(dimLeft);
    animations.push_back(dimRight);
    animations.push_back(dimUp);
    animations.push_back(dimDown);
    return animations;
}

QVector<QRect> nivel::completeAnimationsMamut()
{
    QVector<QRect> animations;
    QRect dimLeft;
    QRect dimRight;
    QRect dimUp;
    QRect dimDown;

    dimLeft.setX(0);
    dimLeft.setY(2 * alturaMamut);
    dimLeft.setHeight(1 * alturaMamut);
    dimLeft.setWidth(8 * anchoMamut);

    dimRight.setX(0);
    dimRight.setY(4 * alturaMamut);
    dimRight.setHeight(1 * alturaMamut);
    dimRight.setWidth(8 * anchoMamut);

    dimUp.setX(0);
    dimUp.setY(3 * alturaMamut);
    dimUp.setHeight(1 * alturaMamut);
    dimUp.setWidth(8 * anchoMamut);

    dimDown.setX(0);
    dimDown.setY(1 * alturaMamut);
    dimDown.setHeight(1 * alturaMamut);
    dimDown.setWidth(8 * anchoMamut);

    animations.push_back(dimLeft);
    animations.push_back(dimRight);
    animations.push_back(dimUp);
    animations.push_back(dimDown);
    return animations;
}
