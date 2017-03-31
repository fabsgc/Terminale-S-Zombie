#include "player.hpp"

    sf::Image m_imagePlayer;
    sf::Image m_imageLife;
    sf::Image m_imageWeapon;

    /**
     * constructeur
     * @access public
     * @return void
    */
    Player::Player()
    {
        m_executionTime = 10000;
        m_lastChangeArme = 0;
        m_lastAttackTime = 0;
        m_armeActive = 1;
        m_teleported = false;
        m_objectWeapon = &m_objectWeapons[m_armeActive];
        m_gameplay = getGameplay();
        m_level = 0;

        m_spriteLife.SetCenter(WIDTH_PLAYER_X/2,WIDTH_PLAYER_Y/2);

        if (!m_imageLife.LoadFromFile("sprites/life.png")) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR]: [Player::Player] : impossible de charger le sprite life"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_spriteLife.SetImage(m_imageLife);
        }

        if(!m_font.LoadFromFile(FONT_GUI))
        {
            std::cout<<"[ERREUR]: [Player::Player] : impossible de charger la police " << FONT_GUI <<std::endl;
        }

        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_1)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR]: [Player::Player] : impossible de charger le sprite player"<<std::endl;
        }

        //initialisation de la class anim
        m_animPlayer.setSprite(&m_imagePlayer);
        m_animPlayer.setSpriteChangeTime(10);
        m_animPlayer.setSpriteNumber(53);
        m_animPlayer.setSpriteWidth(WIDTH_PLAYER_X);
        m_animPlayer.setSpriteHeight(WIDTH_PLAYER_Y);
        m_animPlayer.setSpriteCenterX(WIDTH_PLAYER_X/2);
        m_animPlayer.setSpriteCenterY(WIDTH_PLAYER_Y-20);
    }

    /**
     * calcul la nouvelle position théorique du personnage (la position sera revue par la classe physic)
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param float deltaTime : temps écoule entre 2 frames
     * @access public
     * @return void
    */
    void Player::calculNewPosition(sf::RenderWindow &window, float deltaTime)
    {
        float vitesse_x = 0, vitesse_y = 0, decalage_vitesse = (1/deltaTime) / 60;
        m_executionTime += (deltaTime*1000);


        if(m_teleported == false)
        {
            const sf::Input& Input = window.GetInput();

            if(Input.IsJoystickButtonDown(0, 5) || Input.IsMouseButtonDown(sf::Mouse::Left))
            {
                this->shoot();
            }
            else
            {
                m_sound.stopSound(m_objectWeapons[9].getSound()); //ce bruit est trop long
            }

            if(fabs(Input.GetJoystickAxis(0, sf::Joy::AxisX)) + fabs(Input.GetJoystickAxis(0, sf::Joy::AxisY)) > 40) //un mouvement du joystick
            {
                if(Input.IsJoystickButtonDown(0, 4))
                {
                    m_animPlayer.animStop(deltaTime*1000); //on arrete l'anim du joueur
                    m_sound.stopSound(3);
                }
                else
                {
                    if(Input.GetJoystickAxis(0, sf::Joy::AxisX) > 40)
                    {
                        vitesse_x = ((Input.GetJoystickAxis(0, sf::Joy::AxisX)*m_speed)/100)/decalage_vitesse;
                        m_positionNewPlayer.x = m_positionPlayer.x + vitesse_x;
                    }
                    if(Input.GetJoystickAxis(0, sf::Joy::AxisX) < 40)
                    {
                        vitesse_x = ((Input.GetJoystickAxis(0, sf::Joy::AxisX)*m_speed)/100)/decalage_vitesse;
                        m_positionNewPlayer.x = m_positionPlayer.x + vitesse_x;
                    }
                    if(Input.GetJoystickAxis(0, sf::Joy::AxisY) > 40)
                    {
                        vitesse_y = ((Input.GetJoystickAxis(0, sf::Joy::AxisY)*m_speed)/100)/decalage_vitesse;
                        m_positionNewPlayer.y = m_positionPlayer.y + vitesse_y;
                    }
                    if(Input.GetJoystickAxis(0, sf::Joy::AxisY) < 40)
                    {
                        vitesse_y = ((Input.GetJoystickAxis(0, sf::Joy::AxisY)*m_speed)/100)/decalage_vitesse;
                        m_positionNewPlayer.y = m_positionPlayer.y + vitesse_y;
                    }

                    m_animPlayer.animPlay(deltaTime*1000); // on joue l'anim du joueur
                    m_sound.playSound(3, 60.f, false, m_positionPlayer, 512, 5, true);
                }

                //angle :
                m_positionNewPlayer.rotate = -((atan2(Input.GetJoystickAxis(0, sf::Joy::AxisY), Input.GetJoystickAxis(0, sf::Joy::AxisX))/3.14)*180 + 90);
            }
            else
            {
                if(position.x != Input.GetMouseX() || position.y != Input.GetMouseY())
                    {
                        position.x = Input.GetMouseX();
                        position.y = Input.GetMouseY();
                        position2.x = window.GetWidth()/2;
                        position2.y = window.GetHeight()/2;

                        coefDirecteurPosition = (window.GetHeight()/2-position.y)/(window.GetWidth()/2-position.x);

                        if((position.x <= position2.x && position.y <= position2.y) || (position.x <= position2.x && position.y >= position2.y))
                        {
                            m_positionNewPlayer.rotate = -((atan(coefDirecteurPosition) * 180)/PI - 90);
                        }
                        else if(fabs(coefDirecteurPosition) > 50)
                        {
                            if(position.y < position2.y)
                            {
                                m_positionNewPlayer.rotate = 0;
                            }
                            else
                            {
                                m_positionNewPlayer.rotate = 180;
                            }
                        }
                        else
                        {
                            m_positionNewPlayer.rotate = -(atan(coefDirecteurPosition) * 180)/PI - 90;
                        }
                    }

                if(m_gameplay == 1)
                {
                    if(Input.IsKeyDown(sf::Key::Z)) //aucun mouvement
                    {
                        m_positionNewPlayer.y = m_positionPlayer.y - (cos((m_positionNewPlayer.rotate*PI)/180)*(m_speed))/decalage_vitesse;
                        m_positionNewPlayer.x = m_positionPlayer.x - (sin((m_positionNewPlayer.rotate*PI)/180)*(m_speed))/decalage_vitesse;

                        m_animPlayer.animPlay(deltaTime*1000); // on joue l'anim du joueur
                        m_sound.playSound(3, 60.f, false, m_positionPlayer, 512, 5, true);
                    }
                    else if(Input.IsKeyDown((sf::Key::S)))
                    {
                        m_positionNewPlayer.y = m_positionPlayer.y + (cos((m_positionNewPlayer.rotate*PI)/180)*(m_speed))/decalage_vitesse;
                        m_positionNewPlayer.x = m_positionPlayer.x + (sin((m_positionNewPlayer.rotate*PI)/180)*(m_speed))/decalage_vitesse;

                        m_animPlayer.animPlay(deltaTime*1000); // on joue l'anim du joueur
                        m_sound.playSound(3, 60.f, false, m_positionPlayer, 512, 5, true);
                    }
                    else if(Input.IsKeyDown(sf::Key::Q)) //a gauche
                    {
                        m_positionNewPlayer.y = m_positionPlayer.y - (cos(((m_positionNewPlayer.rotate + 90)*PI)/180)*(m_speed))/decalage_vitesse;
                        m_positionNewPlayer.x = m_positionPlayer.x - (sin(((m_positionNewPlayer.rotate + 90)*PI)/180)*(m_speed))/decalage_vitesse;

                        m_animPlayer.animPlay(deltaTime*1000); // on joue l'anim du joueur
                        m_sound.playSound(3, 60.f, false, m_positionPlayer, 512, 5, true);
                    }
                    else if(Input.IsKeyDown(sf::Key::D)) //a gauche
                    {
                        m_positionNewPlayer.y = m_positionPlayer.y - (cos(((m_positionNewPlayer.rotate - 90)*PI)/180)*(m_speed))/decalage_vitesse;
                        m_positionNewPlayer.x = m_positionPlayer.x - (sin(((m_positionNewPlayer.rotate - 90)*PI)/180)*(m_speed))/decalage_vitesse;

                        m_animPlayer.animPlay(deltaTime*1000); // on joue l'anim du joueur
                        m_sound.playSound(3, 60.f, false, m_positionPlayer, 512, 5, true);
                    }
                    else if(Input.IsKeyDown(sf::Key::Escape)) //aucun mouvement
                    {
                        window.Close();
                    }
                    else
                    {
                        m_animPlayer.animStop(deltaTime*1000); //on arrete l'anim du joueur
                        m_sound.stopSound(3);
                    }
                }
                else if(m_gameplay == 2)
                {
                    if(Input.IsKeyDown(sf::Key::Z)) //aucun mouvement
                    {
                        m_positionNewPlayer.y = m_positionPlayer.y - (m_speed)/decalage_vitesse;

                        if(Input.IsKeyDown(sf::Key::Q))
                        {
                            m_positionNewPlayer.y = m_positionPlayer.y - (2.5*m_speed/3)/decalage_vitesse;
                            m_positionNewPlayer.x = m_positionPlayer.x - (2.5*m_speed/3)/decalage_vitesse;
                        }
                        else if(Input.IsKeyDown(sf::Key::D))
                        {
                            m_positionNewPlayer.y = m_positionPlayer.y - (2.5*m_speed/3)/decalage_vitesse;
                            m_positionNewPlayer.x = m_positionPlayer.x + (2.5*m_speed/3)/decalage_vitesse;
                        }

                        m_animPlayer.animPlay(deltaTime*1000); // on joue l'anim du joueur
                        m_sound.playSound(3, 60.f, false, m_positionPlayer, 512, 5, true);
                    }
                    else if(Input.IsKeyDown((sf::Key::S)))
                    {
                        m_positionNewPlayer.y = m_positionPlayer.y + (m_speed)/decalage_vitesse;

                        if(Input.IsKeyDown(sf::Key::Q))
                        {
                            m_positionNewPlayer.y = m_positionPlayer.y + (2.5*m_speed/3)/decalage_vitesse;
                            m_positionNewPlayer.x = m_positionPlayer.x - (2.5*m_speed/3)/decalage_vitesse;
                        }
                        else if(Input.IsKeyDown(sf::Key::D))
                        {
                            m_positionNewPlayer.y = m_positionPlayer.y + (2.5*m_speed/3)/decalage_vitesse;
                            m_positionNewPlayer.x = m_positionPlayer.x + (2.5*m_speed/3)/decalage_vitesse;
                        }

                        m_animPlayer.animPlay(deltaTime*1000); // on joue l'anim du joueur
                        m_sound.playSound(3, 60.f, false, m_positionPlayer, 512, 5, true);
                    }
                    else if(Input.IsKeyDown(sf::Key::Q)) //a gauche
                    {
                        m_positionNewPlayer.x = m_positionPlayer.x - (m_speed)/decalage_vitesse;

                        m_animPlayer.animPlay(deltaTime*1000); // on joue l'anim du joueur
                        m_sound.playSound(3, 60.f, false, m_positionPlayer, 512, 5, true);
                    }
                    else if(Input.IsKeyDown(sf::Key::D)) //a gauche
                    {
                        m_positionNewPlayer.x = m_positionPlayer.x + (m_speed)/decalage_vitesse;

                        m_animPlayer.animPlay(deltaTime*1000); // on joue l'anim du joueur
                        m_sound.playSound(3, 60.f, false, m_positionPlayer, 512, 5, true);
                    }
                    else if(Input.IsKeyDown(sf::Key::Escape)) //aucun mouvement
                    {
                        window.Close();
                    }
                    else
                    {
                        m_animPlayer.animStop(deltaTime*1000); //on arrete l'anim du joueur
                        m_sound.stopSound(3);
                    }
                }
            }
        }
        else if(m_teleported == true) //on deplace le personnage entre les 2 bornes de teleportation
        {
            if(m_positionNewPlayer.x <= m_positionTeleportationToPlayer.x) //situe avant
            {
                m_positionNewPlayer.x += ((1)*(32)/decalage_vitesse)/fabs(m_coeffTeleported);
            }
            else if(m_positionNewPlayer.x >= m_positionTeleportationToPlayer.x)
            {
                m_positionNewPlayer.x += ((-1)*(32)/decalage_vitesse)/fabs(m_coeffTeleported);
            }

            if(m_positionNewPlayer.y <= m_positionTeleportationToPlayer.y)
            {
                m_positionNewPlayer.y += (fabs(m_coeffTeleported)*(32)/decalage_vitesse)/fabs(m_coeffTeleported);
            }
            else if(m_positionNewPlayer.y >= m_positionTeleportationToPlayer.y)
            {
                m_positionNewPlayer.y += (-fabs(m_coeffTeleported)*(32)/decalage_vitesse)/fabs(m_coeffTeleported);
            }

            if(distance(m_positionNewPlayer, m_positionTeleportationToPlayer) < 32)
            {
                m_teleported = false;
                m_positionNewPlayer.x = m_positionTeleportationToPlayer.x;
                m_positionNewPlayer.y = m_positionTeleportationToPlayer.y;
            }
        }
    }

    /**
     * met a jour la position via les valeurs calculees en cache
     * @access public
     * @return void
    */
    void Player::updatePosition()
    {
        m_positionPlayer = m_positionNewPlayer;
    }

    /**
     * affiche le personnage à l'écran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param float deltaTime : temps entre 2 frame
     * @access public
     * @return void
    */
    void Player::display(sf::RenderWindow &window, float deltaTime)
    {
        if(m_teleported == false) // on n'affiche pas le joueur lorsqu'il est en train d'etre teleporte
        {
            m_sprite = m_animPlayer.getSprite(1, 1);
            m_sprite->SetPosition(sf::Vector2f(m_positionPlayer.x, m_positionPlayer.y)); // Positionnement
            m_sprite->SetRotation(m_positionPlayer.rotate);
            window.Draw((*m_sprite));
        }
    }

    /**
     * affiche les balles du joueur
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param float deltaTime : temps entre 2 frame
     * @access public
     * @return void
    */
    void Player::displayBulletBullet(sf::RenderWindow &window, float deltaTime)
    {
        for(std::list<Bullet_bullet>::iterator it_bullet = m_bulletBullet.begin(); it_bullet!= m_bulletBullet.end(); ++it_bullet)
        {
            it_bullet->display(window, deltaTime);
        }
    }

    /**
     * affiche les balles du joueur
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Player::displayBulletFlame(sf::RenderWindow &window, float deltaTime)
    {
        for(std::list<Bullet_flame>::iterator it_bullet = m_bulletFlame.begin(); it_bullet!= m_bulletFlame.end(); ++it_bullet)
        {
            it_bullet->display(window, deltaTime);
        }
    }

    /**
     * affiche les balles du joueur
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Player::displayBulletGrenade(sf::RenderWindow &window, float deltaTime)
    {
        for(std::list<Bullet_grenade>::iterator it_bullet = m_bulletGrenade.begin(); it_bullet!= m_bulletGrenade.end(); ++it_bullet)
        {
            it_bullet->display(window, deltaTime);
        }
    }

    /**
     * affiche les balles du joueur
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Player::displayBulletMine(sf::RenderWindow &window, float deltaTime)
    {
        for(std::list<Bullet_mine>::iterator it_bullet = m_bulletMine.begin(); it_bullet!= m_bulletMine.end(); ++it_bullet)
        {
            it_bullet->display(window, deltaTime);
        }
    }

    /**
     * affiche les balles du joueur
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Player::displayBulletSword(sf::RenderWindow &window, float deltaTime)
    {
        for(std::list<Bullet_sword>::iterator it_bullet = m_bulletSword.begin(); it_bullet!= m_bulletSword.end(); ++it_bullet)
        {
            it_bullet->display(window, deltaTime);
        }
    }

    /**
     * affiche les infos sur le personnage a l'ecran: vie, arme
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Player::displayInfo(sf::RenderWindow &window, int width, int height)
    {
        //on affiche le sprite de vie
        m_spriteLife.SetPosition(sf::Vector2f(m_positionPlayer.x + (width/2 - 32), m_positionPlayer.y + (height/2 - 23))); // Positionnement
        window.Draw(m_spriteLife);

        //on affiche le sprite de l'arme
        m_spriteWeapon = m_objectWeapon->getSprite();
        m_spriteWeapon.SetPosition(sf::Vector2f(m_positionPlayer.x + (width/2 - 200), m_positionPlayer.y + (height/2 - 32))); // Positionnement
        window.Draw(m_spriteWeapon);

        //on affiche la quantité de vie
        m_textLife.SetText(int2Str(m_life)); // Texte
        m_textLife.SetFont(m_font); // Fonte
        m_textLife.SetSize(40); // Taille de police
        m_textLife.SetStyle(sf::String::Bold);
        m_textLife.SetPosition(sf::Vector2f(m_positionPlayer.x + (width/2 - 114), m_positionPlayer.y + (height/2 - 56))); // Positionnement
        window.Draw(m_textLife);

        //on affiche le nombre de munitions
        m_textWeapon.SetText(int2Str(m_objectWeapon->getMunitions())); // Texte
        m_textWeapon.SetFont(m_font); // Fonte
        m_textWeapon.SetSize(40); // Taille de police
        m_textWeapon.SetStyle(sf::String::Bold);
        m_textWeapon.SetPosition(sf::Vector2f(m_positionPlayer.x + (width/2 - 300), m_positionPlayer.y + (height/2 - 56))); // Positionnement
        window.Draw(m_textWeapon);
    }

    /**
     * inflige des degats au joueur
     * @param Npc &npc : référence vers un object Npc
     * @access public
     * @return void
    */
    void Player::prendreDegat(Npc &npc, float deltaTime)
    {
        if(m_executionTime - (m_lastAttackTime + (deltaTime*1000)) > TIME_BETWEEN_DEGAT)
        {
             m_life -= npc.getDegat();
             m_lastAttackTime = m_executionTime;
             m_sound.playSound(10, 80.f, false, m_positionPlayer, 512, 5, true);
             m_sound.playSound(14, 30.f, false, m_positionPlayer, 512, 5, true);

            if(m_life <= 0)
            {
                m_life = 0;
                m_win = false;
            }
        }
    }

    /**
     * inflige des degats au joueur
     * @param int degat : nombre de degats
     * @param float deltaTime : temps entre chaque appel de la fonction
     * @param int timeBetweenAttack : temps entre deux attaques
     * @access public
     * @return void
    */
    void Player::prendreDegatBullet(int degat, float deltaTime, int timeBetweenAttack)
    {
        if(m_executionTime - (m_lastAttackTime + (deltaTime*1000)) > timeBetweenAttack)
        {
            m_sound.playSound(10, 80.f, false, m_positionPlayer, 512, 5, true);

            m_life -= degat;
            m_lastAttackTime = m_executionTime;

            if(m_life < 0)
            {
                m_life = 0;
                m_win = false;
            }
        }
    }

    /**
     * modifie l'objet Bullet pour tirer
     * @access public
     * @return void
    */
    void Player::shoot()
    {
        if(m_teleported == false) //le joueur ne peut pas tirer quand il est en train d'etre teleporte
        {
            //le dernier tir est assez ancien
            if(m_executionTime - m_objectWeapon->getLastUse() >= m_objectWeapon->getCadence() && m_objectWeapon->getMunitions() > 0)
            {
                if(m_objectWeapon->getId() >= 1 && m_objectWeapon->getId() <= 6) //les 6 premières armes
                {
                    this->shootBullet();
                }
                else
                {
                    switch(m_objectWeapon->getId())
                    {
                        case 7 :
                            this->shootMine();
                        break;

                        case 8 :
                            this->shootGrenade();
                        break;

                        case 9 :
                            this->shootFlame();
                        break;
                    }
                }
            }
            else if(m_executionTime - m_objectWeapon->getLastUse() >= m_objectWeapon->getCadence())
            {
                if(m_objectWeapon->getId() == 10)
                {
                    this->shootSword();
                }
            }
        }
    }

    /**
     * tire une balle
     * @access public
     * @return void
    */
    void Player::shootBullet()
    {
        PositionItem position = m_positionPlayer;

        m_objectWeapon->setLastUse(m_executionTime);
        m_objectWeapon->setMunitions(m_objectWeapon->getMunitions()-1);
        m_sound.playSound(m_objectWeapon->getSound(), 100.f, false, m_positionPlayer, 512, 5, true);


        position.x -= 40 * sin(((m_positionPlayer.rotate) * PI)/180);
        position.y -= 40 * cos(((m_positionPlayer.rotate) * PI)/180);

        //on créé un nouvel objet bullet :
        bulletBullet.setSpeed(m_objectWeapon->getSpeed());
        bulletBullet.setSprite(m_objectWeapon->getSpriteBullet());
        bulletBullet.setPosition(position);
        bulletBullet.setTileBreak((m_objectWeapon->getWeaponTileBreak()));
        bulletBullet.setDegat(m_objectWeapon->getDegat());
        m_bulletBullet.push_back(bulletBullet);

        std::cout<<"[INFORMATION]: [Player::shootBullet] : creation d'une balle"<<std::endl;
    }

    /**
     * tire une mine
     * @access public
     * @return void
    */
    void Player::shootMine()
    {
        PositionItem position = m_positionPlayer;

        m_objectWeapon->setLastUse(m_executionTime);
        m_objectWeapon->setMunitions(m_objectWeapon->getMunitions()-1);

        position.x -= 40 * sin(((m_positionPlayer.rotate) * PI)/180);
        position.y -= 40 * cos(((m_positionPlayer.rotate) * PI)/180);

        bulletMine.setSpeed(m_objectWeapon->getSpeed());
        bulletMine.setPosition(position);
        bulletMine.setExploded(false);
        bulletMine.setActivated(false);
        bulletMine.setTileBreak((m_objectWeapon->getWeaponTileBreak()));
        bulletMine.setDegat(m_objectWeapon->getDegat());
        m_bulletMine.push_back(bulletMine);

        std::cout<<"[INFORMATION]: [Player::shootMine] : creation d'une mine"<<std::endl;
    }

    /**
     * tire une grenade
     * @access public
     * @return void
    */
    void Player::shootGrenade()
    {
        PositionItem position = m_positionPlayer;

        m_objectWeapon->setLastUse(m_executionTime);
        m_objectWeapon->setMunitions(m_objectWeapon->getMunitions()-1);
        m_sound.playSound(m_objectWeapon->getSound(), 100.f, false, m_positionPlayer, 512, 5, true);

        position.x -= 40 * sin(((m_positionPlayer.rotate) * PI)/180);
        position.y -= 40 * cos(((m_positionPlayer.rotate) * PI)/180);

        bulletGrenade.setPosition(position);
        bulletGrenade.setSpeed(m_objectWeapon->getSpeed());
        bulletGrenade.setTileBreak((m_objectWeapon->getWeaponTileBreak()));
        bulletGrenade.setDegat(m_objectWeapon->getDegat());
        m_bulletGrenade.push_back(bulletGrenade);

        std::cout<<"[INFORMATION]: [Player::shootGrenade] : creation d'une grenade"<<std::endl;
    }

    /**
     * tire une flamme
     * @access public
     * @return void
    */
    void Player::shootFlame()
    {
        PositionItem position = m_positionPlayer;

        m_objectWeapon->setLastUse(m_executionTime);
        m_objectWeapon->setMunitions(m_objectWeapon->getMunitions()-1);
        m_sound.playSound(m_objectWeapon->getSound(), 100.f, false, m_positionPlayer, 512, 5, true);

        position.x -= 91 * sin(((m_positionPlayer.rotate) * PI)/180);
        position.y -= 91 * cos(((m_positionPlayer.rotate) * PI)/180);

        bulletFlame.setPosition(position);
        bulletFlame.setTileBreak((m_objectWeapon->getWeaponTileBreak()));
        bulletFlame.setDegat(m_objectWeapon->getDegat());
        m_bulletFlame.push_back(bulletFlame);

        std::cout<<"[INFORMATION]: [Player::shootFlame] : creation d'une flamme"<<std::endl;
    }

    /**
     * tire un coup de sabre
     * @access public
     * @return void
    */
    void Player::shootSword()
    {
        PositionItem position = m_positionPlayer;

        m_objectWeapon->setLastUse(m_executionTime);
        m_sound.playSound(m_objectWeapon->getSound(), 100.f, false, m_positionPlayer, 512, 5, true);

        position.x -= 40 * sin(((m_positionPlayer.rotate) * PI)/180);
        position.y -= 40 * cos(((m_positionPlayer.rotate) * PI)/180);

        bulletSword.setPosition(position);
        bulletSword.setTileBreak((m_objectWeapon->getWeaponTileBreak()));
        bulletSword.setDegat(m_objectWeapon->getDegat());
        m_bulletSword.push_back(bulletSword);

        std::cout<<"[INFORMATION]: [Player::shootSword] : creation d'une epee"<<std::endl;
    }

    /**
     * modifie l'arme en cours d'utilisation
     sf::RenderWindow &window
     * @access public
     * @return void
    */
    void Player::changeWeapon(sf::RenderWindow &window)
    {
        if(m_teleported == false) //le joueur ne peut pas changer d'arme quand il est en train d'etre teleporte
        {
            const sf::Input& Input = window.GetInput();

            if(((Input.IsJoystickButtonDown(0, 6) || Input.IsJoystickButtonDown(0, 2) || Input.IsMouseButtonDown(sf::Mouse::Middle) || Input.IsKeyDown(sf::Key::E)) && m_executionTime - m_lastChangeArme > 250))
            {
                m_lastChangeArme = m_executionTime;

                if(m_armeActive < (NUMBER_WEAPON_PLAYER-1)) //on change l'arme en allant à l'arme supérieur
                {
                    m_armeActive ++;
                }
                else //on reprend la première arme
                {
                    m_armeActive = 1;
                }

                switch(m_armeActive)
                {
                    case 1 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_1)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 1"<<std::endl;
                        }
                    break;

                    case 2 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_2)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 2"<<std::endl;
                        }
                    break;

                    case 3 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_3)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 3"<<std::endl;
                        }
                    break;

                    case 4 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_4)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 4"<<std::endl;
                        }
                    break;

                    case 5 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_5)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 5"<<std::endl;
                        }
                    break;

                    case 6 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_6)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 6"<<std::endl;
                        }
                    break;

                    case 7 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_7)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 7"<<std::endl;
                        }
                    break;

                    case 8 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_8)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 8"<<std::endl;
                        }
                    break;

                    case 9 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_9)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 9"<<std::endl;
                        }
                    break;

                    case 10 :
                        if (!m_imagePlayer.LoadFromFile(SPRITE_PLAYERS_WEAPON_10)) // Si le chargement du fichier a échoué
                        {
                            std::cout<<"[ERREUR]: [Player::changeWeapon] : impossible de charger le sprite player 10"<<std::endl;
                        }
                    break;
                }

                m_animPlayer.setSprite(&m_imagePlayer);
                m_objectWeapon = &m_objectWeapons[m_armeActive];
                m_sound.playSound(1, 50.f, false, m_positionPlayer, 512, 5, true);
            }
        }
    }

    /**
     * modifie la valeur de la vie restante du personnage
     * @param int life : vie
     * @access public
     * @return void
    */
    void Player::setLife(int life)
    {
        m_life = life;
    }

    /**
     * modifie le niveau du personnage
     * @param int level : niveau
     * @access public
     * @return void
    */
    void Player::setLevel(int level)
    {
        m_level = level;
    }

    /**
     * specifie si le joueur a gagne
     * @param bool win : gagne ou non
     * @access public
     * @return void
    */
    void Player::setWin(bool win)
    {
        m_win = win;
    }

    /**
     * modifie la position du joueur a l'ecran
     * @param PositionItem position : position à donner
     * @access public
     * @return void
    */
    void Player::setPosition(PositionItem position)
    {
        m_positionPlayer = position;
        m_positionNewPlayer = position;
    }

    /**
     * modifie la position x du joueur a l'ecran
     * @param float x
     * @access public
     * @return void
    */
    void Player::setPositionX(float x)
    {
        m_positionPlayer.x = x;
        m_positionNewPlayer.x = x;
    }

    /**
     * modifie la position y du joueur a l'ecran
     * @param flot y
     * @access public
     * @return void
    */
    void Player::setPositionY(float y)
    {
        m_positionPlayer.y = y;
        m_positionNewPlayer.y = y;
    }

    /**
     * specifie si le joueur est en train d'etre teleporte
     * @param bool teleported : teleporte ou non ?
     * @param PositionItem positionTo : position de teleportation
     * @param PositionItem positionTeleporteur : position du teleporteur
     * @access public
     * @return void
    */
    void Player::setTeleported(bool teleported, PositionItem positionTo, PositionItem positionTeleporteur, float coeff)
    {
        m_teleported = teleported;

        if(teleported == true)
        {
            m_positionTeleportationToPlayer = positionTo;
            m_positionTeleportationPlayer = positionTeleporteur;
            m_coeffTeleported = coeff;
        }
    }

    /**
     * modifie la vitesse du joueur
     * @param int speed : vitesse
     * @access public
     * @return void
    */
    void Player::setSpeed(int speed)
    {
        if(speed > 1)
        {
            m_speed = speed;
        }
    }

    /**
     * ajoute une carte dans l'inventaire du personnage, les cartes servent à ouvrir des portes
     * @param Object_Card objectCard : object de type carte
     * @access public
     * @return void
    */
    void Player::addCard(Object_Card objectCard)
    {
        m_objectsCard.push_back(objectCard);
    }

    /**
     * modifie l'arme du personnage
     * @param Object_Card objectCard : object de type carte
     * @access public
     * @return void
    */
    void Player::setWeapon(Object_Weapon objectWeapon, int id)
    {
        if(id >= 1 && id < NUMBER_WEAPON_PLAYER)
        {
            m_objectWeapons[id] = objectWeapon;
        }
    }

    /**
     * reremplie en entier la list des balles
     * @param std::list<Bullet_bullet> bullet : liste des balles
     * @access public
     * @return void
    */
    void Player::setBulletBullets(std::list<Bullet_bullet> bulletBullet)
    {
        m_bulletBullet = bulletBullet;
    }

    /**
     * reremplie en entier la list des balles
     * @param std::list<Bullet_mine> bullet : liste des balles
     * @access public
     * @return void
    */
    void Player::setBulletMines(std::list<Bullet_mine> bullet_mine)
    {
        m_bulletMine = bullet_mine;
    }

    /**
     * reremplie en entier la list des balles
     * @param std::list<Bullet_grenade> bullet : liste des balles
     * @access public
     * @return void
    */
    void Player::setBulletGrenades(std::list<Bullet_grenade> bullet_grenade)
    {
        m_bulletGrenade = bullet_grenade;
    }

    /**
     * reremplie en entier la list des balles
     * @param std::list<Bullet_flame> bullet : liste des balles
     * @access public
     * @return void
    */
    void Player::setBulletFlames(std::list<Bullet_flame> bullet_flame)
    {
        m_bulletFlame = bullet_flame;
    }

    /**
     * reremplie en entier la list des balles
     * @param std::list<Bullet_sword> bullet : liste des balles
     * @access public
     * @return void
    */
    void Player::setBulletSwords(std::list<Bullet_sword> bullet_sword)
    {
        m_bulletSword = bullet_sword;
    }

    /**
     * modifie le nombre de munitions d'une des armes du joueur
     * @param int weapon : id de l'arme (entre 1 et 10)
     * @param int munitions : nombre de munitions a rajouter
     * @access public
     * @return void
    */
    void Player::setMunitionsWeapon(int weapon, int munitions)
    {
        m_objectWeapons[weapon].setMunitions(m_objectWeapons[weapon].getMunitions() + munitions);
    }

    /**
     * retourne la quantite de vie du personnage
     * @access public
     * @return int
    */
    int Player::getLife()
    {
        return m_life;
    }

    /**
     * retourne le niveau du personnage
     * @access public
     * @return int
    */
    int Player::getLevel()
    {
        return m_level;
    }

    /**
     * retourne si le joueur a gagne ou non
     * @access public
     * @return int
    */
    bool Player::getWin()
    {
        return m_win;
    }

    /**
     * retourne la vitesse du personnage
     * @access public
     * @return int
    */
    int Player::getSpeed()
    {
        return m_speed;
    }

    /**
     * retourne la position du personnage
     * @access public
     * @return PositionItem
    */
    PositionItem Player::getPosition()
    {
        return m_positionPlayer;
    }

    /**
     * retourne la nouvelle position du personnage
     * @access public
     * @return PositionItem
    */
    PositionItem Player::getNewPosition()
    {
        return m_positionNewPlayer;
    }

    /**
     * retourne la liste des cartes du joueur
     * @access public
     * @return std::list<Object_Card>
    */
    std::list<Object_Card> * Player::getCards()
    {
        return &m_objectsCard;
    }

    /**
     * retourne l'arme du joueur
     * @access public
     * @return int
    */
    Object_Weapon * Player::getWeapon()
    {
        return m_objectWeapon;
    }

    /**
     * retourne l'arme du joueur d'id
     * @param int id : id de l'arme
     * @access public
     * @return int
    */
    Object_Weapon * Player::getWeaponId(int id)
    {
        return &m_objectWeapons[id];
    }

    /**
     * retourne la liste des balles tirées
     * @access public
     * @return std::list<Bullet_bullet>
    */
    std::list<Bullet_bullet> * Player::getBulletBullets()
    {
        return &m_bulletBullet;
    }

    /**
     * retourne la liste des balles tirées
     * @access public
     * @return int
    */
    std::list<Bullet_mine> * Player::getBulletMines()
    {
        return &m_bulletMine;
    }

    /**
     * retourne la liste des balles tirées
     * @access public
     * @return int
    */
    std::list<Bullet_grenade> * Player::getBulletGrenades()
    {
        return &m_bulletGrenade;
    }

    /**
     * retourne la liste des balles tirées
     * @access public
     * @return int
    */
    std::list<Bullet_flame> * Player::getBulletFlames()
    {
        return &m_bulletFlame;
    }

    /**
     * retourne la liste des balles tirées
     * @access public
     * @return int
    */
    std::list<Bullet_sword> * Player::getBulletSwords()
    {
        return &m_bulletSword;
    }

    /**
     * retourne si le joueur est en train d'etre teleporte
     * @access public
     * @return int
    */
    bool Player::getTeleported()
    {
        return m_teleported;
    }

    /**
     * convertit un int en string
     * @param int x : nombre
     * @access public
     * @return string
    */
    std::string Player::int2Str(int x)
    {
        std::stringstream type;
        type << x;
        return type.str();
    }

    /**
     * calcule la distance entre deux points
     * @param PositionItem p1 : point 1
     * @param PositionItem p2 : point 2
     * @access public
     * @return void
    */
    float Player::distance(const PositionItem p1, const PositionItem p2)
    {
        return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
    }

    /**
     * vide toutes les données (armes, cartes) du joueur
     * @access public
     * @return void
    */
    void Player::deleteContentPlayer()
    {
        m_objectsCard.clear();
        m_bulletBullet.clear();
        m_bulletFlame.clear();
        m_bulletGrenade.clear();
        m_bulletMine.clear();
        m_bulletSword.clear();

        m_armeActive = 1;
        m_objectWeapon = &m_objectWeapons[m_armeActive];
    }

    /**
     * desctructeur
     * @access public
     * @return void
    */
    Player::~Player()
    {

    }
