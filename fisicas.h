#ifndef FISICAS_H
#define FISICAS_H

#include "entidad.h"
#include <QPoint>
#include <cmath>

//using namespace std;

class Fisicas {
private:
    float angulo;

public:
    Fisicas();
    void aplicarMovimientoCircularUniforme(Entidad* entidad, float centroX, float centroY, float radio, float velocidadAngular, float deltaTiempo);
    void aplicarMovimientoLinealUniforme(Entidad* entidad, QVector2D direccion, float velocidad, float deltaTiempo);
    void aplicarMovimientoConAceleracion(Entidad* entidad, float direccionX, float direccionY, float velocidad, float aceleracion, float deltaTiempo);
    void aplicarGravedad(Entidad* entidad, float gravedad, float deltaTiempo);
    bool detectarColision(Entidad* entidad1, Entidad* entidad2);
    void aplicarRebote(Entidad* entidad, QVector2D normal);
    void aplicarFuerza(Entidad* entidad, QVector2D fuerza, float masa, float deltaTiempo);
    void perseguirObjetivo(Entidad* entidad, Entidad* objetivo, float velocidad, float deltaTiempo);
};

#endif // FISICAS_H
