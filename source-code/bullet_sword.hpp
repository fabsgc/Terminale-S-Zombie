#ifndef BULLET_SWORD_HPP_INCLUDED
#define BULLET_SWORD_HPP_INCLUDED

#include "include.hpp"
#include "anim.hpp"
#include "bullet.hpp"

    class Bullet_sword : public Bullet
    {
        public :
            Bullet_sword();
            void display(sf::RenderWindow &window, const float deltaTime);
            void calculNewPosition(sf::RenderWindow &window, const float deltaTime);
            bool toOld() const;
            ~Bullet_sword();

        private :
    };

#endif // BULLET_SWORD_HPP_INCLUDED
