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
    bool haAlcanzadoObjetivo(float posicionX, float posicionY, float objetivoX, float objetivoY);

public:
    Fisicas();
    void aplicarMovimientoCircularUniforme(Entidad* entidad, float centroX, float centroY, float radio, float velocidadAngular, float deltaTiempo);
    void aplicarMovimientoConAceleracion(Entidad* entidad, float direccionX, float direccionY, float velocidadInicial, float aceleracionX, float aceleracionY, float deltaTiempo, float obX, float obY);
    void perseguirObjetivo(Entidad* entidad, Entidad* objetivo, float velocidad, float deltaTiempo);
    void aplicarMovimientoPendular(Entidad* entidad, float centroX, float centroY, float longitud, float frecuenciaAngular, float amplitud, float deltaTiempo);

};

#endif // FISICAS_H
