#include "bullet.hpp"

    sf::Image m_imageBullet;
    sf::Sprite m_spriteBullet;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Bullet::Bullet()
    {
        m_exploded = false;
        m_executionTime = 0;
    }

    /**
	 * met a jour la position via les valeurs calculees en cache
	 * @access public
	 * @return void
    */
    void Bullet::updatePosition()
    {
        m_positionBullet.x = m_positionNewBullet.x;
        m_positionBullet.y = m_positionNewBullet.y;
    }

    /**
	 * modifie l'id de la balle qui fait reference a l'arme qui a tire cette balle
	 * @param int id : id de l'arme et de la balle
	 * @access public
	 * @return void
    */
    void Bullet::setId(const int id)
    {
        m_id = id;
    }

    /**
	 * modifie la vitesse de la balle
	 * @param int speed : vitesse
	 * @access public
	 * @return void
    */
    void Bullet::setSpeed(const int speed)
    {
        m_speed = speed;
    }

    /**
	 * modifie la position de la balle
	 * @param int PositionItem position : position
	 * @access public
	 * @return int
    */
    void Bullet::setPosition(const PositionItem position)
    {
        m_positionBullet = position;
        m_positionNewBullet = m_positionBullet;
    }

    /**
	 * specifie si la balle a explose ou non
	 * @param bool exploded : false non, true oui
	 * @access public
	 * @return void
    */
    void Bullet::setExploded(const bool exploded)
    {
        m_exploded = exploded;
    }

    /**
	 * pointeur vers la list contenant les tiles cassables par la balle
	 * @param bool exploded : false non, true oui
	 * @access public
	 * @return void
    */
    void Bullet::setTileBreak(std::list<int> * weaponTileBreak)
    {
        m_weaponTileBreak = weaponTileBreak;
    }

    /**
	 * specifie les degats causes par la balle
	 * @access public
	 * @return int
    */
    void Bullet::setDegat(int degat)
    {
        m_degat = degat;
    }

    /**
	 * modifie l'id de la balle qui fait reference a l'arme qui a tire cette balle
	 * @access public
	 * @return int
    */
    int Bullet::getId() const
    {
        return m_id;
    }

    /**
	 * retourne la vitesse de la balle
	 * @access public
	 * @return int
    */
    int Bullet::getSpeed() const
    {
        return m_speed;
    }

    /**
	 * retourne la position de la balle
	 * @access public
	 * @return PositionItem
    */
    PositionItem Bullet::getPosition() const
    {
        return m_positionBullet;
    }

    /**
	 * retourne la nouvelle position de la balle
	 * @access public
	 * @return PositionItem
    */
    PositionItem Bullet::getNewPosition() const
    {
        return m_positionNewBullet;
    }

    /**
	 * retourne la nouvelle position de la balle
	 * @access public
	 * @return std::list<int> *
    */
    std::list<int> * Bullet::getTileBreak()
    {
        return m_weaponTileBreak;
    }

    /**
	 * retourne les degats causes par la balle
	 * @access public
	 * @return int
    */
    int Bullet::getDegat()
    {
        return m_degat;
    }

    /**
	 * retourne si la balle a explose ou non
	 * @access public
	 * @return bool
    */
    bool Bullet::getExploded()
    {
        return m_exploded;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Bullet::~Bullet()
    {
    }
