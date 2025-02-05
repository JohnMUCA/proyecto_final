#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "entidad.h"
#include "fisicas.h"
#include <QTimer>

class Enemigo : public Entidad, public Fisicas
{  
    Q_OBJECT
public:
    Enemigo(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name, unsigned int ancho, unsigned int alto,unsigned int scale, char tipoM, bool tipoSprite);
    ~Enemigo();
    void set_mov_circular_parametros(float radio, float velocidadAngular, float deltaTiempo,float centrox, float centroy);
    void set_mov_acelerado(float direccionX, float direccionY, float velocidad_Inicial, float aceleracionX, float aceleracionY, float deltaTiempo, float obX, float obY);
    void set_perseguir(Entidad *objetivo, float velocidad, float deltaTiempo);
    void set_aplicarMovimientoPendular(float centroX, float centroY, float frecuenciaAngular, float longitud, float amplitud, float deltaTiempo);
    void empezarPerseguir();

public slots:
    void pausa();
    void renaudar();

private:
    float radio, velocidadAngular, deltaTiempo, centroX, centroY;
    float direccionX,direccionY,velocidad_Inicial,aceleracionX, aceleracionY;
    int xDestino, yDestino;
    float velocidad, aceleracion, frecuenciaAngular,obX, obY;
    float longitud,amplitud;
    QTimer *time;
    Entidad* objetivo;
private slots:
    void realizarMovimientoCircular();
    void realizarMovimientoAcelerado();
    void realizarPerseguir();
    void realizarMovimientoPendular();
};

#endif // ENEMIGO_H
