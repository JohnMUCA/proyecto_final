#include "entidad.h"

Entidad::Entidad(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, unsigned int *keys, QString name, unsigned int ancho, unsigned int alto, unsigned int scale)
{
    width = ancho;
    height = alto;
    this->scale = scale;
    mainPixmap = new sprites(name, scale);
    mainPixmap->set_design_size(width, height);
    mainPixmap->cut_character_pixmap(setCompleteSprites());
    setX(28 * width * scale);
    setY(14 * height * scale);
    setAnimations(rectangulosAnimaciones, numsFotogramas);
    setPixmap(mainPixmap->get_current_pixmap(3));
    setKeys(keys);

}

void Entidad::move(unsigned int key, bool is_valid)
{
    if(key == keys[0]){
        setPixmap(mainPixmap->get_current_pixmap(0));
        if(is_valid) setX(x() - entidadSpeed);
    }
    else if(key == keys[1]){
        setPixmap(mainPixmap->get_current_pixmap(1));
        if(is_valid) setX(x() + entidadSpeed);
    }
    else if(key == keys[2]){
        setPixmap(mainPixmap->get_current_pixmap(2));
        if(is_valid) setY(y() - entidadSpeed);
    }
    else if(key == keys[3]){
        setPixmap(mainPixmap->get_current_pixmap(3));
        if(is_valid) setY(y() + entidadSpeed);
    }
}

void Entidad::setAnimations(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas)
{
    for (int i = 0; i < rectangulosAnimaciones.length(); i++)
    {
        mainPixmap->add_new_animation(rectangulosAnimaciones[i], numsFotogramas[i]);
    }
}

/*void Entidad::agregarAnimacion(QRect rentanguloAnimacion, unsigned int numFotogramas)
{
    mainPixmap->add_new_animation(rentanguloAnimacion, numFotogramas);
}*/

Entidad::~Entidad()
{
    delete mainPixmap;
}

void Entidad::setKeys(unsigned int *Keys)
{
    for(unsigned int i=0;i<4;i++) this->keys[i] = Keys[i];
}

QRect Entidad::setCompleteSprites()
{
    QRect dim;

    dim.setX(51);
    dim.setY(0);
    dim.setHeight(4 * height);
    dim.setWidth(6 * width);

    return dim;
}
