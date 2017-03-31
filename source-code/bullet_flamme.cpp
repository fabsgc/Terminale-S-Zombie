#include "bullet_flame.hpp"

    sf::Image m_imageBulletFlame;
    sf::Sprite * m_spriteBulletFlame;
    Anim m_animBulletFlame;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Bullet_flame::Bullet_flame()
    {
        if (!m_imageBulletFlame.LoadFromFile(SPRITE_BULLET_FLAME)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Bullet_flame::Bullet_flame] : impossible de charger le sprite bullet"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            std::cout<<"[INFORMATION] : [Bullet_flame::Bullet_flame] : creation d'une balle"<<std::endl;
        }

        //animation de la flamme
        m_animBulletFlame.setSprite(&m_imageBulletFlame);
        m_animBulletFlame.setSpriteChangeTime(20);
        m_animBulletFlame.setSpriteNumber(10);
        m_animBulletFlame.setSpriteWidth(WIDTH_BULLET_X_FLAME);
        m_animBulletFlame.setSpriteHeight(WIDTH_BULLET_Y_FLAME);
        m_animBulletFlame.setSpriteCenterX(WIDTH_BULLET_X_FLAME/2);
        m_animBulletFlame.setSpriteCenterY(WIDTH_BULLET_Y_FLAME/2);
    }

    /**
	 * affiche la balle, les flammes n'ont qu'un etat, pas a gerer l'explosion ou non
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Bullet_flame::display(sf::RenderWindow &window, const float deltaTime)
    {
        m_spriteBulletFlame = m_animBulletFlame.getSprite(1, 1);
        m_spriteBulletFlame->SetPosition(sf::Vector2f(m_positionBullet.x, m_positionBullet.y)); // Positionnement
        m_spriteBulletFlame->SetRotation(m_positionBullet.rotate);
        window.Draw((*m_spriteBulletFlame));

        m_executionTime += deltaTime * 1000;
    }

    /**
	 * calcul la nouvelle position théorique de la balle (la position sera revue par la classe physic)
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps écoule entre 2 frames
	 * @access public
	 * @return void
    */
    void Bullet_flame::calculNewPosition(sf::RenderWindow &window, const float deltaTime)
    {
        //la position de la flamme ne va pas changer
        m_animBulletFlame.animPlay(deltaTime*1000); //on joue l'animation de la flamme
    }

    /**
	 * retourne si la balle est trop vieille ou non
	 * @access public
	 * @return bool
    */
    bool Bullet_flame::toOld() const
    {
        if(m_executionTime >= TIME_MAX_BULLET_FLAME)
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
    Bullet_flame::~Bullet_flame()
    {
    }
