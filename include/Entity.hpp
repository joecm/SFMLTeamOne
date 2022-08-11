/*
 * Entity.hpp
 *
 *  Created on: 4 jun 2022
 *      Author: joe
 */

#ifndef INCLUDE_ENTITY_HPP_
#define INCLUDE_ENTITY_HPP_

#include "SceneNode.hpp"

class Entity : public SceneNode
{
	public:
		void setVelocity(sf::Vector2f velocity);
		void setVelocity(float vx, float vy);
		void accelerate(sf::Vector2f velocity);
		void accelerate(float vx, float vy);
		sf::Vector2f getVelocity() const;
		virtual ~Entity();


	private:
		sf::Vector2f mVelocity;
		virtual void updateCurrent(sf::Time dt) override;
};



#endif /* INCLUDE_ENTITY_HPP_ */
