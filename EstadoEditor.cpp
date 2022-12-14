#include "stdafx.h" // precompilado
#include "EstadoEditor.h"

void EstadoEditor::iniciarModos()
{
    _vModo.push_back(new Editor_Mapa(_datosEstado, &_datosEditor, _tileMap));
    _vModo.push_back(new Editor_SpawnerEnemigos(_datosEstado, &_datosEditor, _tileMap));

    _modoEditor = mod_editor::MAPA;
}

/// --------------------- INICIALIZACIONES --------------------------
void EstadoEditor::iniciarVariables()
{
    _velocidadCamara = 100.f;
}

void EstadoEditor::iniciarDatosEditor()
{
    _datosEditor.vista = &_vista;
    _datosEditor.keybinds = &_keybinds;
    _datosEditor.fuente = &_fuente;
    _datosEditor.posMouseVista = &_posMouseVista;
    _datosEditor.posMousePantalla = &_posMousePantalla;
    _datosEditor.posMouseVentana = &_posMouseVentana;
    _datosEditor.posMouseCuadro = &_posMouseCuadro;
    _datosEditor.ppsTeclas = &_ppsTeclas;
    _datosEditor.ppsTeclasMax = &_ppsTeclasMax;
}

void EstadoEditor::iniciarVista()
{
    _vista.setSize(sf::Vector2f(static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.width), static_cast<float>(_datosEstado->opcionesGraficas->_resolucion.height)));
    _vista.setCenter(_datosEstado->opcionesGraficas->_resolucion.width / 2.f, _datosEstado->opcionesGraficas->_resolucion.height / 2.f);
}

void EstadoEditor::iniciarKeybinds()
{
    std::ifstream archivo("config/teclas_editorestado.ini");

    if (archivo.is_open()) {
        std::string accion = "";
        std::string tecla = "";

        while (archivo >> accion >> tecla) {
            _keybinds[accion] = _teclasSoportadas->at(tecla);
        }
    }

    archivo.close();
}

void EstadoEditor::iniciarFondo()
{


}

void EstadoEditor::iniciarFuentes()
{
    if (!_fuente.loadFromFile("recursos/fuentes/Bungee-Regular.ttf")) {
        std::cout << "ERROR::ESTADOEDITOR::NO SE PUDO CARGAR LA FUENTE" << std::endl;
    }
}


void EstadoEditor::iniciarMenuPausa()
{
    _menuPausa = new MenuPausa(_datosEstado->opcionesGraficas->_resolucion, _fuente);

    _menuPausa->agregarBoton("SALIR", gui::p2pY(74.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(10.4f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(4.5f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "SALIR");

    _menuPausa->agregarBoton("GUARDAR", gui::p2pY(55.5f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(10.4f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(4.5f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "GUARDAR");

    _menuPausa->agregarBoton("CARGAR", gui::p2pY(37.f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pX(10.4f, _datosEstado->opcionesGraficas->_resolucion), gui::p2pY(4.5f, _datosEstado->opcionesGraficas->_resolucion), gui::calcTamCaracter(_datosEstado->opcionesGraficas->_resolucion), "CARGAR");
}

void EstadoEditor::iniciarBotones()
{

}

void EstadoEditor::iniciarGUI()
{

}

void EstadoEditor::iniciarTileMap()
{
    _tileMap = new TileMap(_datosEstado->tamanioCuadro, 100, 100, "recursos/img/mapa/terrenos.png");
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
EstadoEditor::EstadoEditor(DatosEstado* datos_estado)
    : EstadoBase(datos_estado)
{
    this->iniciarDatosEditor();

    this->iniciarVariables();
    this->iniciarVista();
    this->iniciarKeybinds();
    this->iniciarFondo();
    this->iniciarFuentes();

    this->iniciarMenuPausa();
    this->iniciarBotones();
    this->iniciarTileMap();
    this->iniciarGUI();

    this->iniciarModos();

    std::cout << "Debug Estado Editor" << std::endl;
}

EstadoEditor::~EstadoEditor()
{
    auto it = _boton.begin();
    for (it = _boton.begin(); it != _boton.end(); ++it) {
        delete it->second;
    }

    delete _menuPausa;
    delete _tileMap;

    for (size_t i = 0; i < _vModo.size(); i++)
    {
        delete _vModo[i];
    }
}


/// --------------------- ACTUALIZACIONES --------------------------
void EstadoEditor::actualizarInput(const float& DT)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("CLOSE"))) && getPpsTeclas())
    {

        if (!_pausa)
        {
            _datosEstado->audio->playSonido("BOTON_CLICK");
            pausarEstado();
        }
        else
        {
            _datosEstado->audio->playSonido("BOTON_ATRAS");
            reanudarEstado();
        }
    }

}

void EstadoEditor::actualizarInputEditor(const float& DT)
{
    // MOVER CAMARA
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_CAM_ARRIBA")))) //TODO: agregar ppsTeclas
    {
        _vista.move(0.f, -_velocidadCamara * DT);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_CAM_ABAJO"))))
    {
        _vista.move(0.f, _velocidadCamara * DT);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_CAM_DERECHA"))))
    {
        _vista.move(_velocidadCamara * DT, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MOVER_CAM_IZQUIERDA"))))
    {
        _vista.move(-_velocidadCamara * DT, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
    {
        _velocidadCamara = 700.f;
    }
    else
    {
        _velocidadCamara = 100.f;
    }

    // CAMBIAR MODO DE EDITOR
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MODO_ARRIBA"))) && getPpsTeclas())
    {
        if (_modoEditor < _vModo.size() -1)
        {
            _modoEditor++;
        }
        else
        {
            std::cout << "ESTADOEDITOR::ESTAS EN EL MODO MAXIMO ("<< _modoEditor << ")" << std::endl;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(_keybinds.at("MODO_ABAJO"))) && getPpsTeclas())
    {
        if (_modoEditor > 0)
        {
            _modoEditor--;
        }
        else
        {
            std::cout << "ESTADOEDITOR::ESTAS EN EL MODO 0 (MAPA)" << std::endl;
        }
    }
}

void EstadoEditor::actualizarBotones()
{
    for (auto& botones : _boton) {
        botones.second->actualizar(_posMouseVentana);
    }

}

void EstadoEditor::actualizarGUI(const float& DT)
{

}

void EstadoEditor::actualizarBotonesMenuPausa()
{
    if (_menuPausa->getClick("CARGAR"))
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        _tileMap->cargarDesdeArchivo("mapa.slmp");
    }

    if (_menuPausa->getClick("GUARDAR"))
    {
        _datosEstado->audio->playSonido("BOTON_CLICK");
        _tileMap->guardarEnArchivo("mapa.slmp");
    }

    if (_menuPausa->getClick("SALIR"))
    {
        _datosEstado->audio->playSonido("BOTON_ATRAS");
        finEstado();
    }
}

void EstadoEditor::actualizarModos(const float& DT)
{
    _vModo[_modoEditor]->actualizar(DT);
}

// ACTUALIZAR ESTADO EDITOR
void EstadoEditor::actualizar(const float& DT)
{
    actualizarPosicionMouse(&_vista);
    actualizarPpsTeclas(DT);
    actualizarInput(DT);

    if (!_pausa) // No pausa
    {
        actualizarGUI(DT);
        actualizarBotones();
        actualizarInputEditor(DT);
        actualizarModos(DT);
    }
    else // pausa
    {
        _menuPausa->actualizar(_posMouseVentana);
        actualizarBotonesMenuPausa();
    }

}


/// --------------------- RENDERIZAR --------------------------
void EstadoEditor::renderBotones(sf::RenderTarget& target)
{
    for (auto& botones : _boton) {
        botones.second->renderizar(target);
    }
}

void EstadoEditor::renderizarGUI(sf::RenderTarget& target)
{

}

void EstadoEditor::renderizarModos(sf::RenderTarget& target)
{
    _vModo[_modoEditor]->renderizar(target);
}

void EstadoEditor::renderizar(sf::RenderTarget* target)
{
    if (!target)
        target = _ventana;

    // render tile map con la vista seteada
    target->setView(_vista);
    _tileMap->renderizar(*target, _posMouseCuadro);
    _tileMap->renderizacionDiferida(*target);

    // render botones con vista por default
    target->setView(_ventana->getDefaultView());
    renderBotones(*target);

    renderizarGUI(*target); // vista dentro del metodo

    renderizarModos(*target);

    if (_pausa)
    {
        // render menu con vista por default
        target->setView(_ventana->getDefaultView());
        _menuPausa->renderizar(*target);
    }


}
