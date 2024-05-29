#include "fisicas.h"


Fisicas::Fisicas()
{
    angulo = 0.0f;
}

void Fisicas::aplicarMovimientoCircularUniforme(Entidad* entidad, float centroX, float centroY, float radio, float velocidadAngular, float deltaTiempo) {
    int pasos = 100;
    float deltaT = deltaTiempo / pasos;

    for (int i = 0; i < pasos; ++i) {
        angulo += velocidadAngular * deltaT;
        float nuevaX = centroX + radio * cos(angulo);
        float nuevaY = centroY + radio * sin(angulo);
        entidad->establecer_posicion(QPoint(nuevaX, nuevaY));
    }
}

void Fisicas::aplicarMovimientoLinealUniforme(Entidad* entidad, QVector2D direccion, float velocidad, float deltaTiempo) {
    int pasos = 10;
    float deltaT = deltaTiempo / pasos;

    direccion.normalize();
    QVector2D desplazamiento = direccion * velocidad * deltaT;

    for (int i = 0; i < pasos; ++i) {
        QPoint nuevaPos = entidad->obtenerPosicion() + desplazamiento.toPoint();
        entidad->establecer_posicion(nuevaPos);
    }
}

void Fisicas::aplicarMovimientoConAceleracion(Entidad* entidad, QVector2D direccion, float velocidad, float aceleracion, float deltaTiempo) {
    int pasos = 10;
    float deltaT = deltaTiempo / pasos;

    direccion.normalize();

    for (int i = 0; i < pasos; ++i) {
        velocidad += aceleracion * deltaT;
        QVector2D desplazamiento = direccion * velocidad * deltaT;
        QPoint nuevaPos = entidad->obtenerPosicion() + desplazamiento.toPoint();
        entidad->establecer_posicion(nuevaPos);
    }
}

void Fisicas::aplicarGravedad(Entidad* entidad, float gravedad, float deltaTiempo) {
    int pasos = 10;
    float deltaT = deltaTiempo / pasos;

    QVector2D desplazamiento(0, gravedad * deltaT);

    for (int i = 0; i < pasos; ++i) {
        QPoint nuevaPos = entidad->obtenerPosicion() + desplazamiento.toPoint();
        entidad->establecer_posicion(nuevaPos);
    }
}

bool Fisicas::detectarColision(Entidad* entidad1, Entidad* entidad2) {
    QRect rect1 = entidad1->obtenerRectangulo();
    QRect rect2 = entidad2->obtenerRectangulo();
    return rect1.intersects(rect2);
}

void Fisicas::aplicarRebote(Entidad* entidad, QVector2D normal) {
    QVector2D velocidad = entidad->obtenerVelocidad();
    QVector2D nuevaVelocidad = velocidad - 2 * QVector2D::dotProduct(velocidad, normal) * normal;
    entidad->establecerVelocidad(nuevaVelocidad);
}

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
