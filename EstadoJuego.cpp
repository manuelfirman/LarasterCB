#include "stdafx.h" // precompilado
#include "EstadoJuego.h"
void EstadoJuego::iniciarVariables()
{
    _gameOver = false;
    _pausa = false;
    _botonesPausa = false;
    _timerSonidoEnemigos.restart();
    _muerteEnemigo.restart();
}
void EstadoJuego::renderizadoDiferido()
{
    // Creando lienzo
    _renderTextura.create(_datosEstado->opcionesGraficas->_resolucion.width, _datosEstado->opcionesGraficas->_resolucion.height);

    _renderSprite.setTexture(_renderTextura.getTexture());
    _renderSprite.setTextureRect(sf::IntRect(0, 0, _datosEstado->opcionesGraficas->_resolucion.width, _datosEstado->opcionesGraficas->_resolucion.height));

}
/// --------------------- INICIALIZACIONES --------------------------
void EstadoJuego::iniciarVistaCam()
{
    _vistaCam.setSize(static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.width), static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.height));

    _vistaCam.setCenter(_datosEstado->opcionesGraficas->_resolucion.width / 2.f, _datosEstado->opcionesGraficas->_resolucion.height / 2.f);
}

void EstadoJuego::iniciarFuentes()
{
    if (!_fuenteJuego.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR LA FUENTE" << std::endl;
    }
}

void EstadoJuego::iniciarKeybinds()
{
    std::ifstream archivo("config/teclas_juego.ini");

    if (archivo.is_open()) {
        std::string accion = "";
        std::string tecla = "";

        while (archivo >> accion >> tecla) {
            _keybinds[accion] = _teclasSoportadas->at(tecla);
        }
    }

    archivo.close();
}

void EstadoJuego::iniciarTexturas()
{
    if (!_texturas["PLANTILLA_JUGADOR"].loadFromFile("recursos/img/personaje/soldier.png")) {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR TEXTURA DE JUGADOR" << std::endl;
    }
    if (!_texturas["DEMON"].loadFromFile("recursos/img/enemigos/demons/demon_rojo.png")) {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR TEXTURA DE ENEMIGO DEMON" << std::endl;
    }
    if (!_texturas["BOSS"].loadFromFile("recursos/img/enemigos/demons/demon_azul.png")) {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR TEXTURA DE ENEMIGO DEMON" << std::endl;
    }
    if (!_texturas["BAT"].loadFromFile("recursos/img/enemigos/bat.png")) {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR TEXTURA DE ENEMIGO BAT" << std::endl;
    }
    if (!_texturas["SLIME"].loadFromFile("recursos/img/enemigos/slime.png")) {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR TEXTURA DE ENEMIGO BAT" << std::endl;
    }
    if (!_texturas["SNAKE"].loadFromFile("recursos/img/enemigos/snake.png")) {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR TEXTURA DE ENEMIGO BAT" << std::endl;
    }
}

void EstadoJuego::iniciarSonidos()
{
    // JUGADOR
    if (!_bufferSonidosJ["JUGADOR_MOV"].loadFromFile("recursos/sonido/jugador/player_mov.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: 'recursos/sonido/jugador/player_mov.wav'" << std::endl;
    if (!_bufferSonidosJ["JUGADOR_HIT"].loadFromFile("recursos/sonido/jugador/player_hit.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: 'recursos/sonido/jugador/player_hit.wav'" << std::endl;
    if (!_bufferSonidosJ["JUGADOR_POTEO"].loadFromFile("recursos/sonido/jugador/player_poteo.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: 'recursos/sonido/jugador/player_poteo.wav'" << std::endl;
    if (!_bufferSonidosJ["JUGADOR_MORIR"].loadFromFile("recursos/sonido/jugador/player_die.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: 'recursos/sonido/jugador/player_die.wav'" << std::endl;
    if (!_bufferSonidosJ["JUGADOR_DMG"].loadFromFile("recursos/sonido/jugador/player_hurt1.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: 'recursos/sonido/jugador/player_hurt1.wav'" << std::endl;
    if (!_bufferSonidosJ["JUGADOR_LEVELUP"].loadFromFile("recursos/sonido/jugador/player_levelup.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: 'recursos/sonido/jugador/player_levelup.wav'" << std::endl;

    // BAT
    if(!_bufferSonidosJ["BAT_ATACAR"].loadFromFile("recursos/sonido/enemigos/bat_attack.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/bat_attack.wav" << std::endl;
    if(!_bufferSonidosJ["BAT_DMG"].loadFromFile("recursos/sonido/enemigos/bat_dmg.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/bat_dmg.wav" << std::endl;
    if(!_bufferSonidosJ["BAT_MORIR"].loadFromFile("recursos/sonido/enemigos/bat_die.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/bat_die.wav" << std::endl;
    if(!_bufferSonidosJ["BAT_MOV"].loadFromFile("recursos/sonido/enemigos/bat_mov.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/bat_mov.wav" << std::endl;

    // SLIME
    if(!_bufferSonidosJ["SLIME_ATACAR"].loadFromFile("recursos/sonido/enemigos/slime_attack.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/slime_attack.wav" << std::endl;
    if(!_bufferSonidosJ["SLIME_DMG"].loadFromFile("recursos/sonido/enemigos/slime_dmg.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/slime_dmg.wav" << std::endl;
    if(!_bufferSonidosJ["SLIME_MORIR"].loadFromFile("recursos/sonido/enemigos/slime_die.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/slime_die.wav" << std::endl;
    if(!_bufferSonidosJ["SLIME_MOV"].loadFromFile("recursos/sonido/enemigos/slime_mov.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/slime_mov.wav" << std::endl;

    // DEMON
    if(!_bufferSonidosJ["DEMON_ATACAR"].loadFromFile("recursos/sonido/enemigos/demon_attack.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/demon_attack.wav" << std::endl;
    if(!_bufferSonidosJ["DEMON_DMG"].loadFromFile("recursos/sonido/enemigos/demon_dmg.wav"))
        std::cout << "ERDEMONESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/demon_dmg.wav" << std::endl;
    if(!_bufferSonidosJ["DEMON_MORIR"].loadFromFile("recursos/sonido/enemigos/demon_die.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/demon_die.wav" << std::endl;
    if(!_bufferSonidosJ["DEMON_MOV"].loadFromFile("recursos/sonido/enemigos/demon_mov.wav"))
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR SONIDO: recursos/sonido/enemigos/demon_mov.wav" << std::endl;


}

void EstadoJuego::iniciarAudio()
{
    this->iniciarSonidos();
    _audio = new Audio("recursos/sonido/musica/musica_juego.ogg", _bufferSonidosJ);

}

void EstadoJuego::iniciarMenuPausa()
{
    _menuPausa = new MenuPausa(_datosEstado->opcionesGraficas->_resolucion, _fuenteJuego);
    _menuPausa->agregarBoton("GUARDAR", gui::p2pY(20.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(13.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(4.5f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "GUARDAR PARTIDA");
    _menuPausa->agregarBoton("TUTORIAL", gui::p2pY(60.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(13.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(4.5f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "TUTORIAL");
    _menuPausa->agregarBoton("VOLVER", gui::p2pY(70.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(13.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(4.5f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "VOLVER");
    _menuPausa->agregarBoton("SALIR", gui::p2pY(80.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(10.4f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(4.5f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "SALIR");
}

void EstadoJuego::iniciarSombras()
{
    if (!_sombra.loadFromFile("vert_sombras.vert", "frag_sombras.frag"))
    {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUEDEN CARGAR LAS SOMBRAS." << std::endl;
    }
}

void EstadoJuego::iniciarJugadores()
{
    _jugador = new Jugador(0, 0, _texturas["PLANTILLA_JUGADOR"], _bufferSonidosJ);
}

void EstadoJuego::iniciarGUIJugador()
{
    _GUIJugador = new GUIJugador(_jugador, _datosEstado->opcionesGraficas->_resolucion);
}

void EstadoJuego::iniciarManagerEnemigos()
{
    _managerEnemigos = new ManagerEnemigos(_enemigos, _texturas, _bufferSonidosJ, *_jugador);
}

void EstadoJuego::iniciarTileMap()
{
    //_tileMap = new TileMap(_datosEstado->tamanioCuadro, 32, 32, "recursos/img/mapa/terrenos/terreno_01.png");

    _tileMap = new TileMap("mapa.slmp");
}

void EstadoJuego::iniciarPopUps()
{
    _popUps = new TextoInfo("recursos/fuentes/kenpixel_square.ttf");
}


/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoJuego::EstadoJuego(DatosEstado* datos_estado) : EstadoBase(datos_estado)
{
    this->renderizadoDiferido();
    this->iniciarVistaCam();
    this->iniciarKeybinds();
    this->iniciarFuentes();
    this->iniciarTexturas();
    this->iniciarAudio();
    this->iniciarMenuPausa();
    this->iniciarSombras();

    this->iniciarJugadores();
    this->iniciarGUIJugador();
    this->iniciarManagerEnemigos();
    this->iniciarTileMap();
    this->iniciarPopUps();


    _audio->playMusica();
}

EstadoJuego::EstadoJuego(DatosEstado* datos_estado, const std::string ruta_slot) : EstadoBase(datos_estado)
{
    this->renderizadoDiferido();
    this->iniciarVistaCam();
    this->iniciarKeybinds();
    this->iniciarFuentes();
    this->iniciarTexturas();
    this->iniciarAudio();
    this->iniciarMenuPausa();
    this->iniciarSombras();

    cargarPartida(ruta_slot);

    this->iniciarGUIJugador();
    this->iniciarManagerEnemigos();
    this->iniciarTileMap();
    this->iniciarPopUps();


    _audio->playMusica();
}

EstadoJuego::~EstadoJuego()
{
    delete _jugador;
    delete _GUIJugador;
    delete _menuPausa;
    delete _managerEnemigos;
    delete _tileMap;
    delete _popUps;
    delete _audio;

    for (size_t i = 0; i < _enemigos.size(); i++) // delete enemigos
    {
        delete _enemigos[i];
    }

}

const bool EstadoJuego::guardarPartida(const std::string ruta_slot)
{
    bool archivoActivo = true;
    std::ofstream archivoOut;
    archivoOut.open(ruta_slot);

    if (archivoOut.is_open())
    {
        archivoOut  << archivoActivo << "\n"                                    // archivo activo
                    << _jugador->getPosicionSprite().x << "\n"                  // posicion X
                    << _jugador->getPosicionSprite().y << "\n"                  // posicion Y
                    << _jugador->getAtributos()->getNivel() << "\n"             // nivel
                    << _jugador->getAtributos()->getExp() << "\n"               // experiencia
                    << _jugador->getAtributos()->getHP() << "\n"                // vida
                    << _jugador->getAtributos()->getVitalidad() << "\n"         // vitalidad
                    << _jugador->getAtributos()->getFuerza() << "\n"            // fuerza
                    << _jugador->getAtributos()->getAgilidad() << "\n"          // agilidad
                    << _jugador->getAtributos()->getDestreza() << "\n"          // destreza
                    << _jugador->getAtributos()->getInteligencia() << "\n"      // inteligencia
                    << _jugador->getAtributos()->getPuntosAtributo();           // puntos de atributo

        archivoOut.close();
        return true;
    }
    else
    {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO GUARDAR PARTIDA EN ARCHIVO " << ruta_slot << std::endl;
    }

    archivoOut.close();
    return false;

}

const bool EstadoJuego::cargarPartida(const std::string ruta_slot)
{
    std::ifstream archivoIn;
    archivoIn.open(ruta_slot);

    if (archivoIn.is_open())
    {
        Atributos aux;
        bool activo;
        float posX;
        float posY;
        int nivel;
        int experiencia;
        int hp;
        int vitalidad;
        int fuerza;
        int agilidad;
        int destreza;
        int inteligencia;
        int puntosAtributo;

        archivoIn >> activo;
        if (activo)
        {
            archivoIn >> posX >> posY >> nivel >> experiencia >> hp >> vitalidad >> fuerza >> agilidad >> destreza >> inteligencia >> puntosAtributo;

            aux.setNivel(nivel);
            aux.setExperiencia(experiencia);
            aux.setHP(hp);
            aux.setVitalidad(vitalidad);
            aux.setFuerza(fuerza);
            aux.setAgilidad(agilidad);
            aux.setDestreza(destreza);
            aux.setInteligencia(inteligencia);
            aux.setPuntosAtributo(puntosAtributo);


            _jugador = new Jugador(posX, posY, _texturas["PLANTILLA_JUGADOR"], _bufferSonidosJ, true, &aux);

            archivoIn.close();
            return true;
        }
    }
    else
    {
        std::cout << "ERROR::ESTADOJUEGO::NO SE PUDO CARGAR PARTIDA. ARCHIVO: " << ruta_slot << std::endl;
    }

    archivoIn.close();
    return true;
}


const bool EstadoJuego::puedeSonar()
{
    if (_timerSonidoEnemigos.getElapsedTime().asSeconds() >= 3)
    {
        _timerSonidoEnemigos.restart().asSeconds();
        return true;
    }
    return false;
}

/// --------------------- ACTUALIZACIONES --------------------------

void EstadoJuego::actualizarVistaCam(const float& DT)
{
     //Jugador centrado
    _vistaCam.setCenter(std::floor(_jugador->getPosicionSprite().x), std::floor(_jugador->getPosicionSprite().y)); // floor para estabilizar el float en pixels

    if (_vistaCam.getSize().x >= _tileMap->getTamanioMaxCuadros().x) {

        if (_vistaCam.getCenter().x - _vistaCam.getSize().x / 2.f < 0.f) {                    // Limite izquierdo
            _vistaCam.setCenter(0.f + _vistaCam.getSize().x / 2.f, _vistaCam.getCenter().y);
        }
        else if (_vistaCam.getCenter().x + _vistaCam.getSize().x / 2.f > 4000.f) {
            _vistaCam.setCenter(4000.f - _vistaCam.getSize().x / 2.f, _vistaCam.getCenter().y);
        }

    }

    if (_vistaCam.getSize().y >= _tileMap->getTamanioMaxCuadros().y) {
        if (_vistaCam.getCenter().y + _vistaCam.getSize().y / 2.f > 4000.f) {
            _vistaCam.setCenter(_vistaCam.getCenter().x, 4000.f - _vistaCam.getSize().y / 2.f);
        }
        else if (_vistaCam.getCenter().y - _vistaCam.getSize().y / 2.f < 0.f) {
            _vistaCam.setCenter(_vistaCam.getCenter().x, 0.f + _vistaCam.getSize().y / 2.f);
        }
    }

    _vistaPosicionCuadros.x = static_cast<int>(_vistaCam.getCenter().x) / static_cast<int>(_datosEstado->tamanioCuadro);
    _vistaPosicionCuadros.y = static_cast<int>(_vistaCam.getCenter().y) / static_cast<int>(_datosEstado->tamanioCuadro);
}

void EstadoJuego::actualizarInput(const float& DT)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("CLOSE")))  && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");

        if(!_pausa){
            _botonesPausa = false;
            pausarEstado();
        }
        else{
            reanudarEstado();
        }
    }

}

void EstadoJuego::actualizarInputJugador(const float& DT)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_IZQUIERDA"))))
        _jugador->mover(-1.f, 0.f, DT);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_DERECHA"))))
        _jugador->mover(1.f, 0.f, DT);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_ARRIBA"))))
        _jugador->mover(0.f, -1.f, DT);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_ABAJO"))))
        _jugador->mover(0.f, 1.f, DT);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("SKILL"))) && getPpsTeclas())
        _jugador->actualizarSkill(DT, _posMouseVista);

}

void EstadoJuego::actualizarBotonesPausa()
{
    if (_menuPausa->getClick("GUARDAR") && getPpsTeclas())
    {
        _botonesPausa = true;
        _datosEstado->audio->playSonido("BOTON_CLICK");
        _menuPausa->agregarBoton("SLOT_1", gui::p2pY(28.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(10.4f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(3.f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "SLOT 1");
        _menuPausa->agregarBoton("SLOT_2", gui::p2pY(38.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(10.4f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(3.f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "SLOT 2");
        _menuPausa->agregarBoton("SLOT_3", gui::p2pY(48.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(10.4f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(3.f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "SLOT 3");
    }

    if (_botonesPausa)
    {

        if (_menuPausa->getClick("SLOT_1") && getPpsTeclas())
        {
            _datosEstado->audio->playSonido("BOTON_CLICK");
            if(guardarPartida("config/cargar_slot1.ini"))
            {
                _menuPausa->agregarBoton("GUARDADO", gui::p2pY(32.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(15.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(2.f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion, 160), "GUARDADO CORRECTAMENTE", true);
            }
            else
            {
                _menuPausa->agregarBoton("SINGUARDAR", gui::p2pY(32.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(15.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(2.f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion, 160), "NO SE PUDO GUARDAR", true);
            }
        }
        if (_menuPausa->getClick("SLOT_2") && getPpsTeclas())
        {
            _datosEstado->audio->playSonido("BOTON_CLICK");
            if(guardarPartida("config/cargar_slot2.ini"))
            {
                _menuPausa->agregarBoton("GUARDADO", gui::p2pY(42.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(15.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(2.f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion, 160), "GUARDADO CORRECTAMENTE", true);
            }
            else
            {
                _menuPausa->agregarBoton("SINGUARDAR", gui::p2pY(42.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(15.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(2.f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion, 160), "NO SE PUDO GUARDAR", true);
            }
        }
        if (_menuPausa->getClick("SLOT_3") && getPpsTeclas())
        {
            _datosEstado->audio->playSonido("BOTON_CLICK");
            if(guardarPartida("config/cargar_slot3.ini"))
            {
                _menuPausa->agregarBoton("GUARDADO", gui::p2pY(52.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(15.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(2.f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion, 160), "GUARDADO CORRECTAMENTE", true);
            }
            else
            {
                _menuPausa->agregarBoton("SINGUARDAR", gui::p2pY(52.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(15.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(2.f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion, 160), "NO SE PUDO GUARDAR", true);
            }
        }
    }

    if (_menuPausa->getClick("TUTORIAL") && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        _estado->push(new EstadoTutorial(_datosEstado));
    }

    if (_menuPausa->getClick("VOLVER") && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_ATRAS");
        _pausa = false;
    }

    if (_menuPausa->getClick("SALIR") && getPpsTeclas())
    {
        _datosEstado->audio->playSonido("BOTON_ATRAS");
        finEstado();
    }
}

void EstadoJuego::actualizarTileMap(const float& DT)
{
    _tileMap->actualizarLimitesMapa(_jugador, DT);
    _tileMap->checkColision(_jugador, DT);
    _tileMap->actualizarTiles(_jugador, DT, *_managerEnemigos);
}

void EstadoJuego::actualizarJugador(const float& DT)
{
    _jugador->actualizar(DT, _posMouseVista);

    _GUIJugador->actualizar(DT);

    if(_jugador->getAtributos()->getHP() <= 0 && !_gameOver)
    {
        _jugador->getSonido().play("MORIR");
        _estado->push(new GameOver(_datosEstado));
        _gameOver = true;
    }

    if(_jugador->getEnMovimiento() && getPpsTeclas()) _jugador->getSonido().playSonidoMov();
}

void EstadoJuego::actualizarAtaques(Enemigos* enemigo, const int indice, const float& DT)
{
        if (enemigo->getLimites().contains(_posMouseVista))                         // aim mouse
        {
            if (enemigo->getDistancia(*_jugador) < _jugador->getArma()->getRango()) // esta en rango?
            {
                if (_jugador->getArma()->getTimerAtaque())                          // puede atacar?
                {
                    if (enemigo->getDmgTerminado())
                    {
                        int dmg = static_cast<int>(_jugador->getArma()->getDMG() + _jugador->getAtributos()->getDmg());
                        enemigo->perderVida(dmg);
                        enemigo->resetTimerDmg();
                        _popUps->agregarPopUp(tipo_popUp::POP_NEGATIVO, enemigo->getCentro().x, enemigo->getCentro().y, "-", dmg, "hp");
                        _jugador->getSonido().play("HIT");
                        enemigo->getSonido().play("DMG");
                    }

                }
            }
        }
}

void EstadoJuego::actualizarEnemigos(const float& DT)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))      // input ataque
    {
        _jugador->setInicioAtaque(true); // inicia ataque
    }


    int indice = 0;

    for (auto* enemigo : _enemigos)
    {
        enemigo->actualizar(DT, _posMouseVista);
        if(enemigo->getEnMovimiento() && puedeSonar())
        {
            enemigo->getSonido().playSonidoMov();
        }

        _tileMap->actualizarLimitesMapa(enemigo, DT); // limites exteriores
        _tileMap->checkColision(enemigo, DT); // Colisiones mapa

        if (_jugador->getIniciaAtaque())
        {
            actualizarAtaques(enemigo, indice, DT); // da?o
        }

        if (_jugador->getDistancia(*enemigo) < enemigo->getRango())
        {
            if (enemigo->getAtaqueTerminado())
            {
                int dmg = static_cast<int>(enemigo->getAtributos()->_dmgMax);
                _jugador->perderHP(dmg);
                enemigo->resetTimerAtaque();
                _popUps->agregarPopUp(tipo_popUp::POP_NEGATIVO, _jugador->getCentro().x, _jugador->getCentro().y, "-", dmg, "hp");
                enemigo->getSonido().play("ATACAR");
                _jugador->getSonido().play("DMG");
            }
        }

        // TODO: buscar otra forma / consultar si no es peligrosa para la memoria
        if (!enemigo->estaVivo())
        {
            enemigo->getSonido().play("MORIR");
            _jugador->ganarExperiencia(enemigo->getExperiencia());
            _popUps->agregarPopUp(tipo_popUp::POP_EXPERIENCIA, _jugador->getCentro().x, _jugador->getCentro().y, "+", static_cast<int>(enemigo->getExperiencia()), "exp");
            _managerEnemigos->eliminarEnemigo(indice);
            --indice;
        }

        ++indice;
    }

    _jugador->setInicioAtaque(false); // reset inicia ataque
}


void EstadoJuego::actualizar(const float& DT)
{
    if(_gameOver) finEstado();

    actualizarPosicionMouse(&_vistaCam);
    actualizarPpsTeclas(DT);
    actualizarInput(DT);

    if (!_pausa) // actualizar sin pausa
    {
        actualizarVistaCam(DT);

        actualizarInputJugador(DT);

        actualizarTileMap(DT);

        actualizarJugador(DT);

        actualizarEnemigos(DT);

        _popUps->actualizar(DT);

        if(_jugador->getAtributos()->getSubeLvl()) _jugador->getSonido().play("LEVELUP");
    }
    else // actualizar con pausa
    {
        _menuPausa->actualizar(_posMouseVentana);
        actualizarBotonesPausa();
    }

}


/// --------------------- RENDERIZAR --------------------------
void EstadoJuego::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    _renderTextura.clear();

    // TODO SE RENDERIZA A TRAVES DEL LIENZO
    // Mapa
    _renderTextura.setView(_vistaCam); // set vista
    _tileMap->renderizar(_renderTextura, _jugador->getCuadroActual(static_cast<int>(_datosEstado->tamanioCuadro)), _jugador->getCentro(), &_sombra);

    // Enemigos
    for (auto* enemigo : _enemigos)
    {
        enemigo->renderizar(_renderTextura, &_sombra, _jugador->getCentro(), false);
    }

    // Jugador
    _jugador->renderizar(_renderTextura, &_sombra, _jugador->getCentro(), false);

    // Render Lienzo
    _tileMap->renderizacionDiferida(_renderTextura);

    // Pop Ups
    _popUps->renderizar(_renderTextura);

    //GUI
    _renderTextura.setView(_renderTextura.getDefaultView()); // vista por default
    _GUIJugador->renderizar(_renderTextura);

    // Pausa
    if (_pausa) {
        _menuPausa->renderizar(_renderTextura);
    }

    _renderTextura.display();

    // RENDERIZADO FINAL
    target->draw(_renderSprite); //(la ventana dibuja el sprite del lienzo, que contiene el renderizado de lo demas)

}
