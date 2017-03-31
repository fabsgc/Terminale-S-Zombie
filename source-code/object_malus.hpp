#ifndef OBJECT_MALUS_HPP_INCLUDED
#define OBJECT_MALUS_HPP_INCLUDED

#include "object.hpp"

    class Object_Malus : public Object
    {
        public:
            Object_Malus();
            ~Object_Malus();
            void display(sf::RenderWindow &window);
            void setType(int type);
            void setValue(int value);
            void setArmeId(int id);
            int getType();
            int getValue();
            int getArmeId();

        private:
            int m_type; // 1 : vitesse, 2 : vie, 3 : munitions armes
            int m_value;
            int m_armeMalus; //dans le cas où le bonus concerne une arme, on identifie quelle est l'arme 1 a 6
            sf::Sprite m_sprite;
    };

#endif // OBJECT_MALUS_HPP_INCLUDED
