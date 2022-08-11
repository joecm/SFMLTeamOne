/*
 * SpriteNode.cpp
 *
 *  Created on: 5 jun 2022
 *      Author: joe
 */

#include "../include/SpriteNode.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

SpriteNode::SpriteNode(const sf::Texture& texture) : mSprite (texture)
{
	// TODO Auto-generated constructor stub

}

SpriteNode::SpriteNode (const sf::Texture& texture, const sf::IntRect& textureRect)
: mSprite(texture, textureRect )
{

}

SpriteNode::~SpriteNode() {
	// TODO Auto-generated destructor stub
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
