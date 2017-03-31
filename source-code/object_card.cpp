#include "object_card.hpp"

    sf::Image m_imageObjectCard;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Object_Card::Object_Card() : Object()
    {
        std::cout<<"[INFORMATION] : [Object_Card] : creation d'une carte"<<std::endl;
    }

    /**
	 * initialise le bon sprite de la carte en fonction de son id
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Object_Card::setSprite(int id)
    {
        m_sprite.SetCenter(WIDTH_SPRITE/2,WIDTH_SPRITE/2);

        if (!m_imageObjectCard.LoadFromFile(SPRITE_OBJECT_CARD)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Player::Player] : impossible de charger le sprite cards"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_sprite.SetImage(m_imageObjectCard);
            m_sprite.SetSubRect(sf::IntRect(WIDTH_SPRITE*(id-1), 0, WIDTH_SPRITE*(id), WIDTH_SPRITE));
        }
    }

    /**
	 * affiche l'objet a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Object_Card::display(sf::RenderWindow &window)
    {
        m_sprite.SetPosition(sf::Vector2f(m_positionObject.x, m_positionObject.y)); // Positionnement
        m_sprite.SetRotation(30);
        m_sprite.SetScale(0.85,0.85);
        window.Draw(m_sprite);
    }

    /**
	 * desctructeur
	 * @access public
	 * @return void
    */
    Object_Card::~Object_Card()
    {

    }
