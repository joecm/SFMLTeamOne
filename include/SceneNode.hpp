/*
 * SceneNode.hpp
 *
 *  Created on: 4 jun 2022
 *      Author: joe
 */

#ifndef INCLUDE_SCENENODE_HPP_
#define INCLUDE_SCENENODE_HPP_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>


#include <vector>
#include <memory>
#include "../include/Category.hpp"

struct Command;
/* Poniendo esto no hace falta declararlo dentro de la clase y tener
 * que usar el ambito
class SceneNode;
typedef std::shared_ptr<SceneNode> Ptr;
*/
class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
	// typedef std::shared_ptr<SceneNode> Ptr;
	using Ptr = std::shared_ptr<SceneNode>;

	SceneNode();
	virtual ~SceneNode();

	// añadir quitar hijos
	void attachChild(Ptr);
	Ptr	detachChild(const SceneNode& node);

	void update(sf::Time dt); // update alcance a todas las entidades

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

	virtual unsigned int getCategory() const;
	void onCommand(const Command& command, sf::Time dt);

private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;

	// making SceneNodes drawables
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	// Updatin the scene
	virtual void updateCurrent(sf::Time dt); // nodo actual
	void updateChildren(sf::Time dt); // nodos hijo

};

#endif /* INCLUDE_SCENENODE_HPP_ */
