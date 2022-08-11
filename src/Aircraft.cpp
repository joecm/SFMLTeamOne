/*
 * Aircraft.cpp
 *
 *  Created on: 4 jun 2022
 *      Author: joe
 */

#include "../include/Aircraft.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

// Relacionar las texturas delos aircraf con las texturas
// de la enum class Textures de ResourceHolder

Textures toTextureID(Aircraft::Type type) { // @suppress("No return")
	switch (type) {
		case Aircraft::Type::Eagle:
			return Textures::Eagle;

		case Aircraft::Type::Raptor:
			return Textures::Raptor;
	}
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
: mType(type), mSprite(textures.get(toTextureID(type)))
{
	// mSprite.setTexture(textures.get(toTextureID(type))); // tambien habría valido

	// Alineando el origen
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

}

Aircraft::~Aircraft() {
	// TODO Auto-generated destructor stub
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	// enviamos el drawable y las transformaciones (traslación, rotación, escala, etc)
	target.draw(mSprite, states);
;}

unsigned int Aircraft::getCategory() const {
	switch (mType) {
		case Type::Eagle:
			return Category::PlayerAircraft;
		default:
			return Category::EnemyAircraft;
	}
}
