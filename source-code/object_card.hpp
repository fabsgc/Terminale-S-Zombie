#ifndef OBJECT_CARD_HPP_INCLUDED
#define OBJECT_CARD_HPP_INCLUDED

#include "object.hpp"

    class Object_Card : public Object
    {
        public:
            Object_Card();
            ~Object_Card();
            void display(sf::RenderWindow &window);
            void setSprite(int id);

        private:
    };

#endif // OBJECT_CARD_HPP_INCLUDED
