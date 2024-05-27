#include "murcielago.h"


Murcielago::Murcielago(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale)
    : Entidad(rectangulosAnimaciones, numsFotogramas, name, ancho, alto, scale) {}

void Murcielago::realizarMovimientoCircular(float centroX, float centroY, float radio, float velocidadAngular, float deltaTiempo) {
    Fisicas fisicas;
    fisicas.aplicarMovimientoCircularUniforme(this, centroX, centroY, radio, velocidadAngular, deltaTiempo);
}
