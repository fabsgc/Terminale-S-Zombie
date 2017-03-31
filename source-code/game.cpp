#include "game.hpp"

    /**
	 * constructeur
	 * @param int width : taille de la fenêtre affichée
	 * @param int height : largeur de la fenêtre affichée
	 * @access public
	 * @return void
    */
    Game::Game(int width, int height)
    {
        if (!m_imageGagne.LoadFromFile(SPRITE_GAGNE)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR] : [Game::Game] : impossible de charger le sprite gagne"<<std::endl;
        }
        else // Si le chargement de l'image a réussi
        {
            m_imageGagne.SetSmooth(false);
            m_spriteGagne.SetImage(m_imageGagne);
        }

        m_spriteGagne.SetCenter(320, 160);
        m_spriteGagne.SetPosition(sf::Vector2f(width/2 , height/2)); // Positionnement

        m_alreadyInit = false;
        m_width = width;
        m_height = height;
        m_lastPause = 0;
        m_executionTime = 10000;

        sf::Vector2f viewCenter(m_width/2,m_height/2);
        sf::Vector2f viewHalfhSize(m_width/2, m_height/2);
        sf::View view(viewCenter, viewHalfhSize);

        m_physic.setWidthHeight(width, height);
        m_guiMessage.setWidthHeight(width, height);

        initMenu();
    }

    /**
	 * initialisation d'une partie
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param int actionCurrent : action en cours : NEWGAME ou LOADGAME
	 * @access public
	 * @return void
    */
    void Game::initGame(sf::RenderWindow &window, int actionCurrent)
    {
        if(m_alreadyInit == false)
        {
            view.SetCenter(m_width/2, m_height/2);
            view.SetHalfSize(m_width/2, m_height/2);
            window.SetView(view);
            view.Zoom(1);

            m_actionCurrent = actionCurrent;

            switch(m_actionCurrent)
            {
                case LOADGAME :
                    this->initPlayerLoadGame(window);
                break;

                case NEWGAME :
                    this->initPlayerNewGame(window);
                break;
            }

            m_alreadyInit = true;
        }
    }

    /**
	 * initialisation une fois pour toute les boutons des menus
	 * @access public
	 * @return void
    */
    void Game::initMenu()
    {
        m_position.x = m_width/2 - WIDTH_MENU_X/2;
        m_position.y = m_height/2 - WIDTH_MENU_Y/2 - 100;
        m_guiMenu.addMenu(MENU_PAUSE_RETURN, m_position, "Retour au jeu", 32);

        m_position.x = m_width/2 - WIDTH_MENU_X/2;
        m_position.y = m_height/2 - WIDTH_MENU_Y/2;
        m_guiMenu.addMenu(MENU_PAUSE_QUIT, m_position, "Quitter la partie", 21);

        m_position.x = m_width/2 - WIDTH_MENU_X/2;
        m_position.y = m_height/2 - WIDTH_MENU_Y/2 + 100;
        m_guiMenu.addMenu(MENU_PAUSE_SAVE, m_position, "Sauvegarder", 38);
    }

    /**
	 * initialisation du joueur pour une nouvelle partie
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Game::initPlayerNewGame(sf::RenderWindow &window)
    {
        m_player.setLevel(1);
        m_player.setWin(false);
        std::ofstream fichier("config/loadgame.conf");

        if(fichier)
        {
            fichier << m_player.getLevel();
        }

        m_player.setWin(false);
        m_alreadyInit = true;

        TiXmlDocument doc("levels/level.xml");
        int entier;
        PositionItem position;

        if(doc.LoadFile()){
            std::cout << "[INFORMATION] : [Game::initPlayerNewGame] chargement de \"level/level.xml\"" << std::endl;

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().Element();

            if(!elem)
            {
                std::cout << "[ERREUR] : [Game::initPlayerNewGame] : le noeud levels n'existe pas" << std::endl;
                window.Close();
            }
            else
            {
                while(elem)
                {
                    elem->QueryIntAttribute("id", &entier);

                    if(entier == m_player.getLevel())
                    {
                        elem->QueryFloatAttribute("positionx", &position.x);
                        elem->QueryFloatAttribute("positiony", &position.y);
                        elem->QueryFloatAttribute("rotate", &position.rotate);
                        elem->QueryIntAttribute("speed", &entier);
                        m_player.setPosition(position);
                        m_player.setSpeed(entier);
                        elem->QueryIntAttribute("life", &entier);
                        m_player.setLife(entier);

                        break;
                    }
                }
            }
        }
    }

    /**
	 * initialisation du joueur pour une partie déjà commencée
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Game::initPlayerLoadGame(sf::RenderWindow &window)
    {
        int entier;

        std::ifstream fichier("config/loadgame.conf");

        if(fichier)
        {
            fichier >> entier;
            m_player.setLevel(entier);
        }
        else
        {
            m_player.setLevel(1);
        }

        m_player.setWin(false);
        m_alreadyInit = true;

        TiXmlDocument doc("levels/level.xml");
        PositionItem position;

        if(doc.LoadFile()){
            std::cout << "[INFORMATION] : [Game::initPlayerNewGame] chargement de \"level/level.xml\"" << std::endl;

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().Element();

            if(!elem)
            {
                std::cout << "[ERREUR] : [Game::initPlayerNewGame] : le noeud levels n'existe pas" << std::endl;
                window.Close();
            }
            else
            {
                while(elem)
                {
                    elem->QueryIntAttribute("id", &entier);

                    if(entier == m_player.getLevel())
                    {
                        elem->QueryFloatAttribute("positionx", &position.x);
                        elem->QueryFloatAttribute("positiony", &position.y);
                        elem->QueryFloatAttribute("rotate", &position.rotate);
                        elem->QueryIntAttribute("speed", &entier);
                        m_player.setPosition(position);
                        m_player.setSpeed(entier);
                        elem->QueryIntAttribute("life", &entier);
                        m_player.setLife(entier);

                        break;
                    }
                }
            }
        }
    }

    /**
	 * affiche "gagne"
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Game::displayWin(sf::RenderWindow &window)
    {
        view.SetCenter(m_width/2, m_height/2);
        m_map.setLevel(0);
        m_map.deleteContentMap();
        m_guiMessage.deleteMessage();
        m_physic.deleteMessage();

        window.Draw(m_spriteGagne);
    }

    /**
	 * affiche "perdu"
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Game::displayLose(sf::RenderWindow &window)
    {
        view.SetCenter(m_width/2, m_height/2);
        m_guiMessage.deleteMessage();
        m_physic.deleteMessage();
    }

    /**
	 * initialisation d'un object de type Object_Card que l'on passera au joueur ensuite
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param int id : id de l'arme
	 * @access public
	 * @return Object_Weapon
    */
    Object_Weapon Game::initWeapon(sf::RenderWindow &window, int id)
    {
        TiXmlDocument doc("config/weapon_config.xml");
        int entier;

        if(doc.LoadFile()){
            std::cout << "[INFORMATION] : [Game::initWeapon] chargement de \"config/weapon_config.xml\"" << std::endl;

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

            if(!elem){
                std::cout << "[ERREUR] : [Game::initWeapon] : le noeud weapon n'existe pas" << std::endl;
                window.Close();
            }
            else
            {
                while (elem){
                    elem->QueryIntAttribute("id", &entier);
                    std::cout << "[INFORMATION] : [Game::initWeapon] weapon : " << entier << std::endl;

                    if(entier == id)
                    {
                        m_objectWeapon.setId(id);

                        elem->QueryIntAttribute("degat", &entier);
                        m_objectWeapon.setDegat(entier);

                        elem->QueryIntAttribute("cadence", &entier);
                        m_objectWeapon.setCadence(entier);

                        m_objectWeapon.setLastUse(0);

                        elem->QueryIntAttribute("munitions", &entier);
                        m_objectWeapon.setMunitions(entier);

                        elem->QueryIntAttribute("sound", &entier);
                        m_objectWeapon.setSound(entier);

                        elem->QueryIntAttribute("speed", &entier);
                        m_objectWeapon.setSpeed(entier);

                        elem->QueryIntAttribute("sprite", &entier);
                        m_objectWeapon.setSpriteBullet(entier);

                        m_objectWeapon.setName(elem->Attribute("nom"));

                        m_objectWeapon.setSprite(id);

                        //on recupere les id des tiles cassables
                        TiXmlHandle sousHdl(elem);
                        TiXmlElement *sousElem = sousHdl.FirstChildElement().Element();

                        if(!sousElem){
                            std::cout << "[ERREUR] : [Game::initWeapon] : aucune tiles cassable" << std::endl;
                        }
                        else
                        {
                            while (sousElem){
                                sousElem->QueryIntAttribute("idtile", &entier);
                                m_objectWeapon.addWeaponTileBreak(entier);
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
            std::cout << "[ERREUR] : [Game::initCard] chargement impossible de \"config/weapon_config.xml\" : " << std::endl;
            std::cout << "\t error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
            window.Close();
        }

        return m_objectWeapon;
    }

    /**
	 * initialisation d'un object de type Object_Card que l'on passera au joueur ensuite
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param int id : id de l'arme
	 * @access public
	 * @return Object_Card
    */
    Object_Card Game::initCard(sf::RenderWindow &window, int id)
    {
        TiXmlDocument doc("config/card_config.xml");
        int entier;

        if(doc.LoadFile()){
            std::cout << "[INFORMATION] : [Game::initCard] chargement de \"config/card_config.xml\"" << std::endl;

            TiXmlHandle hdl(&doc);
            TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

            if(!elem){
                std::cout << "[ERREUR] : [Game::initCard] : le noeud initCard n'existe pas" << std::endl;
                window.Close();
            }
            else
            {
                while (elem){
                    elem->QueryIntAttribute("id", &entier);
                    std::cout << "[INFORMATION] : [Game::initCard] initCard : " << entier << std::endl;

                    if(entier == id)
                    {
                        m_objectCard.setId(id);
                        m_objectCard.setSprite(id);
                        break;
                    }

                    elem = elem->NextSiblingElement(); // iteration
                }
            }
        }
        else
        {
            std::cout << "[ERREUR] : [Game::initCard] chargement impossible de \"config/card_config.xml\" : " << std::endl;
            std::cout << "\t error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
            window.Close();
        }

        return m_objectCard;
    }

    /**
	 * fonction principale pour le jeu
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return int (action)
    */
    int Game::playGame(sf::RenderWindow &window, float deltaTime)
    {
        m_executionTime+=(deltaTime*1000);

        if(m_player.getLife() > 0 && m_player.getWin() == false)
        {
            if(m_map.initMap(window, m_player.getLevel(), &m_player, deltaTime) == true)//temps que la map n'a pas ete chargee, on affiche rien
            {
                //on cherche a savoir si le joueur met en pause
                this->checkPause(window);
                m_player.changeWeapon(window);

                m_map.deleteNpcDead();  // on vire les npc morts avant qu'ils puissent faire du mal au joueur

                //d'abord on calcul les collisions entre player/objet, player/npc, player/decor, player-balles/npc-decor et on modifie les objets nécessaires
                m_actionCurrent = m_physic.calculCollision(window, &m_player, &m_map, &view, deltaTime, m_actionCurrent);

                //ensuite, on affiche tout ce beau monde
                //la map (objet + npc)
                //on recadre la vue
                view.SetCenter(m_player.getPosition().x, m_player.getPosition().y);

                    //on affiche le personnage
                    m_map.displayFloor(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayShadow(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayShadow2(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayBlood(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayCard(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayWeapon(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayBonus(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayMalus(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayTeleportation(window, &m_player, m_width, m_height, deltaTime);
                    m_player.displayBulletBullet(window, deltaTime);
                    m_map.displayObjectFloor(window, &m_player, m_width, m_height, deltaTime);
                    m_player.displayBulletGrenade(window, deltaTime);
                    m_player.displayBulletMine(window, deltaTime);
                    m_player.displayBulletSword(window, deltaTime);
                    m_player.display(window, deltaTime);
                    m_map.displayNpc(window, &m_player, m_width, m_height, deltaTime);
                    m_player.displayBulletFlame(window, deltaTime);
                    m_map.displayDoor(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayObjectWall(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayLight(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayWall(window, &m_player, m_width, m_height, deltaTime);
                    m_map.displayLumiereJaune(window, &m_player, m_width, m_height, deltaTime);
                    m_player.displayInfo(window, m_width, m_height);
                    m_physic.displayMessage(window, deltaTime, m_player.getPosition());
            }
            else
            {
                PositionItem position;
                position.x = 5;
                position.y = 2;
                m_player.setPosition(position);
                view.SetCenter(m_width/2, m_height/2);
            }
        }
        else if(m_player.getLife() <= 0)
        {
            m_actionCurrent = GAMEOVER;
        }
        else if(m_player.getWin() == true)
        {
            m_actionCurrent = WIN;
        }

        //on retourne la bonne action
        return m_actionCurrent;
    }

    /**
	 * fonction affichant le menu de pause
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps écoule depuis le dernier appel de la méthode
	 * @access public
	 * @return int (action)
    */
    int Game::playPause(sf::RenderWindow &window, float deltaTime)
    {
        const sf::Input& Input = window.GetInput();

        view.SetCenter(m_width/2, m_height/2);
        m_executionTime+=(deltaTime*1000);
        m_guiMenu.display(window);

        m_position.x = m_width/2; m_position.y = m_height/2;
        m_guiMessage.display(window, deltaTime, m_position);

        this->checkPause(window);

        if(Input.IsMouseButtonDown(sf::Mouse::Left))
        {
            sf::Sleep(0.2);

            m_buttonClicked = m_guiMenu.getClic(Input.GetMouseX(), Input.GetMouseY());

            switch(m_buttonClicked)
            {
                case MENU_PAUSE_RETURN :
                    m_actionCurrent = LOADGAME;
                    m_guiMessage.deleteMessage();
                break;

                case MENU_PAUSE_QUIT :
                    m_map.setLevel(0); //sinon, on aura pas la jolie animation
                    m_alreadyInit = false;
                    m_actionCurrent = MENU;
                    m_physic.deleteMessage();
                    m_guiMessage.deleteMessage();
                break;

                case MENU_PAUSE_SAVE :
                    m_actionCurrent = SAVE;
                    m_guiMessage.deleteMessage();
                break;
            }
        }

        return m_actionCurrent;
    }

    /**
	 * fonction permettant de savoir si on a appuyé sur pause
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return int (action)
    */
    void Game::checkPause(sf::RenderWindow &window)
    {
        const sf::Input& Input = window.GetInput();

        if((Input.IsJoystickButtonDown(0, 7) && m_executionTime - m_lastPause > 250) || (Input.IsKeyDown(sf::Key::P) && m_executionTime - m_lastPause > 250))
        {
            m_lastPause = m_executionTime;

            if(m_actionCurrent != PAUSE)
            {
                m_actionCurrent = PAUSE;
            }
            else
            {
                m_actionCurrent = LOADGAME;
            }
        }
        else if(Input.IsKeyDown(sf::Key::Escape)) //aucun mouvement
        {
            window.Close();
        }
    }

    /**
	 * fonction permettant de sauvegarder la pogression actuelle
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return int : m_actionCurrent
    */
    int Game::save()
    {
        std::ofstream fichier("config/loadgame.conf");

        if(fichier)
        {
            fichier << m_player.getLevel();
            m_guiMessage.addMessage(TIME_MAX_MESSAGE, "La partie a bien été", "sauvegardée. Vous êtes", " au niveau " + this->int2Str(m_player.getLevel()) + ".");
        }
        else
        {
            m_guiMessage.addMessage(TIME_MAX_MESSAGE, "La partie n'a pas pu", "être sauvegardée.");
        }

        return m_actionCurrent = PAUSE;
    }

    /**
	 * fonction permettant de relancer l'initialisation d'une partie
	 * @param bool init
	 * @access public
	 * @return void
    */
    void Game::setAlreadyInit(bool init)
    {
        m_alreadyInit = init;
    }

    /**
     * convertit un int en string
     * @param int x : nombre
     * @access public
     * @return string
    */
    std::string Game::int2Str(int x)
    {
        std::stringstream type;
        type << x;
        return type.str();
    }

    /**
	 * destructeur
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    Game::~Game()
    {
    }
