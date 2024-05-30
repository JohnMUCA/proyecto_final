#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "entidad.h"
#include "fisicas.h"
#include <QTimer>

class Enemigo : public Entidad, public Fisicas
{  
    Q_OBJECT
public:
    Enemigo(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale);
    ~Enemigo();
    void set_mov_circular_parametros(float radio, float velocidadAngular, float deltaTiempo,float centrox, float centroy);
    void set_mov_acelerado(float direccionX, float direccionY,float velocidad, float aceleracion, float deltaTiempo);
    void set_perseguir(Entidad *objetivo, float velocidad, float deltaTiempo);
private:
    float radio, velocidadAngular, deltaTiempo, centroX, centroY;
    float direccionX,direccionY,velocidad,aceleracion;
    QTimer *time;
    Entidad* objetivo;
private slots:
    void realizarMovimientoCircular();
    void realizarMovimientoAcelerado();
    void realizarPerseguir();
};

#endif // ENEMIGO_H
