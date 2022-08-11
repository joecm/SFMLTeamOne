#include "../include/Application.hpp"
#include "../include/StateIdentifiers"
#include "../include/TitleState.hpp"
#include "../include/MenuState.hpp"
#include "../include/PauseState.hpp"
#include "../include/GameState.hpp"
#include "../include/LoadingState.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);


Application::Application() : mWindow(sf::VideoMode(640, 480), "TeamOne Gamestates", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{
    // mStateStack(Context(mWindow, mTextures, mFonts, mPlayer));
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::Main, "Media/Sansation.ttf");
	mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);
    registerStates();
	// Empezamos con la pantalla de título
	mStateStack.pushState(ID::Title);
}

Application::~Application() 
{

}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate> TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);
            
            // Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
        }
        updateStatistics(dt);
		render();
    }
    
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);
        if (event.type == sf::Event::Closed)
			mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);   
}

void Application::render()
{
    // TODO 
    mWindow.clear();
    
    mStateStack.draw();
    mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);
	
    mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames +=1 ;

    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(ID::Title);
    mStateStack.registerState<MenuState>(ID::Menu);
	mStateStack.registerState<GameState>(ID::Game);
	mStateStack.registerState<PauseState>(ID::Pause);
    mStateStack.registerState<LoadingState>(ID::Loading);
}



