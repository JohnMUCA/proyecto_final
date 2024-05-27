#ifndef MURCIELAGO_H
#define MURCIELAGO_H

#include "entidad.h"
#include "fisicas.h"

class Murcielago : public Entidad , public Fisicas {
public:
    Murcielago(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale);

    void realizarMovimientoCircular(float centroX, float centroY, float radio, float velocidadAngular, float deltaTiempo);
};
#endif // MURCIELAGO_H
