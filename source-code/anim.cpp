#include "anim.hpp"

    /**
     * constructeur
     * @access public
     * @return void
    */
    Anim::Anim()
    {
        m_spriteChangeTime = 100;
        m_spriteExecutionTime = 100;
        m_spriteLastExecution = 0;
        m_spriteNumber = 1;
        m_spriteFirstSprite = 1;
        m_spriteWidth = WIDTH_SPRITE;
        m_spriteHeight = WIDTH_SPRITE;
        m_spriteCenterX = WIDTH_SPRITE/2;
        m_spriteCenterY = WIDTH_SPRITE/2;
        m_spriteCenterY = m_spriteCurrentSprite;
        m_animPlay = false;
    }

    /**
     * initialise le sprite a utiliser pour l'animation
     * @param std::string sprite : chemin vers le sprite
     * @access public
     * @return void
    */
    void Anim::setSprite(const sf::Image * image)
    {
        m_spriteAnim.SetImage((*image));
    }

    /**
     * defini le temps necessaire entre deux changements de sprite a afficher
     * @param int spriteChangeTime : temps en milliseconde
     * @access public
     * @return void
    */
    void Anim::setSpriteChangeTime(const int spriteChangeTime)
    {
        m_spriteChangeTime = spriteChangeTime;
    }

    /**
     * defini le nombre total de sprites sur l'image
     * @param int spriteNumber : nombre de sprites
     * @access public
     * @return void
    */
    void Anim::setSpriteNumber(const int spriteNumber)
    {
        m_spriteNumber = spriteNumber;
    }

    /**
     * defini la largeur du sprite
     * @param int spriteWidth : largeur du sprite (de la zone de l'image a afficher)
     * @access public
     * @return void
    */
    void Anim::setSpriteWidth(const int spriteWidth)
    {
        m_spriteWidth = spriteWidth;
    }

    /**
     * defini la hauteur du sprite
     * @param int spriteHeight : hauteur du sprite (de la zone de l'image a afficher)
     * @access public
     * @return void
    */
    void Anim::setSpriteHeight(const int spriteHeight)
    {
        m_spriteHeight = spriteHeight;
    }

    /**
     * defini le centre en X du sprite (axe autour duquel on fait ensuite les rotations)
     * @param int spriteCenterX : centre du sprite en X
     * @access public
     * @return void
    */
    void Anim::setSpriteCenterX(const int spriteCenterX)
    {
        m_spriteCenterX = spriteCenterX;
    }

    /**
     * defini le centre en Y du sprite (axe autour duquel on fait ensuite les rotations)
     * @param int spriteCenterY : centre du sprite en Y
     * @access public
     * @return void
    */
    void Anim::setSpriteCenterY(const int spriteCenterY)
    {
        m_spriteCenterY = spriteCenterY;
    }

    /**
     * joue l'animation, c'est a dire qu'il choisi le sprite a afficher
     * @param int spriteDeltaTime : temps passe depuis le dernier appel de la fonction
     * @access public
     * @return void
    */
    void Anim::animPlay(const int spriteDeltaTime)
    {
        m_spriteExecutionTime += spriteDeltaTime;

        if(m_animPlay == false) //l'animation etait arretee ? On joue le premier sprite
        {
            m_spriteCurrentSprite = m_spriteFirstSprite;
            m_spriteLastExecution = m_spriteExecutionTime;
            m_animPlay = true;
        }
        else //on joue le bon sprite
        {
            if((m_spriteExecutionTime - m_spriteChangeTime) >= m_spriteLastExecution) //le temps entre 2 sprite est ecoule, on passe a la suivante
            {
                if(m_spriteCurrentSprite < m_spriteNumber)
                {
                    m_spriteCurrentSprite++;
                }
                else
                {
                    m_spriteCurrentSprite = 1;
                }

                m_spriteLastExecution = m_spriteExecutionTime;
            }
        }
    }

    /**
     * arrete l'animation, et remet le sprite en cours sur le premier sprite a jouer
     * @param int spriteDeltaTime : temps passe depuis le dernier appel de la fonction
     * @access public
     * @return void
    */
    void Anim::animStop(const int spriteDeltaTime)
    {
        m_spriteExecutionTime += spriteDeltaTime;
        m_spriteCurrentSprite = m_spriteFirstSprite;
        m_animPlay = false;
    }

    /**
     * retourne le numero du sprite a afficher
     * @access public
     * @return int
    */
    int Anim::getCurrentSprite() const
    {
        return m_spriteCurrentSprite;
    }

    /**
     * retourne le sprite a afficher a l'ecran
     * @param int positionX : position en x a partir de laquelle demarrer le choix du sprite
     * @param int positionY : position en y a partir de laquelle demarrer le choix du sprite
     * @access public
     * @return sf::Sprite
    */
    sf::Sprite * Anim::getSprite(const int positionX, const int positionY)
    {
        m_spriteAnim.SetCenter(m_spriteCenterX, m_spriteCenterY);
        m_spriteAnim.SetSubRect(sf::IntRect(m_spriteWidth*(m_spriteCurrentSprite - 1 + (positionX -1)), m_spriteHeight*(positionY-1), m_spriteWidth*(m_spriteCurrentSprite + (positionX - 1)), m_spriteHeight*(1 + (positionY - 1))));

        return &m_spriteAnim;
    }

    /**
     * destructeur
     * @access public
     * @return void
    */
    Anim::~Anim()
    {

    }
