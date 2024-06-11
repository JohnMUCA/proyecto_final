#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "entidad.h"
#include "fisicas.h"
#include <QTimer>

class Enemigo : public Entidad, public Fisicas
{  
    Q_OBJECT
public:
    Enemigo(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto, unsigned int scale, bool tipoM);
    ~Enemigo();
    void set_mov_circular_parametros(float radio, float velocidadAngular, float deltaTiempo,float centrox, float centroy);
    void set_mov_acelerado(float direccionX, float direccionY, float velocidad_Inicial, float aceleracionX, float aceleracionY, float deltaTiempo);
    void set_perseguir(Entidad *objetivo, float velocidad, float deltaTiempo);
    void set_colision(Entidad *objetivo);
    void empezarPerseguir();
    void empujar();
    bool banderaColision;

private:
    float radio, velocidadAngular, deltaTiempo, centroX, centroY;
    float direccionX,direccionY,velocidad_Inicial,aceleracionX, aceleracionY;
    int xDestino, yDestino;
    float velocidad, aceleracion;
    QTimer *time;
    QTimer *timeColision;
    Entidad* objetivo;
private slots:
    void realizarMovimientoCircular();
    void realizarMovimientoAcelerado();
    void realizarPerseguir();
    //void realizarcolision();

};

#endif // ENEMIGO_H
