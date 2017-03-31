#ifndef GUI_MENU_HPP_INCLUDED
#define GUI_MENU_HPP_INCLUDED

#include "include.hpp"

    class Gui_menu
    {
        public:
            Gui_menu();
            void setWidthHeight(int width, int height);
            void display(sf::RenderWindow &window);
            void addMenu(int id, PositionItem position, std::string message, int decalageLeftMessage);
            int getClic(int x, int y);
            ~Gui_menu();

        private:
            int m_width;
            int m_height;

            GuiMenuItem m_guiMenuItem;
            std::list<GuiMenuItem> m_guiMenusItem;
            sf::Font m_font;
            sf::String m_textMenu;
            SoundManager m_sound;
    };

#endif // GUI_MENU_HPP_INCLUDED
