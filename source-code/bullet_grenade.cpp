#include "bullet_grenade.hpp"

    sf::Image m_imageBulletGrenade;
    sf::Image m_imageBulletGrenadeExploded;
    sf::Sprite m_spriteBulletGrenade;
    sf::Sprite * m_spriteBulletGrenadeExploded;
    Anim m_animBulletGrenade;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Bullet_grenade::Bullet_grenade()
    {
        m_spriteBulletGrenade.SetCenter(WIDTH_BULLET_X_GRENADE/2, WIDTH_BULLET_Y_GRENADE/2);

        if (!m_imageBulletGrenade.LoadFromFile(SPRITE_BULLET_GRENADE)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Bullet_grenade::Bullet_grenade] : impossible de charger le sprite bullet"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_spriteBulletGrenade.SetImage(m_imageBulletGrenade);
            std::cout<<"[INFORMATION] : [Bullet_grenade::Bullet_grenade] : creation d'une balle"<<std::endl;
        }

        if (!m_imageBulletGrenadeExploded.LoadFromFile(SPRITE_BULLET_GRENADE_EXPLODED)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Bullet_grenade::Bullet_grenade] : impossible de charger le sprite bullet explosion"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            std::cout<<"[INFORMATION] : [Bullet_grenade::Bullet_grenade] : creation d'une balle"<<std::endl;
        }

        m_animBulletGrenade.setSprite(&m_imageBulletGrenadeExploded);
        m_animBulletGrenade.setSpriteChangeTime(20);
        m_animBulletGrenade.setSpriteNumber(16);
        m_animBulletGrenade.setSpriteWidth(WIDTH_BULLET_X_GRENADE);
        m_animBulletGrenade.setSpriteHeight(WIDTH_BULLET_Y_GRENADE);
        m_animBulletGrenade.setSpriteCenterX(WIDTH_BULLET_X_GRENADE/2);
        m_animBulletGrenade.setSpriteCenterY(WIDTH_BULLET_Y_GRENADE/2);

        m_timeBeforeExplosion = 0;
        m_timeLastMouvement = 0;
    }

    /**
	 * affiche la balle
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Bullet_grenade::display(sf::RenderWindow &window, float deltaTime)
    {
        //si la mine a saute ou non, on affiche le bon sprite et l'animation
        switch(m_exploded)
        {
            case true : //la mine a saute, on commence a decompter
                m_spriteBulletGrenadeExploded = m_animBulletGrenade.getSprite(1, 1);
                m_spriteBulletGrenadeExploded->SetPosition(sf::Vector2f(m_positionBullet.x, m_positionBullet.y)); // Positionnement
                m_spriteBulletGrenadeExploded->SetRotation(m_positionBullet.rotate);
                window.Draw((*m_spriteBulletGrenadeExploded));

                m_executionTime += deltaTime * 1000;
            break;

            case false : //la mine n'a pas saute, dans ce cas, on affiche le sprite normal de la grenade
                m_spriteBulletGrenade.SetPosition(sf::Vector2f(m_positionBullet.x, m_positionBullet.y)); // Positionnement
                m_spriteBulletGrenade.SetRotation(m_positionBullet.rotate);
                window.Draw(m_spriteBulletGrenade);
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
    void Bullet_grenade::calculNewPosition(sf::RenderWindow &window, float deltaTime)
    {
        if(m_exploded == true)
        {
            m_animBulletGrenade.animPlay(deltaTime*1000); //on joue l'animation de la flamme
        }
        else
        {
            float decalage_vitesse = (1/deltaTime) / FPS;
            m_positionNewBullet.x = m_positionBullet.x + (cos((-(m_positionBullet.rotate+90)*PI)/180)*(m_speed))/decalage_vitesse;
            m_positionNewBullet.y = m_positionBullet.y + (sin((-(m_positionBullet.rotate+90)*PI)/180)*(m_speed))/decalage_vitesse;

            m_timeBeforeExplosion += deltaTime * 1000;

            //on calcule la vitesse qu'il reste a la balle
            if(m_timeBeforeExplosion - (m_timeLastMouvement + (deltaTime*1000)) > TIME_BETWEEN_BULLET_GRENADE_MOUVEMENT)
            {
                if(m_speed <= 0)
                {
                    m_speed = 0;
                }
                else
                {
                    m_timeLastMouvement = m_timeBeforeExplosion;
                    m_speed--;
                }
            }

            //si la grenade a explose, on change la valeur de m_exploded
            if(m_timeBeforeExplosion >= TIME_BEFORE_BULLET_GRENADE_EXPLOSION)
            {
                m_exploded = true;
                m_sound.playSound(22, 100.f, false, m_positionBullet, 512, 5, true);
            }
        }
    }

    /**
	 * retourne si la balle est trop vieille ou non
	 * @access public
	 * @return bool
    */
    bool Bullet_grenade::toOld() const
    {
        switch(m_exploded)
        {
            case true :
                if(m_executionTime >= TIME_MAX_BULLET_GRENADE)
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
	 * destructeur
	 * @access public
	 * @return void
    */
    Bullet_grenade::~Bullet_grenade()
    {
    }
