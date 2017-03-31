#include "object_malus.hpp"

    sf::Image m_imageObjectMalus;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Object_Malus::Object_Malus()
    {
        if (!m_imageObjectMalus.LoadFromFile(SPRITE_MALUS)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Object_Malus::Object_Malus] : impossible de charger le sprite malus"<<std::endl;
        }

        m_sprite.SetCenter(WIDTH_OBJECT_X/2, WIDTH_OBJECT_Y/2);
        m_sprite.SetImage(m_imageObjectMalus);
    }

    /**
	 * affiche le bonus a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Object_Malus::display(sf::RenderWindow &window)
    {
        m_sprite.SetPosition(sf::Vector2f(m_positionObject.x, m_positionObject.y)); // Positionnement
        m_sprite.SetRotation(m_positionObject.rotate);
        m_sprite.SetScale(0.85,0.85);
        window.Draw(m_sprite);
    }

    /**
	 * defini le type du bonus
	 * @param int type : type du bonus
	 * @access public
	 * @return void
    */
    void Object_Malus::setType(int type)
    {
        m_type = type;

        switch(m_type)
        {
            case BONUS_SPEED :
               m_sprite.SetSubRect(sf::IntRect(0, 0, WIDTH_OBJECT_X, WIDTH_OBJECT_Y));
            break;

            case BONUS_LIFE :
                m_sprite.SetSubRect(sf::IntRect(0, WIDTH_OBJECT_Y, WIDTH_OBJECT_X, WIDTH_OBJECT_Y*2));
            break;

            case BONUS_AMMUNITION :
                //fait lorsque l'on indique l'id de l'arme
            break;
        }
    }

    /**
	 * defini la valeur du bonus
	 * @param int value : valeur que donnera le bonus
	 * @access public
	 * @return void
    */
    void Object_Malus::setValue(int value)
    {
        m_value = value;
    }

    /**
	 * defini l'arme sur laquelle peut s'appliquer le bonus
	 * @param int id : id de l'arme dans le cas ou le bonus concerne une arme
	 * @access public
	 * @return void
    */
    void Object_Malus::setArmeId(int id)
    {
        m_armeMalus = id;

        switch(m_type)
        {
            case BONUS_AMMUNITION :
                m_sprite.SetSubRect(sf::IntRect(WIDTH_OBJECT_X*(m_armeMalus-1), WIDTH_OBJECT_Y*2, WIDTH_OBJECT_X*(m_armeMalus), WIDTH_OBJECT_Y*3));
            break;
        }
    }

    /**
	 * retourne le type du bonus
	 * @access public
	 * @return int
    */
    int Object_Malus::getType()
    {
        return m_type;
    }

    /**
	 * retourne la valeur du bonus
	 * @access public
	 * @return int
    */
    int Object_Malus::getValue()
    {
        return m_value;
    }

    /**
	 * retourne l'id de l'arme qui peut-etre concernee
	 * @access public
	 * @return int
    */
    int Object_Malus::getArmeId()
    {
        return m_armeMalus;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Object_Malus::~Object_Malus()
    {

    }
