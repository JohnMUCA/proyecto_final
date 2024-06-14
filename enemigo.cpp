#include "enemigo.h"

Enemigo::Enemigo(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto,
                 unsigned int scale, char tipoM, bool tipoSprite) :
    Entidad(rectangulosAnimaciones, numsFotogramas, name, ancho, alto, scale,tipoSprite), Fisicas()
{

    time = new QTimer;
    if (name == ":/imagenes/murcielago.png")
    {
        if (tipoM == 'M')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoPendular()));
            time->start(100);
        }
        else if (tipoM == 'j')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoCircular()));
            time->start(100);
        }
    }
    else if (name == ":/imagenes/mamut.png") {
        if (tipoM == 'm')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarPerseguir()));
            time->start(300);
        }
    }
    else if (name == ":/imagenes/kati-eloranta-tiger.png") {
        if (tipoM == 't')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoAcelerado()));
            time->start(100);
        }
        else if (tipoM == 'y')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoAcelerado()));
            time->start(100);
        }
        else if (tipoM == 'u')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoAcelerado()));
            time->start(100);
        }
        else if (tipoM == 'i')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoAcelerado()));
            time->start(100);
        }
    }
    else if (name == ":/imagenes/wolfsheet6.png") {
        if (tipoM == 'l')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoAcelerado()));
            time->start(100);
        }
        else if (tipoM == 'z')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoAcelerado()));
            time->start(100);
        }
        else if (tipoM == 'x')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoAcelerado()));
            time->start(100);
        }
        else if (tipoM == 'v')
        {
            connect(time, SIGNAL(timeout()), this, SLOT(realizarMovimientoAcelerado()));
            time->start(100);
        }
    }

    radio = 1;
    velocidadAngular = 1;
    deltaTiempo = 1;
    centroX = 1;
    centroY = 1;
    direccionX = 1;
    direccionY = 1;
    velocidad_Inicial =1;
    aceleracionX = 1;
    aceleracionY = 1;
    aceleracion = 1;
    longitud = 1;
    amplitud =1;
    frecuenciaAngular =1;
    obX = 1;
    obY= 1;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

Enemigo::~Enemigo()
{
    delete time;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void Enemigo::realizarMovimientoCircular()
{
    this->aplicarMovimientoCircularUniforme(this, centroX, centroY, radio, velocidadAngular, deltaTiempo);
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void Enemigo::realizarMovimientoAcelerado()
{
    this->aplicarMovimientoConAceleracion(this,direccionX,direccionY,velocidad_Inicial,aceleracionX,aceleracionY,deltaTiempo,obX , obY);
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void Enemigo::realizarPerseguir()
{

    this->perseguirObjetivo(this, objetivo, velocidad,deltaTiempo);
}

void Enemigo::realizarMovimientoPendular()
{
    this->aplicarMovimientoPendular(this,centroX, centroY,frecuenciaAngular, longitud,amplitud,deltaTiempo);
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void Enemigo::empezarPerseguir()
{
    if (!(time->isActive())) time->start(100);
}

void Enemigo::pausa()
{
    time->stop();
}

void Enemigo::renaudar()
{
    time->start();
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void Enemigo::set_mov_circular_parametros(float radio, float velocidadAngular, float deltaTiempo, float centrox, float centroy)
{
    this->radio = radio;
    this->velocidadAngular = velocidadAngular;
    this->deltaTiempo = deltaTiempo;
    this->centroX = centrox;
    this->centroY = centroy;
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void Enemigo::set_mov_acelerado(float direccionX, float direccionY, float velocidad_Inicial, float aceleracionX, float aceleracionY, float deltaTiempo, float obX, float obY)
{
    this->direccionX = direccionX;
    this->direccionY = direccionY;
    this->velocidad_Inicial = velocidad_Inicial;
    this->aceleracionX = aceleracionX;
    this->aceleracionY = aceleracionY;
    this->deltaTiempo = deltaTiempo;
    this->obX = obX;
    this->obY = obY;

}
//----------------------------------------------------------------------------------------------------------------------------------------------


void Enemigo::set_perseguir(Entidad *objetivo, float velocidad,float deltaTiempo) {
    this->objetivo = objetivo;
    this->velocidad = velocidad;
    this->deltaTiempo = deltaTiempo;
}

void Enemigo::set_aplicarMovimientoPendular(float centroX, float centroY,float frecuenciaAngular, float longitud, float amplitud, float deltaTiempo)
{
    this->centroX = centroX;
    this->centroY= centroY;
    this->frecuenciaAngular = frecuenciaAngular;
    this->longitud = longitud;
    this->amplitud = amplitud;
    this->deltaTiempo = deltaTiempo;
}




