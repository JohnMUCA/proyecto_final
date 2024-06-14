#include "menu.h"

menu::menu(QGraphicsView *graphicsV, QString imageBackground, float nivelScale, unsigned int height, unsigned int width,
           unsigned int x, unsigned int y, QVector<QPushButton *> botones, QGroupBox *grupoBotones, char tipoMenu)
{
    graph = graphicsV;
    this->botones = botones;
    this->grupoBotones = grupoBotones;
    this->tipoMenu = tipoMenu;
    setup_scene(imageBackground, nivelScale, height, width, x, y);
}

menu::~menu()
{
    delete escena;
    delete brocha;
    delete fondoCompleto;
    this->grupoBotones->setVisible(false);
}

void menu::darPasoA_nivel()
{
    emit menu::termine();
}

void menu::pausarJuego()
{
    emit estoyActivo();
}

void menu::setup_scene(QString image_Background, float nivel_Scale, unsigned int _heightMap, unsigned int _widthMap, unsigned int _x, unsigned int _y)
{
    graph->setGeometry(0, 0, 1500, 800);
    escena = new QGraphicsScene;
    escena->setSceneRect(0, 0, graph->width() - 2, graph->height() - 2);
    graph->setScene(escena);
    //----------------------------------------------- Botones ----------------------------------------------

    grupoBotones->setGeometry(0, 0, graph->width(), graph->height());
    if (tipoMenu == 'P')
    {
        botones.value(0)->setGeometry((graph->width() / 2) - 150, (graph->height() / 2) + 86, 300, 60);
        botones.value(1)->setGeometry((graph->width() / 2) - 170, (graph->height() / 2) + 185, 340, 60);
        botones.value(2)->setGeometry((graph->width() / 2) - 130, (graph->height() / 2) + 295, 260, 40);
        botones.value(3)->setGeometry(27, 62, 295, 65);
    }
    else if (tipoMenu == 'C')
    {
        botones.value(0)->setGeometry((graph->width() / 2) - 421, (graph->height() / 2) - 238, 825, 127);
        botones.value(1)->setGeometry((graph->width() / 2) - 421, (graph->height() / 2) - 40, 825, 127);
        botones.value(2)->setGeometry((graph->width() / 2) - 421, (graph->height() / 2) + 176, 825, 127);
        botones.value(3)->setGeometry(43, 43, 315, 70);
    }
    else if (tipoMenu == 'F')
    {
        botones.value(0)->setGeometry((graph->width() / 2) - 240, (graph->height() / 2) + 135, 477, 106);
        botones.value(1)->setGeometry((graph->width() / 2) - 246, (graph->height() / 2) + 275, 496, 109);
    }
    else if (tipoMenu == 'p')
    {
        botones.value(0)->setGeometry((graph->width() / 2) - 179, (graph->height() / 2) - 144, 357, 79);
        botones.value(1)->setGeometry((graph->width() / 2) - 179, (graph->height() / 2) - 12, 357, 79);
        botones.value(2)->setGeometry((graph->width() / 2) - 179, (graph->height() / 2) + 120, 357, 79);
    }
    //------------------------------------------creacion fondoCompleto-----------------------------------------------
    fondoCompleto = new QPixmap();
    fondoCompleto->load(image_Background);
    //----------------------------------------------------------------------------------------------

    //------------------------------------------creacion brocha-----------------------------------------------
    brocha = new QBrush();
    brocha->setTexture(fondoCompleto->copy(_x, _y, _widthMap, _heightMap).scaled(_widthMap * nivel_Scale,
                                                                                 _heightMap * nivel_Scale));
    //-------------------------------------------------------------------------------------------------------------------

    escena->setBackgroundBrush(*brocha);
    this->grupoBotones->setVisible(true);
}
