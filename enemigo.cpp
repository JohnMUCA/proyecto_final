#include "enemigo.h"

Enemigo::Enemigo(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale) :
    Entidad(rectangulosAnimaciones, numsFotogramas, name, ancho, alto, scale), Fisicas()
{
    time = new QTimer;
    connect(time,SIGNAL(timeout()),this,SLOT(realizarPerseguir()));
    time->start(300);

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

void Enemigo::realizarMovimientoAcelerado()
{
    this->aplicarMovimientoConAceleracion(this,direccionX,direccionY,velocidad,aceleracion,deltaTiempo);
}

void Enemigo::realizarPerseguir()
{
    this->perseguirObjetivo(this, objetivo, velocidad,deltaTiempo);
}

void Enemigo::set_mov_circular_parametros(float radio, float velocidadAngular, float deltaTiempo, float centrox, float centroy)
{
    this->radio = radio;
    this->velocidadAngular = velocidadAngular;
    this->deltaTiempo = deltaTiempo;
    this->centroX = centrox;
    this->centroY = centroy;
}

void Enemigo::set_mov_acelerado(float direccionX, float direccionY, float velocidad, float aceleracion, float deltaTiempo)
{
    this->direccionX = direccionX;
    this->direccionY = direccionY;
    this->velocidad = velocidad;
    this->aceleracion = aceleracion;
    this->deltaTiempo = deltaTiempo;
}

void Enemigo::set_perseguir(Entidad *objetivo, float velocidad, float deltaTiempo)
{
    this->objetivo = objetivo; // Asigna el objetivo al que se va a perseguir
    this->velocidad = velocidad;
    this->deltaTiempo = deltaTiempo;
    this->aceleracion = aceleracion;
}
