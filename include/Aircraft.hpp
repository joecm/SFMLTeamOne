/*
 * Aircraft.hpp
 *
 *  Created on: 4 jun 2022
 *      Author: joe
 */

#ifndef INCLUDE_AIRCRAFT_HPP_
#define INCLUDE_AIRCRAFT_HPP_

#include "../include/Entity.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../include/ResourceHolder.hpp"

class Aircraft: public Entity {
public:
	enum class Type {
		Eagle,
		Raptor
	};

	explicit Aircraft(Type type, const TextureHolder& textures);
	virtual ~Aircraft();
	virtual unsigned int getCategory() const override;

private:
	Type mType;
	sf::Sprite mSprite;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* INCLUDE_AIRCRAFT_HPP_ */
