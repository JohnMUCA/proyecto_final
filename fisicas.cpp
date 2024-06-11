#include "fisicas.h"


Fisicas::Fisicas()
{
    angulo = 0.0f;
    n=0;
}

void Fisicas::aplicarMovimientoCircularUniforme(Entidad* entidad, float centroX, float centroY, float radio, float velocidadAngular, float deltaTiempo) {
    float deltaT = deltaTiempo*n;


    angulo = velocidadAngular * deltaT;

    float nuevaX = centroX + radio * cos(angulo);
    float nuevaY = centroY + radio * sin(angulo);
    entidad->establecer_posicion(QPoint(nuevaX, nuevaY));
    n++;

}
//-------------------------------------------------------------------------------------------------------------------
void Fisicas::aplicarMovimientoLinealUniforme(Entidad* entidad, float direccionX, float direccionY, float velocidad, float deltaTiempo) {

    float deltaT = deltaTiempo*n;

    // Calculamos el desplazamiento total usando la fórmula X = X_0 + VT
    float desplazamientoX = direccionX + velocidad * deltaT;
    float desplazamientoY = direccionY + velocidad * deltaT;

    float nuevaX = desplazamientoX;
    float nuevaY = desplazamientoY;

    entidad->establecer_posicion(QPoint(nuevaX, nuevaY));
    n++;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Fisicas::aplicarMovimientoConAceleracion(Entidad* entidad, float direccionX, float direccionY, float velocidadInicial, float aceleracionX, float aceleracionY, float deltaTiempo) {


    float deltaT = deltaTiempo*n;

    float desplazamientoX = direccionX + velocidadInicial * deltaT +0.5 * aceleracionX *deltaT *deltaT;
    float desplazamientoY = direccionY + velocidadInicial * deltaT +0.5 * aceleracionY *deltaT *deltaT;

    float nuevaX = desplazamientoX;
    float nuevaY = desplazamientoY;
    entidad->establecer_posicion(QPoint(nuevaX, nuevaY));
    n++;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Fisicas::aplicarGravedad(Entidad* entidad, float gravedad, float deltaTiempo) {
    int pasos = 10;
    float deltaT = deltaTiempo / pasos;

    QVector2D desplazamiento(0, gravedad * deltaT);

    for (int i = 0; i < pasos; ++i) {
        QPoint nuevaPos = entidad->obtenerPosicion() + desplazamiento.toPoint();
        entidad->establecer_posicion(nuevaPos);
    }
}
//-----------------------------------------------------------------------------------------------------------
/*
void Fisicas::detectarColision(Entidad* entidad1, Entidad* entidad2) {
    if (entidad1->obtenerRectangulo().intersects(entidad2->obtenerRectangulo())) this->quitarvida(entidad2);
}
*/
//----------------------------------------------------------------------------------------------------------------------------------------------
void Fisicas::aplicarRebote(Entidad* entidad, float direccionX, float direccionY) {


    // Calculamos el desplazamiento total usando la fórmula X = X_0 + VT
    float desplazamientoX = direccionX;
    float desplazamientoY = direccionY;


    float rebote_protaX = desplazamientoX;
    float rebote_protaY = desplazamientoY;
    entidad->establecer_posicion(QPoint(rebote_protaX, rebote_protaY));
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
    entidad->establecer_posicion(nuevaPosicion.toPoint());
}
/*
void Fisicas::quitarvida(Entidad* entidad)
{

    entidad->recibir_dagno(1);

}
*/
/*
void Fisicas::aplicarFuerza(Entidad* entidad, QVector2D fuerza, float masa, float deltaTiempo) {
    int pasos = 10;
    float deltaT = deltaTiempo / pasos;

    QVector2D aceleracion = fuerza / masa;
    QVector2D desplazamiento = 0.5 * aceleracion * deltaT * deltaT;

    for (int i = 0; i < pasos; ++i) {
        QVector2D nuevaVelocidad = entidad->obtenerVelocidad() + aceleracion * deltaT;
        entidad->establecerVelocidad(nuevaVelocidad);
        QPoint nuevaPos = entidad->obtenerPosicion() + desplazamiento.toPoint();
        entidad->establecer_posicion(nuevaPos);
    }
}
*/
