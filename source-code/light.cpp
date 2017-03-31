#include "light.hpp"

    sf::Image m_imageLight;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Light::Light()
    {
        if (!m_imageLight.LoadFromFile(SPRITE_LIGHTS)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Light::Light] : impossible de charger le sprite lights"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_sprite.SetImage(m_imageLight);
            std::cout<<"[INFORMATION] : [Light::Light] : creation d'une lampe"<<std::endl;
        }
    }

    /**
	 * affiche une lumiere
	 * @access public
	 * @return void
    */
    void Light::display(sf::RenderWindow &window)
    {
        m_sprite.SetPosition(sf::Vector2f(m_positionLight.x , m_positionLight.y)); // Positionnement
        m_sprite.SetRotation(m_positionLight.rotate); // Positionnement
        window.Draw(m_sprite);
    }

    /**
	 * modifie l'id de la lumière
	 * @param int id : id de la lumiere
	 * @access public
	 * @return void
    */
    void Light::setId(int id)
    {
        m_id =id;
        m_sprite.SetSubRect(sf::IntRect(WIDTH_LIGHT*m_id, 0, WIDTH_LIGHT*(1+m_id), WIDTH_LIGHT));
        m_sprite.SetCenter((WIDTH_LIGHT/2)+32, (WIDTH_LIGHT/2)-32);
    }

    /**
	 * modifie la position de la lumiere
	 * @param PositionItem position : position
	 * @access public
	 * @return void
    */
    void Light::setPosition(PositionItem position)
    {
        m_positionLight = position;
    }

    /**
	 * retourne l'id de la lumiere
	 * @access public
	 * @return int
    */
    int Light::getId()
    {
        return m_id;
    }

    /**
	 * retourne la position de la lumiere
	 * @access public
	 * @return PositionItem
    */
    PositionItem Light::getPosition()
    {
        return m_positionLight;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Light::~Light()
    {
    }
