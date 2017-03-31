#ifndef BULLET_MINE_HPP_INCLUDED
#define BULLET_MINE_HPP_INCLUDED

#include "include.hpp"
#include "anim.hpp"
#include "bullet.hpp"

    class Bullet_mine : public Bullet
    {
        public :
            Bullet_mine();
            void display(sf::RenderWindow &window, const float deltaTime);
            void calculNewPosition(sf::RenderWindow &window, const float deltaTime);
            bool toOld() const;
            bool getActivated() const;
            void setExploded(const bool exploded);
            void setActivated(const bool activated);
            ~Bullet_mine();

        private :
            bool m_activated;
            SoundManager m_sound;
    };

#endif // BULLET_MINE_HPP_INCLUDED
