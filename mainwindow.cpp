#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (nivelActual != nullptr) nivelActual->key_event(event);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    numNivel = '0';
    dificultadJuego = 1;
    puntuaciones = new QString[3];
    puntuaciones[0] = "0";
    puntuaciones[1] = "0";
    puntuaciones[2] = "0";
    ui->BotMenuPrincipal->setVisible(false);
    ui->BotonesContinuar->setVisible(false);
    ui->BotonesFinNivel->setVisible(false);
    ui->BotonesPausa->setVisible(false);
    ui->dificultItems->setVisible(false);
    nivelActual = nullptr;
    menuActual = nullptr;
    setup_menuPrincipal();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (nivelActual != nullptr) delete nivelActual;
    if (menuActual != nullptr) delete menuActual;
}

void MainWindow::terminarNivel(char sigNivel)
{
    puntuaciones[int(numNivel - '1')] = nivelActual->getPuntaje();
    numNivel = sigNivel;
    setup_menuFinNivel();
}

void MainWindow::setup_nivel1()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    nivelActual = new nivel(ui->graphicsView, ":/imagenes/caves.png", ":/imagenes/caves_reference.png", 8, 800, 468, 0, 0, 1, 1,
                            ui->salud, dificultadJuego);
    connect(nivelActual, SIGNAL(heTerminado(char)), this, SLOT(terminarNivel(char)));
    ui->dificultItems->setVisible(false);
    ui->botonPausa->setVisible(true);
    if (numNivel == '0') numNivel = '1';
}

void MainWindow::setup_nivel2()
{

    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    nivelActual = new nivel(ui->graphicsView, ":/imagenes/Yermo.png", ":/imagenes/Yermo_reference.png", 1, 800, 1500, 0, 0, 2, 0,
                            ui->salud, dificultadJuego);
    connect(nivelActual, SIGNAL(heTerminado(char)), this, SLOT(terminarNivel(char)));
    ui->dificultItems->setVisible(false);
    ui->botonPausa->setVisible(true);
}

void MainWindow::setup_nivel3()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    nivelActual = new nivel(ui->graphicsView, ":/imagenes/savannah.png", ":/imagenes/savannah_reference.png", 1, 800, 1500, 0, 0, 3, 0,
                            ui->salud, dificultadJuego);
    connect(nivelActual, SIGNAL(heTerminado(char)), this, SLOT(terminarNivel(char)));
    ui->dificultItems->setVisible(false);
    ui->botonPausa->setVisible(true);
}

void MainWindow::setup_menuPrincipal()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    menuActual = new menu(ui->graphicsView, ":/imagenes/menuPrincipal.png", 1, 800, 1500, 0, 0, setup_botonesMenuP(),
                          ui->BotMenuPrincipal, 'P');
    if (numNivel == '4') numNivel = '3';
    ui->dificultItems->setVisible(true);
    ui->botonPausa->setVisible(false);
}

void MainWindow::setup_menuContinuar()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    menuActual = new menu(ui->graphicsView, ":/imagenes/continuarJuego.png", 1, 800, 1500, 0, 0, setup_botonesMenuContinuar(),
                          ui->BotonesContinuar, 'C');
    ui->dificultItems->setVisible(false);
    ui->botonPausa->setVisible(false);
}

void MainWindow::setup_menuFinNivel()
{
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    if(nivelActual != nullptr)
    {
        delete nivelActual;
        nivelActual = nullptr;
    }
    menuActual = new menu(ui->graphicsView, ":/imagenes/finNivel.png", 1, 800, 1500, 0, 0, setup_botonesMenuPasoNivel(),
                          ui->BotonesFinNivel, 'F');
    ui->botonPausa->setVisible(false);
}

void MainWindow::setup_menuPausa()
{
    menuActual = new menu(ui->graphicsView, ":/imagenes/menuPausa.png", 1, 800, 1500, 0, 0, setup_botonesMenuPausa(),
                          ui->BotonesPausa, 'p');
    ui->botonPausa->setVisible(false);
}

void MainWindow::guardarPartida()
{
    std::ofstream file("datos.txt");
    short int cantidadNivelesCompletados = numNivel - '0';
    for (short int i = 0; i < cantidadNivelesCompletados; i++)
    {
        file << std::string(1, char(i + '1')) << " " << puntuaciones[i].toStdString() << '\n';
    }
    file.close();
}

void MainWindow::cargarPartida()
{
    std::ifstream file("datos.txt");
    int cont = 0;
    std::string linea;
    while (std::getline(file, linea))
    {
        numNivel = linea[0];
        puntuaciones[cont] = QString::fromStdString(linea.substr(2));
        cont++;
    }
    file.close();
}



QVector<QPushButton*> MainWindow::setup_botonesMenuP()
{
    QVector<QPushButton*> botones;
    botones.push_back(ui->jugar);
    botones.push_back(ui->continuar);
    botones.push_back(ui->cargarPartida);
    botones.push_back(ui->salir);
    return botones;
}

QVector<QPushButton*> MainWindow::setup_botonesMenuContinuar()
{
    QVector<QPushButton*> botones;
    botones.push_back(ui->nivel1);
    botones.push_back(ui->nivel2);
    botones.push_back(ui->nivel3);
    botones.push_back(ui->atras);
    return botones;
}

QVector<QPushButton*> MainWindow::setup_botonesMenuPasoNivel()
{
    QVector<QPushButton*> botones;
    botones.push_back(ui->menuPrincipal);
    botones.push_back(ui->siguienteNivel);
    return botones;
}

QVector<QPushButton *> MainWindow::setup_botonesMenuPausa()
{
    QVector<QPushButton*> botones;
    botones.push_back(ui->continuarNivel);
    botones.push_back(ui->reiniciar);
    botones.push_back(ui->menuPrincipalP);
    return botones;
}

void MainWindow::on_jugar_released()
{
    numNivel = '1';
    setup_nivel1();
}


void MainWindow::on_continuar_released()
{
    setup_menuContinuar();
}


void MainWindow::on_atras_released()
{
    setup_menuPrincipal();
}


void MainWindow::on_nivel1_released()
{
    setup_nivel1();
}


void MainWindow::on_nivel2_released()
{
    if(numNivel == '2' || numNivel == '3') setup_nivel2();
}


void MainWindow::on_nivel3_released()
{
    if(numNivel == '3') setup_nivel3();
}


void MainWindow::on_menuPrincipal_released()
{

    setup_menuPrincipal();
}


void MainWindow::on_botonPausa_released()
{
    if (nivelActual != nullptr)
    {
        setup_menuPausa();
        connect(menuActual, SIGNAL(estoyActivo()), nivelActual, SLOT(pausarNivel()));
        connect(menuActual, SIGNAL(termine()), nivelActual, SLOT(recuperaEscena()));
        menuActual->pausarJuego();
    }
}


void MainWindow::on_continuarNivel_released()
{
    menuActual->darPasoA_nivel();
    if (menuActual != nullptr)
    {
        delete menuActual;
        menuActual = nullptr;
    }
    ui->botonPausa->setVisible(true);
}


void MainWindow::on_reiniciar_released()
{
    if (numNivel == '1') setup_nivel1();
    else if (numNivel == '2') setup_nivel2();
    else if (numNivel == '3') setup_nivel3();
    ui->botonPausa->setVisible(true);
}


void MainWindow::on_menuPrincipalP_released()
{
    setup_menuPrincipal();
}


void MainWindow::on_siguienteNivel_released()
{
    if(numNivel == '2') setup_nivel2();
    else if(numNivel == '3') setup_nivel3();
    else if(numNivel == '4')
    {
        numNivel = '3';
        setup_menuPrincipal();
    }
}


void MainWindow::on_cargarPartida_released()
{
    cargarPartida();
}


void MainWindow::on_dificultSelector_valueChanged(int value)
{
    dificultadJuego = value + 1;
}


void MainWindow::on_salir_released()
{
    guardarPartida();
    this->close();
}

