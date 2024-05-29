#include "murcielago.h"


Murcielago::Murcielago(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale)
    : Entidad(rectangulosAnimaciones, numsFotogramas, name, ancho, alto, scale), Fisicas() {}

/*void Murcielago::realizarMovimientoCircular(float centroX, float centroY, float radio, float velocidadAngular, float deltaTiempo) {
    this->aplicarMovimientoCircularUniforme(this, centroX, centroY, radio, velocidadAngular, deltaTiempo);
}
*/
