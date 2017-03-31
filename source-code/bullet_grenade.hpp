#ifndef BULLET_GRENADE_HPP_INCLUDED
#define BULLET_GRENADE_HPP_INCLUDED

#include "include.hpp"
#include "anim.hpp"
#include "bullet.hpp"

    class Bullet_grenade : public Bullet
    {
        public :
            Bullet_grenade();
            void display(sf::RenderWindow &window, const float deltaTime);
            void calculNewPosition(sf::RenderWindow &window, const float deltaTime);
            bool toOld() const;
            ~Bullet_grenade();

        private :
            int m_timeBeforeExplosion;
            int m_timeLastMouvement;
            SoundManager m_sound;
    };

#endif // BULLET_GRENADE_HPP_INCLUDED
