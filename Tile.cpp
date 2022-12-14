#include "stdafx.h" // precompilado
#include "Tile.h"

Tile::Tile()
{
	_colision = false;
	_tipoTile = 0;
}

Tile::Tile(int tipo, int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura, const bool colision)
{
	//_tile.setSize(sf::Vector2f(tamanioCuadroF, tamanioCuadroF));
	//_tile.setFillColor(sf::Color::White);
	//_tile.setOutlineThickness(1.f);
	//_tile.setOutlineColor(sf::Color::Black);
	_tile.setPosition(static_cast<float>(cuadro_x) * tamanioCuadroF, static_cast<float>(cuadro_y) * tamanioCuadroF);
	_tile.setTexture(textura);
	_tile.setTextureRect(rect_textura);

	_colision = colision;
	_tipoTile = tipo;
}

Tile::~Tile()
{

}

const int& Tile::getTipoTile() const
{
	return _tipoTile;
}

const bool& Tile::getColision() const
{
	return _colision;
}

const sf::Vector2f& Tile::getPosicionTile() const
{
	return _tile.getPosition();
}

const sf::FloatRect Tile::getLimites() const
{
	return _tile.getGlobalBounds();
}

const bool Tile::interseccion(const sf::FloatRect limites) const
{
	return _tile.getGlobalBounds().intersects(limites);
}
