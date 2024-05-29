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

private:
    float radio, velocidadAngular, deltaTiempo, centroX, centroY;
    QTimer *time;
private slots:
    void realizarMovimientoCircular();
};

#endif // ENEMIGO_H
