#include "object_teleportation.hpp"

    sf::Image m_imageObjectTeleportation;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Object_Teleportation::Object_Teleportation() : Object()
    {
        if (!m_imageObjectTeleportation.LoadFromFile(SPRITE_OBJECT_TELEPORTATION)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Object_Bonus::Object_Bonus] : impossible de charger le sprite teleportation"<<std::endl;
        }
        else
        {
            m_sprite.SetCenter(WIDTH_OBJECT_TELEPORTATION_X/2, WIDTH_OBJECT_TELEPORTATION_Y/2);
            m_sprite.SetImage(m_imageObjectTeleportation);

            std::cout<<"[INFORMATION] : [Object_Teleportation::Object_Teleportation] : creation d'un teleporteur"<<std::endl;
        }
    }

    /**
	 * affiche la porte a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Object_Teleportation::display(sf::RenderWindow &window)
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
    void Object_Teleportation::setSprite(int id)
    {
        m_spriteId = id;
        m_sprite.SetCenter(WIDTH_OBJECT_TELEPORTATION_X/2, WIDTH_OBJECT_TELEPORTATION_Y/2);

        if (!m_imageObjectTeleportation.LoadFromFile(SPRITE_OBJECT_TELEPORTATION)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Object_Teleportation::setSprite] : impossible de charger le sprite teleportation"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_sprite.SetImage(m_imageObjectTeleportation);
            m_sprite.SetSubRect(sf::IntRect(WIDTH_OBJECT_TELEPORTATION_X*(m_spriteId-1), 0, WIDTH_OBJECT_TELEPORTATION_X*(m_spriteId), WIDTH_OBJECT_TELEPORTATION_Y));
        }
    }

    void Object_Teleportation::setPositionTo(PositionItem positionTo)
    {
        m_positionTo = positionTo;
    }

    PositionItem Object_Teleportation::getPositionTo()
    {
        return m_positionTo;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Object_Teleportation::~Object_Teleportation()
    {

    }
