#ifndef BULLET_FLAME_HPP_INCLUDED
#define BULLET_FLAME_HPP_INCLUDED

#include "include.hpp"
#include "anim.hpp"
#include "bullet.hpp"

    class Bullet_flame : public Bullet
    {
        public :
            Bullet_flame();
            void display(sf::RenderWindow &window, const float deltaTime);
            void calculNewPosition(sf::RenderWindow &window, const float deltaTime);
            bool toOld() const;
            ~Bullet_flame();

        private :
    };

#endif // BULLET_FLAME_HPP_INCLUDED
