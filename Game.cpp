#include "stdafx.h" // precompilado
#include "Game.h"
/// --------------------- INICIALIZACIONES --------------------------
void Game::iniciarVariables()
{
    _ventana = NULL;
    _DT = 0.f;
    _tamanioCuadro = 32.f;
}

void Game::iniciarOpcionesGraficas()
{
    _opcionesGraficas.cargarDesdeArchivo("config/config_grafica.ini");
}

void Game::iniciarDatosEstado()
{
    _datosEstado.tamanioCuadro = _tamanioCuadro;
    _datosEstado.ventana = _ventana;
    _datosEstado.opcionesGraficas = &_opcionesGraficas;
    _datosEstado.teclasSoportadas = &_teclasSoportadas;
    _datosEstado.estado = &_estado;
    _datosEstado.audio = _audio;
    _datosEstado.bufferSonidos = &_bufferSonidos;
}

void Game::iniciarVentana()
{
    if (_opcionesGraficas._fullscreen)
        _ventana = new sf::RenderWindow(_opcionesGraficas._resolucion, _opcionesGraficas._titulo, sf::Style::Fullscreen, _opcionesGraficas._opcionesContexto);
    else
        _ventana = new sf::RenderWindow(_opcionesGraficas._resolucion, _opcionesGraficas._titulo, sf::Style::Titlebar | sf::Style::Close, _opcionesGraficas._opcionesContexto);

    _ventana->setFramerateLimit(_opcionesGraficas._limiteFramerate);
    _ventana->setVerticalSyncEnabled(_opcionesGraficas._sincVertical);
}

void Game::iniciarEstados()
{
    _estado.push(new EstadoMenuPrincipal(&_datosEstado));
}

void Game::iniciarTeclas()
{
    std::ifstream archivo("config/teclas_soportadas.ini");

    if (archivo.is_open()) {
        std::string tecla = "";
        int valor_tecla = 0;

        while (archivo >> tecla >> valor_tecla) {
            _teclasSoportadas[tecla] = valor_tecla;
        }
    }
}

void Game::iniciarAudio()
{
    if (!_bufferSonidos["BOTON_CLICK"].loadFromFile("recursos/sonido/efectos/boton_click.wav"))
        std::cout << "ERROR::ESTADOMENUPRINCIPAL::NO SE PUDO CARGAR SONIDO: recursos/sonidos/efectos/boton_click.wav" << std::endl;
    if (!_bufferSonidos["BOTON_ATRAS"].loadFromFile("recursos/sonido/efectos/boton_atras.wav"))
        std::cout << "ERROR::ESTADOMENUPRINCIPAL::NO SE PUDO CARGAR SONIDO: recursos/sonidos/efectos/boton_atras.wav" << std::endl;

    _audio = new Audio("recursos/sonido/musica/musica_menu.wav", _bufferSonidos);
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
Game::Game()
{
    this->iniciarVariables();
    this->iniciarOpcionesGraficas();
    this->iniciarVentana();
    this->iniciarTeclas();
    this->iniciarAudio();
    this->iniciarDatosEstado();
    this->iniciarEstados();
}

Game::~Game()
{
    delete _ventana;
    delete _audio;
    while (!_estado.empty()) {   // al ser memoria dinamica
        delete _estado.top(); // 1) se elimina el contenido del puntero
        _estado.pop();       // 2) se elimina el puntero
        std::cout << "debug destructor game" << std::endl;
    }
}

void Game::finAplicacion()
{
    std::cout << "Cerrando la aplicacion" << std::endl;
}

/// --------------------- ACTUALIZACIONES --------------------------
void Game::actualizarDT()
{
    _DT = relojDt.restart().asSeconds();
    //    std::cout << _DT << std::endl;
}

void Game::actualizarEventosSFML()
{
    while (_ventana->pollEvent(sfEvento))
    {
        if (sfEvento.type == sf::Event::Closed) {
            _ventana->close();
        }
    }
}

void Game::actualizar()
{
    actualizarEventosSFML();

    /// actualizar si la pila no esta vacia y la ventana esta en foco
    if (!_estado.empty()) {
        if (_ventana->hasFocus())
        {
            _estado.top()->actualizar(_DT);

            if (_estado.top()->getSalir())
            {
                _estado.top()->finEstado();
                delete _estado.top(); // libera memoria
                _estado.pop(); // saca puntero
            }
        }
    }
    /// si la pila esta vacia, cierra ventana
    else {
        finAplicacion();
        _ventana->close();
    }
}


/// --------------------- RENDERIZAR --------------------------
void Game::renderizar() {
    /// Clear.
    _ventana->clear();

    /// Renderizar
    if (!_estado.empty()) {
        _estado.top()->renderizar();
    }

    /// Display.
    _ventana->display();
}

/// --------------------- GAMELOOP --------------------------
void Game::gameloop()
{
    while (_ventana->isOpen()) {
        /// Delta Time.
        this->actualizarDT();
        /// Actualizar
        this->actualizar();
        /// Renderizar
        this->renderizar();
    }
}
