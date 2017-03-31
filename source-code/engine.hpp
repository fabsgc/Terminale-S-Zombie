#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include "include.hpp"
#include "game.hpp"
#include "menu.hpp"

    class Engine
    {
        public:
            Engine(int width, int height);
            ~Engine();
            void run(sf::RenderWindow &window, float deltaTime);

        private:
            long m_executionTime;
            long m_lastGameOverTime;
            long m_lastWinTime;
            int actionCurrent; //action en cours : MENU, NEWGAME, LOADGAME
            Game m_game; //instance de la class gérant une partie
            Menu m_menu; //instance de la classe gérant le menu
    };

#endif // ENGINE_HPP_INCLUDED
