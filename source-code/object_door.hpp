#ifndef OBJECT_DOOR_HPP_INCLUDED
#define OBJECT_DOOR_HPP_INCLUDED

#include "object.hpp"

    class Object_Door : public Object
    {
        public:
            Object_Door();
            ~Object_Door();
            void display(sf::RenderWindow &window);
            void setSprite(int id);
            void setOpen(bool open);
            void setChangeLevel(bool changeLevel);
            void setWin(bool win);
            bool getOpen();
            bool getChangeLevel();
            bool getWin();

        private:
            bool m_open;
            int m_spriteId;
            bool m_changeLevel;
            bool m_win;
            sf::Sprite m_sprite;
    };


#endif // OBJECT_DOOR_HPP_INCLUDED
