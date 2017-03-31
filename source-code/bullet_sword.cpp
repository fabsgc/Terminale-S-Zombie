#include "bullet_sword.hpp"

    sf::Image m_imageBulletSword;
    sf::Sprite * m_spriteBulletSword;
    Anim m_animBulletSword;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Bullet_sword::Bullet_sword()
    {
        if (!m_imageBulletSword.LoadFromFile(SPRITE_BULLET_SWORD)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Bullet_sword::Bullet_sword] : impossible de charger le sprite bullet"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            std::cout<<"[INFORMATION] : [Bullet_sword::Bullet_sword] : creation d'une balle"<<std::endl;
        }

        // animation d'un coup d'épée
        m_animBulletSword.setSprite(&m_imageBulletSword);
        m_animBulletSword.setSpriteChangeTime(20);
        m_animBulletSword.setSpriteNumber(6);
        m_animBulletSword.setSpriteWidth(WIDTH_BULLET_X_SWORD);
        m_animBulletSword.setSpriteHeight(WIDTH_BULLET_Y_SWORD);
        m_animBulletSword.setSpriteCenterX(WIDTH_BULLET_X_SWORD/2);
        m_animBulletSword.setSpriteCenterY(WIDTH_BULLET_Y_SWORD);
    }

    /**
	 * affiche la balle
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Bullet_sword::display(sf::RenderWindow &window, const float deltaTime)
    {
        m_spriteBulletSword = m_animBulletSword.getSprite(1, 1);
        m_spriteBulletSword->SetPosition(sf::Vector2f(m_positionBullet.x, m_positionBullet.y)); // Positionnement
        m_spriteBulletSword->SetRotation(m_positionBullet.rotate);
        window.Draw((*m_spriteBulletSword));
        m_executionTime += deltaTime * 1000;
    }

    /**
	 * calcul la nouvelle position théorique de la balle (la position sera revue par la classe physic)
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps écoule entre 2 frames
	 * @access public
	 * @return void
    */
    void Bullet_sword::calculNewPosition(sf::RenderWindow &window, const float deltaTime)
    {
        m_animBulletSword.animPlay(deltaTime*1000); //on joue l'animation de la flamme
    }

    /**
	 * retourne si la balle est trop vieille ou non
	 * @access public
	 * @return bool
    */
    bool Bullet_sword::toOld() const
    {
        if(m_executionTime >= TIME_MAX_BULLET_SWORD)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Bullet_sword::~Bullet_sword()
    {
    }
