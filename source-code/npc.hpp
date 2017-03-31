#include "player.hpp"

#ifndef NPC_HPP_INCLUDED
#define NPC_HPP_INCLUDED

#include "include.hpp"
#include "node.hpp"
#include "pathfinder.hpp"
#include "object.hpp"
#include "object_door.hpp"
#include "bullet.hpp"

    class Npc
    {
        public:
            Npc();
            ~Npc();
            void prendreDegat(int degat, float deltaTime, int timeBetweenAttack);
            void calculNewPosition(sf::RenderWindow &window, float deltaTime);
            void updatePosition();
            void display(sf::RenderWindow &window);

            void setId(int id);
            void setDegat(int degat);
            void setLife(int life);
            void setSpeed(int speed);
            void setPosition(PositionItem position);
            void setPositionX(float x);
            void setPositionY(float y);
            void setSprite(std::string sprite);
            void setTypeSprite(int typeSprite);
            void setMapAstar(std::map <std::pair<int,int>, Node> * map);
            void setNodeStartAstar(int x, int y);
            void setNodeEndAstar(int x, int y);
            void setFindPath(bool findPath);
            void setPlayerDetected(bool playerDetected);
            void setPlayerPosition(PositionItem positionPlayer);
            void setActionCurrent(int actionCurrent);
            int getId();
            int getDegat();
            int getLife();
            int getSpeed();
            int getTypeSprite();
            std::map <std::pair<int,int>, Node> * getMapAstar();
            bool setFindPath();
            int setActionCurrent();
            Node * getNodeStartAstar();
            Node * getNodeEndAstar();
            bool getFindPath();
            bool getPlayerDetected();
            int getActionCurrent();
            PositionItem getPosition();
            PositionItem getNewPosition();

        private:
            SoundManager m_sound;
            int m_id;
            int m_degat;
            int m_life;
            int m_speed;
            int m_typeSprite;
            long m_executionTime;
            long m_lastAttackTime;
            PositionItem m_positionNpc;
            PositionItem m_positionNewNpc; //on calcul la nouvelle position, on la met en "cache"

            std::map <std::pair<int,int>, Node> * m_map;
            Node m_nodeStart;
            Node m_nodeEnd;
            Node m_nodePlayer;
            Node m_nodeNpc;
            std::map <int, Node> m_path;
            Node * m_currentNodePath;
            int m_widthPath;
            bool m_playerDetected;
            int m_lastSearchPathPlayerTime;
            PositionItem m_positionPlayer;
            int m_actionCurrent;
            bool m_findPath;
            unsigned int m_nodePath; //numero du node on l'on va

            sf::Sprite * m_sprite;
            Anim m_animNpc;
    };

#endif // NPC_HPP_INCLUDED
