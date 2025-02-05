#include "nivel.h"
#include "qlabel.h"

nivel::nivel(QGraphicsView *graphicsV, QString imageBackground, QString imageReference, float nivelScale,
             unsigned int heightMap, unsigned int widthMap, unsigned int x, unsigned int y, unsigned short numNivel,
             bool setFocus, QLabel* salud, int dificultad)
{
    focus = setFocus;
    graph = graphicsV;
    pausaN = 0;
    puntaje = "0";
    numeroSigNivel = numNivel + '1';
    dificultadNivel = dificultad;
    prota = nullptr;
    mamut = nullptr;
    murcielagos = nullptr;
    tigres = nullptr;
    lobos = nullptr;
    comidas = nullptr;
    trigos = nullptr;
    zanahorias = nullptr;
    tomates = nullptr;
    cavernicolas = nullptr;

    numsFotogramasProta = nullptr;
    numsFotogramasMurcielago = nullptr;
    numsFotogramasMamut = nullptr;
    numsFotogramasTigre = nullptr;
    numsFotogramasLobo = nullptr;
    numsFotogramasComida = nullptr;
    numsFotogramasTrigo = nullptr;
    numsFotogramasZanahoria = nullptr;
    numsFotogramasTomate = nullptr;
    numsFotogramasCavernicola = nullptr;

    setup_scene(imageBackground, imageReference, nivelScale, heightMap, widthMap, x, y);
    setup_prota(numNivel);
    setup_murcielago(numNivel);
    setup_Mamut(numNivel);
    setup_Tigre(numNivel);
    setup_Lobo(numNivel);
    setup_Trigo(numNivel);
    setup_Zanahoria(numNivel);
    setup_Tomate(numNivel);
    setup_cavernicola(numNivel);
    this->salud = salud;
    timeColision = new QTimer;
    QObject::connect(timeColision,SIGNAL(timeout()),this,SLOT(detectarAtaque()));
    timeColision->start(200);
    if (murcielagos != nullptr)
    {
        for (int i = 0; i < 4; i++)
        {
            connect(this, SIGNAL(pausarEnemigo()), murcielagos[i], SLOT(pausa()));
            connect(this, SIGNAL(renaudarEnemigo()), murcielagos[i], SLOT(renaudar()));
        }
    }

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

nivel::~nivel()
{
    if (prota != nullptr) delete prota;
    if (murcielagos != nullptr) delete[] murcielagos;
    if (mamut != nullptr) delete mamut;
    if (tigres != nullptr) delete[] tigres;
    if (lobos != nullptr) delete[] lobos;
    if (comidas != nullptr) delete[] comidas;
    if (trigos != nullptr) delete[] trigos;
    if (zanahorias != nullptr) delete[] zanahorias;
    if (tomates != nullptr) delete[] tomates;
    if (cavernicolas != nullptr) delete[] cavernicolas;


    if (numsFotogramasProta != nullptr)delete[] numsFotogramasProta;
    if (numsFotogramasMurcielago != nullptr)delete numsFotogramasMurcielago;
    if (numsFotogramasMamut != nullptr)delete[] numsFotogramasMamut;
    if (numsFotogramasTigre != nullptr)delete[] numsFotogramasTigre;
    if (numsFotogramasLobo != nullptr)delete[] numsFotogramasLobo;
    if (numsFotogramasComida != nullptr)delete numsFotogramasComida;
    if (numsFotogramasTrigo != nullptr)delete numsFotogramasTrigo;
    if (numsFotogramasZanahoria != nullptr)delete numsFotogramasZanahoria;
    if (numsFotogramasTomate != nullptr)delete numsFotogramasTomate;
    if (numsFotogramasCavernicola != nullptr) delete[] numsFotogramasCavernicola;

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
    if (!pausaN)
    {
        bool isValid = 1;

        if(unsigned(event->key()) == prota_keys[0]) isValid = left_movement_is_valid(prota);
        else if(unsigned(event->key()) == prota_keys[1]) isValid = right_movement_is_valid(prota);
        else if(unsigned(event->key()) == prota_keys[2]) isValid = up_movement_is_valid(prota);
        else if(unsigned(event->key()) == prota_keys[3]) isValid = down_movement_is_valid(prota);

        //if(murcielagos != nullptr && (prota->y()>= 2000 && prota->y()<2100)) murcielagos[2]->empezarPerseguir();
        prota->move(event->key(), isValid);
        prota->muerte(event->key());
        if(mamut != nullptr)mamut->atack(event->key());
        if(mamut != nullptr) mamut->move(event->key(), 1);

        for (int i = 0; i < 4; i++){
            if(tigres != nullptr)tigres[i]->atack(event->key());
            if(tigres != nullptr)tigres[i]->move(event->key(), 1);
        }

        for (int i = 0; i < 4; i++){
            if(lobos != nullptr)lobos[i]->atack(event->key());
            if(lobos != nullptr)lobos[i]->move(event->key(), 1);
        }

        for (int i = 0; i < 4; i++){
            if(cavernicolas != nullptr)cavernicolas[i]->muerte(event->key());
            if(cavernicolas != nullptr)cavernicolas[i]->move(event->key(), 1);
        }

        if(focus && (prota->y()<(700) || prota->y()>(30))) set_focus_element(prota,16, 16 * 4);
        if((prota->x() >= 2560 && prota->x() <= 2680) && (prota->y() >= 4480 && prota->y() <= 4600))
        {
            puntaje = "10";
            emit heTerminado(numeroSigNivel);
        }
    }
}

QString nivel::getPuntaje() const
{
    return puntaje;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void nivel::detectarAtaque()
{
    if (!pausaN)
    {
        bool colision = 0;
        short int numEnemigo;
        char enemigo;

        if (mamut != nullptr && prota->obtenerRectangulo().intersects(mamut->obtenerRectangulo()))
        {
            colision = 1;
            prota->recibir_dagno(mamut->getdagno());
            enemigo = 'M';
        }

        for (int j = 0; j < 4; j++)
        {
            if (tigres != nullptr && prota->obtenerRectangulo().intersects(tigres[j]->obtenerRectangulo()))
            {
                colision = 1;
                prota->recibir_dagno(tigres[j]->getdagno());
                numEnemigo = j;
                enemigo = 't';
                break;
            }
            else if (murcielagos != nullptr && prota->obtenerRectangulo().intersects(murcielagos[j]->obtenerRectangulo()))
            {
                colision = 1;
                prota->recibir_dagno(murcielagos[j]->getdagno());
                numEnemigo = j;
                enemigo = 'm';
                break;
            }
            else if (lobos != nullptr && prota->obtenerRectangulo().intersects(lobos[j]->obtenerRectangulo()))
            {
                colision = 1;
                prota->recibir_dagno(lobos[j]->getdagno());
                numEnemigo = j;
                enemigo = 'l';
                break;
            }
            else if (cavernicolas != nullptr && prota->obtenerRectangulo().intersects(cavernicolas[j]->obtenerRectangulo()))
            {
                colision = 1;
                prota->recibir_dagno(cavernicolas[j]->getdagno());
                numEnemigo = j;
                enemigo = 'c';
                break;
            }
        }

        salud->setText(QString::number(prota->obtenerSalud()));
        if (colision) {
            int diffX = 0;
            int diffY = 0;
            if (murcielagos != nullptr && enemigo == 'm')
            {
                diffX = prota->x() - murcielagos[numEnemigo]->x();
                diffY = prota->y() - murcielagos[numEnemigo]->y();
            }
            else if (mamut != nullptr && enemigo == 'M')
            {
                diffX = prota->x() - mamut->x();
                diffY = prota->y() - mamut->y();
            }
            else if (tigres != nullptr && enemigo == 't')
            {
                diffX = prota->x() - tigres[numEnemigo]->x();
                diffY = prota->y() - tigres[numEnemigo]->y();
            }
            else if (lobos != nullptr && enemigo == 'l')
            {
                diffX = prota->x() - lobos[numEnemigo]->x();
                diffY = prota->y() - lobos[numEnemigo]->y();
            }
            else if (cavernicolas != nullptr && enemigo == 'c')
            {
                diffX = prota->x() - cavernicolas[numEnemigo]->x();
                diffY = prota->y() - cavernicolas[numEnemigo]->y();
            }

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
        if (prota->obtenerSalud() == 0)
        {
            puntaje = "10";
            emit heTerminado(numeroSigNivel);
        }
    }
}

void nivel::recuperaEscena()
{
    pausaN = 0;
    emit renaudarEnemigo();
    graph->setScene(escena);
}

void nivel::pausarNivel()
{
    emit pausarEnemigo();
    pausaN = 1;
}
void nivel::setProta_keys()
{
    prota_keys[0] = Qt::Key_A;
    prota_keys[1] = Qt::Key_D;
    prota_keys[2] = Qt::Key_W;
    prota_keys[3] = Qt::Key_S;
    prota_keys[4] = Qt::Key_Space;
}

void nivel::setMamut_keys()
{
    mamut_keys[0] = Qt::Key_J;
    mamut_keys[1] = Qt::Key_L;
    mamut_keys[2] = Qt::Key_I;
    mamut_keys[3] = Qt::Key_K;
    mamut_keys[4] = Qt::Key_U;
    mamut_keys[5] = Qt::Key_O;
    mamut_keys[6] = Qt::Key_Y;
    mamut_keys[7] = Qt::Key_P;
}

void nivel::setTigre_keys()
{
   tigre_keys[0] = Qt::Key_4;
   tigre_keys[1] = Qt::Key_6;
   tigre_keys[2] = Qt::Key_8;
   tigre_keys[3] = Qt::Key_2;
   tigre_keys[4] = Qt::Key_7;
   tigre_keys[5] = Qt::Key_9;
   tigre_keys[6] = Qt::Key_1;
   tigre_keys[7] = Qt::Key_3;
}

void nivel::setLobo_keys()
{
    lobo_keys[0] = Qt::Key_Q;
    lobo_keys[1] = Qt::Key_E;
    lobo_keys[2] = Qt::Key_R;
    lobo_keys[3] = Qt::Key_T;
    lobo_keys[4] = Qt::Key_F;
    lobo_keys[5] = Qt::Key_G;
    lobo_keys[6] = Qt::Key_H;
    lobo_keys[7] = Qt::Key_N;
}

void nivel::setCavernicola_keys()
{
    cavernicola_keys [0] = Qt::Key_V;
    cavernicola_keys [1] = Qt::Key_M;
    cavernicola_keys [2] = Qt::Key_B;
    cavernicola_keys [3] = Qt::Key_N;
    cavernicola_keys [4] = Qt::Key_0;

}


void nivel::setNumsFotogramasProta()
{
    numsFotogramasProta = new unsigned int[5];
    numsFotogramasProta[0] = 3;
    numsFotogramasProta[1] = 3;
    numsFotogramasProta[2] = 3;
    numsFotogramasProta[3] = 3;
    numsFotogramasProta[4] = 4;
}

void nivel::setNumsFotogramasMurcielago()
{
    numsFotogramasMurcielago = new unsigned int;
    *numsFotogramasMurcielago = 3;

}

void nivel::setNumsFotogramasMamut()
{
    numsFotogramasMamut = new unsigned int[8];
    numsFotogramasMamut[0] = 8;
    numsFotogramasMamut[1] = 8;
    numsFotogramasMamut[2] = 8;
    numsFotogramasMamut[3] = 8;
    numsFotogramasMamut[4] = 6;
    numsFotogramasMamut[5] = 6;
    numsFotogramasMamut[6] = 6;
    numsFotogramasMamut[7] = 6;

}

void nivel::setNumsFotogramasTigre()
{
    numsFotogramasTigre = new unsigned int[8];
    numsFotogramasTigre[0] = 4;
    numsFotogramasTigre[1] = 4;
    numsFotogramasTigre[2] = 4;
    numsFotogramasTigre[3] = 4;
    numsFotogramasTigre[4] = 4;
    numsFotogramasTigre[5] = 4;
    numsFotogramasTigre[6] = 4;
    numsFotogramasTigre[7] = 4;

}

void nivel::setNumsFotogramasLobo()
{
    numsFotogramasLobo = new unsigned int[8];
    numsFotogramasLobo[0] = 4;
    numsFotogramasLobo[1] = 4;
    numsFotogramasLobo[2] = 4;
    numsFotogramasLobo[3] = 4;
    numsFotogramasLobo[4] = 4;
    numsFotogramasLobo[5] = 4;
    numsFotogramasLobo[6] = 4;
    numsFotogramasLobo[7] = 4;
}


void nivel::setNumsFotogramasComida()
{
    numsFotogramasComida = new unsigned int;
    *numsFotogramasComida = 1;
}

void nivel::setNumsFotogramasTrigo()
{
    numsFotogramasTrigo = new unsigned int;
    *numsFotogramasTrigo = 1;
}

void nivel::setNumsFotogramasZanahoria()
{
    numsFotogramasZanahoria = new unsigned int;
    *numsFotogramasZanahoria = 1;
}

void nivel::setNumsFotogramasTomate()
{
    numsFotogramasTomate = new unsigned int;
    *numsFotogramasTomate = 1;
}



void nivel::setNumsFotogramasCavernicolas()
{
    numsFotogramasCavernicola = new unsigned int[5];
    numsFotogramasCavernicola[0] = 3;
    numsFotogramasCavernicola[1] = 3;
    numsFotogramasCavernicola[2] = 3;
    numsFotogramasCavernicola[3] = 3;
    numsFotogramasCavernicola[4] = 4;
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
        prota->setX(11.5 * anchoProta * scaleProta);
        prota->setY(5.5 * alturaProta * scaleProta);
    }
    else if(_numNivel == 3)
    {
        prota->setX(10.5 * anchoProta * scaleProta);
        prota->setY(6 * alturaProta * scaleProta);
    }
    prota->setDagno(20);
    prota->setSalud(100);
    prota->setKeys(prota_keys);
    escena->addItem(prota);
    if (focus) set_focus_element(prota, anchoProta * scaleProta, alturaProta * scaleProta);

}

void nivel::setup_murcielago(unsigned short _numNivel)
{
    if (_numNivel == 1){
        setNumsFotogramasMurcielago();
        murcielagos = new Enemigo*[4];
        for (int i = 0; i < 2; i++)
        {
            murcielagos[i] = new Enemigo(completeAnimationsMurcielago(), numsFotogramasMurcielago, ":/imagenes/murcielago.png",
                                     anchoMurcielago, alturaMurcielago, scaleMurcielago,'M',1);
        }

        murcielagos[0]->setX(18.5 * anchoMurcielago * scaleMurcielago);
        murcielagos[0]->setY(15 * alturaMurcielago * scaleMurcielago);
        murcielagos[0]->set_aplicarMovimientoPendular(murcielagos[0]->x(), murcielagos[0]->y(),3,100,1,0.1);


        murcielagos[1]->setX(19 * anchoMurcielago * scaleMurcielago);
        murcielagos[1]->setY(52.5 * alturaMurcielago * scaleMurcielago);
        murcielagos[1]->set_aplicarMovimientoPendular(murcielagos[1]->x(), murcielagos[1]->y(),3,100,1,0.1);

        for (int i = 0; i < 2; i++)
        {
            murcielagos[i+2] = new Enemigo(completeAnimationsMurcielago(), numsFotogramasMurcielago, ":/imagenes/murcielago.png",
                                         anchoMurcielago, alturaMurcielago, scaleMurcielago,'j',1);
        }

        murcielagos[2]->setX(22.5 * anchoMurcielago * scaleMurcielago);
        murcielagos[2]->setY(31 * alturaMurcielago * scaleMurcielago);
        murcielagos[2]->set_mov_circular_parametros(80, 3 , 0.1, murcielagos[2]->x(), murcielagos[2]->y());

        murcielagos[3]->setX(16 * anchoMurcielago * scaleMurcielago);
        murcielagos[3]->setY(37  * alturaMurcielago * scaleMurcielago);
        murcielagos[3]->set_mov_circular_parametros(80, 3 , 0.1, murcielagos[3]->x(), murcielagos[3]->y());

        for (int i = 0; i < 4; i++)
        {
            murcielagos[i]->setDagno(int((dificultadNivel / 3.0) * 40));
            murcielagos[i]->setSalud(60);
            //murcielagos[i]->set_mov_acelerado(murcielagos[i]->x(),murcielagos[i]->y(),3,-7,-3,0.1);
            //murcielagos[i]->set_perseguir(prota,100,0.1);
            //murcielagos[i]->set_aplicarMovimientoPendular(murcielagos[0]->x(), murcielagos[0]->y(),3,100,1,0.1);
            escena->addItem(murcielagos[i]);
        }
    }
}
void nivel::setup_Mamut(unsigned short _numNivel)
{
    if(_numNivel == 2 || _numNivel == 3){
        setMamut_keys();
        setNumsFotogramasMamut();

        mamut = new Enemigo(completeAnimationsMamut(), numsFotogramasMamut, ":/imagenes/mamut.png",
                            anchoMamut, alturaMamut, scaleMamut,'m',1);


        mamut->setX(5.5 * anchoMamut * scaleMamut);
        mamut->setY(3 * alturaMamut * scaleMamut);

        mamut->setDagno(int((dificultadNivel / 3.0) * 50));
        mamut->setSalud(100);
        mamut->set_perseguir(prota,100,0.1);
        mamut->setKeys(mamut_keys);
        escena->addItem(mamut);
    }
}

void nivel::setup_Tigre(unsigned short _numNivel)
{
    if(_numNivel == 2 || _numNivel == 3){
        setTigre_keys();
        setNumsFotogramasTigre();
        tigres = new Enemigo*[4];

        tigres[0] = new Enemigo(completeAnimationsTigre(), numsFotogramasTigre, ":/imagenes/kati-eloranta-tiger.png",
                               anchoTigre, alturaTigre, scaleTigre,'t',0);

        tigres[0]->setX(9 * anchoTigre * scaleTigre);
        tigres[0]->setY(0 * alturaTigre * scaleTigre);
        tigres[0]->set_mov_acelerado(tigres[0]->x(),tigres[0]->y(),2,0,10,0.1,9 * anchoTigre * scaleTigre,5.7 * alturaTigre * scaleTigre);

        tigres[1] = new Enemigo(completeAnimationsTigre(), numsFotogramasTigre, ":/imagenes/kati-eloranta-tiger.png",
                                anchoTigre, alturaTigre, scaleTigre,'y',0);

        tigres[1]->setX(21 * anchoTigre * scaleTigre);
        tigres[1]->setY(2.4 * alturaTigre * scaleTigre);
        tigres[1]->set_mov_acelerado(tigres[1]->x(),tigres[1]->y(),2,-10,0,0.1,0 * anchoTigre * scaleTigre,2.4 * alturaTigre * scaleTigre);

        tigres[2] = new Enemigo(completeAnimationsTigre(), numsFotogramasTigre, ":/imagenes/kati-eloranta-tiger.png",
                                anchoTigre, alturaTigre, scaleTigre,'u',0);

        tigres[2]->setX(9 * anchoTigre * scaleTigre);
        tigres[2]->setY(5.7 * alturaTigre * scaleTigre);
        tigres[2]->set_mov_acelerado(tigres[2]->x(),tigres[2]->y(),2,0,-10,0.1,9 * anchoTigre * scaleTigre,0 * alturaTigre * scaleTigre);

        tigres[3] = new Enemigo(completeAnimationsTigre(), numsFotogramasTigre, ":/imagenes/kati-eloranta-tiger.png",
                                anchoTigre, alturaTigre, scaleTigre,'i',0);

        tigres[3]->setX(0 * anchoTigre * scaleTigre);
        tigres[3]->setY(2.4 * alturaTigre * scaleTigre);
        tigres[3]->set_mov_acelerado(tigres[3]->x(),tigres[3]->y(),3,10,0,0.1,21 * anchoTigre * scaleTigre,2.4 * alturaTigre * scaleTigre);


        for (int i = 0; i < 4; i++){
            tigres[i]->setDagno(int((dificultadNivel / 3.0) * 40));
            tigres[i]->setSalud(60);
            tigres[i]->setKeys(tigre_keys);
            escena->addItem(tigres[i]);
        }
    }
}

void nivel::setup_Lobo(unsigned short _numNivel)
{
    if(_numNivel == 1 || _numNivel == 2 ){
        setLobo_keys();
        setNumsFotogramasLobo();
        lobos = new Enemigo*[4];

            if(_numNivel == 1)
            {
                lobos[0] = new Enemigo(completeAnimationsLobo(), numsFotogramasLobo, ":/imagenes/wolfsheet6.png",
                                   anchoLobo, alturaLobo, scaleLobo,1,0);
                lobos[0]->setX(27 * anchoLobo * scaleLobo);
                lobos[0]->setY(19 * alturaLobo * scaleLobo);

                lobos[1] = new Enemigo(completeAnimationsLobo(), numsFotogramasLobo, ":/imagenes/wolfsheet6.png",
                                       anchoLobo, alturaLobo, scaleLobo,1,0);
                lobos[1]->setX(56 * anchoLobo * scaleLobo);
                lobos[1]->setY(25 * alturaLobo * scaleLobo);

                lobos[2] = new Enemigo(completeAnimationsLobo(), numsFotogramasLobo, ":/imagenes/wolfsheet6.png",
                                       anchoLobo, alturaLobo, scaleLobo,1,0);
                lobos[2]->setX(40.5 * anchoLobo * scaleLobo);
                lobos[2]->setY(31.3 * alturaLobo * scaleLobo);

                lobos[3] = new Enemigo(completeAnimationsLobo(), numsFotogramasLobo, ":/imagenes/wolfsheet6.png",
                                       anchoLobo, alturaLobo, scaleLobo,1,0);
                lobos[3]->setX(2 * anchoLobo * scaleLobo);
                lobos[3]->setY(23 * alturaLobo * scaleLobo);

            }
            else
            {
                lobos[0] = new Enemigo(completeAnimationsLobo(), numsFotogramasLobo, ":/imagenes/wolfsheet6.png",
                                       anchoLobo, alturaLobo, scaleLobo,'l',0);
                lobos[0]->setX(0 * anchoLobo * scaleLobo);
                lobos[0]->setY(0 * alturaLobo * scaleLobo);
                lobos[0]->set_mov_acelerado(lobos[0]->x(),lobos[0]->y(),3,10,10,0.1,21 * anchoLobo * scaleLobo,2.4 * alturaLobo * scaleLobo);

                lobos[1] = new Enemigo(completeAnimationsLobo(), numsFotogramasLobo, ":/imagenes/wolfsheet6.png",
                                      anchoLobo, alturaLobo, scaleLobo,'z',0);
                lobos[1]->setX(28.8 * anchoLobo * scaleLobo);
                lobos[1]->setY(0 * alturaLobo * scaleLobo);
                lobos[1]->set_mov_acelerado(lobos[1]->x(),lobos[1]->y(),3,-10,10,0.1,21 * anchoLobo * scaleLobo,2.4 * alturaLobo * scaleLobo);

                lobos[2] = new Enemigo(completeAnimationsLobo(), numsFotogramasLobo, ":/imagenes/wolfsheet6.png",
                                       anchoLobo, alturaLobo, scaleLobo,'x',0);
                lobos[2]->setX(28.8 * anchoLobo * scaleLobo);
                lobos[2]->setY(5.7 * alturaLobo * scaleLobo);
                lobos[2]->set_mov_acelerado(lobos[2]->x(),lobos[2]->y(),3,-10,-10,0.1,21 * anchoLobo * scaleLobo,2.4 * alturaLobo * scaleLobo);

                lobos[3] = new Enemigo(completeAnimationsLobo(), numsFotogramasLobo, ":/imagenes/wolfsheet6.png",
                                       anchoLobo, alturaLobo, scaleLobo,'v',0);
                lobos[3]->setX(0 * anchoLobo * scaleLobo);
                lobos[3]->setY(5.7 * alturaLobo * scaleLobo);
                lobos[3]->set_mov_acelerado(lobos[3]->x(),lobos[3]->y(),3,10,-10,0.1,21 * anchoLobo * scaleLobo,2.4 * alturaLobo * scaleLobo);
            }

        for (int i = 0; i < 4; i++)
        {
                lobos[i]->setDagno(int((dificultadNivel / 3) * 40));
                lobos[i]->setSalud(60);
                lobos[i]->setKeys(lobo_keys);
                escena->addItem(lobos[i]);
        }

    }
}

void nivel::setup_Comida(unsigned short _numNivel)
{
    // MOVER A ENEMIGO
    if (_numNivel == 1 || _numNivel == 2 || _numNivel == 3){
        setNumsFotogramasComida();
        comidas = new recursos*[8];
        for (int i = 0; i < 8; i++) //------
        {
            comidas[i] = new recursos(completeAnimationcomida(), *numsFotogramasComida, anchocomida,
                                      alturacomida, scaleComida, 1, ":/imagenes/food.png",'k',1);
        }

        if(_numNivel == 1)
        {
            comidas[0]->setX(27 * anchocomida * scaleLobo);
            comidas[0]->setY(19 * alturaLobo * scaleLobo);

            comidas[1]->setX(27 * anchoLobo * scaleLobo);
            comidas[1]->setY(19 * alturaLobo * scaleLobo);

            comidas[2]->setX(27 * anchoLobo * scaleLobo);
            comidas[2]->setY(19 * alturaLobo * scaleLobo);

            comidas[3]->setX(27 * anchoLobo * scaleLobo);
            comidas[3]->setY(19 * alturaLobo * scaleLobo);

            comidas[4]->setX(27 * anchoLobo * scaleLobo);
            comidas[4]->setY(19 * alturaLobo * scaleLobo);

            comidas[5]->setX(27 * anchoLobo * scaleLobo);
            comidas[5]->setY(19 * alturaLobo * scaleLobo);

            comidas[6]->setX(27 * anchoLobo * scaleLobo);
            comidas[6]->setY(19 * alturaLobo * scaleLobo);

            comidas[7]->setX(27 * anchoLobo * scaleLobo);
            comidas[7]->setY(19 * alturaLobo * scaleLobo);

        }
        else
        {
            lobos[0]->setX(17 * anchoLobo * scaleLobo);
            lobos[0]->setY(0 * alturaLobo * scaleLobo);

            lobos[1]->setX(28.8 * anchoLobo * scaleLobo);
            lobos[1]->setY(3.1 * alturaLobo * scaleLobo);

            lobos[2]->setX(17 * anchoLobo * scaleLobo);
            lobos[2]->setY(5.7 * alturaLobo * scaleLobo);

            lobos[3]->setX(0 * anchoLobo * scaleLobo);
            lobos[3]->setY(3.1 * alturaLobo * scaleLobo);
        }
        for (int i = 0; i < 4; i++)
        {
            murcielagos[i]->setDagno(20);
            murcielagos[i]->setSalud(60);
            //murcielagos[i]->set_mov_acelerado(murcielagos[i]->x(),murcielagos[i]->y(),3,-7,-3,0.1);
            murcielagos[i]->set_perseguir(prota,100,0.1);
            //murcielagos[i]->set_mov_circular_parametros(80, 3 , 0.1, murcielagos[i]->x(), murcielagos[i]->y());
            escena->addItem(murcielagos[i]);
        }
    }
}

void nivel::setup_Trigo(unsigned short _numNivel)
{
    if (_numNivel == 3){
        setNumsFotogramasTrigo();
        trigos = new recursos*[4];

        for (int i = 0; i < 4; i++){
            trigos[i] = new recursos(completeAnimationtrigo(), *numsFotogramasTrigo, anchoTrigo,
                                     alturaTrigo,scaleTrigo,1,":/imagenes/farming.png",'T',1);
        }
        //trigos[0]->setX(1 * anchoTrigo * scaleTrigo);
        //trigos[0]->setY(1 * alturaTrigo * scaleTrigo);

        trigos[0]->setX(22.5 * anchoTrigo * scaleTrigo);
        trigos[0]->setY(13.3 * alturaTrigo * scaleTrigo);

        trigos[1]->setX(24.5 * anchoTrigo * scaleTrigo);
        trigos[1]->setY(13.3 * alturaTrigo * scaleTrigo);

        trigos[2]->setX(26.3 * anchoTrigo * scaleTrigo);
        trigos[2]->setY(13.3 * alturaTrigo * scaleTrigo);

        trigos[3]->setX(28* anchoTrigo * scaleTrigo);
        trigos[3]->setY(13.3 * alturaTrigo * scaleTrigo);



        for (int i = 0; i < 4; i++)
        {
            escena->addItem(trigos[i]);
        }
    }
}

void nivel::setup_Zanahoria(unsigned short _numNivel)
{
    if (_numNivel == 3){
        setNumsFotogramasZanahoria();
        zanahorias = new recursos*[4];

        for (int i = 0; i < 4; i++){
            zanahorias[i] = new recursos(completeAnimationzanahoria(), *numsFotogramasZanahoria, anchoTrigo,
                                     alturaTrigo,scaleTrigo,1,":/imagenes/farming.png",'z',1);
        }


        zanahorias[0]->setX(22.5 * anchoTrigo * scaleTrigo);
        zanahorias[0]->setY(14.5 * alturaTrigo * scaleTrigo);

        zanahorias[1]->setX(24.5 * anchoTrigo * scaleTrigo);
        zanahorias[1]->setY(14.5 * alturaTrigo * scaleTrigo);

        zanahorias[2]->setX(26.3 * anchoTrigo * scaleTrigo);
        zanahorias[2]->setY(14.5 * alturaTrigo * scaleTrigo);

        zanahorias[3]->setX(28* anchoTrigo * scaleTrigo);
        zanahorias[3]->setY(14.5 * alturaTrigo * scaleTrigo);



        for (int i = 0; i < 4; i++)
        {
            escena->addItem(zanahorias[i]);
        }
    }
}

void nivel::setup_Tomate(unsigned short _numNivel)
{
    if (_numNivel == 3){
        setNumsFotogramasTomate();
        tomates = new recursos*[4];

        for (int i = 0; i < 4; i++){
            tomates[i] = new recursos(completeAnimationtomates(), *numsFotogramasTomate, anchoTrigo,
                                         alturaTrigo,scaleTrigo,1,":/imagenes/farming.png",'t',1);
        }


        tomates[0]->setX(22.5 * anchoTrigo * scaleTrigo);
        tomates[0]->setY(16 * alturaTrigo * scaleTrigo);

        tomates[1]->setX(24.5 * anchoTrigo * scaleTrigo);
        tomates[1]->setY(16 * alturaTrigo * scaleTrigo);

        tomates[2]->setX(26.3 * anchoTrigo * scaleTrigo);
        tomates[2]->setY(16 * alturaTrigo * scaleTrigo);

        tomates[3]->setX(28* anchoTrigo * scaleTrigo);
        tomates[3]->setY(16 * alturaTrigo * scaleTrigo);



        for (int i = 0; i < 4; i++)
        {
            escena->addItem(tomates[i]);
        }
    }
}


void nivel::setup_cavernicola(unsigned short _numNivel)
{
    if(_numNivel == 3 ){
        setCavernicola_keys();
        setNumsFotogramasCavernicolas();
        cavernicolas = new Enemigo*[4];

        for (int i = 0; i < 4; i++)
        {
            cavernicolas[i] = new Enemigo(completeAnimationsCavernicola(), numsFotogramasCavernicola, ":/imagenes/caveMan_Enemigo.png",
                                   anchoProta, alturaProta, scaleProta,1,1);

        }

        {
            cavernicolas[0]->setX(10.5 * anchoProta * scaleProta);
            cavernicolas[0]->setY(0 * alturaProta * scaleProta);

            cavernicolas[1]->setX(22 * anchoProta * scaleProta);
            cavernicolas[1]->setY(6 * alturaProta * scaleProta);

            cavernicolas[2]->setX(10.5 * anchoProta * scaleProta);
            cavernicolas[2]->setY(11 * alturaProta * scaleProta);

            cavernicolas[3]->setX(0 * anchoProta * scaleProta);
            cavernicolas[3]->setY(6 * alturaProta * scaleProta);

        }

        for (int i = 0; i < 4; i++)
        {
            cavernicolas[i]->setDagno(20);
            cavernicolas[i]->setSalud(60);
            cavernicolas[i]->setKeys(cavernicola_keys);
            escena->addItem(cavernicolas[i]);
        }

    }
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
    QRect dimMuerte;

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

    dimMuerte.setX(0 * anchoProta);
    dimMuerte.setY(2 * alturaProta);
    dimMuerte.setHeight(1 * alturaProta);
    dimMuerte.setWidth(4 * anchoProta);


    animations.push_back(dimLeft);
    animations.push_back(dimRight);
    animations.push_back(dimUp);
    animations.push_back(dimDown);
    animations.push_back(dimMuerte);

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
    QRect dimLeftAtaque;
    QRect dimRightAtaque;
    QRect dimUpAtaque;
    QRect dimDownAtaque;

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

    dimLeftAtaque.setX(0 * anchoTigre);
    dimLeftAtaque.setY(2 * alturaTigre +  1 * anchoTigre);
    dimLeftAtaque.setHeight(1 * anchoTigre);
    dimLeftAtaque.setWidth(4 * alturaTigre);

    dimRightAtaque.setX(4 * alturaTigre);
    dimRightAtaque.setY(2 * alturaTigre + 1 * anchoTigre);
    dimRightAtaque.setHeight(1 * anchoTigre);
    dimRightAtaque.setWidth(4 * alturaTigre);

    dimUpAtaque.setX(4 * anchoTigre);
    dimUpAtaque.setY(1 * alturaTigre);
    dimUpAtaque.setHeight(1 * alturaTigre);
    dimUpAtaque.setWidth(4 * anchoTigre);

    dimDownAtaque.setX(0 * anchoTigre);
    dimDownAtaque.setY(1 * alturaTigre);
    dimDownAtaque.setHeight(1 * alturaTigre);
    dimDownAtaque.setWidth(4 * anchoTigre);

    animations.push_back(dimLeft);
    animations.push_back(dimRight);
    animations.push_back(dimUp);
    animations.push_back(dimDown);
    animations.push_back(dimLeftAtaque);
    animations.push_back(dimRightAtaque);
    animations.push_back(dimUpAtaque);
    animations.push_back(dimDownAtaque);
    return animations;
}

QVector<QRect> nivel::completeAnimationsLobo()
{
    QVector<QRect> animations;
    QRect dimLeft;
    QRect dimRight;
    QRect dimUp;
    QRect dimDown;
    QRect dimLeftAtaque;
    QRect dimRightAtaque;
    QRect dimUpAtaque;
    QRect dimDownAtaque;

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

    dimLeftAtaque.setX(0 * anchoLobo);
    dimLeftAtaque.setY(2 * alturaLobo +  1 * anchoLobo);
    dimLeftAtaque.setHeight(1 * anchoLobo);
    dimLeftAtaque.setWidth(4 * alturaLobo);

    dimRightAtaque.setX(4 * alturaLobo);
    dimRightAtaque.setY(2 * alturaLobo + 1 * anchoLobo);
    dimRightAtaque.setHeight(1 * anchoLobo);
    dimRightAtaque.setWidth(4 * alturaLobo);

    dimUpAtaque.setX(4 * anchoLobo);
    dimUpAtaque.setY(1 * alturaLobo);
    dimUpAtaque.setHeight(1 * alturaLobo);
    dimUpAtaque.setWidth(4 * anchoLobo);

    dimDownAtaque.setX(0 * anchoLobo);
    dimDownAtaque.setY(1 * alturaLobo);
    dimDownAtaque.setHeight(1 * alturaLobo);
    dimDownAtaque.setWidth(4 * anchoLobo);

    animations.push_back(dimLeft);
    animations.push_back(dimRight);
    animations.push_back(dimUp);
    animations.push_back(dimDown);
    animations.push_back(dimLeftAtaque);
    animations.push_back(dimRightAtaque);
    animations.push_back(dimUpAtaque);
    animations.push_back(dimDownAtaque);
    return animations;
}

QVector<QRect> nivel::completeAnimationsMamut()
{
    QVector<QRect> animations;
    QRect dimLeft;
    QRect dimRight;
    QRect dimUp;
    QRect dimDown;
    QRect dimLeftAtaque;
    QRect dimRightAtaque;
    QRect dimUpAtaque;
    QRect dimDownAtaque;


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

    dimLeftAtaque.setX(0 * anchoMamut);
    dimLeftAtaque.setY(7 * alturaMamut);
    dimLeftAtaque.setHeight(1 * alturaMamut);
    dimLeftAtaque.setWidth(6 * anchoMamut);

    dimRightAtaque.setX(0 * anchoMamut);
    dimRightAtaque.setY(8 * alturaMamut);
    dimRightAtaque.setHeight(1 * alturaMamut);
    dimRightAtaque.setWidth(6 * anchoMamut);

    dimUpAtaque.setX(0 * anchoMamut);
    dimUpAtaque.setY(6 * alturaMamut);
    dimUpAtaque.setHeight(1 * alturaMamut);
    dimUpAtaque.setWidth(6 * anchoMamut);

    dimDownAtaque.setX(0 * anchoMamut);
    dimDownAtaque.setY(5 * alturaMamut);
    dimDownAtaque.setHeight(1 * alturaMamut);
    dimDownAtaque.setWidth(6 * anchoMamut);


    animations.push_back(dimLeft);
    animations.push_back(dimRight);
    animations.push_back(dimUp);
    animations.push_back(dimDown);
    animations.push_back(dimLeftAtaque);
    animations.push_back(dimRightAtaque);
    animations.push_back(dimUpAtaque);
    animations.push_back(dimDownAtaque);
    return animations;
}

QRect nivel::completeAnimationcomida()
{
    QRect animation;

    animation.setX(0 * anchocomida);
    animation.setY(0);
    animation.setHeight(1 * alturacomida);
    animation.setWidth(0 * anchocomida);

    return animation;
}

QRect nivel::completeAnimationtrigo()
{
    QRect animation;

    animation.setX(0 * anchoTrigo);
    animation.setY(0 * alturaTrigo);
    animation.setHeight(1 * alturaTrigo);
    animation.setWidth(1 * anchoTrigo);

    return animation;
}

QRect nivel::completeAnimationzanahoria()
{
    QRect animation;

    animation.setX(1 * anchoTrigo);
    animation.setY(0 * alturaTrigo);
    animation.setHeight(1 * alturaTrigo);
    animation.setWidth(1 * anchoTrigo);

    return animation;
}

QRect nivel::completeAnimationtomates()
{
    QRect animation;

    animation.setX(2 * anchoTrigo);
    animation.setY(0 * alturaTrigo);
    animation.setHeight(1 * alturaTrigo);
    animation.setWidth(1 * anchoTrigo);

    return animation;
}

QVector<QRect> nivel::completeAnimationsCavernicola()
{
    QVector<QRect> animations;
    QRect dimLeft;
    QRect dimRight;
    QRect dimUp;
    QRect dimDown;
    QRect dimMuerte;

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

    dimMuerte.setX(0 * anchoProta);
    dimMuerte.setY(2 * alturaProta);
    dimMuerte.setHeight(1 * alturaProta);
    dimMuerte.setWidth(4 * anchoProta);


    animations.push_back(dimLeft);
    animations.push_back(dimRight);
    animations.push_back(dimUp);
    animations.push_back(dimDown);
    animations.push_back(dimMuerte);

    return animations;
}


