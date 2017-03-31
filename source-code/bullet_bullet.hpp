#ifndef BULLET_BULLET_HPP_INCLUDED
#define BULLET_BULLET_HPP_INCLUDED

#include "include.hpp"
#include "bullet.hpp"

    class Bullet_bullet : public Bullet
    {
        public :
            Bullet_bullet();
            void display(sf::RenderWindow &window, const float deltaTime);
            void calculNewPosition(sf::RenderWindow &window, const float deltaTime);
            bool toOld() const;
            void setSprite(const int sprite);
            int getSprite() const;
            ~Bullet_bullet();

        private :
            int m_spriteId; //permet de savoir quel sprite afficher pour la balle
    };

#endif // BULLET_BULLET_HPP_INCLUDED
