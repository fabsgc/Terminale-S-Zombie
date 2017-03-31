#include "menu.hpp"

    /**
	 * constructeur
	 * @param int width : taille de la fenêtre affichée
	 * @param int height : largeur de la fenêtre affichée
	 * @access public
	 * @return void
    */
    Menu::Menu(int width, int height)
    {
        if (!m_imageLogo.LoadFromFile(SPRITE_LOGO)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Menu::Menu] : impossible de charger le sprite logo"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_imageLogo.SetSmooth(false);
            m_spriteLogo.SetImage(m_imageLogo);
        }

        m_spriteLogo.SetCenter(160, 0);
        m_spriteLogo.SetPosition(sf::Vector2f(width/2 , 0)); // Positionnement

        m_alreadyInit = false;
        m_width = width;
        m_height = height;
    }

    /**
	 * initialisation du menu principal
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param int actionCurrent : action en cours : MENU
	 * @access public
	 * @return void
    */
    void Menu::initMenu(sf::RenderWindow &window, int actionCurrent)
    {
        if(m_alreadyInit == false)
        {
            m_actionCurrent = actionCurrent;
            m_alreadyInit = true;

            m_position.x = m_width/2 - WIDTH_MENU_X/2;
            m_position.y = m_height/2 - WIDTH_MENU_Y/2 - 100;
            m_guiMenu.addMenu(MENU_NEW_GAME, m_position, "Nouvelle partie", 24);

            m_position.x = m_width/2 - WIDTH_MENU_X/2;
            m_position.y = m_height/2 - WIDTH_MENU_Y/2;
            m_guiMenu.addMenu(MENU_LOAD_GAME, m_position, "Charger la partie", 18);

            m_position.x = m_width/2 - WIDTH_MENU_X/2;
            m_position.y = m_height/2 - WIDTH_MENU_Y/2 + 100;
            m_guiMenu.addMenu(MENU_QUIT, m_position, "Quitter", 68);
        }
    }

    /**
	 * fonction gérant le menu
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return int action
    */
    int Menu::playMenu(sf::RenderWindow &window, float deltaTime)
    {
        const sf::Input& Input = window.GetInput();

        view.SetCenter(m_width/2, m_height/2);
        window.Draw(m_spriteLogo);
        m_guiMenu.display(window);

        if(Input.IsMouseButtonDown(sf::Mouse::Left))
        {
            sf::Sleep(0.2);
            m_buttonClicked = m_guiMenu.getClic(Input.GetMouseX(), Input.GetMouseY());

            switch(m_buttonClicked)
            {
                case MENU_NEW_GAME :
                    m_actionCurrent = NEWGAME;
                break;

                case MENU_LOAD_GAME :
                    m_actionCurrent = LOADGAME;
                break;

                case MENU_QUIT :
                    window.Close();
                break;
            }
        }
        else if(Input.IsKeyDown(sf::Key::Escape)) //aucun mouvement
        {
            window.Close();
        }
        else
        {
            m_actionCurrent = MENU;
        }

        return m_actionCurrent;
    }

    /**
	 * desctructeur
	 * @access public
	 * @return void
    */
    Menu::~Menu()
    {
    }
