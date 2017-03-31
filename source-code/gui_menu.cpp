#include "gui_menu.hpp"

    sf::Image m_imageGui_menu;

    /**
     * constructeur
     * @access public
     * @return void
    */
    Gui_menu::Gui_menu()
    {
        if(!m_font.LoadFromFile(FONT_GUI_MENU))
        {
            std::cout<<"[ERREUR]: [Gui_menu::Gui_menu] : impossible de charger la police " << FONT_GUI_MENU <<std::endl;
        }

        if (!m_imageGui_menu.LoadFromFile(SPRITE_MENU)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR]: [Gui_menu::Gui_menu] : impossible de charger le sprite menu"<<std::endl;
        }
    }

    /**
	 * donne la taille et la hauteur de la fenetre : utile pour les messages
	 * @param int width : largeur
	 * @param int height : hauteur
	 * @access public
	 * @return void
    */
    void Gui_menu::setWidthHeight(int width, int height)
    {
        m_width = width;
        m_height = height;
    }

    /**
	 * affiche les menus a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Gui_menu::display(sf::RenderWindow &window)
    {
        for(std::list<GuiMenuItem>::iterator it_menu = m_guiMenusItem.begin(); it_menu!=m_guiMenusItem.end(); ++it_menu)
        {
            it_menu->sprite.SetPosition(sf::Vector2f(it_menu->position.x, it_menu->position.y)); // Positionnement
            it_menu->sprite.SetRotation(0);
            window.Draw((it_menu->sprite));

            m_textMenu.SetFont(m_font); // Fonte
            m_textMenu.SetSize(25); // Taille de police

            m_textMenu.SetText(it_menu->message); // Texte
            m_textMenu.SetPosition(sf::Vector2f(it_menu->position.x + it_menu->decalageLeftMessage, it_menu->position.y + 27)); // Positionnement
            window.Draw(m_textMenu);
        }
    }

    /**
	 * ajoute un nouveau menu
	 * @param int id : id du menu, utile pour getClic
	 * @param float deltaTime : temps entre 2 frame
	 * @param Player * player : pointeur vers le joueur
	 * @param int decalageLeftMessage : decalage en pixel a gauche pour centrer
	 * @access public
	 * @return void
    */
    void Gui_menu::addMenu(int id, PositionItem position, std::string message, int decalageLeftMessage)
    {
        m_guiMenuItem.id = id;
        m_guiMenuItem.position = position;
        m_guiMenuItem.message = message;
        m_guiMenuItem.decalageLeftMessage = decalageLeftMessage;
        m_guiMenuItem.sprite.SetImage(m_imageGui_menu);

        m_guiMenusItem.push_back(m_guiMenuItem);
    }

    /**
	 * detecte sur quelles boutons le joueur a clique, 0 pour rien
	 * @param int x : position x du clic
	 * @param int y : position y du clic
	 * @access public
	 * @return int
    */
    int Gui_menu::getClic(int x, int y)
    {
        for(std::list<GuiMenuItem>::iterator it_menu = m_guiMenusItem.begin(); it_menu!=m_guiMenusItem.end(); ++it_menu)
        {
            if(x >= it_menu->position.x && x <= it_menu->position.x + WIDTH_MENU_X && y >= it_menu->position.y && y <= it_menu->position.y + WIDTH_MENU_Y)
            {
                m_sound.playSound(1, 50.f, false, it_menu->position, 512, 5, true);
                return it_menu->id;
            }
        }

        return 0;
    }

    /**
     * desctructeur
     * @access public
     * @return void
    */
    Gui_menu::~Gui_menu()
    {

    }
