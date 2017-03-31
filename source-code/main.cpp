#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "include.hpp"
#include "engine.hpp"

int main()
{
    float width = getScreen();
    float height = getScreen() * ((float)sf::VideoMode::GetDesktopMode().Height/(float)sf::VideoMode::GetDesktopMode().Width);
    float deltaTime;

    //sf::RenderWindow window(sf::VideoMode(width, height, 32), "Zombie MC", sf::Style::Close);
    sf::RenderWindow window(sf::VideoMode(width, height, 32), "Zombie MC", sf::Style::Fullscreen);
    sf::Clock Clock;
    Engine engine(width, height);

    window.SetFramerateLimit(FPS);
    window.UseVerticalSync(true);
    MusicManager::playMusic("sounds/musique.ogg", 40.f, true);

    std::cout << "[INFORMATION] : [main] hauteur : " << width << std::endl;
    std::cout << "[INFORMATION] : [main] largeur : " << height << std::endl;
    std::cout << "[INFORMATION] : [main] initiation de \"Engine\"" << std::endl;
    std::cout << "[INFORMATION] : [main] framerate limite a " << FPS << " fps" << std::endl;
    std::cout << "[INFORMATION] : [main] synchronisation verticale activee" << std::endl;

    while (window.IsOpened())
    {
        sf::Event event;
        deltaTime = Clock.GetElapsedTime();

        while(window.GetEvent(event))
        {
            if(event.Type == sf::Event::Closed)
            {
                window.Close();
            }
        }

        window.Clear(sf::Color(5,10,20));
        engine.run(window, deltaTime);
        Clock.Reset();
        window.Display();
    }

    return EXIT_SUCCESS;
}
