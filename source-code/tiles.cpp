#include "tiles.hpp"

    sf::Image m_imageTiles;

    /**
     * constructeur
     * @access public
     * @return void
    */
    Tiles::Tiles()
    {
        if (!m_imageTiles.LoadFromFile(SPRITE_TILES)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR]: [Tiles::Tiles] : impossible de charger le sprite tiles"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_imageTiles.SetSmooth(false);
            m_sprite.SetImage(m_imageTiles);
        }

        m_life = 125;
        m_lastAttackTime = 0;
    }

    /**
     * construit le tile
     * @param bool collision : true ou false : le sprite peut-etre traverse ou non
     * @param int id : position du sprite sur l'image
     * @param PositionItem position : position du sprite a l'ecran
     * @access public
     * @return void
    */
    void Tiles::initTile(const bool collision, const int id, const PositionItem position)
    {
        m_sprite.SetCenter(WIDTH_SPRITE/2,WIDTH_SPRITE/2);
        m_sprite.SetRotation(position.rotate);
        m_collision = collision;
        m_id = id;
        m_positionTiles = position;

        m_sprite.SetSubRect(sf::IntRect(WIDTH_SPRITE*id, 0, WIDTH_SPRITE*(1+id), WIDTH_SPRITE));
        m_sprite.SetPosition(sf::Vector2f(m_positionTiles.x , m_positionTiles.y )); // Positionnement
        //std::cout<<"[INFORMATION]: [Tiles::Tiles] : creation d'une tile / type : " << id << "/ x :" << m_positionTiles.x << " /y : " << m_positionTiles.y <<std::endl;
    }

    /**
     * positionne le sprite a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Tiles::display(sf::RenderWindow &window, float deltaTime)
    {
        m_executionTime += (deltaTime*1000);
        window.Draw(m_sprite);
    }

    /**
     * ajoute des degats, ce qui fait diminuer la vie du bloc
     * @param int degats : nombre de degats a infliger
     * @access public
     * @return void
    */
    void Tiles::prendreDegat(const int degat, float deltaTime, int timeBetweenAttack)
    {
        if(m_executionTime - (m_lastAttackTime + (deltaTime*1000)) > timeBetweenAttack)
        {
            m_life -= degat;
            m_lastAttackTime = m_executionTime;

            if(m_life < 0)
            {
                m_life = 0;
            }
        }
    }

    /**
     * retourne si le sprite peut-être traverse ou non
     * @access public
     * @return bool
    */
    bool Tiles::getCollision()
    {
        return m_collision;
    }

    /**
     * retourne le reste de vie du bloc
     * @access public
     * @return int
    */
    int Tiles::getLife()
    {
        return m_life;
    }

    /**
     * retourne la position du sprite
     * @access public
     * @return PositionItem
    */
    PositionItem Tiles::getPosition()
    {
        return m_positionTiles;
    }

    /**
     * retourne l'id du bloc
     * @access public
     * @return int
    */
    int Tiles::getId()
    {
        return m_id;
    }

    Tiles::~Tiles()
    {
    }
