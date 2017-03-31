#ifndef GUI_MESSAGE_HPP_INCLUDED
#define GUI_MESSAGE_HPP_INCLUDED

#include "include.hpp"
#include "player.hpp"

    class Gui_message
    {
        public:
            Gui_message();
            void setWidthHeight(int width, int height);
            void display(sf::RenderWindow &window, float deltaTime, PositionItem position);
            void addMessage(int time_max = TIME_MAX_MESSAGE, std::string message1 = "", std::string message2 = "", std::string message3 = "");
            void deleteMessage();
            ~Gui_message();
        private:
            int m_width;
            int m_height;

            GuiMessageItem m_guiMessageItem;
            std::list<GuiMessageItem> m_guiMessagesItem;
            sf::Font m_font;
            sf::String m_textMessage;
    };

#endif // GUI_MESSAGE_HPP_INCLUDED
