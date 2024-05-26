#include "objetos.h"

objetos::objetos(QString name, unsigned int ancho, unsigned int alto, unsigned int scale)
{
    width = ancho;
    height = alto;
    mainPixmap = new sprites(name, scale);
    mainPixmap->set_design_size(width, height);
    mainPixmap->cut_character_pixmap(set_complete_sprites());
    //setPixmap(QPixmap(name).scaled(width,height));
    set_animations();
    setX(28 * width * scale);
    setY(14 * height * scale);
    setPixmap(mainPixmap->get_current_pixmap(3));
}

QRect objetos::set_complete_sprites()
{
    QRect dim;

    dim.setX(51);
    dim.setY(0);
    dim.setHeight(4 * height);
    dim.setWidth(6 * width);

    return dim;
}

void objetos::move(unsigned int key, bool is_valid)
{
    if(key == keys[0]){
        setPixmap(mainPixmap->get_current_pixmap(0));
        if(is_valid) setX(x() - objectSpeed);
    }
    else if(key == keys[1]){
        setPixmap(mainPixmap->get_current_pixmap(1));
        if(is_valid) setX(x() + objectSpeed);
    }
    else if(key == keys[2]){
        setPixmap(mainPixmap->get_current_pixmap(2));
        if(is_valid) setY(y() - objectSpeed);
    }
    else if(key == keys[3]){
        setPixmap(mainPixmap->get_current_pixmap(3));
        if(is_valid) setY(y() + objectSpeed);
    }
}

void objetos::set_keys(unsigned int *keys)
{
    for(unsigned int i=0;i<4;i++) this->keys[i] = keys[i];
}



void objetos::set_animations()
{
    set_left_animation();
    set_right_animation();
    set_up_animation();
    set_down_animation();
    set_death_animation();
}

void objetos::set_left_animation()
{
    QRect dim;

    dim.setX(0);
    dim.setY(1 * height);
    dim.setHeight(1 * height);
    dim.setWidth(3 * width);

    mainPixmap->add_new_animation(dim,3);
}

void objetos::set_right_animation()
{
    QRect dim;

    dim.setX(3 * width);
    dim.setY(1 * height);
    dim.setHeight(1 * height);
    dim.setWidth(3 * width);

    mainPixmap->add_new_animation(dim,3);
}

void objetos::set_up_animation()
{
    QRect dim;

    dim.setX(0);
    dim.setY(0);
    dim.setHeight(1 * height);
    dim.setWidth(3 * width);

    mainPixmap->add_new_animation(dim,3);
}

void objetos::set_down_animation()
{
    QRect dim;

    dim.setX(3 * width);
    dim.setY(0);
    dim.setHeight(1 * height);
    dim.setWidth(3 * width);

    mainPixmap->add_new_animation(dim,3);
}

void objetos::set_death_animation()
{
    QRect dim;

    dim.setX(1 * width);
    dim.setY(2 * height);
    dim.setHeight(1 * height);
    dim.setWidth(4 * width);

    mainPixmap->add_new_animation(dim,4);
}

