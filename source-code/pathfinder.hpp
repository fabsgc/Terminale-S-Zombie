#ifndef PATHFINDER_HPP_INCLUDED
#define PATHFINDER_HPP_INCLUDED

#include "include.hpp"
#include "node.hpp"

    class Pathfinder
    {
        public:
            Pathfinder();
            std::map <int, Node> findpath(std::map <std::pair<int,int>, Node> * map, Node * nodeStart, Node * nodeEnd);
            ~Pathfinder();

        private:
            void removeFromCloseList(std::pair <int,int> position);
            void removeFromOpenList(std::pair <int,int> position);
            void addToCloseList(std::pair <int,int> position, int id, Node * node);
            void addToOpenList(std::pair <int,int> position, int id, Node * node);
            Node* getCurrentNode();
            std::map <int, Node*> getNeighbours(Node * node);
            bool isOnCloseList(std::pair <int,int> position);
            bool isOnOpenList(std::pair <int,int> position);

            std::map <std::pair<int,int>, Node> * m_map;
            std::map <int, Node> m_finalPath;
            std::map <int, Node*> m_closeList;
            std::map <int, Node*> m_openList;
            int m_i_open;
            int m_j_close; //indice liste ouverte/fermee
    };

#endif // PATHFINDER_HPP_INCLUDED
