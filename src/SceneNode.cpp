/*
 * SceneNode.cpp
 *
 *  Created on: 4 jun 2022
 *      Author: joe
 */

#include "../include/SceneNode.hpp"
#include <cassert>
#include <algorithm>
#include "../include/Command.hpp"

SceneNode::SceneNode() : mChildren(), mParent{nullptr} {

}

SceneNode::~SceneNode() {

}

void SceneNode::attachChild(Ptr child) {
	child->mParent=this;
	mChildren.push_back(child);
}

// ¡ojo que Ptr es un typedef dentro de una class y hay que indicar el ambito
SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
	// Pág. 528 STL devuelve iterador a la posición del primer elemento en el rango del predicado
	// std::vector<Ptr>::iterator found es un iterador a un shared_pointer que apunta a un nodo de escena
	auto found = std::find_if(mChildren.begin(), mChildren.end(),\
			[&] (std::shared_ptr<SceneNode>& p) -> bool { return p.get() == &node; });
	// la función lambda recibe como parametro por referencia el shared_ptr p de cada elemento que recorre
	// y comprueba si su dirección es la misma que el node, el nodo pasado
	assert(found != mChildren.end());

	Ptr result = *found;
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt) {
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// Apply transform of current node, encadena 2 transformaciones
	// las del padre y la del nodo actual utilizando la sobrecarga
	// del operador * ver clase Transform.
	states.transform *= getTransform();
	// Ahora states.transform contiene las tranformaciones ABSOLUTAS del WORLD
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {

}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const {
	for (const std::shared_ptr<SceneNode>& child : mChildren) {
		child->draw(target, states);
	}

}

void SceneNode::updateCurrent(sf::Time)
{
	// Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
	for(Ptr& child: mChildren)
		child->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const {
	// subimos en la jerarquía para acumular transformaciones hasta el nodo root
	sf::Transform transform = sf::Transform::Identity; // matriz identidad
	for (const SceneNode* node =this; node != nullptr; node=node->mParent) {
		transform=node->getTransform()*transform;
	}
	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
	// necesitamos una posición, un punto. Se transforma empleando la sobrecarga
	// del operador unario * en la clase  Transform ver clases Transformable para ver
	// lo que devuelve el miembro getTransform() y cómo una transformaciónla convertimnos a
	// un punto multiplicandopor un vector
	return getWorldTransform() * sf::Vector2f();
	// la siguiente expresión es equivalente
	// return getWorldTransform().transformPoint(sf::Vector2f());
}

unsigned int SceneNode::getCategory() const {
	return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time dt) {

	if (command.category & getCategory())
		command.action(*this, dt);

	for (Ptr& child : mChildren)
		child->onCommand(command, dt);

}
