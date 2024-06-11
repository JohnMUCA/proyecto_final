#ifndef FISICAS_H
#define FISICAS_H

#include "entidad.h"
#include <QPoint>
#include <cmath>

//using namespace std;

class Fisicas {
private:
    float angulo;
    int n;

public:
    Fisicas();
    void aplicarMovimientoCircularUniforme(Entidad* entidad, float centroX, float centroY, float radio, float velocidadAngular, float deltaTiempo);
    void aplicarMovimientoLinealUniforme(Entidad* entidad, float direccionX, float direccionY, float velocidad, float deltaTiempo);
    void aplicarMovimientoConAceleracion(Entidad* entidad, float direccionX, float direccionY, float velocidadInicial, float aceleracionX, float aceleracionY, float deltaTiempo);
    void detectarColision(Entidad* entidad1, Entidad* entidad2);

    void aplicarGravedad(Entidad* entidad, float gravedad, float deltaTiempo);

    void aplicarRebote(Entidad* entidad, float direccionX, float direccionY);
    void aplicarFuerza(Entidad* entidad, QVector2D fuerza, float masa, float deltaTiempo);
    void perseguirObjetivo(Entidad* entidad, Entidad* objetivo, float velocidad, float deltaTiempo);
    void quitarvida(Entidad *entidad);
};

#endif // FISICAS_H
