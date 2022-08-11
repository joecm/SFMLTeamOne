/*
 * ResourceHolder.hpp
 *
 *  Created on: 4 jun 2022
 *      Author: joe
 */

#ifndef INCLUDE_RESOURCEHOLDER_HPP_
#define INCLUDE_RESOURCEHOLDER_HPP_

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

enum class Textures	{
		Eagle,
		Raptor,
		Desert,
		TitleScreen,
};

enum class Fonts
{
	Main,
};

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;
typedef ResourceHolder<sf::Texture, Textures> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts> FontHolder;


template <typename Resource, typename Identifier>
class ResourceHolder {
public:
	void load(Identifier id, const std::string& filename);

	template <typename Parameter> // sobrecarga que cuble el caso particular de shaders
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

private:
	std::map<Identifier, std::shared_ptr<Resource>>	mResourceMap;
	void insertResource(Identifier id, std::shared_ptr<Resource> resource);
};

// Como es una clase templatizada se ha de definir aquí
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
	std::shared_ptr<Resource> resource = std::make_shared<Resource>();
	if(!resource->loadFromFile(filename))
		throw std::runtime_error("RecourseHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, resource);
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{
	// Create and load resource
	std::shared_ptr<Resource> resource = std::make_shared<Resource>();
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, resource);
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
	auto found = mResourceMap.find(id);
	assert(found!= mResourceMap.end());

	return *found->second;

}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::shared_ptr<Resource> resource) {
	// Insert y check sucess
	auto inserted = mResourceMap.insert({id, resource});
	assert(inserted.second);
}

#endif /* INCLUDE_RESOURCEHOLDER_HPP_ */
