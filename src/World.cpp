/*
 * World.cpp
 *
 *  Created on: 5 jun 2022
 *      Author: joe
 */

#include "../include/World.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
// #include <algorithm>

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosiiton(mWorldView.getSize().x/2, mWorldBounds.height - mWorldView.getSize().y/2)
, mScrollSpeed(-50.f)
, mPlayerAircraft(nullptr)
{
	loadTextures(); // cargamos texturas
	buildScene(); // construimos la escena

	// Center The view
	mWorldView.setCenter(mSpawnPosiiton);
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::loadTextures()
{
	mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
}

void World::buildScene() {
	for (std::size_t i=0; i<LayerCount; ++i) { // creamos 2 SceneLayers
		SceneNode::Ptr layer = std::make_shared<SceneNode>();
		mSceneLayers[i] = layer.get(); // añadimos al array de SceneLayers puntero crudo
		mSceneGraph.attachChild(layer); // adjuntamos al nodoo root cada SceneLayers
	}
	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the backgorund sprite to the scene
	std::shared_ptr<SpriteNode> backgroundSprite = std::make_shared<SpriteNode>(texture, textureRect);
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(backgroundSprite); // a la capa mScenelayer[0]

	// Add player's aircraft
	std::shared_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::Eagle, mTextures));
	mPlayerAircraft = leader.get(); // puntero crudo
	mPlayerAircraft->setPosition(mSpawnPosiiton);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(leader);

	/*
	// Add two escorting aircrafts, placed relatively to the main plane
	std::shared_ptr<Aircraft> leftEscort = std::make_shared<Aircraft>(Aircraft::Type::Raptor, mTextures);
	leftEscort->setPosition(-80.f, 50.f); // posición relativa al leader.
	mPlayerAircraft->attachChild(leftEscort);

	std::shared_ptr<Aircraft> rightEscort = std::make_shared<Aircraft>(Aircraft::Type::Raptor, mTextures);
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(rightEscort);
	*/
}

void World::update(sf::Time dt)
{
	// Scroll the world
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	mPlayerAircraft->setVelocity(0.f, 0.f);

	// Forward commands to scene graph, adapt velocity (scrolling, diagonal correction)
	while (!mCommandQueue.isEmpty())
			mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	adaptPlayerVelocity();
	// Apply movements
	mSceneGraph.update(dt);
	adaptPlayerPosition();
}

void World::draw()
{
	// establecemos la vista
	mWindow.setView(mWorldView);
	// delegamos el dibujo al scene graph
	mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// If moving diagonally, reduce velocity (to have always same velocity)
	if (velocity.x != 0.f && velocity.y != 0.f)
		mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

	// Add scrolling velocity
	mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}

