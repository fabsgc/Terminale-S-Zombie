#include "gui_message.hpp"

    sf::Image m_imageGui_message;

    /**
     * constructeur
     * @access public
     * @return void
    */
    Gui_message::Gui_message()
    {
        if(!m_font.LoadFromFile(FONT_GUI_MESSAGE))
        {
            std::cout<<"[ERREUR]: [Gui_message::Gui_message] : impossible de charger la police " << FONT_GUI_MESSAGE <<std::endl;
        }

        if (!m_imageGui_message.LoadFromFile(SPRITE_MESSAGE)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR]: [Gui_message::Gui_message] : impossible de charger le sprite message"<<std::endl;
        }
    }

    /**
	 * donne la taille et la hauteur de la fenetre : utile pour les messages
	 * @param int width : largeur
	 * @param int height : hauteur
	 * @access public
	 * @return void
    */
    void Gui_message::setWidthHeight(int width, int height)
    {
        m_width = width;
        m_height = height;
    }

    /**
	 * affiche les messages a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps entre 2 frame
	 * @param Player * player : pointeur vers le joueur
	 * @access public
	 * @return void
    */
    void Gui_message::display(sf::RenderWindow &window, float deltaTime, PositionItem position)
    {
        int i = 0, j = 0; //sert a compter le nombre de messages a afficher

        for(std::list<GuiMessageItem>::iterator it_message = m_guiMessagesItem.begin(); it_message!=m_guiMessagesItem.end(); ++it_message)
        {
            it_message->execution_time += (deltaTime*1000);

            if(it_message->execution_time > it_message->time_max) // on deruit
            {
                //m_guiMessagesItem.erase(it_message++);
            }
            else //on affiche
            {
                if(i * (WIDTH_MESSAGE_X + 10) > m_width - WIDTH_MESSAGE_X)
                {
                    j++;
                    i = 0;
                }

                it_message->position.x = i * (WIDTH_MESSAGE_X + 10) + position.x - m_width/2;
                it_message->position.y = j * (WIDTH_MESSAGE_Y + 10) + position.y - m_height/2;

                it_message->sprite.SetPosition(sf::Vector2f(it_message->position.x, it_message->position.y)); // Positionnement
                it_message->sprite.SetRotation(0);
                window.Draw((it_message->sprite));

                m_textMessage.SetFont(m_font); // Fonte
                m_textMessage.SetSize(16); // Taille de police

                m_textMessage.SetText(it_message->message1); // Texte
                m_textMessage.SetPosition(sf::Vector2f(it_message->position.x + 20, it_message->position.y + 15)); // Positionnement
                window.Draw(m_textMessage);

                m_textMessage.SetText(it_message->message2); // Texte
                m_textMessage.SetPosition(sf::Vector2f(it_message->position.x + 20, it_message->position.y + 34)); // Positionnement
                window.Draw(m_textMessage);

                m_textMessage.SetText(it_message->message3); // Texte
                m_textMessage.SetPosition(sf::Vector2f(it_message->position.x + 20, it_message->position.y + 52)); // Positionnement
                window.Draw(m_textMessage);

                i++;
            }
        }
    }

    /**
	 * ajoute une nouveau message a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps entre 2 frame
	 * @param Player * player : pointeur vers le joueur
	 * @access public
	 * @return void
    */
    void Gui_message::addMessage(int time_max, std::string message1, std::string message2, std::string message3)
    {
        m_guiMessageItem.time_max = time_max;
        m_guiMessageItem.message1 = message1;
        m_guiMessageItem.message2 = message2;
        m_guiMessageItem.message3 = message3;
        m_guiMessageItem.execution_time = 0;
        m_guiMessageItem.sprite.SetImage(m_imageGui_message);
        m_guiMessagesItem.push_back(m_guiMessageItem);
    }

    /**
	 * supprime les messages en cours d'affichage
	 * @access public
	 * @return void
    */
    void Gui_message::deleteMessage()
    {
        m_guiMessagesItem.clear();
    }

    /**
     * desctructeur
     * @access public
     * @return void
    */
    Gui_message::~Gui_message()
    {

    }
