#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include "include.hpp"

    class Light
    {
        public:
            Light();
            ~Light();
            void display(sf::RenderWindow &window);
            void setId(int id);
            void setPosition(PositionItem position);
            int getId();
            PositionItem getPosition();
        protected:
            int m_id;
            PositionItem m_positionLight;
            sf::Sprite m_sprite;
    };

#endif // LIGHT_HPP_INCLUDED
