#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

namespace sf {
    class Sprite;
    class Text;
}

// Función sobrecargada
void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

/*
template <typename Res>
void center(Res) {
   sf::FloatRect bounds = Res.getLocalBounds();
   Res.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f)); 
};
*/

#endif // __UTILITY_HPP__