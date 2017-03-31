#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "include.hpp"
#include "gui_message.hpp"
#include "gui_menu.hpp"
#include "physic.hpp"
#include "object.hpp"
#include "object_card.hpp"
#include "object_weapon.hpp"
#include "object_door.hpp"
#include "object_bonus.hpp"
#include "object_malus.hpp"
#include "object_teleportation.hpp"
#include "bullet.hpp"
#include "tiles.hpp"
#include "light.hpp"
#include "map.hpp"
#include "player.hpp"
#include "npc.hpp"

    class Game
    {
        public:
            Game(int width, int height);
            ~Game();
            void initGame(sf::RenderWindow &window, int actionCurrent);
            void initMenu();
            int playGame(sf::RenderWindow &window, float deltaTime);
            int playPause(sf::RenderWindow &window, float deltaTime);
            void checkPause(sf::RenderWindow &window);
            void displayWin(sf::RenderWindow &window);
            void displayLose(sf::RenderWindow &window);
            int save();
            void setAlreadyInit(bool init);

        private:
            void initPlayerNewGame(sf::RenderWindow &window);
            void initPlayerLoadGame(sf::RenderWindow &window);
            std::string int2Str(int x);

            int m_actionCurrent;
            bool m_alreadyInit;
            int m_width;
            int m_height;
            time_t m_lastPause; //temps depuis la dernière pause, permet d'eviter d'avoir un effet de boucle avec sf::input
            sf::View view;
            time_t t;
            Physic m_physic;
            Map m_map;
            SoundManager m_sound;
            PositionItem m_position;
            Object_Weapon m_objectWeapon; //sert lors ce qu'on affecte une arme au joueur, on construit l'object ici puis on le donne au joueur
            Object_Card m_objectCard; //sert lors ce qu'on donne une nouvelle carte au joueur, on construit l'object ici puis on le donne au joueur
            Player m_player;
            Gui_menu m_guiMenuPause;
            long m_executionTime;
            int m_buttonClicked;

            Object_Weapon initWeapon(sf::RenderWindow &window, int id);
            Object_Card initCard(sf::RenderWindow &window, int id);
            Object_Door initDoor(sf::RenderWindow &window, int id);

            Gui_menu m_guiMenu;
            Gui_message m_guiMessage;

            sf::Sprite m_spriteGagne;
            sf::Image m_imageGagne;
    };

#endif // GAME_HPP_INCLUDED
