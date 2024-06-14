#include "entidad.h"

Entidad::Entidad(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas, QString name,
                 unsigned int ancho, unsigned int alto, unsigned int scale, bool tipoSprite)
{
    salud = 100;
    dagno = 20;
    ultimaTecla = Qt::Key_A;

    width = ancho;
    height = alto;
    this->scale = scale;
    mainPixmap = new sprites(name, scale, tipoSprite);
    mainPixmap->set_design_size(width, height);

    if (name == ":/imagenes/caveMan.png" || name == ":/imagenes/caveMan_Enemigo.png")
    {
       mainPixmap->cut_character_pixmap(getCompleteSpritesProta());
    }
    else if(name == ":/imagenes/murcielago.png")
    {
        mainPixmap->cut_character_pixmap(getCompleteSpritesMurcielago());
    }
    else if(name == ":/imagenes/mamut.png"){
        mainPixmap->cut_character_pixmap(getCompleteSpritesMamut());
    }
    else if(name == ":/imagenes/kati-eloranta-tiger.png"){
        mainPixmap->cut_character_pixmap(getCompleteSpritesTigre());
    }
    else if(name == ":/imagenes/wolfsheet6.png"){
        mainPixmap->cut_character_pixmap(getCompleteSpritesLobo());
    }

    setX(0 * width * scale);
    setY(0 * height * scale);

    setAnimations(rectangulosAnimaciones, numsFotogramas);
    setPixmap(mainPixmap->get_current_pixmap(0));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

Entidad::~Entidad()
{
    delete mainPixmap;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

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

    ultimaTecla = key;

}
void Entidad::atack(unsigned int key)
{
    if(key == keys[4]){
        setPixmap(mainPixmap->get_current_pixmap(4));
    }
    else if(key == keys[5]){
        setPixmap(mainPixmap->get_current_pixmap(5));
    }
    else if(key == keys[6]){
        setPixmap(mainPixmap->get_current_pixmap(6));
    }
    else if(key == keys[7]){
        setPixmap(mainPixmap->get_current_pixmap(7));
    }

    ultimaTecla = key;
}

void Entidad::muerte(unsigned int key)
{
    if(key == keys[4]){
        setPixmap(mainPixmap->get_current_pixmap(4));
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void Entidad::setAnimations(QVector<QRect> rectangulosAnimaciones, unsigned int *numsFotogramas)
{
    for (int i = 0; i < rectangulosAnimaciones.length(); i++)
    {
        mainPixmap->add_new_animation(rectangulosAnimaciones[i], numsFotogramas[i]);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void Entidad::setKeys(unsigned int *Keys)
{
    for(unsigned int i=0;i<8;i++) this->keys[i] = Keys[i];
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void Entidad::setDagno(short _dagno)
{
    dagno = _dagno;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void Entidad::setSalud(int _salud)
{
    salud = _salud;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

void Entidad::recibir_dagno(short cantidad) {
    salud -= cantidad;
    if (salud < 0) salud = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

QRect Entidad::obtenerRectangulo() const {
    return QRect(this->x(), this->y(), width * scale, height * scale);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

int Entidad::obtenerSalud() const
{
    return salud;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

unsigned int Entidad::obtenerUltimaTecla() const
{
    return ultimaTecla;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

int Entidad::getVelocidad()
{
    return entidadSpeed;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

short Entidad::getdagno()
{
    return dagno;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

QRect Entidad::getCompleteSpritesProta()
{
    QRect dim;

    dim.setX(51);
    dim.setY(0);
    dim.setHeight(4 * height);
    dim.setWidth(6 * width);

    return dim;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

QRect Entidad::getCompleteSpritesMurcielago()
{
    QRect dim;

    dim.setX(1 * height);
    dim.setY(0);
    dim.setHeight(1 * height);
    dim.setWidth(3 * width);

    return dim;
}
//---------------------------------------------------------------------------
QRect Entidad::getCompleteSpritesMamut()
{
    QRect dim;
    dim.setX(0 * height);
    dim.setY(0 * width);
    dim.setHeight(9 * height);
    dim.setWidth(8 * width);

    return dim;
}

QRect Entidad::getCompleteSpritesTigre()
{
    QRect dim;
    dim.setX(0 * height);
    dim.setY(0 * width);
    dim.setHeight(2 * height + 2 * width);
    dim.setWidth(8 * height);

    return dim;
}

QRect Entidad::getCompleteSpritesLobo()
{
    QRect dim;
    dim.setX(0 * height);
    dim.setY(0 * width);
    dim.setHeight(2 * height + 2 * width);
    dim.setWidth(8 * height);

    return dim;
}


