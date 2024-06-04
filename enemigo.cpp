#include "enemigo.h"
#include "entidad.h"

Enemigo::Enemigo(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale) :
    Entidad(rectangulosAnimaciones, numsFotogramas, name, ancho, alto, scale), Fisicas()
{
    time = new QTimer;
    connect(time,SIGNAL(timeout()),this,SLOT(realizarMovimientoAcelerado()));
    time->start(100);


    radio = 1;
    velocidadAngular = 1;
    deltaTiempo = 1;
    centroX = 1;
    centroY = 1;
    direccionX = 1;
    direccionY = 1;
    velocidad_Inicial = 1;
    aceleracionX = 1;
    aceleracionY = 1;
    aceleracion = 1;


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
    this->aplicarMovimientoConAceleracion(this,direccionX,direccionY,velocidad_Inicial,aceleracionX,aceleracionY,deltaTiempo);
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


void Enemigo::set_mov_acelerado(float direccionX, float direccionY, float velocidad_Inicial, float aceleracionX, float aceleracionY, float deltaTiempo)
{
    this->direccionX = direccionX;
    this->direccionY = direccionY;
    this->velocidad_Inicial = velocidad_Inicial;
    this->aceleracionX = aceleracionX;
    this->aceleracionY = aceleracionY;
    this->deltaTiempo = deltaTiempo;
}
//----------------------------------------------------------------------------------------------------------------------------------------------


void Enemigo::set_perseguir(Entidad *objetivo, float velocidad,float deltaTiempo) {
    this->objetivo = objetivo;
    this->velocidad = velocidad;
    this->deltaTiempo = deltaTiempo;
}

