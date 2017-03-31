#include "object_door.hpp"

    sf::Image m_imageObjectDoor;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Object_Door::Object_Door() : Object()
    {
        std::cout<<"[INFORMATION] : [Object_Door::Object_Door] : creation d'une porte"<<std::endl;
        m_open = false;
        m_changeLevel = false;
        m_win = false;
    }

    /**
	 * affiche la porte a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Object_Door::display(sf::RenderWindow &window)
    {
        m_sprite.SetPosition(sf::Vector2f(m_positionObject.x, m_positionObject.y)); // Positionnement
        m_sprite.SetRotation(m_positionObject.rotate);
        window.Draw(m_sprite);
    }

    /**
	 * initialise le bon sprite de la porte en question
	 * @param int id : numero du sprite
	 * @access public
	 * @return void
    */
    void Object_Door::setSprite(int id)
    {
        m_spriteId = id;
        m_sprite.SetCenter(WIDTH_OBJECT_DOOR_X/2, WIDTH_OBJECT_DOOR_Y/2);

        if (!m_imageObjectDoor.LoadFromFile(SPRITE_OBJECT_DOOR)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Object_Door::setSprite] : impossible de charger le sprite doors"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_sprite.SetImage(m_imageObjectDoor);

            if(m_open == false) //porte fermée
            {
                m_sprite.SetSubRect(sf::IntRect(WIDTH_OBJECT_DOOR_X*(m_spriteId-1), 0, WIDTH_OBJECT_DOOR_X*(m_spriteId), WIDTH_OBJECT_DOOR_Y));
            }
            else //porte ouverte
            {
                m_sprite.SetSubRect(sf::IntRect(WIDTH_OBJECT_DOOR_X*(m_spriteId-1), WIDTH_OBJECT_DOOR_Y, WIDTH_OBJECT_DOOR_X*(m_spriteId), WIDTH_OBJECT_DOOR_Y*2));
            }
        }
    }

    /**
	 * spécifie si la porte est fermee ou ouverte
	 * @param bool open : porte fermee ou ouverte
	 * @param bool first : permet de savoir si on initialise ou si on modifie l'etat de la porte (pour le son)
	 * @access public
	 * @return void
    */
    void Object_Door::setOpen(bool open)
    {
        m_open = open;
        this->setSprite(m_spriteId); //on met à jour le sprite de la porte
    }

    /**
	 * spécifie si passer par la porte fait changer de niveau
	 * @param bool changeLevel
	 * @access public
	 * @return void
    */
    void Object_Door::setChangeLevel(bool changeLevel)
    {
        m_changeLevel = changeLevel;
    }

    /**
	 * spécifie si passer par la porte fait gagner
	 * @param bool changeLevel
	 * @access public
	 * @return void
    */
    void Object_Door::setWin(bool win)
    {
        m_win = win;
    }

    /**
	 * retourne si la porte est ouverte ou non
	 * @param bool open : porte fermee ou ouverte
	 * @access public
	 * @return void
    */
    bool Object_Door::getOpen()
    {
        return m_open;
    }

    /**
	 * retourne si passer par la porte fait changer de niveau
	 * @access public
	 * @return bool
    */
    bool Object_Door::getChangeLevel()
    {
        return m_changeLevel;
    }

    /**
	 * retourne si passer par la porte fait gagner
	 * @access public
	 * @return bool
    */
    bool Object_Door::getWin()
    {
        return m_win;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Object_Door::~Object_Door()
    {

    }
