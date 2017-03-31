#include "bullet_mine.hpp"

    sf::Image m_imageBulletMine;
    sf::Image m_imageBulletMineExploded;
    sf::Sprite m_spriteBulletMine;
    sf::Sprite * m_spriteBulletMineExploded;
    Anim m_animBulletMine;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Bullet_mine::Bullet_mine()
    {
        m_spriteBulletMine.SetCenter(WIDTH_BULLET_X_MINE/2, WIDTH_BULLET_Y_MINE/2);

        if (!m_imageBulletMine.LoadFromFile(SPRITE_BULLET_MINE)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Bullet_mine::Bullet_mine] : impossible de charger le sprite bullet"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_spriteBulletMine.SetImage(m_imageBulletMine);
            std::cout<<"[INFORMATION] : [Bullet_mine::Bullet_mine] : creation d'une balle"<<std::endl;
        }

        if (!m_imageBulletMineExploded.LoadFromFile(SPRITE_BULLET_MINE_EXPLODED)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Bullet_mine::Bullet_mine] : impossible de charger le sprite bullet explosion"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            std::cout<<"[INFORMATION] : [Bullet_mine::Bullet_mine] : creation d'une balle"<<std::endl;
        }

        //animation de l'explosion de la mine
        m_animBulletMine.setSprite(&m_imageBulletMineExploded);
        m_animBulletMine.setSpriteChangeTime(10);
        m_animBulletMine.setSpriteNumber(32);
        m_animBulletMine.setSpriteWidth(WIDTH_BULLET_X_MINE);
        m_animBulletMine.setSpriteHeight(WIDTH_BULLET_Y_MINE);
        m_animBulletMine.setSpriteCenterX(WIDTH_BULLET_X_MINE/2);
        m_animBulletMine.setSpriteCenterY(WIDTH_BULLET_Y_MINE/2);
    }

    /**
	 * affiche la balle
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Bullet_mine::display(sf::RenderWindow &window, const float deltaTime)
    {
        //si la mine a saute ou non, on affiche le bon sprite et l'animation
        switch(m_exploded)
        {
            case true : //la mine a saute, on commence a decompter
                m_spriteBulletMineExploded = m_animBulletMine.getSprite(1, 1);
                m_spriteBulletMineExploded->SetPosition(sf::Vector2f(m_positionBullet.x, m_positionBullet.y)); // Positionnement
                m_spriteBulletMineExploded->SetRotation(m_positionBullet.rotate);
                window.Draw((*m_spriteBulletMineExploded));

                m_executionTime += deltaTime * 1000;

                m_sound.playSound(22, 100.f, false, m_positionBullet, 512, 5, true);
            break;

            case false :
                m_spriteBulletMine.SetPosition(sf::Vector2f(m_positionBullet.x, m_positionBullet.y)); // Positionnement
                m_spriteBulletMine.SetRotation(m_positionBullet.rotate);
                window.Draw(m_spriteBulletMine);
            break;
        }
    }

    /**
	 * calcul la nouvelle position théorique de la balle (la position sera revue par la classe physic)
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps écoule entre 2 frames
	 * @access public
	 * @return void
    */
    void Bullet_mine::calculNewPosition(sf::RenderWindow &window, const float deltaTime)
    {
        m_animBulletMine.animPlay(deltaTime*1000); //on joue l'animation de la flamme
    }

    /**
	 * retourne si la mine a bien eu le temps d'exploser
	 * @access public
	 * @return bool
    */
    bool Bullet_mine::toOld() const
    {
        switch(m_exploded)
        {
            case true :
                if(m_executionTime >= TIME_MAX_BULLET_MINE && m_activated == true)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            break;

            case false :
                return false;
            break;
        }

        return false;
    }

    /**
     * specifie si la balle a explose ou non (utilisee dans la class physic)
     * @param bool exploded : balle explosee ou non
     * @access public
     * @return void
    */
    void Bullet_mine::setExploded(const bool exploded)
    {
        m_exploded = exploded;
    }

    /**
     * specifie  si la mine a ete activee
     * @param bool exploded : balle explosee ou non
     * @access public
     * @return void
    */
    void Bullet_mine::setActivated(const bool activated)
    {
        m_activated = activated;
    }

    /**
     * retourne si la mine a ete activee
     * @param bool exploded : balle explosee ou non
     * @access public
     * @return void
    */
    bool Bullet_mine::getActivated() const
    {
        return m_activated;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Bullet_mine::~Bullet_mine()
    {
    }
