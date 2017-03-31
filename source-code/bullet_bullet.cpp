#include "bullet_bullet.hpp"

    sf::Image m_imageBulletBullet;
    sf::Sprite m_spriteBulletBullet;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Bullet_bullet::Bullet_bullet()
    {
        m_spriteBulletBullet.SetCenter(WIDTH_BULLET_X_BULLET/2,WIDTH_BULLET_Y_BULLET);

        if (!m_imageBulletBullet.LoadFromFile(SPRITE_BULLET_BULLET)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Bullet_bullet::Bullet_bullet] : impossible de charger le sprite bullet"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_spriteBulletBullet.SetImage(m_imageBulletBullet);
            std::cout<<"[INFORMATION] : [Bullet_bullet::Bullet_bullet] : creation d'une balle"<<std::endl;
        }
    }

    /**
	 * affiche la balle
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps ecoule entre deux frames
	 * @access public
	 * @return void
    */
    void Bullet_bullet::display(sf::RenderWindow &window, const float deltaTime)
    {
        m_spriteBulletBullet.SetPosition(sf::Vector2f(m_positionBullet.x, m_positionBullet.y)); // Positionnement
        m_spriteBulletBullet.SetRotation(m_positionBullet.rotate);
        window.Draw(m_spriteBulletBullet);

        m_executionTime += deltaTime * 1000;
    }

    /**
	 * calcul la nouvelle position théorique de la balle (la position sera revue par la classe physic)
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps écoule entre 2 frames
	 * @access public
	 * @return void
    */
    void Bullet_bullet::calculNewPosition(sf::RenderWindow &window, const float deltaTime)
    {
        float decalage_vitesse = (1/deltaTime) / FPS;
        m_positionNewBullet.x = m_positionBullet.x + (cos((-(m_positionBullet.rotate+90)*PI)/180)*(m_speed))/decalage_vitesse;
        m_positionNewBullet.y = m_positionBullet.y + (sin((-(m_positionBullet.rotate+90)*PI)/180)*(m_speed))/decalage_vitesse;
    }

    /**
	 * retourne si la balle est trop vieille ou non
	 * @access public
	 * @return bool
    */
    bool Bullet_bullet::toOld() const
    {
        if(m_executionTime > TIME_MAX_BULLET_BULLET)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
	 * modifie le sprite de la balle qui fait reference a l'arme qui a tire cette balle pour afficher le bon sprite
	 * @param int sprite : id du sprite a afficher
	 * @access public
	 * @return void
    */
    void Bullet_bullet::setSprite(const int sprite)
    {
        m_spriteId = sprite;
        m_spriteBulletBullet.SetSubRect(sf::IntRect(WIDTH_BULLET_X_BULLET*(m_spriteId-1), 0, WIDTH_BULLET_X_BULLET*(m_spriteId), WIDTH_BULLET_Y_BULLET));
    }

    /**
	 * retourne l'id de la balle
	 * @access public
	 * @return int
    */
    int Bullet_bullet::getSprite() const
    {
        return m_spriteId;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Bullet_bullet::~Bullet_bullet()
    {
    }
