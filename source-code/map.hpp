#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "include.hpp"
#include "node.hpp"
#include "pathfinder.hpp"
#include "object.hpp"
#include "object_card.hpp"
#include "object_weapon.hpp"
#include "object_door.hpp"
#include "object_bonus.hpp"
#include "object_malus.hpp"
#include "object_teleportation.hpp"
#include "tiles.hpp"
#include "light.hpp"
#include "npc.hpp"
#include "player.hpp"

    class Map
    {
        public:
            Map();
            ~Map();
            void displayFloor(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayShadow(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayShadow2(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayLumiereJaune(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayWall(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayObjectFloor(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayObjectWall(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayNpc(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayWeapon(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayCard(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayDoor(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayBonus(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayMalus(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayTeleportation(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayLight(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            void displayBlood(sf::RenderWindow &window, Player * m_player, int width, int height, float deltaTime);
            bool initMap(sf::RenderWindow &window, int level, Player * player, float deltaTime);
            void setNpcs(std::list<Npc> npcs);
            void setLevel(int level);
            std::list<Npc> * getNpcs();
            std::list<Object_Bonus> * getObjectBonus();
            std::list<Object_Card> * getObjectCard();
            std::list<Object_Door> * getObjectDoor();
            std::list<Object_Malus> * getObjectMalus();
            std::list<Object_Weapon> * getObjectWeapon();
            std::list<Object_Teleportation> * getObjectTeleportation();
            std::map<std::pair<int, int>, Tiles> * getTilesWall();
            std::list<Tiles> * getTilesObjectFloor();
            std::list<Tiles> * getTilesObjectWall();
            int getNumberNpc();
            std::map <std::pair<int,int>, Node> * getMMap();
            Npc initNpc(sf::RenderWindow &window, int id, PositionItem position);
            Object_Weapon initWeapon(sf::RenderWindow &window, int id, PositionItem position);
            Object_Card initCard(sf::RenderWindow &window, int id, PositionItem position);
            Object_Door initDoor(sf::RenderWindow &window, int id, PositionItem position, bool open);
            Object_Teleportation initTeleportation(sf::RenderWindow &window, int id, PositionItem position);
            void initBonus(sf::RenderWindow &window, TiXmlElement * Elem);
            void initMalus(sf::RenderWindow &window, TiXmlElement * Elem);
            void setNumberNpc(int npc);
            void deleteNpcDead();
            void deleteContentMap();
            int getLevel();
            std::string int2Str(int x);
        private:
            std::list<Npc> m_npc;
            std::list<Object_Card> m_objectsCard;
            std::list<Object_Weapon> m_objectsWeapon;
            std::list<Object_Door> m_objectsDoor;
            std::list<Object_Bonus> m_objectsBonus;
            std::list<Object_Malus> m_objectsMalus;
            std::list<Object_Teleportation> m_objectsTeleportation;

            std::map<std::pair<int, int>, Tiles> m_tilesFloor;
            std::map<std::pair<int, int>, Tiles> m_tilesShadow;
            std::map<std::pair<int, int>, Tiles> m_tilesShadow2;
            std::map<std::pair<int, int>, Tiles> m_tilesLumiereJaune;
            std::map<std::pair<int, int>, Tiles> m_tilesWall;

            std::list<Tiles> m_tilesObjectFloor;
            std::list<Tiles> m_tilesObjectWall;
            std::list<Tiles> m_tilesBlood;
            std::list<Light> m_lights;

            SoundManager m_sound;
            int m_level;
            Npc npc;
            Object_Card object_Card;
            Object_Weapon object_Weapon;
            Object_Door object_Door;
            Object_Bonus object_Bonus;
            Object_Malus object_Malus;
            Object_Teleportation object_Teleportation;
            Tiles tile;
            Light light;
            PositionItem position;
            int m_objectBonusType;
            int m_objectMalusType;
            int m_numberNpc; //pour fini un niveau, il faut tuer tous les ennemis
            long m_lastLoadLevel; //permet de faire patienter au moment du chargement du niveau
            long m_executionTime;
            sf::Font m_font; //sert a ecrire le nom du niveau au chargement
            sf::String m_textNameLevel;
            std::string m_nameLevel; //contient le nom du niveau
            bool m_initializedLevel; //permet de savoir si le nom du niveau a ete recupere

            std::map <std::pair<int,int>, Node> m_map; //a cause des structures actuelles, on doit coder une simple map contenant juste 1 booléen pour dire si la case est un obstacle (true) ou non (false)
    };

#endif // MAP_HPP_INCLUDED
