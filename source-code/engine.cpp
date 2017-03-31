#include "engine.hpp"

    /**
	 * constructeur
	 * @param int width : taille de la fenêtre affichée
	 * @param int height : largeur de la fenêtre affichée
	 * @access public
	 * @return void
    */
    Engine::Engine(int width, int height) : m_game(width, height), m_menu(width, height)
    {
        actionCurrent = MENU;

        m_executionTime = 0;
        m_lastGameOverTime = 0;
        m_lastWinTime = 0;
    }

    /**
	 * lance l'application à chaque tour de la boucle principale du main
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return void
    */
    void Engine::run(sf::RenderWindow &window, float deltaTime)
    {
        m_executionTime += deltaTime*1000;

        switch(actionCurrent)
        {
            case MENU :
                m_menu.initMenu(window, MENU);
                actionCurrent = m_menu.playMenu(window, deltaTime);
            break;

            case NEWGAME :
                m_game.initGame(window, NEWGAME);
                actionCurrent = m_game.playGame(window, deltaTime);

                m_lastGameOverTime = 0;
                m_lastWinTime = 0;
            break;

            case LOADGAME :
                m_game.initGame(window, LOADGAME);
                actionCurrent = m_game.playGame(window, deltaTime);

                m_lastGameOverTime = 0;
                m_lastWinTime = 0;
            break;

            case GAMEOVER :
                m_game.displayLose(window);

                m_lastGameOverTime += deltaTime*1000;

                if(m_lastGameOverTime > TIME_BETWEEN_WIN_GAMEOVER)
                {
                    m_game.setAlreadyInit(false);
                    m_game.initGame(window, LOADGAME);
                    m_lastGameOverTime = 0;
                    actionCurrent = m_game.playGame(window, deltaTime);
                }
            break;

            case WIN :
                m_game.displayWin(window);

                m_lastWinTime += deltaTime*1000;

                if(m_lastWinTime > TIME_BETWEEN_WIN_GAMEOVER)
                {
                    m_game.setAlreadyInit(false);
                    m_lastWinTime = 0;
                    actionCurrent = MENU;
                }
            break;

            case PAUSE :
                actionCurrent = m_game.playPause(window, deltaTime);
            break;

            case SAVE :
                actionCurrent = m_game.save();
            break;
        }
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Engine::~Engine()
    {
    }
