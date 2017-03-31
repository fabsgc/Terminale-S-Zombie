#include "physic.hpp"

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Physic::Physic()
    {
        m_timeLastCreateMessageErrorWinChangeLevel = 0;
        m_executionTime = 100000;
    }

    /**
	 * sachant que l'on ne travaille QUE avec des pointeurs, initialise les différents pointeurs vers tous les types d'objets à gérer
	 * @param Player * player : pointeur vers le joueur
	 * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::setPointerValue(Player * player, Map* map)
    {
        m_bullet_bullet = player->getBulletBullets(); //on copie la liste des balles
        m_bullet_flame = player->getBulletFlames(); //on copie la liste des balles
        m_bullet_grenade = player->getBulletGrenades(); //on copie la liste des balles
        m_bullet_mine = player->getBulletMines(); //on copie la liste des balles
        m_bullet_sword = player->getBulletSwords(); //on copie la liste des balles

        m_npc = map->getNpcs(); //on copie la liste des npc

        m_object_bonus = map->getObjectBonus();
        m_object_card = map->getObjectCard();
        m_object_door = map->getObjectDoor();
        m_object_malus = map->getObjectMalus();
        m_object_weapon = map->getObjectWeapon();
        m_object_teleportation = map->getObjectTeleportation();
        m_object_card_player = player->getCards();

        m_tilesWall = map->getTilesWall();
        m_tilesObjectFloor = map->getTilesObjectFloor();
        m_tilesObjectWall = map->getTilesObjectWall();
    }

    /**
	 * donne la taille et la hauteur de la fenetre : utile pour les messages
	 * @param int width : largeur
	 * @param int height : hauteur
	 * @access public
	 * @return void
    */
    void Physic::setWidthHeight(int width, int height)
    {
        m_guiMessage.setWidthHeight(width, height);
    }

    /**
	 * supprime les messages a l'ecran
	 * @access public
	 * @return void
    */
    void Physic::deleteMessage()
    {
        m_guiMessage.deleteMessage();
    }

    /**
	 * permet d'afficher les messages
	 * @access public
	 * @return void
    */
    void Physic::displayMessage(sf::RenderWindow &window, float deltaTime, PositionItem position)
    {
        m_guiMessage.display(window, deltaTime, position);
    }

    /**
	 * gère les evenements pour toutes les entités
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param Player * player : pointeur vers le joueur
	 * @param Map * map : pointeur vers la map
     * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
     * @param int actionCurrent : il est possible que la class modifie l'action : fin de niveau, fin de jeu, mort
	 * @access public
	 * @return int actionCurrent
    */
    int Physic::calculCollision(sf::RenderWindow &window, Player * player, Map * map, sf::View * view, float deltaTime, int actionCurrent)
    {
        m_executionTime += deltaTime*1000;

        this->setPointerValue(player, map);
        this->calculPositionPlayer(window, player, deltaTime);
        this->calculPositionNpc(window, map, deltaTime);
        this->calculPositionBulletBullet(window, player, deltaTime);
        this->calculPositionBulletFlame(window, player, deltaTime);
        this->calculPositionBulletGrenade(window, player, deltaTime);
        this->calculPositionBulletMine(window, player, deltaTime);
        this->calculPositionBulletSword(window, player, deltaTime);

        m_positionPlayer = player->getNewPosition();

        if(player->getTeleported() == false)
        {
            this->calculCollisionPlayerNpc(player, map, deltaTime);
            this->calculCollisionPlayerNpcAttack(player, map, deltaTime);
            this->calculCollisionPlayerBulletGrenade(player, map, deltaTime);
            this->calculCollisionPlayerBulletMine(player, map, deltaTime);
            this->calculCollisionPlayerObjectBonus(player, map);
            this->calculCollisionPlayerObjectCard(player, map);
            actionCurrent = this->calculCollisionPlayerObjectDoor(player, map, actionCurrent, deltaTime);
            this->calculCollisionPlayerObjectMalus(player, map);
            this->calculCollisionPlayerObjectWeapon(player, map);
            this->calculCollisionPlayerObjectTeleportation(player, map);
            this->calculCollisionPlayerTilesObjectFloor(player, map);
            this->calculCollisionPlayerTilesWall(player, map);
        }

        this->calculCollisionNpcBulletBullet(player, map, deltaTime);
        this->calculCollisionNpcBulletFlame(player, map, deltaTime);
        this->calculCollisionNpcBulletGrenade(player, map, deltaTime);
        this->calculCollisionNpcBulletMine(player, map, deltaTime);
        this->calculCollisionNpcBulletSword(player, map, deltaTime);
        this->calculCollisionNpcObjectDoor(player, map);
        this->calculCollisionNpcTilesObjectFloor(player, map);
        this->calculCollisionNpcTilesWall(player, map);
        this->calculCollisionBulletBulletTilesObjectFloor(player, map, deltaTime);
        this->calculCollisionBulletBulletTilesWall(player, map, deltaTime);
        this->calculCollisionBulletBulletObjectDoor(player, map, deltaTime);
        this->calculCollisionBulletFlameTilesObjectWall(player, map, deltaTime);
        this->calculCollisionBulletFlameTilesObjectFloor(player, map, deltaTime);
        this->calculCollisionBulletFlameTilesWall(player, map, deltaTime);
        this->calculCollisionBulletGrenadeTilesObjectWall(player, map, deltaTime);
        this->calculCollisionBulletGrenadeTilesObjectFloor(player, map, deltaTime);
        this->calculCollisionBulletGrenadeTilesWall(player, map, deltaTime);
        this->calculCollisionBulletGrenadeObjectDoor(player, map, deltaTime);
        this->calculCollisionBulletMineTilesObjectWall(player, map, deltaTime);
        this->calculCollisionBulletMineTilesObjectFloor(player, map, deltaTime);
        this->calculCollisionBulletMineTilesWall(player, map, deltaTime);
        this->calculCollisionBulletSwordTilesObjectWall(player, map, deltaTime);
        this->calculCollisionBulletSwordTilesObjectFloor(player, map, deltaTime);
        this->calculCollisionBulletSwordTilesWall(player, map, deltaTime);
        this->calculCollisionBulletSwordObjectDoor(player, map, deltaTime);

        this->calculOpenDoors(player, map);

        this->updatePositionPlayer(player);
        this->updatePositionNpc(map);
        this->updatePositionBulletBullet(player);
        this->updatePositionBulletFlame(player);
        this->updatePositionBulletGrenade(player);
        this->updatePositionBulletMine(player);
        this->updatePositionBulletSword(player);

        return actionCurrent;
    }

    /**
	 * calcul la nouvelle position du joueur
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param Player * player : pointeur vers le joueur
     * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return void
    */
    void Physic::calculPositionPlayer(sf::RenderWindow &window, Player * player, float deltaTime)
    {
        player->calculNewPosition(window, deltaTime);
    }

    /**
	 * calcul la nouvelle position des npc
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param Map* map : pointeur vers la map
     * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return void
    */
    void Physic::calculPositionNpc(sf::RenderWindow &window, Map* map, float deltaTime)
    {
        for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
        {
            it_npc->calculNewPosition(window, deltaTime);
        }
    }

    /**
	 * calcul la nouvelle position des balles type bullet
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param Player * player : pointeur vers le joueur
     * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return void
    */
    void Physic::calculPositionBulletBullet(sf::RenderWindow &window, Player * player, float deltaTime)
    {
        for(std::list<Bullet_bullet>::iterator it_bullet = m_bullet_bullet->begin(); it_bullet!= m_bullet_bullet->end(); ++it_bullet)
        {
            it_bullet->calculNewPosition(window, deltaTime);

            if(it_bullet->toOld() == true)
            {
                m_bullet_bullet->erase(it_bullet++);
            }
        }
    }

    /**
	 * calcul la nouvelle position des balles type flamme
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param Player * player : pointeur vers le joueur
     * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return void
    */
    void Physic::calculPositionBulletFlame(sf::RenderWindow &window, Player * player, float deltaTime)
    {
        for(std::list<Bullet_flame>::iterator it_bullet = m_bullet_flame->begin(); it_bullet!= m_bullet_flame->end(); ++it_bullet)
        {
            it_bullet->calculNewPosition(window, deltaTime);

            if(it_bullet->toOld() == true)
            {
                m_bullet_flame->erase(it_bullet++);
            }
        }
    }

    /**
	 * calcul la nouvelle position des balles type grenade
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param Player * player : pointeur vers le joueur
     * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return void
    */
    void Physic::calculPositionBulletGrenade(sf::RenderWindow &window, Player * player, float deltaTime)
    {
        for(std::list<Bullet_grenade>::iterator it_bullet = m_bullet_grenade->begin(); it_bullet!= m_bullet_grenade->end(); ++it_bullet)
        {
            it_bullet->calculNewPosition(window, deltaTime);

            if(it_bullet->toOld() == true)
            {
                m_bullet_grenade->erase(it_bullet++);
            }
        }
    }

    /**
	 * calcul la nouvelle position des balles type mine
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param Player * player : pointeur vers le joueur
     * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return void
    */
    void Physic::calculPositionBulletMine(sf::RenderWindow &window, Player * player, float deltaTime)
    {
        for(std::list<Bullet_mine>::iterator it_bullet = m_bullet_mine->begin(); it_bullet!= m_bullet_mine->end(); ++it_bullet)
        {
            it_bullet->calculNewPosition(window, deltaTime);

            if(it_bullet->toOld() == true)
            {
                m_bullet_mine->erase(it_bullet++);
            }
        }
    }

    /**
	 * calcul la nouvelle position des balles type sabre
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param Player * player : pointeur vers le joueur
     * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return void
    */
    void Physic::calculPositionBulletSword(sf::RenderWindow &window, Player * player, float deltaTime)
    {
        for(std::list<Bullet_sword>::iterator it_bullet = m_bullet_sword->begin(); it_bullet!= m_bullet_sword->end(); ++it_bullet)
        {
            it_bullet->calculNewPosition(window, deltaTime);

            if(it_bullet->toOld() == true)
            {
                m_bullet_sword->erase(it_bullet++);
            }
        }
    }

    /**
	 * calcul une collision entre joueur et npc
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerNpc(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
        {
            m_positionNpc = it_npc->getNewPosition();

            //on calcule la distance entre les milieux
            if( fabs(distance(m_positionPlayer, m_positionNpc)) < WIDTH_PLAYER_X)
            {
                player->prendreDegat((*it_npc), deltaTime);
            }
        }
    }

    /**
	 * calcul une collision entre joueur et npc, enfin, la zone de detection du NPC
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerNpcAttack(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
        {
            m_positionNpc = it_npc->getNewPosition();

            //on calcule la distance entre les milieux
            if( fabs(distance(m_positionPlayer, m_positionNpc)) < 512)
            {
            }
        }
    }

    /**
	 * calcul une collision entre joueur et grenade ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerBulletGrenade(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_grenade>::iterator it_bullet = m_bullet_grenade->begin(); it_bullet!=m_bullet_grenade->end(); ++it_bullet)
        {
            if(it_bullet->getExploded() == true)
            {
                m_positionBullet1 = it_bullet->getPosition();

                if(fabs(distance(m_positionBullet1, player->getPosition())) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                {
                    player->prendreDegatBullet(it_bullet->getDegat(), deltaTime, 350);

                    if(player->getLife() <= 0)
                    {
                        m_bullet_grenade->erase(it_bullet++);
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre joueur et mine ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerBulletMine(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_mine>::iterator it_bullet = m_bullet_mine->begin(); it_bullet!=m_bullet_mine->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();

            if(it_bullet->getActivated() == true)
            {
                if(it_bullet->getExploded() == true)
                {
                    if(fabs(distance(m_positionBullet1, player->getPosition())) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                    {
                        player->prendreDegatBullet(it_bullet->getDegat(), deltaTime, 350);

                        if(player->getLife() <= 0)
                        {
                            m_bullet_mine->erase(it_bullet++);
                        }
                    }
                }
                else if(it_bullet->getExploded() == false)
                {
                    if(fabs(distance(m_positionBullet1, player->getPosition())) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                    {
                        it_bullet->setExploded(true);
                    }
                }
            }
            else if(it_bullet->getActivated() == false) //on detecte l'eloignement du joueur
            {
                if(fabs(distance(m_positionBullet1, player->getPosition())) > (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                {
                    it_bullet->setActivated(true);
                }
            }
        }
    }

    /**
	 * calcul une collision entre joueur et bonus ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerObjectBonus(Player * player, Map* map)
    {
        for(std::list<Object_Bonus>::iterator it_object = m_object_bonus->begin(); it_object!=m_object_bonus->end(); ++it_object)
        {
            m_positionOther = it_object->getPosition();

            if(fabs(distance(m_positionPlayer, m_positionOther)) <= 8*WIDTH_PLAYER_X/10)
            {
                switch(it_object->getType())
                {
                    case BONUS_LIFE :
                        m_guiMessage.addMessage(TIME_MAX_MESSAGE, "Vous avez gagné " + int2Str(it_object->getValue()), "points de vie");
                        player->setLife(player->getLife() + it_object->getValue());
                    break;

                    case BONUS_SPEED :
                        m_guiMessage.addMessage(TIME_MAX_MESSAGE, "Vous avez gagné " + int2Str(it_object->getValue()), "points de vitesse");
                        player->setSpeed(player->getSpeed() + it_object->getValue());
                    break;

                    case BONUS_AMMUNITION :
                        m_guiMessage.addMessage(TIME_MAX_MESSAGE, "Vous avez gagné " + int2Str(it_object->getValue()), "munitions pour votre", player->getWeaponId(it_object->getArmeId())->getName());
                        player->setMunitionsWeapon(it_object->getArmeId(), it_object->getValue());
                    break;
                }

                m_sound.playSound(1, 80.f, false, m_positionPlayer);
                m_object_bonus->erase(it_object++);
            }
        }
    }

    /**
	 * calcul une collision entre joueur et carte ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerObjectCard(Player * player, Map* map)
    {
        for(std::list<Object_Card>::iterator it_object = m_object_card->begin(); it_object!=m_object_card->end(); ++it_object)
        {
            m_positionOther = it_object->getPosition();

            if(fabs(distance(m_positionPlayer, m_positionOther)) <= 8*WIDTH_PLAYER_X/10)
            {
                //on parcours les portes et on ouvre la bonne porte
                for(std::list<Object_Door>::iterator it_object_door = m_object_door->begin(); it_object_door!=m_object_door->end(); ++it_object_door)
                {
                    if(it_object_door->getId() == it_object->getId())
                    {
                        it_object_door->setOpen(true);

                        Node * node;

                        if(fabs(m_positionOther.rotate) == 0 ||  fabs(m_positionOther.rotate) == 180) //horizontale
                        {
                            node = &map->getMMap()->operator[](std::pair<int,int>(it_object_door->getPosition().x/64 - 0.5, it_object_door->getPosition().y/64));
                            node->setObstacle(false);
                            node = &map->getMMap()->operator[](std::pair<int,int>(it_object_door->getPosition().x/64 + 0.5, it_object_door->getPosition().y/64));
                            node->setObstacle(false);
                        }
                        else if(fabs(m_positionOther.rotate) == 90)//verticale
                        {
                            node = &map->getMMap()->operator[](std::pair<int,int>(it_object_door->getPosition().x/64, it_object_door->getPosition().y/64 - 0.5));
                            node->setObstacle(false);
                            node = &map->getMMap()->operator[](std::pair<int,int>(it_object_door->getPosition().x/64, it_object_door->getPosition().y/64 + 0.5));
                            node->setObstacle(false);
                        }

                        m_sound.playSound(11, 60.f, false, it_object_door->getPosition());
                    }
                }

                m_guiMessage.addMessage(TIME_MAX_MESSAGE, "Vous avez trouvé la ", "carte d'accès numéro " + int2Str(it_object->getId()));

                m_sound.playSound(1, 60.f, false, m_positionPlayer);
                player->addCard((*it_object));
                m_object_card->erase(it_object++);
            }
        }
    }

    /**
	 * calcul une collision entre joueur et porte ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return int
    */
    int Physic::calculCollisionPlayerObjectDoor(Player * player, Map* map, int actionCurrent, float deltaTime)
    {
        PositionItem point1, point2;

        for(std::list<Object_Door>::iterator it_object = m_object_door->begin(); it_object!=m_object_door->end(); ++it_object)
        {
            m_positionOther = it_object->getPosition();

            //les portes étants 2 fois plus larges, il faut les tester en les divisant par 2
            //les portes sont toujours à un angle de 0 ou 90 degres
            if(fabs(m_positionOther.rotate) == 0 ||  fabs(m_positionOther.rotate) == 180) //horizontale
            {
                point1.x = m_positionOther.x + WIDTH_OBJECT_DOOR_X/4;
                point1.y = m_positionOther.y;

                point2.x = m_positionOther.x - WIDTH_OBJECT_DOOR_X/4;
                point2.y = m_positionOther.y;
            }
            else if(fabs(m_positionOther.rotate) == 90)//verticale
            {
                point1.x = m_positionOther.x;
                point1.y = m_positionOther.y + WIDTH_OBJECT_DOOR_Y/4;

                point2.x = m_positionOther.x;
                point2.y = m_positionOther.y - WIDTH_OBJECT_DOOR_Y/4;
            }

            if(it_object->getOpen() == false) //on peut traverser l'objet ?
            {
                //ensuite, on fait les deux test de collision normaux
                if(fabs(distance(m_positionPlayer, point1)) <= WIDTH_PLAYER_X + 5)
                {
                    //on cherche à savoir quelle sera la meilleure position : HAUT,BAS,GAUCHE,DROITE
                    m_positionCollision[HAUT].x = m_positionPlayer.x;
                    m_positionCollision[HAUT].y = point1.y - WIDTH_SPRITE/2 - 32;

                    m_positionCollision[BAS].x = m_positionPlayer.x;
                    m_positionCollision[BAS].y = point1.y + WIDTH_SPRITE/2 + 32;

                    m_positionCollision[DROITE].x = point1.x + WIDTH_SPRITE/2 + 32;
                    m_positionCollision[DROITE].y = m_positionPlayer.y;

                    m_positionCollision[GAUCHE].x = point1.x - WIDTH_SPRITE/2 - 32;
                    m_positionCollision[GAUCHE].y = m_positionPlayer.y;

                    m_positionPlayer.x = m_positionCollision[lowDistance(m_positionPlayer)].x;
                    m_positionPlayer.y = m_positionCollision[lowDistance(m_positionPlayer)].y;

                    player->setPosition(m_positionPlayer);
                }
                else if(fabs(distance(m_positionPlayer, point2)) <= WIDTH_PLAYER_X + 5)
                {
                    //on cherche à savoir quelle sera la meilleure position : HAUT,BAS,GAUCHE,DROITE
                    m_positionCollision[HAUT].x = m_positionPlayer.x;
                    m_positionCollision[HAUT].y = point2.y - WIDTH_SPRITE/2 - 32;

                    m_positionCollision[BAS].x = m_positionPlayer.x;
                    m_positionCollision[BAS].y = point2.y + WIDTH_SPRITE/2 + 32;

                    m_positionCollision[DROITE].x = point2.x + WIDTH_SPRITE/2 + 32;
                    m_positionCollision[DROITE].y = m_positionPlayer.y;

                    m_positionCollision[GAUCHE].x = point2.x - WIDTH_SPRITE/2 - 32;
                    m_positionCollision[GAUCHE].y = m_positionPlayer.y;

                    m_positionPlayer.x = m_positionCollision[lowDistance(m_positionPlayer)].x;
                    m_positionPlayer.y = m_positionCollision[lowDistance(m_positionPlayer)].y;

                    player->setPosition(m_positionPlayer);
                }

            }
            else if(it_object->getOpen() == true)
            {
                if(fabs(distance(m_positionPlayer, point1)) <= WIDTH_PLAYER_X + 5 || fabs(distance(m_positionPlayer, point2)) <= WIDTH_PLAYER_X + 5)
                {
                    if(map->getNumberNpc() <= 12)
                    {
                        if(it_object->getChangeLevel() == true)
                        {
                             player->setLevel(player->getLevel()+1);
                        }

                        if(it_object->getWin() == true)
                        {
                            actionCurrent = WIN;
                        }
                    }
                    else
                    {
                        if(m_timeLastCreateMessageErrorWinChangeLevel < (m_executionTime - TIME_BETWEEN_CREATE_MESSAGE_ERROR_WINCHANGELEVEL) && (it_object->getWin() == true || it_object->getChangeLevel() == true))
                        {
                            m_timeLastCreateMessageErrorWinChangeLevel = m_executionTime;
                            m_guiMessage.addMessage(TIME_MAX_MESSAGE, "Il reste encore des", "zombies à tuer pour", "terminer");
                        }
                    }
                }
            }
        }

        return actionCurrent;
    }

    /**
	 * calcul une collision entre joueur et malus ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerObjectMalus(Player * player, Map* map)
    {
        for(std::list<Object_Malus>::iterator it_object = m_object_malus->begin(); it_object!=m_object_malus->end(); ++it_object)
        {
            m_positionOther = it_object->getPosition();

            if(fabs(distance(m_positionPlayer, m_positionOther)) <= 8*WIDTH_PLAYER_X/10)
            {
                switch(it_object->getType())
                {
                    case BONUS_LIFE :
                        m_guiMessage.addMessage(TIME_MAX_MESSAGE, "Vous avez perdu " + int2Str(it_object->getValue()), "points de vie");
                        player->setLife(player->getLife() - it_object->getValue());
                    break;

                    case BONUS_SPEED :
                        m_guiMessage.addMessage(TIME_MAX_MESSAGE, "Vous avez perdu " + int2Str(it_object->getValue()), "points de vitesse");
                        player->setSpeed(player->getSpeed() - it_object->getValue());
                    break;

                    case BONUS_AMMUNITION :
                        m_guiMessage.addMessage(TIME_MAX_MESSAGE, "Vous avez perdu " + int2Str(it_object->getValue()), "munitions pour votre", player->getWeaponId(it_object->getArmeId())->getName());
                        player->setMunitionsWeapon(it_object->getArmeId(), -it_object->getValue());
                    break;
                }

                m_sound.playSound(17, 40.f, false, m_positionPlayer);
                m_object_malus->erase(it_object++);
            }
        }
    }

    /**
	 * calcul une collision entre joueur et armes ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerObjectWeapon(Player * player, Map* map)
    {
        for(std::list<Object_Weapon>::iterator it_object = m_object_weapon->begin(); it_object!=m_object_weapon->end(); ++it_object)
        {
            m_positionOther = it_object->getPosition();

            if(fabs(distance(m_positionPlayer, m_positionOther)) <= 8*WIDTH_PLAYER_X/10)
            {
                m_sound.playSound(1, 40.f, false, m_positionPlayer);
                player->setMunitionsWeapon(it_object->getId(), it_object->getMunitions());
                m_guiMessage.addMessage(TIME_MAX_MESSAGE, "Vous avez gagné " + int2Str(it_object->getMunitions()), "munitions pour votre", it_object->getName());
                m_object_weapon->erase(it_object++);
            }
        }
    }

    /**
	 * calcul une collision entre joueur teleporteur ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerObjectTeleportation(Player * player, Map* map)
    {
        float coeff;

        for(std::list<Object_Teleportation>::iterator it_object = m_object_teleportation->begin(); it_object!=m_object_teleportation->end(); ++it_object)
        {
            m_positionOther = it_object->getPosition();

            if(fabs(distance(m_positionPlayer, m_positionOther)) <= 6*WIDTH_PLAYER_X/10)
            {
                coeff = (m_positionPlayer.y - it_object->getPositionTo().y)/(m_positionPlayer.x - it_object->getPositionTo().x);
                player->setTeleported(true, it_object->getPositionTo(), m_positionOther, coeff);

            }
        }
    }

    /**
	 * calcul une collision entre joueur et objet au sol ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerTilesObjectFloor(Player * player, Map* map)
    {
        for(std::list<Tiles>::iterator it_tile = m_tilesObjectFloor->begin(); it_tile!=m_tilesObjectFloor->end(); ++it_tile)
        {
            if(it_tile->getCollision() == true) //on peut traverser l'objet ?
            {
                m_positionOther = it_tile->getPosition();

                if(fabs(distance(m_positionPlayer, m_positionOther)) <= WIDTH_PLAYER_X + 5)
                {
                    //on cherche à savoir quelle sera la meilleure position : HAUT,BAS,GAUCHE,DROITE
                    m_positionCollision[HAUT].x = m_positionPlayer.x;
                    m_positionCollision[HAUT].y = m_positionOther.y - WIDTH_SPRITE/2 - 32;

                    m_positionCollision[BAS].x = m_positionPlayer.x;
                    m_positionCollision[BAS].y = m_positionOther.y + WIDTH_SPRITE/2 + 32;

                    m_positionCollision[DROITE].x = m_positionOther.x + WIDTH_SPRITE/2 + 32;
                    m_positionCollision[DROITE].y = m_positionPlayer.y;

                    m_positionCollision[GAUCHE].x = m_positionOther.x - WIDTH_SPRITE/2 - 32;
                    m_positionCollision[GAUCHE].y = m_positionPlayer.y;

                    m_positionPlayer.x = m_positionCollision[lowDistance(m_positionPlayer)].x;
                    m_positionPlayer.y = m_positionCollision[lowDistance(m_positionPlayer)].y;

                    player->setPosition(m_positionPlayer);
                }
            }
        }
    }

    /**
	 * calcul une collision entre joueur et bonus ######## FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionPlayerTilesWall(Player * player, Map* map)
    {
        m_positionPlayer = player->getPosition();

        int minimum_i = (m_positionPlayer.x - (256))/64;
        int maximum_i = (m_positionPlayer.x + (256))/64;

        int minimum_j = (m_positionPlayer.y - (256))/64;
        int maximum_j = (m_positionPlayer.y + (256))/64;

        std::map<std::pair<int, int>, Tiles>::iterator it;

        for(int i = minimum_i;i <= maximum_i;i++)
        {
            for(int j = minimum_j;j <= maximum_j;j++)
            {
                it = m_tilesWall->find(std::pair<int,int>(i,j));

                if(it!=m_tilesWall->end())
                {
                    if(it->second.getCollision() == true) //on peut traverser l'objet ?
                    {
                        m_positionOther = it->second.getPosition();

                        if(fabs(distance(m_positionPlayer, m_positionOther)) <= WIDTH_PLAYER_X + 5)
                        {
                            m_positionCollision[HAUT].x = m_positionPlayer.x;
                            m_positionCollision[HAUT].y = m_positionOther.y - WIDTH_PLAYER_X/2 - 38;

                            m_positionCollision[BAS].x = m_positionPlayer.x;
                            m_positionCollision[BAS].y = m_positionOther.y + WIDTH_PLAYER_X/2 + 38;

                            m_positionCollision[DROITE].x = m_positionOther.x + WIDTH_PLAYER_X/2 + 38;
                            m_positionCollision[DROITE].y = m_positionPlayer.y;

                            m_positionCollision[GAUCHE].x = m_positionOther.x - WIDTH_PLAYER_X/2 - 38;
                            m_positionCollision[GAUCHE].y = m_positionPlayer.y;

                            switch(lowDistance(m_positionPlayer))
                            {
                                case HAUT :
                                    player->setPositionY(m_positionCollision[HAUT].y);
                                break;

                                case BAS :
                                    player->setPositionY(m_positionCollision[BAS].y);
                                break;

                                case DROITE :
                                    player->setPositionX(m_positionCollision[DROITE].x);
                                break;

                                case GAUCHE :
                                    player->setPositionX(m_positionCollision[GAUCHE].x);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre npc et balle normales ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionNpcBulletBullet(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_bullet>::iterator it_bullet = m_bullet_bullet->begin(); it_bullet!=m_bullet_bullet->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();

            for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
            {
                m_positionNpc = it_npc->getPosition();

                if(fabs(distance(m_positionNpc, m_positionBullet1)) <= WIDTH_PLAYER_X / 2)
                {
                    it_npc->prendreDegat(it_bullet->getDegat(), deltaTime, 0);

                    if(it_npc->getLife()<= 0)
                    {
                        map->setNumberNpc(map->getNumberNpc() - 1);
                    }

                    m_bullet_bullet->erase(it_bullet++);
                    break;
                }
            }
        }
    }

    /**
	 * calcul une collision entre npc et flamme ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionNpcBulletFlame(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;

        for(std::list<Bullet_flame>::iterator it_bullet = m_bullet_flame->begin(); it_bullet!=m_bullet_flame->end(); ++it_bullet)
        {
            point1 = point2 = m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            point1.x -= WIDTH_BULLET_X_FLAME/4 * sin(((point1.rotate + 90) * PI)/180);
            point1.y -= WIDTH_BULLET_Y_FLAME/2 * cos(((point1.rotate + 90) * PI)/180);

            point2.x -= WIDTH_BULLET_X_FLAME/4 * sin(((point2.rotate - 90) * PI)/180);
            point2.y -= WIDTH_BULLET_Y_FLAME/2 * cos(((point2.rotate - 90) * PI)/180);

            for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
            {
                m_positionNpc = it_npc->getPosition();

                if(fabs(distance(point1, m_positionNpc)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_FLAME/4) || fabs(distance(point2, m_positionNpc)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_FLAME/4))
                {
                    it_npc->prendreDegat(it_bullet->getDegat(), deltaTime, 120);
                }
            }
        }
    }

    /**
	 * calcul une collision entre npc et grenade ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionNpcBulletGrenade(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_grenade>::iterator it_bullet = m_bullet_grenade->begin(); it_bullet!=m_bullet_grenade->end(); ++it_bullet)
        {
            if(it_bullet->getExploded() == true)
            {
                m_positionBullet1 = it_bullet->getPosition();
                m_weaponTileBreak = it_bullet->getTileBreak();

                for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
                {
                    m_positionNpc = it_npc->getPosition();

                    if(fabs(distance(m_positionBullet1, m_positionNpc)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                    {
                        it_npc->prendreDegat(it_bullet->getDegat(), deltaTime, 280);
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre npc et bonus ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionNpcBulletMine(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_mine>::iterator it_bullet = m_bullet_mine->begin(); it_bullet!=m_bullet_mine->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();

            for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
            {
                m_positionNpc = it_npc->getPosition();

                if(it_bullet->getActivated() == true)
                {
                    if(it_bullet->getExploded() == true)
                    {
                        if(fabs(distance(m_positionBullet1, m_positionNpc)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                        {
                            it_npc->prendreDegat(it_bullet->getDegat(), deltaTime, 350);
                        }
                    }
                    else if(it_bullet->getExploded() == false)
                    {
                        if(fabs(distance(m_positionBullet1, m_positionNpc)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                        {
                            it_bullet->setExploded(true);
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre npc et epee ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionNpcBulletSword(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;

        for(std::list<Bullet_sword>::iterator it_bullet = m_bullet_sword->begin(); it_bullet!=m_bullet_sword->end(); ++it_bullet)
        {
            point1 = point2 = m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            point1.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point1.rotate + 90) * PI)/180);
            point1.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point1.rotate + 90) * PI)/180);

            point2.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point2.rotate - 90) * PI)/180);
            point2.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point2.rotate - 90) * PI)/180);

            for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
            {
                m_positionNpc = it_npc->getPosition();

                if(fabs(distance(point1, m_positionNpc)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16) || fabs(distance(point2,m_positionNpc)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16))
                {
                    it_npc->prendreDegat(it_bullet->getDegat(), deltaTime, 850);
                }
            }
        }
    }

    /**
	 * calcul une collision entre npc et porte
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionNpcObjectDoor(Player * player, Map* map)
    {
        PositionItem point1, point2;

        for(std::list<Object_Door>::iterator it_object = m_object_door->begin(); it_object!=m_object_door->end(); ++it_object)
        {
            m_positionOther = it_object->getPosition();

            //les portes étants 2 fois plus larges, il faut les tester en les divisant par 2
            //les portes sont toujours à un angle de 0 ou 90 degres
            if(fabs(m_positionOther.rotate) == 0 ||  fabs(m_positionOther.rotate) == 180) //horizontale
            {
                point1.x = m_positionOther.x + WIDTH_OBJECT_DOOR_X/4;
                point1.y = m_positionOther.y;

                point2.x = m_positionOther.x - WIDTH_OBJECT_DOOR_X/4;
                point2.y = m_positionOther.y;
            }
            else if(fabs(m_positionOther.rotate) == 90)//verticale
            {
                point1.x = m_positionOther.x;
                point1.y = m_positionOther.y + WIDTH_OBJECT_DOOR_Y/4;

                point2.x = m_positionOther.x;
                point2.y = m_positionOther.y - WIDTH_OBJECT_DOOR_Y/4;
            }

            if(it_object->getOpen() == false) //on peut traverser l'objet ?
            {
                for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
                {
                    m_positionNpc = it_npc->getPosition();

                    //ensuite, on fait les deux test de collision normaux
                    if(fabs(distance(m_positionNpc, point1)) <= WIDTH_NPC_X)
                    {
                        //on cherche à savoir quelle sera la meilleure position : HAUT,BAS,GAUCHE,DROITE
                        m_positionCollision[HAUT].x = m_positionNpc.x;
                        m_positionCollision[HAUT].y = point1.y - WIDTH_SPRITE/2 - 32;

                        m_positionCollision[BAS].x = m_positionNpc.x;
                        m_positionCollision[BAS].y = point1.y + WIDTH_SPRITE/2 + 32;

                        m_positionCollision[DROITE].x = point1.x + WIDTH_SPRITE/2 + 32;
                        m_positionCollision[DROITE].y = m_positionNpc.y;

                        m_positionCollision[GAUCHE].x = point1.x - WIDTH_SPRITE/2 - 32;
                        m_positionCollision[GAUCHE].y = m_positionNpc.y;

                        m_positionNpc.x = m_positionCollision[lowDistance(m_positionNpc)].x;
                        m_positionNpc.y = m_positionCollision[lowDistance(m_positionNpc)].y;

                        it_npc->setPosition(m_positionNpc);
                    }
                    else if(fabs(distance(m_positionNpc, point2)) <= WIDTH_NPC_X)
                    {
                        //on cherche à savoir quelle sera la meilleure position : HAUT,BAS,GAUCHE,DROITE
                        m_positionCollision[HAUT].x = m_positionNpc.x;
                        m_positionCollision[HAUT].y = point2.y - WIDTH_SPRITE/2 - 32;

                        m_positionCollision[BAS].x = m_positionNpc.x;
                        m_positionCollision[BAS].y = point2.y + WIDTH_SPRITE/2 + 32;

                        m_positionCollision[DROITE].x = point2.x + WIDTH_SPRITE/2 + 32;
                        m_positionCollision[DROITE].y = m_positionNpc.y;

                        m_positionCollision[GAUCHE].x = point2.x - WIDTH_SPRITE/2 - 32;
                        m_positionCollision[GAUCHE].y = m_positionNpc.y;

                        m_positionNpc.x = m_positionCollision[lowDistance(m_positionNpc)].x;
                        m_positionNpc.y = m_positionCollision[lowDistance(m_positionNpc)].y;

                        it_npc->setPosition(m_positionNpc);
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre npc et objets sol
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionNpcTilesObjectFloor(Player * player, Map* map)
    {
        for(std::list<Tiles>::iterator it_tile = m_tilesObjectFloor->begin(); it_tile!=m_tilesObjectFloor->end(); ++it_tile)
        {
            if(it_tile->getCollision() == true) //on peut traverser l'objet ?
            {
                m_positionOther = it_tile->getPosition();

                for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
                {
                    m_positionNpc = it_npc->getPosition();

                    if(fabs(distance(m_positionNpc, m_positionOther)) < WIDTH_NPC_X)
                    {
                        //on cherche à savoir quelle sera la meilleure position : HAUT,BAS,GAUCHE,DROITE
                        m_positionCollision[HAUT].x = m_positionNpc.x;
                        m_positionCollision[HAUT].y = m_positionOther.y - WIDTH_SPRITE/2 - 32;

                        m_positionCollision[BAS].x = m_positionNpc.x;
                        m_positionCollision[BAS].y = m_positionOther.y + WIDTH_SPRITE/2 + 32;

                        m_positionCollision[DROITE].x = m_positionOther.x + WIDTH_SPRITE/2 + 32;
                        m_positionCollision[DROITE].y = m_positionNpc.y;

                        m_positionCollision[GAUCHE].x = m_positionOther.x - WIDTH_SPRITE/2 - 32;
                        m_positionCollision[GAUCHE].y = m_positionNpc.y;

                        m_positionNpc.x = m_positionCollision[lowDistance(m_positionNpc)].x;
                        m_positionNpc.y = m_positionCollision[lowDistance(m_positionNpc)].y;

                        it_npc->setPosition(m_positionNpc);
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre npc et sol
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionNpcTilesWall(Player * player, Map* map)
    {
        int minimum_i;
        int maximum_i;

        int minimum_j;
        int maximum_j;

        for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
        {
            m_positionNpc = it_npc->getPosition();

            minimum_i = (m_positionNpc.x - (128))/64;
            maximum_i = (m_positionNpc.x + (128))/64;

            minimum_j = (m_positionNpc.y - (128))/64;
            maximum_j = (m_positionNpc.y + (128))/64;

            std::map<std::pair<int, int>, Tiles>::iterator it;

            for(int i = minimum_i;i <= maximum_i;i++)
            {
                for(int j = minimum_j;j <= maximum_j;j++)
                {
                    it = m_tilesWall->find(std::pair<int,int>(i,j));

                    if(it!=m_tilesWall->end())
                    {
                        if(it->second.getCollision() == true) //on peut traverser l'objet ?
                        {
                            m_positionOther = it->second.getPosition();

                            if(fabs(distance(m_positionNpc, m_positionOther)) < WIDTH_NPC_X + 5)
                            {
                                //on cherche à savoir quelle sera la meilleure position : HAUT,BAS,GAUCHE,DROITE
                                m_positionCollision[HAUT].x = m_positionNpc.x;
                                m_positionCollision[HAUT].y = m_positionOther.y - WIDTH_SPRITE/2 - 40;

                                m_positionCollision[BAS].x = m_positionNpc.x;
                                m_positionCollision[BAS].y = m_positionOther.y + WIDTH_SPRITE/2 + 40;

                                m_positionCollision[DROITE].x = m_positionOther.x + WIDTH_SPRITE/2 + 40;
                                m_positionCollision[DROITE].y = m_positionNpc.y;

                                m_positionCollision[GAUCHE].x = m_positionOther.x - WIDTH_SPRITE/2 - 40;
                                m_positionCollision[GAUCHE].y = m_positionNpc.y;

                                switch(lowDistance(m_positionNpc))
                                {
                                    case HAUT :
                                        it_npc->setPositionY(m_positionCollision[HAUT].y);
                                    break;

                                    case BAS :
                                        it_npc->setPositionY(m_positionCollision[BAS].y);
                                    break;

                                    case DROITE :
                                        it_npc->setPositionX(m_positionCollision[DROITE].x);
                                    break;

                                    case GAUCHE :
                                        it_npc->setPositionX(m_positionCollision[GAUCHE].x);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre balle et objet du sol ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletBulletTilesObjectFloor(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_bullet>::iterator it_bullet = m_bullet_bullet->begin(); it_bullet!=m_bullet_bullet->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            for(std::list<Tiles>::iterator it_tile = m_tilesObjectFloor->begin(); it_tile!=m_tilesObjectFloor->end(); ++it_tile)
            {
                if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                {
                    m_positionOther = it_tile->getPosition();

                    if(fabs(distance(m_positionOther, m_positionBullet1)) <= WIDTH_PLAYER_X / 2 + 5)
                    {
                        for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                        {
                            if(it_tile->getId() == *it_int)
                            {
                                it_tile->prendreDegat(it_bullet->getDegat(), deltaTime, 0);
                                break;
                            }
                        }

                         m_bullet_bullet->erase(it_bullet++);
                         m_sound.playSound(16, 100.f, false, m_positionBullet1, 512, 5, true);
                         break;
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre balle et murs ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletBulletTilesWall(Player * player, Map* map, float deltaTime)
    {
        int minimum_i;
        int maximum_i;
        int minimum_j;
        int maximum_j;

        for(std::list<Bullet_bullet>::iterator it_bullet = m_bullet_bullet->begin(); it_bullet!=m_bullet_bullet->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();

            minimum_i = (m_positionBullet1.x - (128))/64;
            maximum_i = (m_positionBullet1.x + (128))/64;

            minimum_j = (m_positionBullet1.y - (128))/64;
            maximum_j = (m_positionBullet1.y + (128))/64;

            std::map<std::pair<int, int>, Tiles>::iterator it;

            for(int i = minimum_i;i <= maximum_i;i++)
            {
                for(int j = minimum_j;j <= maximum_j;j++)
                {
                    it = m_tilesWall->find(std::pair<int,int>(i,j));

                    if(it!=m_tilesWall->end())
                    {
                        m_positionOther = it->second.getPosition();

                        if(fabs(distance(m_positionOther, m_positionBullet1)) <= WIDTH_SPRITE / 2 + 5)
                        {
                            for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                            {
                                if(it->second.getId() == *it_int)
                                {
                                    it->second.prendreDegat(it_bullet->getDegat(), deltaTime, 0);
                                    break;
                                }
                            }

                            m_bullet_bullet->erase(it_bullet++);
                            m_sound.playSound(16, 100.f, false, m_positionBullet1, 512, 5, true);
                            break;
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre balle et portes ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletBulletObjectDoor(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;

        for(std::list<Bullet_bullet>::iterator it_bullet = m_bullet_bullet->begin(); it_bullet!=m_bullet_bullet->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();

            for(std::list<Object_Door>::iterator it_object = m_object_door->begin(); it_object!=m_object_door->end(); ++it_object)
            {
                m_positionOther = it_object->getPosition();

                //les portes étants 2 fois plus larges, il faut les tester en les divisant par 2
                //les portes sont toujours à un angle de 0 ou 90 degres
                if(fabs(m_positionOther.rotate) == 0 ||  fabs(m_positionOther.rotate) == 180) //horizontale
                {
                    point1.x = m_positionOther.x + WIDTH_OBJECT_DOOR_X/4;
                    point1.y = m_positionOther.y;

                    point2.x = m_positionOther.x - WIDTH_OBJECT_DOOR_X/4;
                    point2.y = m_positionOther.y;
                }
                else if(fabs(m_positionOther.rotate) == 90)//verticale
                {
                    point1.x = m_positionOther.x;
                    point1.y = m_positionOther.y + WIDTH_OBJECT_DOOR_Y/4;

                    point2.x = m_positionOther.x;
                    point2.y = m_positionOther.y - WIDTH_OBJECT_DOOR_Y/4;
                }

                if(it_object->getOpen() == false) //on peut traverser l'objet ?
                {
                    //ensuite, on fait les deux test de collision normaux
                    if(fabs(distance(m_positionBullet1, point1)) <= WIDTH_SPRITE/2 + 5 || fabs(distance(m_positionBullet1, point2)) <= WIDTH_SPRITE/2 + 5)
                    {
                        m_bullet_bullet->erase(it_bullet++);
                        m_sound.playSound(16, 100.f, false, m_positionBullet1, 512, 5, true);
                        break;
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre flammes et objet du mur #### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletFlameTilesObjectWall(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;

        for(std::list<Bullet_flame>::iterator it_bullet = m_bullet_flame->begin(); it_bullet!=m_bullet_flame->end(); ++it_bullet)
        {
            point1 = point2 = m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            point1.x -= WIDTH_BULLET_X_FLAME/4 * sin(((point1.rotate + 90) * PI)/180);
            point1.y -= WIDTH_BULLET_Y_FLAME/2 * cos(((point1.rotate + 90) * PI)/180);

            point2.x -= WIDTH_BULLET_X_FLAME/4 * sin(((point2.rotate - 90) * PI)/180);
            point2.y -= WIDTH_BULLET_Y_FLAME/2 * cos(((point2.rotate - 90) * PI)/180);

            for(std::list<Tiles>::iterator it_tile = m_tilesObjectWall->begin(); it_tile!=m_tilesObjectWall->end(); ++it_tile)
            {
                m_positionOther = it_tile->getPosition();

                if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                {
                    if(fabs(distance(point1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_FLAME/4 + 8) || fabs(distance(point2, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_FLAME/4 + 8))
                    {
                        for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                        {
                            if(it_tile->getId() == *it_int)
                            {
                                it_tile->prendreDegat(it_bullet->getDegat(), deltaTime, 150);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre flammes et objet du sol #### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletFlameTilesObjectFloor(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;

        for(std::list<Bullet_flame>::iterator it_bullet = m_bullet_flame->begin(); it_bullet!=m_bullet_flame->end(); ++it_bullet)
        {
            point1 = point2 = m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            point1.x -= WIDTH_BULLET_X_FLAME/4 * sin(((point1.rotate + 90) * PI)/180);
            point1.y -= WIDTH_BULLET_Y_FLAME/2 * cos(((point1.rotate + 90) * PI)/180);

            point2.x -= WIDTH_BULLET_X_FLAME/4 * sin(((point2.rotate - 90) * PI)/180);
            point2.y -= WIDTH_BULLET_Y_FLAME/2 * cos(((point2.rotate - 90) * PI)/180);

            for(std::list<Tiles>::iterator it_tile = m_tilesObjectFloor->begin(); it_tile!=m_tilesObjectFloor->end(); ++it_tile)
            {
                m_positionOther = it_tile->getPosition();

                if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                {
                    if(fabs(distance(point1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_FLAME/4 + 8) || fabs(distance(point2, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_FLAME/4 + 8))
                    {
                        for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                        {
                            if(it_tile->getId() == *it_int)
                            {
                                it_tile->prendreDegat(it_bullet->getDegat(), deltaTime, 150);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre flammes et murs #### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletFlameTilesWall(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;
        int minimum_i;
        int maximum_i;
        int minimum_j;
        int maximum_j;

        for(std::list<Bullet_flame>::iterator it_bullet = m_bullet_flame->begin(); it_bullet!=m_bullet_flame->end(); ++it_bullet)
        {
            point1 = point2 = m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            point1.x -= WIDTH_BULLET_X_FLAME/4 * sin(((point1.rotate + 90) * PI)/180);
            point1.y -= WIDTH_BULLET_Y_FLAME/2 * cos(((point1.rotate + 90) * PI)/180);

            point2.x -= WIDTH_BULLET_X_FLAME/4 * sin(((point2.rotate - 90) * PI)/180);
            point2.y -= WIDTH_BULLET_Y_FLAME/2 * cos(((point2.rotate - 90) * PI)/180);

            minimum_i = (m_positionBullet1.x - (128))/64;
            maximum_i = (m_positionBullet1.x + (128))/64;

            minimum_j = (m_positionBullet1.y - (128))/64;
            maximum_j = (m_positionBullet1.y + (128))/64;

            std::map<std::pair<int, int>, Tiles>::iterator it;

            for(int i = minimum_i;i <= maximum_i;i++)
            {
                for(int j = minimum_j;j <= maximum_j;j++)
                {
                    it = m_tilesWall->find(std::pair<int,int>(i,j));

                    if(it!=m_tilesWall->end())
                    {
                        m_positionOther = it->second.getPosition();

                        if(fabs(distance(point1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_FLAME/4 + 8) || fabs(distance(point2, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_FLAME/4 + 8))
                        {
                            for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                            {
                                if(it->second.getId() == *it_int)
                                {
                                    it->second.prendreDegat(it_bullet->getDegat(), deltaTime, 150);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre flammes et objet du mur #### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletGrenadeTilesObjectWall(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_grenade>::iterator it_bullet = m_bullet_grenade->begin(); it_bullet!=m_bullet_grenade->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            if(it_bullet->getExploded() == true)
            {
                for(std::list<Tiles>::iterator it_tile = m_tilesObjectWall->begin(); it_tile!=m_tilesObjectWall->end(); ++it_tile)
                {
                    m_positionOther = it_tile->getPosition();

                    if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                    {
                        if(fabs(distance(m_positionBullet1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_GRENADE/2))
                        {
                            for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                            {
                                if(it_tile->getId() == *it_int)
                                {
                                    it_tile->prendreDegat(it_bullet->getDegat(), deltaTime, 280);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre grenades objet du sol
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletGrenadeTilesObjectFloor(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_grenade>::iterator it_bullet = m_bullet_grenade->begin(); it_bullet!=m_bullet_grenade->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            if(it_bullet->getExploded() == true)
            {
                for(std::list<Tiles>::iterator it_tile = m_tilesObjectFloor->begin(); it_tile!=m_tilesObjectFloor->end(); ++it_tile)
                {
                    m_positionOther = it_tile->getPosition();

                    if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                    {
                        if(fabs(distance(m_positionBullet1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_GRENADE/2))
                        {
                            for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                            {
                                if(it_tile->getId() == *it_int)
                                {
                                    it_tile->prendreDegat(it_bullet->getDegat(), deltaTime, 280);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                for(std::list<Tiles>::iterator it_tile = m_tilesObjectFloor->begin(); it_tile!=m_tilesObjectFloor->end(); ++it_tile)
                {
                    m_positionOther = it_tile->getPosition();

                    if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                    {
                        if(fabs(distance(m_positionBullet1, m_positionOther)) <= (WIDTH_SPRITE/2 + 15))
                        {
                            it_bullet->setSpeed(0);
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre grenades et mur
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletGrenadeTilesWall(Player * player, Map* map, float deltaTime)
    {
        int minimum_i;
        int maximum_i;
        int minimum_j;
        int maximum_j;

        for(std::list<Bullet_grenade>::iterator it_bullet = m_bullet_grenade->begin(); it_bullet!=m_bullet_grenade->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();

            minimum_i = (m_positionBullet1.x - (256))/64;
            maximum_i = (m_positionBullet1.x + (256))/64;

            minimum_j = (m_positionBullet1.y - (256))/64;
            maximum_j = (m_positionBullet1.y + (256))/64;

            std::map<std::pair<int, int>, Tiles>::iterator it;

            if(it_bullet->getExploded() == true)
            {
                m_weaponTileBreak = it_bullet->getTileBreak();

                for(int i = minimum_i;i <= maximum_i;i++)
                {
                    for(int j = minimum_j;j <= maximum_j;j++)
                    {
                        it = m_tilesWall->find(std::pair<int,int>(i,j));

                        if(it!=m_tilesWall->end())
                        {
                            m_positionOther = it->second.getPosition();

                            if(it->second.getCollision() == true) //on peut traverser l'objet ?
                            {
                                if(fabs(distance(m_positionBullet1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                                {
                                    for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                                    {
                                        if(it->second.getId() == *it_int)
                                        {
                                            it->second.prendreDegat(it_bullet->getDegat(), deltaTime, 280);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                for(int i = minimum_i;i <= maximum_i;i++)
                {
                    for(int j = minimum_j;j <= maximum_j;j++)
                    {
                        it = m_tilesWall->find(std::pair<int,int>(i,j));

                        if(it!=m_tilesWall->end())
                        {
                            m_positionOther = it->second.getPosition();

                            if(it->second.getCollision() == true) //on peut traverser l'objet ?
                            {
                                if(fabs(distance(m_positionBullet1, m_positionOther)) <= (WIDTH_SPRITE/2 + 15))
                                {
                                    it_bullet->setSpeed(0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre balle et portes #### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletGrenadeObjectDoor(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;

        for(std::list<Bullet_grenade>::iterator it_bullet = m_bullet_grenade->begin(); it_bullet!=m_bullet_grenade->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();

            for(std::list<Object_Door>::iterator it_object = m_object_door->begin(); it_object!=m_object_door->end(); ++it_object)
            {
                m_positionOther = it_object->getPosition();

                //les portes étants 2 fois plus larges, il faut les tester en les divisant par 2
                //les portes sont toujours à un angle de 0 ou 90 degres
                if(fabs(m_positionOther.rotate) == 0 ||  fabs(m_positionOther.rotate) == 180) //horizontale
                {
                    point1.x = m_positionOther.x + WIDTH_OBJECT_DOOR_X/4;
                    point1.y = m_positionOther.y;

                    point2.x = m_positionOther.x - WIDTH_OBJECT_DOOR_X/4;
                    point2.y = m_positionOther.y;
                }
                else if(fabs(m_positionOther.rotate) == 90)//verticale
                {
                    point1.x = m_positionOther.x;
                    point1.y = m_positionOther.y + WIDTH_OBJECT_DOOR_Y/4;

                    point2.x = m_positionOther.x;
                    point2.y = m_positionOther.y - WIDTH_OBJECT_DOOR_Y/4;
                }

                if(it_object->getOpen() == false) //on peut traverser l'objet ?
                {
                    if(fabs(distance(m_positionBullet1, point1)) <= (WIDTH_SPRITE/2 + 15) || fabs(distance(m_positionBullet1, point2)) <= (WIDTH_SPRITE/2 + 15))
                    {
                        it_bullet->setSpeed(0);
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre mines et objets des murs ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletMineTilesObjectWall(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_mine>::iterator it_bullet = m_bullet_mine->begin(); it_bullet!=m_bullet_mine->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            if(it_bullet->getExploded() == true)
            {
                for(std::list<Tiles>::iterator it_tile = m_tilesObjectWall->begin(); it_tile!=m_tilesObjectWall->end(); ++it_tile)
                {
                    m_positionOther = it_tile->getPosition();

                    if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                    {
                        if(fabs(distance(m_positionBullet1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                        {
                            for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                            {
                                if(it_tile->getId() == *it_int)
                                {
                                    it_tile->prendreDegat(it_bullet->getDegat(), deltaTime, 280);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre mines et objets du sol ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletMineTilesObjectFloor(Player * player, Map* map, float deltaTime)
    {
        for(std::list<Bullet_mine>::iterator it_bullet = m_bullet_mine->begin(); it_bullet!=m_bullet_mine->end(); ++it_bullet)
        {
            m_positionBullet1 = it_bullet->getPosition();

            for(std::list<Tiles>::iterator it_tile = m_tilesObjectFloor->begin(); it_tile!=m_tilesObjectFloor->end(); ++it_tile)
            {
                m_positionOther = it_tile->getPosition();
                m_weaponTileBreak = it_bullet->getTileBreak();

                if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                {
                    if(it_bullet->getExploded() == true)
                    {
                        if(fabs(distance(m_positionBullet1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                        {
                            for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                            {
                                if(it_tile->getId() == *it_int)
                                {
                                    it_tile->prendreDegat(it_bullet->getDegat(), deltaTime, 280);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre mines et murs
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletMineTilesWall(Player * player, Map* map, float deltaTime)
    {
        int minimum_i;
        int maximum_i;
        int minimum_j;
        int maximum_j;

        for(std::list<Bullet_mine>::iterator it_bullet = m_bullet_mine->begin(); it_bullet!=m_bullet_mine->end(); ++it_bullet)
        {
            if(it_bullet->getExploded() == true)
            {
                m_positionBullet1 = it_bullet->getPosition();

                minimum_i = (m_positionBullet1.x - (256))/64;
                maximum_i = (m_positionBullet1.x + (256))/64;

                minimum_j = (m_positionBullet1.y - (256))/64;
                maximum_j = (m_positionBullet1.y + (256))/64;

                std::map<std::pair<int, int>, Tiles>::iterator it;

                for(int i = minimum_i;i <= maximum_i;i++)
                {
                    for(int j = minimum_j;j <= maximum_j;j++)
                    {
                        it = m_tilesWall->find(std::pair<int,int>(i,j));

                        if(it!=m_tilesWall->end())
                        {
                            if(it->second.getCollision() == true) //on peut traverser l'objet ?
                            {
                                m_positionOther = it->second.getPosition();

                                if(fabs(distance(m_positionBullet1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_MINE/2))
                                {
                                    for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                                    {
                                        if(it->second.getId() == *it_int)
                                        {
                                            it->second.prendreDegat(it_bullet->getDegat(), deltaTime, 280);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre epee et objets des murs ##### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletSwordTilesObjectWall(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;

        for(std::list<Bullet_sword>::iterator it_bullet = m_bullet_sword->begin(); it_bullet!=m_bullet_sword->end(); ++it_bullet)
        {
            point1 = point2 = m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            point1.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point1.rotate + 90) * PI)/180);
            point1.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point1.rotate + 90) * PI)/180);

            point2.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point2.rotate - 90) * PI)/180);
            point2.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point2.rotate - 90) * PI)/180);

            for(std::list<Tiles>::iterator it_tile = m_tilesObjectWall->begin(); it_tile!=m_tilesObjectWall->end(); ++it_tile)
            {
                m_positionOther = it_tile->getPosition();

                if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                {
                    if(fabs(distance(point1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16) || fabs(distance(point2, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16))
                    {
                        for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                        {
                            if(it_tile->getId() == *it_int)
                            {
                                it_tile->prendreDegat(it_bullet->getDegat(), deltaTime, 850);
                                break;
                            }
                        }

                        m_sound.playSound(21, 100.f, false, m_positionOther, 512, 5, true);
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre epee et objets du sol #### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletSwordTilesObjectFloor(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;

        for(std::list<Bullet_sword>::iterator it_bullet = m_bullet_sword->begin(); it_bullet!=m_bullet_sword->end(); ++it_bullet)
        {
            point1 = point2 = m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            point1.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point1.rotate + 90) * PI)/180);
            point1.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point1.rotate + 90) * PI)/180);

            point2.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point2.rotate - 90) * PI)/180);
            point2.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point2.rotate - 90) * PI)/180);

            for(std::list<Tiles>::iterator it_tile = m_tilesObjectFloor->begin(); it_tile!=m_tilesObjectFloor->end(); ++it_tile)
            {
                m_positionOther = it_tile->getPosition();

                if(it_tile->getCollision() == true) //on peut traverser l'objet ?
                {
                    if(fabs(distance(point1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16) || fabs(distance(point2, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16))
                    {
                        for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                        {
                            if(it_tile->getId() == *it_int)
                            {
                                it_tile->prendreDegat(it_bullet->getDegat(), deltaTime, 900);
                                break;
                            }
                        }

                        m_sound.playSound(21, 100.f, false, m_positionOther, 512, 5, true);
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre epee et mur #### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletSwordTilesWall(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2;
        int minimum_i;
        int maximum_i;
        int minimum_j;
        int maximum_j;

        for(std::list<Bullet_sword>::iterator it_bullet = m_bullet_sword->begin(); it_bullet!=m_bullet_sword->end(); ++it_bullet)
        {
            point1 = point2 = m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            minimum_i = (m_positionBullet1.x - (128))/64;
            maximum_i = (m_positionBullet1.x + (128))/64;

            minimum_j = (m_positionBullet1.y - (128))/64;
            maximum_j = (m_positionBullet1.y + (128))/64;

            point1.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point1.rotate + 90) * PI)/180);
            point1.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point1.rotate + 90) * PI)/180);

            point2.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point2.rotate - 90) * PI)/180);
            point2.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point2.rotate - 90) * PI)/180);

            std::map<std::pair<int, int>, Tiles>::iterator it;

            for(int i = minimum_i;i <= maximum_i;i++)
            {
                for(int j = minimum_j;j <= maximum_j;j++)
                {
                    it = m_tilesWall->find(std::pair<int,int>(i,j));

                    if(it!=m_tilesWall->end())
                    {
                        if(it->second.getCollision() == true) //on peut traverser l'objet ?
                        {
                            m_positionOther = it->second.getPosition();

                            if(fabs(distance(point1, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16) || fabs(distance(point2, m_positionOther)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16))
                            {
                                for(std::list<int>::iterator it_int = m_weaponTileBreak->begin(); it_int!=m_weaponTileBreak->end(); ++it_int)
                                {
                                    if(it->second.getId() == *it_int)
                                    {
                                        it->second.prendreDegat(it_bullet->getDegat(), deltaTime, 900);
                                        break;
                                    }
                                }

                                m_sound.playSound(21, 100.f, false, m_positionOther, 512, 5, true);
                            }
                        }
                    }
                }
            }
        }
    }

    /**
	 * calcul une collision entre balle et portes #### FAIT
	 * @param Player * player : pointeur vers le joueur
     * @param Map * map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::calculCollisionBulletSwordObjectDoor(Player * player, Map* map, float deltaTime)
    {
        PositionItem point1, point2, point3, point4;

        for(std::list<Bullet_sword>::iterator it_bullet = m_bullet_sword->begin(); it_bullet!=m_bullet_sword->end(); ++it_bullet)
        {
            point1 = point2 = m_positionBullet1 = it_bullet->getPosition();
            m_weaponTileBreak = it_bullet->getTileBreak();

            point1.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point1.rotate + 90) * PI)/180);
            point1.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point1.rotate + 90) * PI)/180);

            point2.x -= WIDTH_BULLET_X_SWORD/4 * sin(((point2.rotate - 90) * PI)/180);
            point2.y -= WIDTH_BULLET_Y_SWORD/2 * cos(((point2.rotate - 90) * PI)/180);

            for(std::list<Object_Door>::iterator it_object = m_object_door->begin(); it_object!=m_object_door->end(); ++it_object)
            {
                m_positionOther = it_object->getPosition();

                //les portes étants 2 fois plus larges, il faut les tester en les divisant par 2
                //les portes sont toujours à un angle de 0 ou 90 degres
                if(fabs(m_positionOther.rotate) == 0 ||  fabs(m_positionOther.rotate) == 180) //horizontale
                {
                    point3.x = m_positionOther.x + WIDTH_OBJECT_DOOR_X/4;
                    point3.y = m_positionOther.y;

                    point4.x = m_positionOther.x - WIDTH_OBJECT_DOOR_X/4;
                    point4.y = m_positionOther.y;
                }
                else if(fabs(m_positionOther.rotate) == 90)//verticale
                {
                    point3.x = m_positionOther.x;
                    point3.y = m_positionOther.y + WIDTH_OBJECT_DOOR_Y/4;

                    point4.x = m_positionOther.x;
                    point4.y = m_positionOther.y - WIDTH_OBJECT_DOOR_Y/4;
                }

                if(it_object->getOpen() == false) //on peut traverser l'objet ?
                {
                    if(fabs(distance(point1, point3)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16)
                       || fabs(distance(point1, point4)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16)
                       || fabs(distance(point2, point3)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16)
                       || fabs(distance(point2, point4)) <= (WIDTH_SPRITE/2 + WIDTH_BULLET_X_SWORD/4 + 16))
                    {
                        m_sound.playSound(21, 100.f, false, m_positionOther, 512, 5, true);
                    }
                }
            }
        }
    }

    /**
	 * met a jour la position du joueur #### FAIT
	 * @param Player * player : pointeur vers le joueur
	 * @access public
	 * @return void
    */
    void Physic::updatePositionPlayer(Player * player)
    {
        player->updatePosition();
    }

    /**
	 * met a jour la position des npc #### FAIT
	 * @param Map* map : pointeur vers la map
	 * @access public
	 * @return void
    */
    void Physic::updatePositionNpc(Map* map)
    {
        for(std::list<Npc>::iterator it_npc = m_npc->begin(); it_npc!=m_npc->end(); ++it_npc)
        {
            it_npc->updatePosition();
        }
    }

    /**
	 * met a jour la position des balles type bullet #### FAIT
	 * @param Player * player : pointeur vers le joueur
	 * @access public
	 * @return void
    */
    void Physic::updatePositionBulletBullet(Player * player)
    {
        for(std::list<Bullet_bullet>::iterator it_bullet = m_bullet_bullet->begin(); it_bullet!= m_bullet_bullet->end(); ++it_bullet)
        {
            it_bullet->updatePosition();
        }
    }

    /**
	 * met a jour la position des balles type flamme #### FAIT
	 * @param Player * player : pointeur vers le joueur
	 * @access public
	 * @return void
    */
    void Physic::updatePositionBulletFlame(Player * player)
    {
        for(std::list<Bullet_flame>::iterator it_bullet = m_bullet_flame->begin(); it_bullet!= m_bullet_flame->end(); ++it_bullet)
        {
            it_bullet->updatePosition();
        }
    }

    /**
	 * met a jour la position des balles type grenade #### FAIT
	 * @param Player * player : pointeur vers le joueur
	 * @access public
	 * @return void
    */
    void Physic::updatePositionBulletGrenade(Player * player)
    {
        for(std::list<Bullet_grenade>::iterator it_bullet = m_bullet_grenade->begin(); it_bullet!= m_bullet_grenade->end(); ++it_bullet)
        {
            it_bullet->updatePosition();
        }
    }

    /**
	 * met a jour la position des balles type mine #### FAIT
	 * @param Player * player : pointeur vers le joueur
	 * @access public
	 * @return void
    */
    void Physic::updatePositionBulletMine(Player * player)
    {
        for(std::list<Bullet_mine>::iterator it_bullet = m_bullet_mine->begin(); it_bullet!= m_bullet_mine->end(); ++it_bullet)
        {
            it_bullet->updatePosition();
        }
    }

    /**
	 * met a jour la position des balles type sabre #### FAIT
	 * @param Player * player : pointeur vers le joueur
	 * @access public
	 * @return void
    */
    void Physic::updatePositionBulletSword(Player * player)
    {
        for(std::list<Bullet_sword>::iterator it_bullet = m_bullet_sword->begin(); it_bullet!= m_bullet_sword->end(); ++it_bullet)
        {
            it_bullet->updatePosition();
        }
    }

    void Physic::calculOpenDoors(Player * player, Map* map)
    {
        //on parcourt la liste des portes
        for(std::list<Object_Door>::iterator it_object = m_object_door->begin(); it_object!=m_object_door->end(); ++it_object)
        {
            if(it_object->getOpen() == false)
            {
                //pour chaque porte, on parcourt la liste des cartes, on regarde si le joueur a la bonne carte pour ouvrir la porte
                for(std::list<Object_Card>::iterator it_object_card = m_object_card_player->begin(); it_object_card!=m_object_card_player->end(); ++it_object_card)
                {
                    if(it_object_card->getId() == it_object->getId())
                    {
                        it_object->setOpen(true);
                    }
                }
            }
        }
    }

    /**
	 * calcule la distance entre deux points #### FAIT
	 * @param PositionItem p1 : point 1
	 * @param PositionItem p2 : point 2
	 * @access public
	 * @return void
    */
    float Physic::distance(const PositionItem p1, const PositionItem p2)
    {
        return sqrt((pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2)));
    }

    /**
	 * calcule la plus petite distance entre la position actuelle et les positions possibles #### FAIT
	 * @param PositionItem p1 : point 1
	 * @param PositionItem p2 : point 2
	 * @access public
	 * @return void
    */
    int Physic::lowDistance(const PositionItem p1)
    {
        int distanceCollision[4];
        int small = HAUT;
        int i = 0;

        distanceCollision[HAUT] = distance(p1, m_positionCollision[HAUT]);
        distanceCollision[BAS] = distance(p1, m_positionCollision[BAS]);
        distanceCollision[DROITE] = distance(p1, m_positionCollision[DROITE]);
        distanceCollision[GAUCHE] = distance(p1, m_positionCollision[GAUCHE]);

        //parmi les 4 distances, on retrouve la plus petite
        for(i=1;i<4;i++)
        {
            if(distanceCollision[i] < distanceCollision[small])
            {
                small = i;
            }
        }

        return small;
    }

    /**
     * convertit un int en string
     * @param int x : nombre
     * @access public
     * @return string
    */
    std::string Physic::int2Str(int x)
    {
        std::stringstream type;
        type << x;
        return type.str();
    }

    /**
	 * desctructeur
	 * @access public
	 * @return void
    */
    Physic::~Physic()
    {

    }
