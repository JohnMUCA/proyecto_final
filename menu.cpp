#include "menu.h"

menu::menu(QGraphicsView *graphicsV, QString imageBackground, float nivelScale, unsigned int height, unsigned int width,
           unsigned int x, unsigned int y, QVector<QPushButton *> botones, QGroupBox *grupoBotones, char tipoMenu)
{
    graph = graphicsV;
    this->botones = botones;
    this->grupoBotones = grupoBotones;
    setup_scene(imageBackground, nivelScale, height, width, x, y);
}

menu::~menu()
{
    delete escena;
    delete brocha;
    delete fondoCompleto;
    this->grupoBotones->setVisible(false);
}

void menu::setup_scene(QString image_Background, float nivel_Scale, unsigned int _heightMap, unsigned int _widthMap, unsigned int _x, unsigned int _y)
{
    graph->setGeometry(0, 0, 1500, 800);
    escena = new QGraphicsScene;
    escena->setSceneRect(0, 0, graph->width() - 2, graph->height() - 2);
    graph->setScene(escena);
    //----------------------------------------------- Botones ----------------------------------------------

    grupoBotones->setGeometry(0, 0, graph->width(), graph->height());
    botones.value(0)->setGeometry((graph->width() / 2) - 70, (graph->height() / 2) - 30, 140, 60);
    botones.value(1)->setGeometry((graph->width() / 2) - 80, (graph->height() / 2) + 60, 160, 60);

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
