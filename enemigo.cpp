#include "enemigo.h"

Enemigo::Enemigo(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale) :
    Entidad(rectangulosAnimaciones, numsFotogramas, name, ancho, alto, scale), Fisicas()
{
    time = new QTimer;
    connect(time,SIGNAL(timeout()),this,SLOT(realizarMovimientoCircular()));
    time->start(200);

    radio = 1;
    velocidadAngular = 1;
    deltaTiempo = 1;
    centroX = 1;
    centroY = 1;
}

Enemigo::~Enemigo()
{
    delete time;
}

void Enemigo::realizarMovimientoCircular()
{
    this->aplicarMovimientoCircularUniforme(this, centroX, centroY, radio, velocidadAngular, deltaTiempo);
}

void Enemigo::set_mov_circular_parametros(float radio, float velocidadAngular, float deltaTiempo, float centrox, float centroy)
{
    this->radio = radio;
    this->velocidadAngular = velocidadAngular;
    this->deltaTiempo = deltaTiempo;
    this->centroX = centrox;
    this->centroY = centroy;
}
