#include "recursos.h"

recursos::recursos(QRect rectanguloAnimacion, unsigned int numFotogramas, unsigned int width,
                   unsigned int height, unsigned int scale, bool type, QString name, char tipoCultivo, bool tipoSprites)
{
    mainPixmap = new sprites(name,scale,tipoSprites);
    this->width = width;
    this->height = height;
    this->scale = scale;
    this->type = type;

    mainPixmap->set_design_size(width, height);

    if (name == ":/imagenes/food.png")
    {
        mainPixmap->cut_character_pixmap(getCompleteSpritesComida());
    }
    else if (name == ":/imagenes/farming.png")
    {
        if (tipoCultivo == 'T')mainPixmap->cut_character_pixmap(getCompleteSpritesTrigo());

        else if(tipoCultivo == 'z')mainPixmap->cut_character_pixmap(getCompleteSpritesZanahoria());

        else if(tipoCultivo == 't')mainPixmap->cut_character_pixmap(getCompleteSpritesTomate());
    }

    setAnimation(rectanguloAnimacion, numFotogramas);


    set_type_recurso(name, tipoCultivo);
}

recursos::~recursos()
{
    delete mainPixmap;
}

QRect recursos::obtenerRectangulo() const
{
    return QRect(this->x(), this->y(), width * scale, height * scale);
}

void recursos::setAnimation(QRect rectangulosAnimaciones, unsigned int numsFotogramas)
{
    mainPixmap->add_new_animation(rectangulosAnimaciones, numsFotogramas);
}


void recursos::set_type_recurso(QString name, char tipoCultivo)
{
    if(type){
        setPixmap(mainPixmap->get_fixed_image(getCompleteSpritesComida()));
        if (name == ":/imagenes/farming.png" ){
            if (tipoCultivo == 'T')setPixmap(mainPixmap->get_fixed_image(getCompleteSpritesTrigo()));
            else if(tipoCultivo == 'z')setPixmap(mainPixmap->get_fixed_image(getCompleteSpritesZanahoria()));
            else if(tipoCultivo == 't')setPixmap(mainPixmap->get_fixed_image(getCompleteSpritesTomate()));
        }
    //else setPixmap(mainPixmap->get_fixed_image(getCompleteSpritesLanza()));

    }

    //else setPixmap(mainPixmap->get_fixed_image(getCompleteSpritesFuego()));
}



QRect recursos::getCompleteSpritesComida()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1 * height);
    dim.setWidth(1 * width);

    return dim;

}


QRect recursos::getCompleteSpritesTrigo()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1 * height);
    dim.setWidth(1 * width);

    return dim;

}

QRect recursos::getCompleteSpritesZanahoria()
{
    QRect dim;

    dim.setX(1 * width);
    dim.setY(0 * height);
    dim.setHeight(1 * height);
    dim.setWidth(1 * width);

    return dim;

}

QRect recursos::getCompleteSpritesTomate()
{
    QRect dim;

    dim.setX(2 * width);
    dim.setY(0 * height);
    dim.setHeight(1 * height);
    dim.setWidth(1 * width);

    return dim;

}





