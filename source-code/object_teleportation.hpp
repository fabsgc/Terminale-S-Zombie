#ifndef OBJECT_TELEPORTATION_HPP_INCLUDED
#define OBJECT_TELEPORTATION_HPP_INCLUDED

#include "object.hpp"

    class Object_Teleportation : public Object
    {
        public:
            Object_Teleportation();
            ~Object_Teleportation();
            void display(sf::RenderWindow &window);
            void setSprite(int id);
            void setPositionTo(PositionItem positionTo);
            PositionItem getPositionTo();

        private:
            int m_spriteId;
            sf::Sprite m_sprite;
            PositionItem m_positionTo; //vers ou pointe le teleporteur
    };

#endif // OBJECT_TELEPORTATION_HPP_INCLUDED
