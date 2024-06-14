#include "fisicas.h"


bool Fisicas::haAlcanzadoObjetivo(float posicionX, float posicionY, float objetivoX, float objetivoY)
{
    // Definir una pequeña tolerancia para considerar que se ha alcanzado el objetivo
    const float epsilon = 0.01f;

    // Comprobar si la posición actual está cerca del objetivo en ambas coordenadas
    bool alcanzadoX = std::fabs(posicionX - objetivoX) < epsilon;
    bool alcanzadoY = std::fabs(posicionY - objetivoY) < epsilon;

    // Se considera que se ha alcanzado el objetivo si ambas coordenadas están cerca del objetivo
    return alcanzadoX && alcanzadoY;
}

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
                                              float aceleracionX, float aceleracionY, float deltaTiempo, float obX , float obY) {

    static float velocidadX = velocidadInicial;  // Variable estática para mantener la velocidad en X
    static float velocidadY = velocidadInicial;  // Variable estática para mantener la velocidad en Y

    float deltaT = deltaTiempo * n;

    // Calcular el desplazamiento utilizando las ecuaciones del movimiento uniformemente acelerado
    float desplazamientoX = direccionX + velocidadX * deltaT + 0.5 * aceleracionX * deltaT * deltaT;
    float desplazamientoY = direccionY + velocidadY * deltaT + 0.5 * aceleracionY * deltaT * deltaT;

    float nuevaX = desplazamientoX;
    float nuevaY = desplazamientoY;

    entidad->setPos(QPoint(nuevaX, nuevaY));


    if (haAlcanzadoObjetivo(nuevaX, nuevaY, obX, obY)) {

        velocidadX = -velocidadX;
        velocidadY = -velocidadY;
        aceleracionX = -aceleracionX;
        aceleracionY = -aceleracionY;
        velocidadX += aceleracionX * deltaT;
        velocidadY += aceleracionY * deltaT;
    }
    // Actualizar las velocidades con las nuevas aceleraciones

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

void Fisicas::aplicarMovimientoPendular(Entidad* entidad, float centroX, float centroY,float frecuenciaAngular,float longitud, float amplitud, float deltaTiempo)
{

    float pi = 3.1415926535;

    float deltaT = deltaTiempo * n;

    // Calcular el ángulo del péndulo usando la fórmula del movimiento armónico simple
    float angulo = amplitud * cos(frecuenciaAngular * deltaT + (pi/2));

    // Calcular la posición del péndulo
    float posicionX = longitud * sin(angulo);
    float posicionY = longitud * cos(angulo);

    // Ajustar la posición del péndulo respecto al origen
    float nuevaX = centroX + posicionX;
    float nuevaY = centroY + posicionY;

    // Actualizar la posición de la entidad
    entidad->setPos(QPoint(nuevaX, nuevaY));
    n++;
}
