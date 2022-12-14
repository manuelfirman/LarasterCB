#include "stdafx.h"
#include "demonboss.h"

void DemonBoss::iniciarVariables()
{

}

void DemonBoss::iniciarIA()
{
    // _inteligenciaArtificial->AgregarOpcion();
    //
}

void DemonBoss::iniciarAnimaciones()
{
    // key - Velocidad animacion - inicioX - inicioY - framesX - framesY
    _animacion->agregarAnimacion("QUIETO", 6.f, 0, 0, 2, 0, 64, 64);         // Quieto
    _animacion->agregarAnimacion("CAMINAR_ABAJO", 6.f, 0, 2, 3, 2, 64, 64);   // Caminar abajo
    _animacion->agregarAnimacion("CAMINAR_ARRIBA", 6.f, 0, 0, 3, 0, 64, 64);    // Caminar arriba
    _animacion->agregarAnimacion("CAMINAR_X", 6.f, 0, 3, 3, 3, 64, 64);         // Caminar derecha
}

void DemonBoss::iniciarGUI()
{
    _barraHP.setSize(sf::Vector2f(200.f, 15.f));
    _barraHP.setFillColor(sf::Color::Red);
    _barraHP.setPosition(_sprite.getPosition().x - _barraHP.getSize().x / 1.3f, _sprite.getPosition().y);
}

DemonBoss::DemonBoss(float x, float y, sf::Texture& textura, std::map<std::string, sf::SoundBuffer>& sonidos, SpawnerEnemigos& tile_spawner, Entidades& jugador) : Enemigos(tile_spawner)
{
    this->iniciarVariables();
    crearHitbox(_sprite, -70.f, +35.f, 56.f, 80.f);       // Hitbox
    crearComponenteMovimiento(80.f, 1700.f, 1000.f);    // Movimiento
    crearComponenteAnimacion(textura);                  // Animacion
    crearComponenteAtributos(250);                        // Atributos
    crearComponenteSonidos(sonidos, "DEMON");           // Sonidos
    setPosicion(x, y);                                  // Posicion
    this->iniciarAnimaciones();                         // Animaciones
    this->iniciarGUI();                                 // GUI
    _sprite.setScale(2.f, 2.f);

    _inteligenciaArtificial = new IA(jugador, *this);
}

DemonBoss::~DemonBoss()
{
    delete _inteligenciaArtificial;
}

void DemonBoss::actualizarIA(const float DT)
{
     _inteligenciaArtificial->seguir(DT);
    // _inteligenciaArtificial->atacar();
    // _inteligenciaArtificial->
}

void DemonBoss::actualizarAnimacion(const float& DT)
{
    if (_movimiento->getEstadoMov(QUIETO))
    {
        _animacion->play("QUIETO", DT);
    }
    else if (_movimiento->getEstadoMov(MOV_DERECHA))
    {
        _sprite.setOrigin((_sprite.getGlobalBounds().width / 2.f) - (_hitbox->getLimites().width / 4.f), 0.f);
        _sprite.setScale(2.f, 2.f);
        _animacion->play("CAMINAR_X", DT, _movimiento->getVelocidad().x, _movimiento->getVelocidadMax());
    }
    else if (_movimiento->getEstadoMov(MOV_IZQUIERDA))
    {
        _sprite.setOrigin(0.f, 0.f);
        _sprite.setScale(-2.f, 2.f);
        _animacion->play("CAMINAR_X", DT, _movimiento->getVelocidad().x, _movimiento->getVelocidadMax());
    }
    else if (_movimiento->getEstadoMov(MOV_ABAJO))
    {
        _animacion->play("CAMINAR_ABAJO", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
    }
    else if (_movimiento->getEstadoMov(MOV_ARRIBA))
    {
        _animacion->play("CAMINAR_ARRIBA", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
    }
}


void DemonBoss::actualizar(const float& DT, sf::Vector2f& posMouseVista)
{
    _movimiento->actualizar(DT);

    _barraHP.setFillColor(sf::Color::Red);
    _barraHP.setSize(sf::Vector2f(200.f * (static_cast<float>(_atributos->_hp) / _atributos->_hpMax), 15.f));
    _barraHP.setPosition(_sprite.getPosition().x - _barraHP.getSize().x / 1.5f, _sprite.getPosition().y);

    actualizarIA(DT);

    actualizarAnimacion(DT);

    _hitbox->actualizar();
}

void DemonBoss::renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox)
{
    if (sombra)
    {
        sombra->setUniform("tieneTextura", true);
        sombra->setUniform("luz", posLuz);
        target.draw(_sprite, sombra);
    }
    else // si no hay sombra
        target.draw(_sprite);

    target.draw(_barraHP);

    if (mostrar_hitbox)
        _hitbox->renderizar(target);

}
