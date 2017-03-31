#include "npc.hpp"

    sf::Image m_imageNpc;

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Npc::Npc()
    {
        m_executionTime = 10000;
        m_lastAttackTime = 0;
        m_lastSearchPathPlayerTime = 0;
        m_actionCurrent = STARTBASE_TO_ENDBASE;
        m_findPath = NPC_FIND_PATH_FALSE;
        m_playerDetected = false;
        m_nodePath = 0;
    }

    /**
	 * inflige des degats au npc
	 * @param Bullet &bullet : reference vers l'objet Bullet du joueur
	 * @access public
	 * @return void
    */
    void Npc::prendreDegat(int degat, float deltaTime, int timeBetweenAttack)
    {
        if(m_executionTime - (m_lastAttackTime + (deltaTime*1000)) > timeBetweenAttack)
        {
            m_sound.playSound(18, 100.f, false, m_positionNpc, 512, 5, true);

            m_life -= degat;
            m_lastAttackTime = m_executionTime;

            if(m_life < 0)
            {
                m_life = 0;
            }
        }
    }

    /**
	 * calcul la nouvelle position théorique du npc (la position sera revue par la classe physic encore que)
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @param float deltaTime : temps écoule entre 2 frames
	 * @access public
	 * @return void
    */
    void Npc::calculNewPosition(sf::RenderWindow &window, float deltaTime)
    {
        float decalage_vitesse = (1/deltaTime) / 60;
        float coefDirecteurPosition = 0;

        if(m_playerDetected == true)
        {
            if(m_lastSearchPathPlayerTime < m_executionTime - TIME_BETWEEN_SEARCHPATHPLAYER) //on a assez attendu, on peut relancer une recherche
            {
                m_lastSearchPathPlayerTime = m_executionTime;
                m_actionCurrent = NPC_TO_PLAYER;
            }
        }
        else
        {
            switch(m_actionCurrent)
            {
                case STARTBASE_TO_ENDBASE :
                    if(m_findPath == NPC_FIND_PATH_FALSE) //on a trouve le chemin ?
                    {
                        Pathfinder m_pathFinder;
                        m_nodeStart.setDistStartCurrentG(0);
                        m_nodeStart.setDistCurrentEndH(distancePoint(m_nodeEnd.getX(), m_nodeEnd.getY(), m_nodeStart.getX(), m_nodeStart.getY())* NODE_DISTANCE_VALUE);
                        m_nodeStart.setGhF(m_nodeStart.getDistCurrentEndH());
                        m_path = m_pathFinder.findpath(m_map, &m_nodeStart, &m_nodeEnd);
                        m_findPath = NPC_FIND_PATH_TRUE;
                        m_nodePath = 0;
                    }
                    else // oui, chemin trouve
                    {
                        //on a parcouru tous les noeuds du chemin ?
                        if(m_nodePath < m_path.size()-1)
                        {
                            //quand on est tout proche du centre du noeud, on change de noeud
                            if(distancePoint(m_positionNpc.x, m_positionNpc.y, m_path[m_nodePath].getX()*64, m_path[m_nodePath].getY()*64) < 45)
                            {
                                m_nodePath++;

                                coefDirecteurPosition = (m_positionNewNpc.y - (m_path[m_nodePath].getY()*64))/(m_positionNewNpc.x - m_path[m_nodePath].getX()*64);

                                if(coefDirecteurPosition > 10000)
                                {
                                    coefDirecteurPosition = 10000;
                                }
                                if(coefDirecteurPosition < -10000)
                                {
                                    coefDirecteurPosition = -10000;
                                }

                                if(m_positionNewNpc.x >= (m_path[m_nodePath].getX()*64) )
                                {
                                    m_positionNewNpc.rotate = ((atan(-coefDirecteurPosition) * 180)/PI + 90);
                                }
                                else
                                {
                                    m_positionNewNpc.rotate = ((atan(-coefDirecteurPosition) * 180)/PI - 90);
                                }
                            }
                            else //on avance vers le noeud
                            {
                                m_positionNewNpc.y = m_positionNpc.y - (cos((m_positionNewNpc.rotate*PI)/180)*(2.5))/decalage_vitesse;
                                m_positionNewNpc.x = m_positionNpc.x - (sin((m_positionNewNpc.rotate*PI)/180)*(2.5))/decalage_vitesse;
                            }
                        }
                        else //on a tout parcouru, ca veut dire qu'on doit aller dans l'autre sens
                        {
                            m_actionCurrent = ENDBASE_TO_STARTBASE;
                            m_findPath = NPC_FIND_PATH_FALSE;
                        }
                    }
                break;

                case ENDBASE_TO_STARTBASE :
                    if(m_findPath == NPC_FIND_PATH_FALSE)
                    {
                        Pathfinder m_pathFinder;
                        m_nodeEnd.setDistStartCurrentG(0);
                        m_nodeEnd.setDistCurrentEndH(distancePoint(m_nodeEnd.getX(), m_nodeEnd.getY(), m_nodeStart.getX(), m_nodeStart.getY())* NODE_DISTANCE_VALUE);
                        m_nodeEnd.setGhF(m_nodeStart.getDistCurrentEndH());
                        m_path = m_pathFinder.findpath(m_map, &m_nodeEnd, &m_nodeStart);
                        m_findPath = NPC_FIND_PATH_TRUE;
                        m_nodePath = 0;
                    }
                    else
                    {
                        //on a parcouru tous les noeuds du chemin ?
                        if(m_nodePath < m_path.size()-1)
                        {
                            //quand on est tout proche du centre du noeud, on change de noeud
                            if(distancePoint(m_positionNpc.x, m_positionNpc.y, m_path[m_nodePath].getX()*64, m_path[m_nodePath].getY()*64) < 45)
                            {
                                m_nodePath++;
                                coefDirecteurPosition = (m_positionNewNpc.y - (m_path[m_nodePath].getY()*64))/(m_positionNewNpc.x - m_path[m_nodePath].getX()*64);

                                if(coefDirecteurPosition > 10000)
                                {
                                    coefDirecteurPosition = 10000;
                                }
                                if(coefDirecteurPosition < -10000)
                                {
                                    coefDirecteurPosition = -10000;
                                }

                                if(m_positionNewNpc.x >= (m_path[m_nodePath].getX()*64) )
                                {
                                    m_positionNewNpc.rotate = ((atan(-coefDirecteurPosition) * 180)/PI + 90);
                                }
                                else
                                {
                                    m_positionNewNpc.rotate = ((atan(-coefDirecteurPosition) * 180)/PI - 90);
                                }
                            }
                            else //on avance vers le noeud
                            {
                                m_positionNewNpc.y = m_positionNpc.y - (cos((m_positionNewNpc.rotate*PI)/180)*(2.5))/decalage_vitesse;
                                m_positionNewNpc.x = m_positionNpc.x - (sin((m_positionNewNpc.rotate*PI)/180)*(2.5))/decalage_vitesse;
                            }
                        }
                        else //on a tout parcouru, ca veut dire qu'on doit aller dans l'autre sens
                        {
                            m_actionCurrent = STARTBASE_TO_ENDBASE;
                            m_findPath = NPC_FIND_PATH_FALSE;
                        }
                    }
                break;

                case NPC_TO_STARTBASE :
                    if(m_findPath == NPC_FIND_PATH_FALSE)
                    {

                    }
                    else
                    {

                    }
                break;

                case NPC_TO_ENDBASE :
                    m_actionCurrent = NPC_TO_STARTBASE;
                break;

                case NPC_TO_PLAYER :
                    m_actionCurrent = NPC_TO_STARTBASE;
                    m_findPath = NPC_FIND_PATH_FALSE;
                break;
            }
        }

        switch(m_findPath)
        {
            case NPC_FIND_PATH_FALSE :

            break;

            case NPC_FIND_PATH_TRUE :

            break;
        }

        /*m_positionNewNpc.x += 1;
        m_positionNewNpc.y -= 2;*/
        m_executionTime += (deltaTime*1000);
        m_animNpc.animPlay(deltaTime*1000);
    }

    /**
	 * met a jour la position via les valeurs calculees en cache
	 * @access public
	 * @return void
    */
    void Npc::updatePosition()
    {
        m_positionNpc = m_positionNewNpc;
    }

    /**
	 * affiche le npc a l'ecran
	 * @param sf::RenderWindow &window : référence vers l'instance de la fenêtre
	 * @access public
	 * @return void
    */
    void Npc::display(sf::RenderWindow &window)
    {
        m_sprite = m_animNpc.getSprite(1, m_typeSprite);
        m_sprite->SetPosition(sf::Vector2f(m_positionNpc.x, m_positionNpc.y)); // Positionnement
        m_sprite->SetRotation(m_positionNpc.rotate);
        window.Draw((*m_sprite));
    }

    /**
	 * modifie l'id du npc
	 * @param int id : id
	 * @access public
	 * @return void
    */
    void Npc::setId(int id)
    {
        m_id = id;
    }

    /**
	 * modifie le nombre de degats qu'infilige le npc
	 * @param int degat : nombre de degats
	 * @access public
	 * @return void
    */
    void Npc::setDegat(int degat)
    {
        m_degat = degat;
    }

    /**
	 * modifie la valeur de la vie restante du npc
	 * @param int life : vie
	 * @access public
	 * @return void
    */
    void Npc::setLife(int life)
    {
        m_life = life;
    }

    /**
	 * modifie la vitesse du npc
	 * @param int speed : vitesse
	 * @access public
	 * @return void
    */
    void Npc::setSpeed(int speed)
    {
        m_speed = speed;
    }

    /**
	 * modifie la position du npc a l'ecran
	 * @param PositionItem position : position à donner
	 * @access public
	 * @return void
    */
    void Npc::setPosition(PositionItem position)
    {
        m_positionNpc = position;
        m_positionNewNpc = m_positionNpc;
    }

    /**
     * modifie la position x du joueur a l'ecran
     * @param float x
     * @access public
     * @return void
    */
    void Npc::setPositionX(float x)
    {
        m_positionNpc.x = x;
        m_positionNewNpc.x = x;
    }

    /**
     * modifie la position y du joueur a l'ecran
     * @param flot y
     * @access public
     * @return void
    */
    void Npc::setPositionY(float y)
    {
        m_positionNpc.y = y;
        m_positionNewNpc.y = y;
    }

    /**
	 * modifie le position du npc a l'ecran
	 * @param std::string sprite : chemin
	 * @access public
	 * @return void
    */
    void Npc::setSprite(std::string sprite)
    {
        if (!m_imageNpc.LoadFromFile(sprite)) // Si le chargement du fichier a échoué
        {
            std::cout<<"[ERREUR]: [Npc::setSprite] : impossible de charger le sprite npc"<<std::endl;
        }

        m_animNpc.setSprite(&m_imageNpc);
        m_animNpc.setSpriteChangeTime(10);
        m_animNpc.setSpriteNumber(53);
        m_animNpc.setSpriteWidth(WIDTH_NPC_X);
        m_animNpc.setSpriteHeight(WIDTH_NPC_Y);
        m_animNpc.setSpriteCenterX(WIDTH_NPC_X/2);
        m_animNpc.setSpriteCenterY(WIDTH_NPC_Y-20);
    }

    /**
	 * permet de savoir sur l'image des sprites quelle perso prendre
	 * @param std::string sprite : chemin
	 * @access public
	 * @return void
    */
    void Npc::setTypeSprite(int typeSprite)
    {
        m_typeSprite = typeSprite;
    }

    /**
	 * permet d'avoir un pointeur vers la map en simplifiee et optimisee pour la recherche de chemin
	 * @param std::string sprite : chemin
	 * @access public
	 * @return void
    */
    void Npc::setMapAstar(std::map <std::pair<int,int>, Node> * map)
    {
        m_map = map;
    }

    /**
	 * modifie le noeud de depart pour la recherche de chemin
	 * @param : int x : position X dans le monde
	 * @param : int y : position Y dans le monde
	 * @access public
	 * @return void
    */
    void Npc::setNodeStartAstar(int x, int y)
    {
        m_nodeStart.setX(x);
        m_nodeStart.setY(y);
    }

    /**
	 * modifie le noeud d'arrivee pour la recherche de chemin
	 * @param : int x : position X dans le monde
	 * @param : int y : position Y dans le monde
	 * @access public
	 * @return void
    */
    void Npc::setNodeEndAstar(int x, int y)
    {
        m_nodeEnd.setX(x);
        m_nodeEnd.setY(y);
    }

    /**
	 * specifie si le npc a trouve son chemin ou non
	 * @param bool findPath : chemin trouve ou non
	 * @access public
	 * @return void
    */
    void Npc::setFindPath(bool findPath)
    {
        m_findPath = findPath;
    }

    /**
	 * specifie si le npc a trouve le joueur
	 * @param boll findPath : chemin trouve ou non
	 * @access public
	 * @return void
    */
    void Npc::setPlayerDetected(bool playerDetected)
    {
        m_playerDetected = playerDetected;
    }

    /**
	 * la class physic utilisera cette methode pour transmettre au npc la position du joueur
	 * @param PositionItem positionPlayer : position du joueur
	 * @access public
	 * @return void
    */
    void Npc::setPlayerPosition(PositionItem positionPlayer)
    {
        m_positionPlayer = positionPlayer;
    }

    /**
	 * specifie l'action suivie par le npc
	 * @param int actionCurrent : action en cours
	 * @access public
	 * @return void
    */
    void Npc::setActionCurrent(int actionCurrent)
    {
        m_actionCurrent = actionCurrent;
    }

    /**
	 * retourne l'id du npc
	 * @param int id : id
	 * @access public
	 * @return void
    */
    int Npc::getId()
    {
        return m_id;
    }

    /**
	 * modifie le nombre de degats qu'infilige le npc
	 * @param int degat : nombre de degats
	 * @access public
	 * @return void
    */
    int Npc::getDegat()
    {
        return m_degat;
    }

    /**
	 * retourne la quantite de vie du npc
	 * @access public
	 * @return int
    */
    int Npc::getLife()
    {
        return m_life;
    }

    /**
	 * retourne la vitesse du personnage
	 * @access public
	 * @return int
    */
    int Npc::getSpeed()
    {
        return m_speed;
    }

    /**
	 * retourne la position du npc
	 * @access public
	 * @return PositionItem
    */
    PositionItem Npc::getPosition()
    {
        return m_positionNpc;
    }

    /**
	 * retourne la nouvelle position du npc
	 * @access public
	 * @return PositionItem
    */
    PositionItem Npc::getNewPosition()
    {
        return m_positionNewNpc;
    }

    /**
	 * retourne le type du sprite
	 * @access public
	 * @return int
    */
    int Npc::getTypeSprite()
    {
        return m_typeSprite;
    }

    /**
	 * retourne la map connue par le npc (pointeur
	 * @access public
	 * @return std::map <std::pair<int,int>, int> *
    */
    std::map <std::pair<int,int>, Node> * Npc::getMapAstar()
    {
        return m_map;
    }

    /**
	 * modifie le noeud de depart pour la recherche de chemin
	 * @access public
	 * @return &Node
    */
    Node * Npc::getNodeStartAstar()
    {
        return &m_nodeStart;
    }

    /**
	 * modifie le noeud d'arrivee pour la recherche de chemin
	 * @access public
	 * @return &Node
    */
    Node * Npc::getNodeEndAstar()
    {
        return &m_nodeEnd;
    }

    /**
	 * retourne si le npc a trouve son chemin ou non
	 * @access public
	 * @return bool
    */
    bool Npc::getFindPath()
    {
        return m_findPath;
    }

    bool Npc::getPlayerDetected()
    {
        return m_playerDetected;
    }

    /**
	 * retourne l'action suivie par le npc
	 * @access public
	 * @return int
    */
    int Npc::getActionCurrent()
    {
        return m_actionCurrent;
    }

    /**
	 * desctructeur
	 * @access public
	 * @return void
    */
    Npc::~Npc()
    {

    }
