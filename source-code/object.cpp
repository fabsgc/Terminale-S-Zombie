#include "object.hpp"

    sf::Image m_imageObject;

    Object::Object()
    {
        m_sprite.SetCenter(WIDTH_OBJECT_X/2,WIDTH_OBJECT_Y/2);

        if (!m_imageObject.LoadFromFile(SPRITE_OBJECT)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Object::Object] : impossible de charger ls sprite"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_sprite.SetImage(m_imageObject);
        }
    }

    /**
	 * affiche l'objet a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Object::display(sf::RenderWindow &window)
    {
        m_sprite.SetPosition(sf::Vector2f(m_positionObject.x, m_positionObject.y)); // Positionnement
        m_sprite.SetRotation(m_positionObject.rotate);
        window.Draw(m_sprite);
    }

    /**
	 * specifie l'id de l'objet
	 * @param int id : id de l'objet
	 * @access public
	 * @return void
    */
    void Object::setId(int id)
    {
        m_id = id;
    }

    /**
	 * specifie l'id de l'objet
	 * @param int id : id de l'objet
	 * @access public
	 * @return void
    */
    void Object::setSprite(std::string sprite)
    {
        if (!m_imageObject.LoadFromFile(sprite)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Object::setSprite] : impossible de charger le sprite"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_sprite.SetImage(m_imageObject);
        }
    }

    /**
	 * specifie la position de l'objet
	 * @param PositionItem position : position de l'objet
	 * @access public
	 * @return void
    */
    void Object::setPosition(PositionItem position)
    {
        m_positionObject = position;
    }

    /**
	 * retourne l'id de l'objet
	 * @access public
	 * @return int
    */
    int Object::getId()
    {
        return m_id;
    }

    /**
	 * retourne le sprite de l'objet
	 * @access public
	 * @return sf::Sprite
    */
    sf::Sprite Object::getSprite()
    {
        return m_sprite;
    }

    /**
	 * retourne la position de l'objet
	 * @access public
	 * @return PositionItem
    */
    PositionItem Object::getPosition()
    {
        return m_positionObject;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Object::~Object()
    {

    }
