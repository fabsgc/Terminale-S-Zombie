#include "object_weapon.hpp"

    sf::Image m_imageObjectWeapon;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Object_Weapon::Object_Weapon() : Object()
    {
        std::cout<<"[INFORMATION] : [Object_Weapon::Object_Weapon] : creation d'une arme"<<std::endl;
    }

    /**
	 * initialise le bon sprite de l'arme en fonction de son id
	 * @param int id : numero du sprite
	 * @access public
	 * @return void
    */
    void Object_Weapon::setSprite(int id)
    {
        m_sprite.SetCenter(WIDTH_SPRITE/2,WIDTH_SPRITE/2);

        if (!m_imageObjectWeapon.LoadFromFile(SPRITE_OBJECT_WEAPON)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Object_Weapon::setSprite] : impossible de charger le sprite weapons"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_sprite.SetImage(m_imageObjectWeapon);
            m_sprite.SetSubRect(sf::IntRect(WIDTH_SPRITE*(id-1), 0, WIDTH_SPRITE*(id), WIDTH_SPRITE));
        }
    }

    /**
	 * initialise le bon sprite de l'arme en fonction de son id
	 * @param int id : numero du sprite qui sera affichee
	 * @access public
	 * @return void
    */
    void Object_Weapon::setSpriteBullet(int id)
    {
        m_spriteBullet = id;
    }

    /**
	 * affiche l'objet a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Object_Weapon::display(sf::RenderWindow &window)
    {
        m_sprite.SetPosition(sf::Vector2f(m_positionObject.x, m_positionObject.y)); // Positionnement
        m_sprite.SetRotation(30);
        m_sprite.SetScale(0.85,0.85);
        window.Draw(m_sprite);
    }

    /**
	 * modifie le nombre de degats qu'infligent l'arme
	 * @param int degat : nombre de degats
	 * @access public
	 * @return void
    */
    void Object_Weapon::setDegat(int degat)
    {
        m_degat = degat;
    }

    /**
	 * modifie la cadence de l'arme
	 * @param int cadence : cadence
	 * @access public
	 * @return void
    */
    void Object_Weapon::setCadence(int cadence)
    {
        m_cadence = cadence;
    }

    /**
	 * modifie la date (timestamp) de la derniere utilisation
	 * @param int lastUse : date
	 * @access public
	 * @return void
    */
    void Object_Weapon::setLastUse(long lastUse)
    {
        m_lastUse = lastUse;
    }

    /**
	 * modifie le nombre de munitions de l'arme
	 * @param int munitions : nombre de munitions
	 * @access public
	 * @return void
    */
    void Object_Weapon::setMunitions(int munitions)
    {
        if(munitions >= 0)
        {
            m_munitions = munitions;
        }
        else
        {
            m_munitions = 0;
        }
    }

    /**
	 * modifie l'id du son a jouer, en fonction de l'arme, c'est le son a l'emission ou a l'explosion
	 * @param int sound : id du son a jouer
	 * @access public
	 * @return void
    */
    void Object_Weapon::setSound(int sound)
    {
        m_sound = sound;
    }

    /**
	 * modifie la vitesse de la balle
	 * @param int speed : vitesse
	 * @access public
	 * @return void
    */
    void Object_Weapon::setSpeed(int speed)
    {
        m_speed = speed;
    }

    /**
	 * modifie le nom de l'arme
	 * @param std::string name : nom
	 * @access public
	 * @return void
    */
    void Object_Weapon::setName(std::string name)
    {
        m_name = name;
    }

    /**
	 * ajoute l'id des tiles qui peuvent etre detruites par cette arme
	 * @param int speed : vitesse
	 * @access public
	 * @return void
    */
    void Object_Weapon::addWeaponTileBreak(int id)
    {
        m_weaponTileBreak.push_back(id);
    }

    /**
	 * retourne l'id du sprite de la balle qui faudra afficher
	 * @access public
	 * @return void
    */
    int Object_Weapon::getSpriteBullet()
    {
        return m_spriteBullet;
    }

    /**
	 * retourne le nombre de degats qu'inflige une balle
	 * @access public
	 * @return int
    */
    int Object_Weapon::getDegat()
    {
        return m_degat;
    }

    /**
	 * retourne la cadence de l'arme
	 * @access public
	 * @return int
    */
    int Object_Weapon::getCadence()
    {
        return m_cadence;
    }

    /**
	 * retourne la date (timestamp) de derniere utilisation
	 * @access public
	 * @return int
    */
    int Object_Weapon::getLastUse()
    {
        return m_lastUse;
    }

    /**
	 * retourne le nombre de munitions restantes
	 * @access public
	 * @return int
    */
    int Object_Weapon::getMunitions()
    {
        return m_munitions;
    }

    /**
	 * retourne l'id du son que doit emettre la balle a chaque tir
	 * @access public
	 * @return int
    */
    int Object_Weapon::getSound()
    {
        return m_sound;
    }

    /**
	 * retourne la vitesse de la balle
	 * @access public
	 * @return int
    */
    int Object_Weapon::getSpeed()
    {
        return m_speed;
    }

    /**
	 * retourne le nom de l'arme
	 * @access public
	 * @return std::string
    */
    std::string Object_Weapon::getName()
    {
        return m_name;
    }

    /**
	 * retourne les tiles cassables
	 * @access public
	 * @return int
    */
    std::list<int> * Object_Weapon::getWeaponTileBreak()
    {
        return &m_weaponTileBreak;
    }

    /**
	 * destructeur
	 * @access public
	 * @return void
    */
    Object_Weapon::~Object_Weapon()
    {

    }
