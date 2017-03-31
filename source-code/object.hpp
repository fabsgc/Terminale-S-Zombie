#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include "include.hpp"

    class Object
    {
        public:
            Object();
            ~Object();
            void display(sf::RenderWindow &window);
            void setId(int id);
            void setSprite(std::string sprite);
            void setPosition(PositionItem position);
            int getId();
            sf::Sprite getSprite();
            PositionItem getPosition();

        protected:
            int m_id;
            PositionItem m_positionObject;
            sf::Sprite m_sprite;
    };

#endif // OBJECT_HPP_INCLUDED
