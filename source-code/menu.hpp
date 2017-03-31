#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "include.hpp"
#include "gui_menu.hpp"

    class Menu
    {
        public:
            Menu(int width, int height);
            ~Menu();
            void initMenu(sf::RenderWindow &window, int actionCurrent);
            int playMenu(sf::RenderWindow &window, float deltaTime);

        private:
            int m_actionCurrent;
            bool m_alreadyInit;
            int m_width;
            int m_height;
            int m_buttonClicked;
            PositionItem m_position;
            sf::View view;

            Gui_menu m_guiMenu;
            sf::Sprite m_spriteLogo;
            sf::Image m_imageLogo;
    };

#endif // MENU_HPP_INCLUDED
