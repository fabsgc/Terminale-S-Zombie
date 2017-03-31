#include "map.hpp"

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Map::Map()
    {
        std::cout<<"[INFORMATION] : [Map::Map] : creation d'une map"<<std::endl;
        m_level = 0;
        m_lastLoadLevel = 0;
        m_executionTime = 0;
        m_initializedLevel = false;
        m_numberNpc = 0;

        if(!m_font.LoadFromFile(FONT_GUI))
        {
            std::cout<<"[ERREUR]: [Map::Map] : impossible de charger la police " << FONT_GUI <<std::endl;
        }

        //std::cout << m_map[std::pair<int,int>(0,0)].getX() << std::endl;
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayFloor(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        position = m_player->getPosition();

        int minimum_i = (position.x - (width/2 + 64))/64;
        int maximum_i = (position.x + (width/2 + 64))/64;

        int minimum_j = (position.y - (height/2 + 64))/64;
        int maximum_j = (position.y + (height/2 + 64))/64;

        //int k = 0;
        std::map<std::pair<int, int>, Tiles>::iterator it;

        for(int i = minimum_i;i <= maximum_i;i++)
        {
            for(int j = minimum_j;j <= maximum_j;j++)
            {
                it = m_tilesFloor.find(std::pair<int,int>(i,j));

                if(it!=m_tilesFloor.end())
                {
                    it->second.display(window, deltaTime);
                }
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayShadow(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        position = m_player->getPosition();

        int minimum_i = (position.x - (width/2 + 64))/64;
        int maximum_i = (position.x + (width/2 + 64))/64;

        int minimum_j = (position.y - (height/2 + 64))/64;
        int maximum_j = (position.y + (height/2 + 64))/64;

        //int k = 0;
        std::map<std::pair<int, int>, Tiles>::iterator it;

        for(int i = minimum_i;i <= maximum_i;i++)
        {
            for(int j = minimum_j;j <= maximum_j;j++)
            {
                it = m_tilesShadow.find(std::pair<int,int>(i,j));

                if(it!=m_tilesShadow.end())
                {
                    it->second.display(window, deltaTime);
                }
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayShadow2(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        position = m_player->getPosition();

        int minimum_i = (position.x - (width/2 + 64))/64;
        int maximum_i = (position.x + (width/2 + 64))/64;

        int minimum_j = (position.y - (height/2 + 64))/64;
        int maximum_j = (position.y + (height/2 + 64))/64;

        //int k = 0;
        std::map<std::pair<int, int>, Tiles>::iterator it;

        for(int i = minimum_i;i <= maximum_i;i++)
        {
            for(int j = minimum_j;j <= maximum_j;j++)
            {
                it = m_tilesShadow2.find(std::pair<int,int>(i,j));

                if(it!=m_tilesShadow2.end())
                {
                    it->second.display(window, deltaTime);
                }
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayLumiereJaune(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        position = m_player->getPosition();

        int minimum_i = (position.x - (width/2 + 64))/64;
        int maximum_i = (position.x + (width/2 + 64))/64;

        int minimum_j = (position.y - (height/2 + 64))/64;
        int maximum_j = (position.y + (height/2 + 64))/64;

        //int k = 0;
        std::map<std::pair<int, int>, Tiles>::iterator it;

        for(int i = minimum_i;i <= maximum_i;i++)
        {
            for(int j = minimum_j;j <= maximum_j;j++)
            {
                it = m_tilesLumiereJaune.find(std::pair<int,int>(i,j));

                if(it!=m_tilesLumiereJaune.end())
                {
                    it->second.display(window, deltaTime);
                }
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayWall(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        position = m_player->getPosition();

        int minimum_i = (position.x - (width/2 + 64))/64;
        int maximum_i = (position.x + (width/2 + 64))/64;

        int minimum_j = (position.y - (height/2 + 64))/64;
        int maximum_j = (position.y + (height/2 + 64))/64;

        //int k = 0;
        std::map<std::pair<int, int>, Tiles>::iterator it;

        for(int i = minimum_i;i <= maximum_i;i++)
        {
            for(int j = minimum_j;j <= maximum_j;j++)
            {
                it = m_tilesWall.find(std::pair<int,int>(i,j));

                if(it!=m_tilesWall.end())
                {
                    if(it->second.getLife() <= 0)
                    {
                        m_sound.playSound(15, 100.f, false, it->second.getPosition());

                        m_map[std::pair<int,int>(it->second.getPosition().x/64, it->second.getPosition().y/64)].setObstacle(false);
                        m_tilesWall.erase(it);
                    }
                    else
                    {
                        it->second.display(window, deltaTime);
                    }
                }
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayObjectFloor(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Tiles>::iterator it_tiles = m_tilesObjectFloor.begin(); it_tiles!=m_tilesObjectFloor.end(); ++it_tiles)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_tiles->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_tiles->getPosition().y)) < (height/2 + height/4))
            {
                if(it_tiles->getLife() <= 0)
                {
                    m_tilesObjectFloor.erase(it_tiles++);
                    m_sound.playSound(15, 100.f, false, it_tiles->getPosition());
                }
                else
                {
                    it_tiles->display(window, deltaTime);
                }
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayObjectWall(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Tiles>::iterator it_tiles = m_tilesObjectWall.begin(); it_tiles!=m_tilesObjectWall.end(); ++it_tiles)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_tiles->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_tiles->getPosition().y)) < (height/2 + height/4))
            {
                if(it_tiles->getLife() <= 0)
                {
                    m_tilesObjectWall.erase(it_tiles++);
                    m_sound.playSound(15, 100.f, false, it_tiles->getPosition());
                }
                else
                {
                    it_tiles->display(window, deltaTime);
                }
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayNpc(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Npc>::iterator it_npc = m_npc.begin(); it_npc!=m_npc.end(); ++it_npc)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_npc->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_npc->getPosition().y)) < (height/2 + height/4))
            {
                it_npc->display(window);
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayWeapon(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Object_Weapon>::iterator it_weapons = m_objectsWeapon.begin(); it_weapons!=m_objectsWeapon.end(); ++it_weapons)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_weapons->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_weapons->getPosition().y)) < (height/2 + height/4))
            {
                it_weapons->display(window);
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayTeleportation(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Object_Teleportation>::iterator it_teleportations = m_objectsTeleportation.begin(); it_teleportations!=m_objectsTeleportation.end(); ++it_teleportations)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_teleportations->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_teleportations->getPosition().y)) < (height/2 + height/4))
            {
                it_teleportations->display(window);
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayCard(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Object_Card>::iterator it_cards = m_objectsCard.begin(); it_cards!=m_objectsCard.end(); ++it_cards)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_cards->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_cards->getPosition().y)) < (height/2 + height/4))
            {
                it_cards->display(window);
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayDoor(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Object_Door>::iterator it_doors = m_objectsDoor.begin(); it_doors!=m_objectsDoor.end(); ++it_doors)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_doors->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_doors->getPosition().y)) < (height/2 + height/4))
            {
                it_doors->display(window);
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayBonus(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Object_Bonus>::iterator it_bonuss = m_objectsBonus.begin(); it_bonuss!=m_objectsBonus.end(); ++it_bonuss)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_bonuss->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_bonuss->getPosition().y)) < (height/2 + height/4))
            {
                it_bonuss->display(window);
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayMalus(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Object_Malus>::iterator it_maluss = m_objectsMalus.begin(); it_maluss!=m_objectsMalus.end(); ++it_maluss)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_maluss->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_maluss->getPosition().y)) < (height/2 + height/4))
            {
                it_maluss->display(window);
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayLight(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Light>::iterator it_lights = m_lights.begin(); it_lights!=m_lights.end(); ++it_lights)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_lights->getPosition().x)) < width && fabs(fabs(position.y) - fabs(it_lights->getPosition().y)) < height)
            {
                it_lights->display(window);
            }
        }
    }

    /**
     * affiche la map a l'ecran
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @access public
     * @return void
    */
    void Map::displayBlood(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime)
    {
        for(std::list<Tiles>::iterator it_tiles = m_tilesBlood.begin(); it_tiles!=m_tilesBlood.end(); ++it_tiles)
        {
            position = m_player->getPosition();

            if(fabs(fabs(position.x) - fabs(it_tiles->getPosition().x)) < (width/2 + width/4) && fabs(fabs(position.y) - fabs(it_tiles->getPosition().y)) < (height/2 + height/4))
            {
                it_tiles->display(window, deltaTime);
            }
        }
    }

    /**
     * charge la map a chaque changement de niveau. fonction a toujours appeler
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param int level : niveau a charger
     * @access public
     * @return bool
    */
    bool Map::initMap(sf::RenderWindow &window, int level, Player * player, float deltaTime)
    {
        m_executionTime+= deltaTime*1000;

        if(m_level != level) //si on a pas déjà chargé le niveau, on le charge
        {
            if(m_lastLoadLevel >= TIME_BETWEEN_LOADING) //chargement termine, on charge vraiment
            {
                m_lastLoadLevel = 0; //on remet le temps de chargement a 0
                m_initializedLevel = false;
                m_numberNpc = 0;
                this->deleteContentMap(); //on vide les infos de la map
                player->deleteContentPlayer(); //on vide les données du joueur

                m_level = level;
                TiXmlDocument doc("levels/level.xml");
                int entier, i = 1, x1, y1, x2, y2;
                int id, rotation;
                bool collision, open;
                PositionItem position;

                if(doc.LoadFile()){
                    std::cout << "[INFORMATION] : [Map::initMap] chargement de \"level/level.xml\"" << std::endl;

                    TiXmlHandle hdl(&doc);
                    TiXmlElement *elem = hdl.FirstChildElement().Element();

                    if(!elem)
                    {
                        std::cout << "[ERREUR] : [Map::initMap] : le noeud levels n'existe pas" << std::endl;
                        window.Close();
                    }
                    else
                    {
                        while(elem)
                        {
                            elem->QueryIntAttribute("id", &entier);

                            if(entier == m_level)
                            {
                                elem->QueryFloatAttribute("positionx", &position.x);
                                elem->QueryFloatAttribute("positiony", &position.y);
                                elem->QueryFloatAttribute("rotate", &position.rotate);
                                elem->QueryIntAttribute("speed", &entier);
                                player->setPosition(position);
                                player->setSpeed(entier);
                                elem->QueryIntAttribute("life", &entier);
                                player->setLife(entier);

                                TiXmlHandle sousHdl(elem);
                                TiXmlElement *sousElem = sousHdl.FirstChildElement().Element();

                                if(!sousElem){
                                    std::cout << "[ERREUR] : [Map::initMap] : les enfants de levels n'existent pas" << std::endl;
                                    window.Close();
                                }
                                else
                                {
                                    while(sousElem)
                                    {
                                        TiXmlHandle sousSousHdl(sousElem);
                                        TiXmlElement *sousSousElem = sousSousHdl.FirstChildElement().Element();

                                        switch(i)
                                        {
                                            case 1 : //les portes
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de doors" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryFloatAttribute("rotation", &position.rotate);

                                                        sousSousElem->QueryIntAttribute("open", &entier);

                                                        if(entier == 1)
                                                        {
                                                            open = true;
                                                        }
                                                        else
                                                        {
                                                            /* ## on cree la map qui servira au A* ## */
                                                            if(position.rotate == 0)
                                                            {
                                                                m_map[std::make_pair(position.x - 0.5, position.y)].setObstacle(true);
                                                                m_map[std::make_pair(position.x + 0.5, position.y)].setObstacle(true);

                                                                m_map[std::make_pair(position.x - 0.5, position.y)].setParent(position.x - 0.5, position.y);
                                                                m_map[std::make_pair(position.x + 0.5, position.y)].setParent(position.x + 0.5, position.y);

                                                                m_map[std::make_pair(position.x - 0.5, position.y)].setX(position.x - 0.5);
                                                                m_map[std::make_pair(position.x - 0.5, position.y)].setY(position.y);
                                                                m_map[std::make_pair(position.x + 0.5, position.y)].setX(position.x + 0.5);
                                                                m_map[std::make_pair(position.x + 0.5, position.y)].setY(position.y);
                                                            }
                                                            else if(position.rotate == 90)
                                                            {
                                                                m_map[std::make_pair(position.x, position.y - 0.5)].setObstacle(true);
                                                                m_map[std::make_pair(position.x, position.y + 0.5)].setObstacle(true);

                                                                m_map[std::make_pair(position.x, position.y - 0.5)].setParent(position.x, position.y - 0.5);
                                                                m_map[std::make_pair(position.x, position.y + 0.5)].setParent(position.x, position.y + 0.5);

                                                                m_map[std::make_pair(position.x, position.y - 0.5)].setX(position.x);
                                                                m_map[std::make_pair(position.x, position.y - 0.5)].setY(position.y - 0.5);
                                                                m_map[std::make_pair(position.x, position.y + 0.5)].setX(position.x);
                                                                m_map[std::make_pair(position.x, position.y + 0.5)].setY(position.y + 0.5);
                                                            }

                                                            open = false;
                                                        }

                                                        position.x*=64;
                                                        position.y*=64;

                                                        m_objectsDoor.push_back(this->initDoor(window, id, position, open));

                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 2 : //les armes
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de weapons" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);

                                                        position.x*=64;
                                                        position.y*=64;

                                                        m_objectsWeapon.push_back(this->initWeapon(window, id, position));

                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 3 : //les cartes
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de cards" << std::endl;
                                                    window.Close();
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);

                                                        position.x*=64;
                                                        position.y*=64;

                                                        m_objectsCard.push_back(this->initCard(window, id, position));

                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 4 : //les npc
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de npc" << std::endl;
                                                    window.Close();
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);

                                                        position.x*=64;
                                                        position.y*=64;

                                                        npc = this->initNpc(window, id, position);

                                                        sousSousElem->QueryIntAttribute("startx", &x1);
                                                        sousSousElem->QueryIntAttribute("starty", &y1);
                                                        npc.setNodeStartAstar(x1, y1);

                                                        sousSousElem->QueryIntAttribute("endx", &x2);
                                                        sousSousElem->QueryIntAttribute("endy", &y2);
                                                        npc.setNodeEndAstar(x2, y2);

                                                        m_npc.push_back(npc);
                                                        m_numberNpc++;

                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 5 : //les bonus
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de bonus" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        this->initBonus(window, sousSousElem);
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 6 : //les malus
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de malus" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        this->initMalus(window, sousSousElem);
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 7 : //les teleporteurs
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de teleporteurs" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryIntAttribute("rotation", &rotation);

                                                        position.x*=64;
                                                        position.y*=64;
                                                        position.rotate = rotation;

                                                        m_objectsTeleportation.push_back(this->initTeleportation(window, id, position));

                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 8 : //les lampes
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de lampes" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryIntAttribute("rotation", &rotation);

                                                        position.rotate = rotation;

                                                        light.setId(id);
                                                        light.setPosition(position);
                                                        m_lights.push_back(light);
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 9 : //les tiles floor
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de tiles floor" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryIntAttribute("rotation", &rotation);
                                                        sousSousElem->QueryIntAttribute("collision", &entier);

                                                        if(m_map[std::make_pair(position.x, position.y)].getObstacle() != true)
                                                        {
                                                            m_map[std::make_pair(position.x, position.y)].setObstacle(false);
                                                            m_map[std::make_pair(position.x, position.y)].setParent(position.x, position.y);
                                                            m_map[std::make_pair(position.x, position.y)].setX(position.x);
                                                            m_map[std::make_pair(position.x, position.y)].setY(position.y);
                                                        }

                                                        position.x*=64;
                                                        position.y*=64;
                                                        position.rotate = rotation;

                                                        if(entier == 0)
                                                        {
                                                            collision = false;
                                                        }
                                                        else
                                                        {
                                                            collision = true;
                                                        }

                                                        tile.initTile(collision, id, position);
                                                        m_tilesFloor.insert(std::make_pair(std::make_pair(position.x/64, position.y/64), tile));
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 10 : //les tiles des murs
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de tiles wall" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryIntAttribute("rotation", &rotation);
                                                        sousSousElem->QueryIntAttribute("collision", &entier);

                                                        /* ## on cree la map qui servira au A* ## */
                                                        m_map[std::make_pair(position.x, position.y)].setObstacle(true);
                                                        m_map[std::make_pair(position.x, position.y)].setParent(position.x, position.y);
                                                        m_map[std::make_pair(position.x, position.y)].setX(position.x);
                                                        m_map[std::make_pair(position.x, position.y)].setY(position.y);

                                                        position.x*=64;
                                                        position.y*=64;
                                                        position.rotate = rotation;

                                                        if(entier == 0)
                                                        {
                                                            collision = false;
                                                        }
                                                        else
                                                        {
                                                            collision = true;
                                                        }

                                                        tile.initTile(collision, id, position);
                                                        m_tilesWall.insert(std::make_pair(std::make_pair(position.x/64, position.y/64), tile));
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 11 : //les tiles des objets
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de tiles object floor" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryIntAttribute("rotation", &rotation);
                                                        sousSousElem->QueryIntAttribute("collision", &entier);

                                                        position.x*=64;
                                                        position.y*=64;
                                                        position.rotate = rotation;

                                                        if(entier == 0)
                                                        {
                                                            collision = false;
                                                        }
                                                        else //on ne peut pas passer au travers
                                                        {
                                                            /* ## on cree la map qui servira au A* ## */
                                                            m_map[std::make_pair(position.x, position.y)].setObstacle(true);
                                                            m_map[std::make_pair(position.x, position.y)].setParent(position.x, position.y);

                                                            collision = true;
                                                        }

                                                        tile.initTile(collision, id, position);
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                        m_tilesObjectFloor.push_back(tile);
                                                    }
                                                }
                                            break;

                                            case 12 : //les tiles des objets des murs
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de tiles objectWall" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryIntAttribute("rotation", &rotation);
                                                        sousSousElem->QueryIntAttribute("collision", &entier);

                                                        position.x*=64;
                                                        position.y*=64;
                                                        position.rotate = rotation;

                                                        if(entier == 0)
                                                        {
                                                            collision = false;
                                                        }
                                                        else
                                                        {
                                                            collision = true;
                                                        }

                                                        tile.initTile(collision, id, position);
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                        m_tilesObjectWall.push_back(tile);
                                                    }
                                                }
                                            break;

                                            case 13 : //les tiles shadow
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de tiles shadow" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryIntAttribute("rotation", &rotation);
                                                        sousSousElem->QueryIntAttribute("collision", &entier);

                                                        position.x*=64;
                                                        position.y*=64;
                                                        position.rotate = rotation;

                                                        if(entier == 0)
                                                        {
                                                            collision = false;
                                                        }
                                                        else
                                                        {
                                                            collision = true;
                                                        }

                                                        tile.initTile(collision, id, position);
                                                        m_tilesShadow.insert(std::make_pair(std::make_pair(position.x/64, position.y/64), tile));
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 14 : //les tiles shadow2
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de tiles shadow" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryIntAttribute("rotation", &rotation);
                                                        sousSousElem->QueryIntAttribute("collision", &entier);

                                                        position.x*=64;
                                                        position.y*=64;
                                                        position.rotate = rotation;

                                                        if(entier == 0)
                                                        {
                                                            collision = false;
                                                        }
                                                        else
                                                        {
                                                            collision = true;
                                                        }

                                                        tile.initTile(collision, id, position);
                                                        m_tilesShadow2.insert(std::make_pair(std::make_pair(position.x/64, position.y/64), tile));
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 15 : //les tiles shadow
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de tiles shadow" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        sousSousElem->QueryIntAttribute("id", &id);
                                                        sousSousElem->QueryFloatAttribute("positionx", &position.x);
                                                        sousSousElem->QueryFloatAttribute("positiony", &position.y);
                                                        sousSousElem->QueryIntAttribute("rotation", &rotation);
                                                        sousSousElem->QueryIntAttribute("collision", &entier);

                                                        position.x*=64;
                                                        position.y*=64;
                                                        position.rotate = rotation;

                                                        if(entier == 0)
                                                        {
                                                            collision = false;
                                                        }
                                                        else
                                                        {
                                                            collision = true;
                                                        }

                                                        tile.initTile(collision, id, position);
                                                        m_tilesLumiereJaune.insert(std::make_pair(std::make_pair(position.x/64, position.y/64), tile));
                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;

                                            case 16 :
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas de d'armes pour le joueur" << std::endl;
                                                }
                                                else
                                                {
                                                    int j = 1;
                                                    while(sousSousElem)
                                                    {
                                                        std::cout << "[INFORMATION] : [Map::initMap] : weapon id : " << sousSousElem->Attribute("id") << std::endl;
                                                        sousSousElem->QueryIntAttribute("id", &entier);

                                                        player->setWeapon(this->initWeapon(window, entier, position), j);

                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                        j++;
                                                    }
                                                }
                                            break;

                                            case 17 :
                                                if(!sousSousElem){
                                                    std::cout << "[ERREUR] : [Map::initMap] : il n'y a pas d'objets pour le joueur" << std::endl;
                                                }
                                                else
                                                {
                                                    while(sousSousElem)
                                                    {
                                                        std::cout << "[INFORMATION] : [Map::initMap] : card id : " << sousSousElem->Attribute("id") << std::endl;
                                                        sousSousElem->QueryIntAttribute("type", &entier);

                                                        if(entier == 1) //carte
                                                        {
                                                            sousSousElem->QueryIntAttribute("id", &entier);
                                                            player->addCard(this->initCard(window, entier, position));
                                                        }

                                                        sousSousElem = sousSousElem->NextSiblingElement(); // iteration
                                                    }
                                                }
                                            break;
                                        }
                                        i++;
                                        sousElem = sousElem->NextSiblingElement(); // iteration
                                    }
                                }
                                break; // on a trouve le niveau, on stop la première boucle
                            }
                            else
                            {
                                std::cout << "[ERREUR] : [Map::initMap] niveau introuvable " << std::endl;
                            }

                            elem = elem->NextSiblingElement(); // iteration
                        }
                    }
                }
                else
                {
                    std::cout << "[ERREUR] : [Map::initMap] chargement impossible de \"levels/level.xml\" : " << std::endl;
                    std::cout << "\t error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
                    window.Close();
                }

                return true;
            }
            else //on affiche le nom du niveau
            {
                m_lastLoadLevel+=deltaTime*1000;

                if(m_initializedLevel == false) //on a pas encore le nom du niveau
                {
                    TiXmlDocument doc("levels/level.xml");
                    TiXmlHandle hdl(&doc);
                    int entier;

                    if(doc.LoadFile())
                    {
                        m_initializedLevel = true;
                        TiXmlElement *elem = hdl.FirstChildElement().Element();
                        std::cout << "[INFORMATION] : [Map::initMap] sdklsd chargement de \"level/level.xml\"" << std::endl;

                        if(!elem)
                        {
                            std::cout << "[ERREUR] : [Map::initMap] : le noeud levels n'existe pas" << std::endl;
                            window.Close();
                        }
                        else
                        {
                            while(elem)
                            {
                                elem->QueryIntAttribute("id", &entier);

                                if(entier == level)
                                {
                                    m_nameLevel = elem->Attribute("name");
                                    break;
                                }
                                else
                                {
                                    elem = elem->NextSiblingElement(); // iteration
                                }
                            }
                        }
                    }
                    else
                    {
                        std::cout << "[ERREUR] : [Map::initMap] chargement impossible de \"levels/level.xml\" : " << std::endl;
                        std::cout << "\t error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
                        window.Close();
                    }
                }

                m_textNameLevel.SetFont(m_font); // Fonte
                m_textNameLevel.SetSize(45); // Taille de police
                m_textNameLevel.SetStyle(sf::String::Bold);
                m_textNameLevel.SetPosition(sf::Vector2f(45, 25)); // Positionnement*/
                m_textNameLevel.SetText(m_nameLevel); // Texte
                window.Draw(m_textNameLevel);

                return false;
            }
        }

        return true;
    }

    /**
     * reremplie en entier la list des npc
     * @param std::list<Npc> npcs : liste des npc
     * @access public
     * @return void
    */
    void Map::setNpcs(std::list<Npc> npcs)
    {
        m_npc = npcs;
    }

    /**
     * modifie le numero du niveau
     * @param int level : niveau
     * @access public
     * @return void
    */
    void Map::setLevel(int level)
    {
        m_level = level;
    }

    /**
     * configure un npc
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param PositionItem position : position du npc
     * @param int id : id l'arme
     * @access public
     * @return Npc
    */
    Npc Map::initNpc(sf::RenderWindow &window, int id, PositionItem position)
    {
        int entier;
        TiXmlDocument doc("config/npc_config.xml");
        object_Weapon.setPosition(position);

        if(doc.LoadFile()){
            std::cout << "[INFORMATION] : [Map::initNpc] chargement de \"config/npc_config.xml\"" << std::endl;

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

            if(!elem){
                std::cout << "[ERREUR] : [Map::initNpc] : le noeud npc n'existe pas" << std::endl;
                window.Close();
            }
            else
            {
                while (elem){
                    elem->QueryIntAttribute("id", &entier);
                    std::cout << "[INFORMATION] : [Map::initWeapon] npc : " << entier << std::endl;

                    if(entier == id)
                    {
                        npc.setId(id);

                        elem->QueryIntAttribute("degat", &entier);
                        npc.setDegat(entier);

                        elem->QueryIntAttribute("life", &entier);
                        npc.setLife(entier);

                        elem->QueryIntAttribute("speed", &entier);
                        npc.setSpeed(entier);

                        elem->QueryIntAttribute("type", &entier);
                        npc.setTypeSprite(entier);

                        npc.setSprite(elem->Attribute("sprite"));

                        npc.setPosition(position);

                        npc.setMapAstar(&m_map);

                        break;
                    }

                    elem = elem->NextSiblingElement(); // iteration
                }
            }
        }
        else
        {
            std::cout << "[ERREUR] : [Map::initNpc] chargement impossible de \"config/npc_config.xml\" : " << std::endl;
            std::cout << "\t error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
            window.Close();
        }

        return npc;
    }

    /**
     * configure une arme
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param int id : id l'arme
     * @param PositionItem position : position
     * @access public
     * @return Object_Weapon
    */
    Object_Weapon Map::initWeapon(sf::RenderWindow &window, int id, PositionItem position)
    {
        int entier;
        TiXmlDocument doc("config/weapon_config.xml");
        object_Weapon.setPosition(position);

        if(doc.LoadFile())
        {
            std::cout << "[INFORMATION] : [Map::initWeapon] chargement de \"config/weapon_config.xml\"" << std::endl;

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

            if(!elem){
                std::cout << "[ERREUR] : [Map::initWeapon] : le noeud weapon n'existe pas" << std::endl;
                window.Close();
            }
            else
            {
                while (elem){
                    elem->QueryIntAttribute("id", &entier);
                    std::cout << "[INFORMATION] : [Map::initWeapon] weapon : " << entier << std::endl;

                    if(entier == id)
                    {
                        object_Weapon.setId(id);

                        elem->QueryIntAttribute("degat", &entier);
                        object_Weapon.setDegat(entier);

                        elem->QueryIntAttribute("cadence", &entier);
                        object_Weapon.setCadence(entier);

                        object_Weapon.setLastUse(0);

                        elem->QueryIntAttribute("munitions", &entier);
                        object_Weapon.setMunitions(entier);

                        elem->QueryIntAttribute("sound", &entier);
                        object_Weapon.setSound(entier);

                        elem->QueryIntAttribute("speed", &entier);
                        object_Weapon.setSpeed(entier);

                        elem->QueryIntAttribute("sprite", &entier);
                        object_Weapon.setSpriteBullet(entier);

                        object_Weapon.setName(elem->Attribute("nom"));

                        object_Weapon.setSprite(id);

                        //on recupere les id des tiles cassables
                        TiXmlHandle sousHdl(elem);
                        TiXmlElement *sousElem = sousHdl.FirstChildElement().Element();

                        if(!sousElem){
                            std::cout << "[ERREUR] : [Map::initWeapon] : aucune tiles cassable" << std::endl;
                        }
                        else
                        {
                            while (sousElem){
                                sousElem->QueryIntAttribute("idtile", &entier);
                                object_Weapon.addWeaponTileBreak(entier);
                                sousElem = sousElem->NextSiblingElement(); // iteration
                            }
                        }

                        break;
                    }

                    elem = elem->NextSiblingElement(); // iteration
                }
            }
        }
        else
        {
            std::cout << "[ERREUR] : [Map::initWeapon] chargement impossible de \"config/weapon_config.xml\" : " << std::endl;
            std::cout << "\t error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
            window.Close();
        }

        return object_Weapon;
    }

    /**
     * configure un teleporteur
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param int id : id du teleporteur
     * @param PositionItem position : position
     * @access public
     * @return Object_Teleportation
    */
    Object_Teleportation Map::initTeleportation(sf::RenderWindow &window, int id, PositionItem position)
    {
        int entier;
        TiXmlDocument doc("config/teleportation_config.xml");
        object_Teleportation.setPosition(position);

        if(doc.LoadFile())
        {
            std::cout << "[INFORMATION] : [Map::initTeleportation] chargement de \"config/teleportation_config.xml\"" << std::endl;

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

            if(!elem)
            {
                std::cout << "[ERREUR] : [Map::initTeleportation] : le noeud teleportation n'existe pas" << std::endl;
                window.Close();
            }
            else
            {
                while (elem)
                {
                    elem->QueryIntAttribute("id", &entier);
                    std::cout << "[INFORMATION] : [Map::initTeleportation] teleporteur : " << entier << std::endl;

                    if(entier == id)
                    {
                        object_Teleportation.setId(id);

                        elem->QueryIntAttribute("sprite", &entier);
                        object_Teleportation.setSprite(entier);
                        elem->QueryFloatAttribute("tox", &position.x);
                        elem->QueryFloatAttribute("toy", &position.y);

                        position.x*=64;
                        position.y*=64;

                        object_Teleportation.setPositionTo(position);

                        break;
                    }

                    elem = elem->NextSiblingElement(); // iteration
                }
            }
        }
        else
        {
            std::cout << "[ERREUR] : [Map::initTeleportation] chargement impossible de \"config/teleportation_config.xml\" : " << std::endl;
            std::cout << "\t error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
            window.Close();
        }

        return object_Teleportation;
    }

    /**
     * configure une carte
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param int id : id de la carte
     * @param PositionItem position : position
     * @access public
     * @return Object_Card Map
    */
    Object_Card Map::initCard(sf::RenderWindow &window, int id, PositionItem position)
    {
        int entier = 0;
        TiXmlDocument doc("config/card_config.xml");
        object_Card.setPosition(position);

        if(doc.LoadFile()){
            std::cout << "[INFORMATION] : [Map::initCard] chargement de \"config/card_config.xml\"" << std::endl;

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

            if(!elem){
                std::cout << "[ERREUR] : [Map::initCard] : le noeud initCard n'existe pas" << std::endl;
                window.Close();
            }
            else
            {
                while (elem){
                    elem->QueryIntAttribute("id", &entier);
                    std::cout << "[INFORMATION] : [Map::initCard] initCard : " << id << "/" << entier << std::endl;

                    if(entier == id)
                    {
                        object_Card.setId(id);
                        object_Card.setSprite(id);
                        break;
                    }

                    elem = elem->NextSiblingElement(); // iteration
                }
            }
        }
        else
        {
            std::cout << "[ERREUR] : [Map::initCard] chargement impossible de \"config/card_config.xml\" : " << std::endl;
            std::cout << "\t error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
            window.Close();
        }

        return object_Card;
    }

    /**
     * configure une porte
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param int id : id de le porte
     * @param PositionItem position : position
     * @param bool open : la porte est ouverte ou non
     * @access public
     * @return Object_Door
    */
    Object_Door Map::initDoor(sf::RenderWindow &window, int id, PositionItem position, bool open)
    {
        int entier;
        TiXmlDocument doc("config/door_config.xml");
        object_Card.setPosition(position);

        if(doc.LoadFile()){
            std::cout << "[INFORMATION] : [Map::initDoor] chargement de \"config/door_config.xml\"" << std::endl;

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

            if(!elem){
                std::cout << "[ERREUR] : [Map::initDoor] : le noeud initDoor n'existe pas" << std::endl;
                window.Close();
            }
            else
            {
                while (elem){
                    elem->QueryIntAttribute("id", &entier);
                    std::cout << "[INFORMATION] : [Map::initDoor] initDoor : " << id << std::endl;

                    if(entier == id)
                    {
                        object_Door.setId(id);

                        elem->QueryIntAttribute("changelevel", &entier);
                        if(entier == 0)
                        {
                            object_Door.setChangeLevel(false);
                        }
                        else
                        {
                            object_Door.setChangeLevel(true);
                        }

                        elem->QueryIntAttribute("win", &entier);
                        if(entier == 0)
                        {
                            object_Door.setWin(false);
                        }
                        else
                        {
                            object_Door.setWin(true);
                        }

                        elem->QueryIntAttribute("sprite", &entier);
                        object_Door.setSprite(entier);
                        object_Door.setPosition(position);
                        object_Door.setOpen(open);

                        break;
                    }

                    elem = elem->NextSiblingElement(); // iteration
                }
            }
        }
        else
        {
            std::cout << "[ERREUR] : [Map::initDoor] chargement impossible de \"config/door_config.xml\" : " << std::endl;
            std::cout << "\t error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
            window.Close();
        }

        return object_Door;
    }

    /**
     * configure un bonus
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param TiXmlElement * Elem : pointeur vers l'instance de lecture du xml
     * @param
     * @access public
     * @return Object_Door
    */
    void Map::initBonus(sf::RenderWindow &window, TiXmlElement * Elem)
    {
        int entier;

        Elem->QueryIntAttribute("type", &entier);
        object_Bonus.setType(entier);

        Elem->QueryIntAttribute("value", &entier);
        object_Bonus.setValue(entier);

        Elem->QueryIntAttribute("armeid", &entier);
        object_Bonus.setArmeId(entier);

        Elem->QueryFloatAttribute("positionx", &position.x);
        Elem->QueryFloatAttribute("positiony", &position.y);
        Elem->QueryFloatAttribute("rotate", &position.rotate);

        position.x*=64;
        position.y*=64;
        position.rotate*=64;

        object_Bonus.setPosition(position);

        m_objectsBonus.push_back(object_Bonus);
    }

    /**
     * configure un malus
     * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
     * @param TiXmlElement * Elem : pointeur vers l'instance de lecture du xml
     * @access public
     * @return Object_Door
    */
    void Map::initMalus(sf::RenderWindow &window, TiXmlElement * Elem)
    {
        int entier;

        Elem->QueryIntAttribute("type", &entier);
        object_Malus.setType(entier);

        Elem->QueryIntAttribute("value", &entier);
        object_Malus.setValue(entier);

        Elem->QueryIntAttribute("armeid", &entier);
        object_Malus.setArmeId(entier);

        Elem->QueryFloatAttribute("positionx", &position.x);
        Elem->QueryFloatAttribute("positiony", &position.y);
        Elem->QueryFloatAttribute("rotate", &position.rotate);

        position.x*=64;
        position.y*=64;
        position.rotate*=64;

        object_Malus.setPosition(position);

        m_objectsMalus.push_back(object_Malus);
    }

    /**
     * supprime les npc morts
     * @access public
     * @return void
    */
    void Map::deleteNpcDead()
    {
        for(std::list<Npc>::iterator it_npc = m_npc.begin(); it_npc!=m_npc.end(); ++it_npc)
        {
            if(it_npc->getLife() <= 0)
            {
                m_sound.playSound(20, 100.f, false, it_npc->getPosition(), 512, 5, true);
                tile.initTile(false, 63, it_npc->getPosition());
                m_tilesBlood.push_back(tile);
                m_npc.erase(it_npc++);
            }
        }
    }

    /**
     * retourne la liste de tous les npc de la map
     * @access public
     * @return std::list<Npc>
    */
    std::list<Npc> * Map::getNpcs()
    {
        return &m_npc;
    }

    /**
     * retourne le nombre npc
     * @access public
     * @return int npc
    */
    int Map::getNumberNpc()
    {
        return m_numberNpc;
    }

    /**
     * retourne la "map" de l'IA
     * @access public
     * @return int npc
    */
    std::map <std::pair<int,int>, Node> * Map::getMMap()
    {
        return &m_map;
    }

    /**
     * retourne la liste de tous les bonus de la map
     * @access public
     * @return std::list<Object_Bonus>
    */
    std::list<Object_Bonus> * Map::getObjectBonus()
    {
        return &m_objectsBonus;
    }

    /**
     * retourne la liste de toutes les cartes de la map
     * @access public
     * @return std::list<Object_Card>
    */
    std::list<Object_Card> * Map::getObjectCard()
    {
        return &m_objectsCard;
    }

    /**
     * retourne la liste de toutes les portes de la map
     * @access public
     * @return std::list<Object_Door>
    */
    std::list<Object_Door> * Map::getObjectDoor()
    {
        return &m_objectsDoor;
    }

    /**
     * retourne la liste de tous les malus de la map
     * @access public
     * @return std::list<Object_Malus>
    */
    std::list<Object_Malus> * Map::getObjectMalus()
    {
        return &m_objectsMalus;
    }

    /**
     * retourne la liste de toutes les armes de la map
     * @access public
     * @return std::list<Object_Weapon>
    */
    std::list<Object_Weapon> * Map::getObjectWeapon()
    {
        return &m_objectsWeapon;
    }

    /**
     * retourne la liste de tous les teleporteurs
     * @access public
     * @return std::list<Object_Weapon>
    */
    std::list<Object_Teleportation> * Map::getObjectTeleportation()
    {
        return &m_objectsTeleportation;
    }

    /**
     * retourne la liste de tous les tiles de la map
     * @access public
     * @return std::list<Tiles>
    */
    std::map<std::pair<int, int>, Tiles> * Map::getTilesWall()
    {
        return &m_tilesWall;
    }

    /**
     * retourne la liste de tous les tiles de la map
     * @access public
     * @return std::list<Tiles>
    */
    std::list<Tiles> * Map::getTilesObjectFloor()
    {
        return &m_tilesObjectFloor;
    }

    /**
     * retourne la liste de tous les tiles de la map
     * @access public
     * @return std::list<Tiles>
    */
    std::list<Tiles> * Map::getTilesObjectWall()
    {
        return &m_tilesObjectWall;
    }

    /**
     * retourne le numero du niveau
     * @access public
     * @return int
    */
    int Map::getLevel()
    {
        return m_level;
    }

    /**
     * vide la map entre chaque niveau
     * @access public
     * @return void
    */
    void Map::deleteContentMap()
    {
        m_tilesFloor.clear();
        m_tilesWall.clear();
        m_tilesObjectFloor.clear();
        m_tilesObjectWall.clear();
        m_npc.clear();
        m_objectsWeapon.clear();
        m_objectsTeleportation.clear();
        m_objectsCard.clear();
        m_objectsDoor.clear();
        m_objectsBonus.clear();
        m_objectsMalus.clear();
        m_lights.clear();
    }

    /**
     * modifie le nombre de npc
     * @param int npc : nombre de npc restant
     * @access public
     * @return void
    */
    void Map::setNumberNpc(int npc)
    {
        m_numberNpc = npc;
    }

    /**
     * convertit un int en string
     * @param int x : nombre
     * @access public
     * @return string
    */
    std::string Map::int2Str(int x)
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
    Map::~Map()
    {
    }
