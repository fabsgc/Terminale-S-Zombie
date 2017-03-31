#include "object_bonus.hpp"

    sf::Image m_imageObjectBonus;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Object_Bonus::Object_Bonus()
    {
        if (!m_imageObjectBonus.LoadFromFile(SPRITE_BONUS)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Object_Bonus::Object_Bonus] : impossible de charger le sprite bonus"<<std::endl;
        }

        m_sprite.SetCenter(WIDTH_OBJECT_X/2, WIDTH_OBJECT_Y/2);
        m_sprite.SetImage(m_imageObjectBonus);
    }

    /**
	 * affiche le bonus a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Object_Bonus::display(sf::RenderWindow &window)
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
    void Object_Bonus::setType(int type)
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
    void Object_Bonus::setValue(int value)
    {
        m_value = value;
    }

    /**
	 * defini l'arme sur laquelle peut s'appliquer le bonus
	 * @param int id : id de l'arme dans le cas ou le bonus concerne une arme
	 * @access public
	 * @return void
    */
    void Object_Bonus::setArmeId(int id)
    {
        m_armeBonus = id;

        switch(m_type)
        {
            case BONUS_AMMUNITION :
                m_sprite.SetSubRect(sf::IntRect(WIDTH_OBJECT_X*(m_armeBonus-1), WIDTH_OBJECT_Y*2, WIDTH_OBJECT_X*(m_armeBonus), WIDTH_OBJECT_Y*3));
            break;
        }
    }

    /**
	 * retourne le type du bonus
	 * @access public
	 * @return int
    */
    int Object_Bonus::getType()
    {
        return m_type;
    }

    /**
	 * retourne la valeur du bonus
	 * @access public
	 * @return int
    */
    int Object_Bonus::getValue()
    {
        return m_value;
    }

    /**
	 * retourne l'id de l'arme qui peut-etre concernee
	 * @access public
	 * @return int
    */
    int Object_Bonus::getArmeId()
    {
        return m_armeBonus;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Object_Bonus::~Object_Bonus()
    {

    }
