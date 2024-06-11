#include "fisicas.h"


Fisicas::Fisicas()
{
    angulo = 0.0f;
    n=0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------
void Fisicas::aplicarMovimientoCircularUniforme(Entidad* entidad, float centroX, float centroY, float radio,
                                                float velocidadAngular, float deltaTiempo) {
    float deltaT = deltaTiempo*n;


    angulo = velocidadAngular * deltaT;

    float nuevaX = centroX + radio * cos(angulo);
    float nuevaY = centroY + radio * sin(angulo);
    entidad->setPos(QPoint(nuevaX, nuevaY));
    n++;

}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fisicas::aplicarMovimientoConAceleracion(Entidad* entidad, float direccionX, float direccionY, float velocidadInicial,
                                              float aceleracionX, float aceleracionY, float deltaTiempo) {


    float deltaT = deltaTiempo*n;

    float desplazamientoX = direccionX + velocidadInicial * deltaT +0.5 * aceleracionX *deltaT *deltaT;
    float desplazamientoY = direccionY + velocidadInicial * deltaT +0.5 * aceleracionY *deltaT *deltaT;

    float nuevaX = desplazamientoX;
    float nuevaY = desplazamientoY;
    entidad->setPos(QPoint(nuevaX, nuevaY));
    n++;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
void Fisicas::perseguirObjetivo(Entidad* entidad, Entidad *objetivo,  float velocidad, float deltaTiempo)
{
    // Calcula la dirección hacia el objetivo
    QPointF direccion = objetivo->pos() - entidad->pos();

    // Normaliza la dirección
    float magnitud = sqrt(direccion.x() * direccion.x() + direccion.y() * direccion.y());
    if (magnitud != 0) {
        direccion /= magnitud;
    } else {
        // Manejar el caso cuando el objetivo y la entidad están en la misma posición
        // aca es donde se quiere implantat una subfisica llamada detectar colision
        // Para evitar división por cero
        direccion = QPointF(0, 0);
    }
    // Calcula el desplazamiento con interpolación
    QPointF desplazamiento = direccion * velocidad * deltaTiempo;

    // Aplica el desplazamiento a la posición actual con interpolación
    QPointF nuevaPosicion = entidad->pos() + desplazamiento;

    // Establece la nueva posición
    entidad->setPos(nuevaPosicion.toPoint());
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------
