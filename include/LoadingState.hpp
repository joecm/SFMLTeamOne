#ifndef __LOADINGSTATE_HPP__
#define __LOADINGSTATE_HPP__

#include "../include/State.hpp"
#include "../include/ParallelTask.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>



class LoadingState : public State
{
private:
    sf::Text mLoadingText; // string de Cargando Recursos
	sf::RectangleShape mProgressBarBackground; // fonde de barra de progreso
	sf::RectangleShape mProgressBar; // relleno de la barra
	ParallelTask mLoadingTask;
    
public:
    LoadingState(StateStack& stack, Context context);
    virtual ~LoadingState();

    virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
    void setCompletion(float percent);
};




#endif // __LOADINGSTATE_HPP__