#ifndef TILES_HPP_INCLUDED
#define TILES_HPP_INCLUDED

#include "include.hpp"

    class Tiles
    {
        public:
            Tiles();
            ~Tiles();
            void initTile(const bool collision, const int id, const PositionItem position);
            void display(sf::RenderWindow &window, float deltaTime);
            void prendreDegat(const int degat, float deltaTime, int timeBetweenAttack);
            bool getCollision();
            PositionItem getPosition();
            int getLife();
            int getId();

        private:
            int m_id;
            int m_life;
            bool m_collision;
            sf::Sprite m_sprite;
            long m_executionTime;
            long m_lastAttackTime;
            PositionItem m_positionTiles;

    };

#endif // TILES_HPP_INCLUDED
