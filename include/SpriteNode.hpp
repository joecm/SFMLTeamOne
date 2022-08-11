/*
 * SpriteNode.hpp
 *
 *  Created on: 5 jun 2022
 *      Author: joe
 */

#ifndef INCLUDE_SPRITENODE_HPP_
#define INCLUDE_SPRITENODE_HPP_

#include "SceneNode.hpp"

#include <SFML/Graphics/Sprite.hpp>

class SpriteNode : public SceneNode {
	public:
		explicit SpriteNode(const sf::Texture& texture);
		SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);
		virtual ~SpriteNode();


	private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		sf::Sprite mSprite;
};

#endif /* INCLUDE_SPRITENODE_HPP_ */
