#include "pathfinder.hpp"

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Pathfinder::Pathfinder()
    {

    }

    /**
	 * fonction de calcul du chemin a suivre par le npc
	 * @param std::map <std::pair<int,int>, int> * map : pointeur vers le "monde"
	 * @param Node * nodeStart : pointeur vers le noeud de depart de la recherche
	 * @param Node * nodeEnd : pointeur vers le noeud d'arrivee de la recherche
	 * @access public
	 * @return void
    */
    std::map <int, Node> Pathfinder::findpath(std::map <std::pair<int,int>, Node> * map, Node * nodeStart, Node * nodeEnd)
    {
        m_map = map;
        m_i_open = 0;
        m_j_close = 0;
        int f_final = 0;
        Node * currentNode;
        Node * tmpNode;

        /**
        - Ajout du node de départ à la liste ouverte.
        - Entrée dans la boucle suivante:
          - Récupération du node avec le plus petit F contenu dans la liste ouverte. On le nommera CURRENT.
          - Basculer CURRENT dans la liste fermée.
          - Pour chacun des 4 nodes adjacents à CURRENT appliquer la méthode suivante:

          * Si le node est un obstacle ou est dans la liste fermée ignorez-le et
        passer à l'analyse d'un autre node.

          * Si le node n'est pas dans la liste ouverte, ajoutez-le à ladite liste
            et faites de CURRENT son parent(P). Calculez et enregistrez
            ses propriétés F, G et H.

          * Si le node est déjà dans la liste ouverte, recalculez son G, s'il est inférieur
            à l'ancien, faites de CURRENT son parent(P) et recalculez et enregistrez
            ses propriétés F et H.

          * Stopper la boucle de recherche si vous ajoutez le node d'arrivée à la liste fermée ou si la liste ouverte est vide,
        dans ce dernier cas, il n'y a pas de chemin possible entre A et B.

        - Prenez le node d'arrivée et reconstruisez le chemin à rebours, càd en bouclant sur les propriétés parentes
        jusqu'à ce que le parent soit CURRENT.
        */

        this->addToOpenList(std::make_pair(nodeStart->getX(), nodeStart->getY()), m_i_open, nodeStart);

        while(m_openList.size() > 0)
        {
            //Recuperation du node avec le plus petit F contenu dans la liste ouverte. On le nommera CURRENT.
            currentNode = getCurrentNode();

            //stopper la boucle si on ajoute le noeud d'arrivee à la liste fermee
            if(currentNode->getX() == nodeEnd->getX() && currentNode->getY() == nodeEnd->getY())
            {
                break;
            }

            //Basculer CURRENT dans la liste fermée.
            addToCloseList(std::make_pair(currentNode->getX(), currentNode->getY()), m_j_close, currentNode);

            //recuperation des voisins de CURRENT
            std::map <int, Node*> neighbours = getNeighbours(currentNode);
            int maximum = neighbours.size();

            // Pour chacun des 8 nodes adjacents à CURRENT appliquer la méthode suivante:
            for(int i = 0; i < maximum; ++i)
            {
                Node * node = neighbours[i];

                //Si le node est un obstacle ou est dans la liste fermée ignorez-le et passer à l'analyse d'un autre node.
                if(this->isOnCloseList(std::make_pair(node->getX(), node->getY())) || node->getObstacle() == true)
                {
                    continue;
                }

                /* on calcule le nouveau g */
                tmpNode = &m_map->operator[](std::pair<int,int>(node->getParent().first, node->getParent().second));
                int newG = tmpNode->getDistStartCurrentG() + NODE_DISTANCE_VALUE;

                /*on calcule le nouveau h */
                int newH = (distancePoint(nodeEnd->getX(), nodeEnd->getY(), node->getX(), node->getY())) * NODE_DISTANCE_VALUE;

                /*on calcule le nouveau F*/
                int newF = newH + newG;

                if(this->isOnOpenList(std::make_pair(node->getX(), node->getY())))
                {
                    //Si le node est déjà dans la liste ouverte, recalculez son G, s'il est inférieur à l'ancien,
                    //faites de CURRENT  son parent(P) et recalculez et enregistrez ses propriétés F et H.

                    if(newH <= currentNode->getDistCurrentEndH())
                    {
                        node->setParent(currentNode->getX(), currentNode->getY());
                        node->setDistStartCurrentG(newG);
                        node->setDistCurrentEndH(newH);
                        node->setGhF(newF);
                    }
                }
                else
                {
                    //Si le node n'est pas dans la liste ouverte, ajoutez-le à la dite liste et faites de CURRENT son parent(P).
                    //Calculez et enregistrez ses propriétés F, G et H.
                    node->setParent(currentNode->getX(), currentNode->getY());
                    node->setDistStartCurrentG(newG);
                    node->setDistCurrentEndH(newH);
                    node->setGhF(newF);

                    this->addToOpenList(std::make_pair(node->getX(), node->getY()), m_i_open, node);
                }
            }
        }

        // on est sorti de la liste, on a deux solutions, soit la liste ouverte est vide dans ces cas là il
        // n'y a pas de solutions et on retoure directement finalPath;
        if(m_openList.size() == 0)
        {
            return m_finalPath;
        }

        //on recupere le chemin (copie cette fois, pas de pointeur)
        f_final = 0;
        for(std::map<int, Node*>::iterator it_list = m_closeList.begin(); it_list!= m_closeList.end(); ++it_list)
        {
            m_finalPath[f_final] = (*it_list->second);
            f_final++;
        }
        m_finalPath[f_final++] = (*currentNode);

        return m_finalPath;
    }

    /**
	 * supprimer un node de la liste fermee
	 * @param std::pair <int,int> position : indice du node a supprimer
	 * @access public
	 * @return void
    */
    void Pathfinder::removeFromCloseList(std::pair <int,int> position)
    {
        for(std::map<int, Node*>::iterator it_list = m_closeList.begin(); it_list!= m_closeList.end(); ++it_list)
        {
            if(it_list->second->getX() == position.first && it_list->second->getY() == position.second)
            {
                m_closeList.erase(it_list++);
                break;
            }
        }
    }

    /**
	 * supprimer un node de la liste ouverte
	 * @param std::pair <int,int> position : indice du node a supprimer
	 * @access public
	 * @return void
    */
    void Pathfinder::removeFromOpenList(std::pair <int,int> position)
    {
        for(std::map<int, Node*>::iterator it_list = m_openList.begin(); it_list!= m_openList.end(); ++it_list)
        {
            if(it_list->second->getX() == position.first && it_list->second->getY() == position.second)
            {
                m_openList.erase(it_list++);
                break;
            }
        }
    }

    /**
	 * ajouter un node a la liste ouverte tout en etant sur qu'il ne se trouve pas dans la liste fermee
	 * @param std::pair <int,int> position : indice du node
	 * @param int id
	 * @param Node * node : node a ajouter
	 * @access public
	 * @return void
    */
    void Pathfinder::addToCloseList(std::pair <int,int> position, int id, Node * node)
    {
        this->removeFromOpenList(position);
        m_closeList[id] = node;
        m_j_close++;
    }

    /**
	 * ajouter un node a la liste fermée tout en etant sur qu'il ne se trouve pas dans la liste ouverte
	 * @param std::pair <int,int> position : indice du node a supprimer
	 * @param int id
	 * @param Node * node : node a ajouter
	 * @access public
	 * @return void
    */
    void Pathfinder::addToOpenList(std::pair <int,int> position, int id, Node * node)
    {
        this->removeFromOpenList(position);
        m_openList[id] = node;
        m_i_open++;
    }

    /**
	 * recuperer le node avec le plus petit F contenu dans la liste ouverte
	 * @access public
	 * @return Node*
    */
    Node* Pathfinder::getCurrentNode()
    {
        std::map <int, Node*>::iterator it;
        int minF = 1000000;
        Node * currentNode;

        for (it = m_openList.begin() ; it != m_openList.end() ; it++)
        {
            if((*it).second->getGhF() < minF )
            {
                minF = (*it).second->getGhF();
                currentNode = (*it).second;
            }
        }

        return currentNode;
    }

    /**
	 * recuperer les voisins du node courant
	 * @param Node * node : noeud courant
	 * @access public
	 * @return std::map <int, Node*>
    */
    std::map <int, Node*> Pathfinder::getNeighbours(Node * node)
    {
        std::map <int, Node*> neighbours;

        // on calcule l'indice de la ligne au dessus de la ligne du node
        int indiceUp = node->getX() - 1;
        // on calcule l'indice de la ligne au dessus de la ligne du node
        int indiceBottom = node->getX() + 1;
        // on calcule l'indice de la colonne à gauche de la colonne du node
        int indiceLeft = node->getY() - 1;
        // on calcule l'indice de la colonne à droite de la colonne du node
        int indiceRight= node->getY() + 1;

        //node du dessus
        neighbours[0] = &m_map->operator[](std::pair<int,int>(indiceUp, node->getY()));
        //node du dessous
        neighbours[1] = &m_map->operator[](std::pair<int,int>(indiceBottom,node->getY()));
        //node de gauche
        neighbours[2] = &m_map->operator[](std::pair<int,int>(node->getX(),indiceLeft));
        //node de droite
        neighbours[3] = &m_map->operator[](std::pair<int,int>(node->getX(),indiceRight));

        return neighbours;
    }

    /**
	 * savoir si un node se trouve dans la liste fermee
	 * @param std::pair <int,int> position : indice du node a ajouter
	 * @access public
	 * @return bool
    */
    bool Pathfinder::isOnCloseList(std::pair <int,int> position)
    {
        std::map <int, Node*>::iterator it;

        for ( it = m_closeList.begin() ; it != m_closeList.end() ; it++)
        {
            if((*it).second->getParent() == position)
            {
                return true;
            }
        }

        return false;
    }

    /**
	 * savoir si un node se trouve dans la liste ouverte
	 * @param std::pair <int,int> position : indice du node a ajouter
	 * @access public
	 * @return bool
    */
    bool Pathfinder::isOnOpenList(std::pair <int,int> position)
    {
        std::map <int, Node*>::iterator it;

        for ( it = m_openList.begin() ; it != m_openList.end() ; it++)
        {
            if((*it).second->getX() == position.first && (*it).second->getY() == position.second)
            {
                return true;
            }
        }

        return false;
    }

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    Pathfinder::~Pathfinder()
    {

    }
