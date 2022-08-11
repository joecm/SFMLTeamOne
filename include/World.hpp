/*
 * World.hpp
 *
 *  Created on: 5 jun 2022
 *      Author: joe
 */

#ifndef INCLUDE_WORLD_HPP_
#define INCLUDE_WORLD_HPP_

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
//#include <SFML/Graphics/RenderWindow.hpp>

#include "../include/ResourceHolder.hpp"
#include "../include/SceneNode.hpp"
#include "../include/Aircraft.hpp"
#include "../include/SpriteNode.hpp"

#include <array>
#include <queue>

#include "../include/Command.hpp"
#include "../include/CommandQueue.hpp"

// Forward declaration
namespace sf {
	class RenderWindow;
}

class World : private sf::NonCopyable {
public:
	explicit World(sf::RenderWindow& window);
	~World();
	void update(sf::Time);
	void draw();

	CommandQueue& getCommandQueue();

private:
	void loadTextures();
	void buildScene();
	void adaptPlayerPosition();
	void adaptPlayerVelocity();
	//enum class Layer
	//Lo dejo como enum plain porque LayerCount pretende ser el número de elementos
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};
	// Rendering Data
	sf::RenderWindow& mWindow; // render window
	sf::View mWorldView; // current view
	TextureHolder mTextures; // TextureHolder

	SceneNode mSceneGraph; // Grafo de Escena - Nodo Root
	std::array<SceneNode*, LayerCount> mSceneLayers;

	// Logical Data
	sf::FloatRect mWorldBounds;
	sf::Vector2f mSpawnPosiiton;
	float mScrollSpeed;
	Aircraft* mPlayerAircraft;

	CommandQueue mCommandQueue;
};

#endif /* INCLUDE_WORLD_HPP_ */
