#ifndef PHYSIC_HPP_INCLUDED
#define PHYSIC_HPP_INCLUDED

#include "include.hpp"
#include "node.hpp"
#include "pathfinder.hpp"
#include "gui_message.hpp"
#include "map.hpp"
#include "bullet.hpp"
#include "bullet_bullet.hpp"
#include "bullet_flame.hpp"
#include "bullet_grenade.hpp"
#include "bullet_mine.hpp"
#include "bullet_sword.hpp"
#include "object.hpp"
#include "object_card.hpp"
#include "object_weapon.hpp"
#include "object_door.hpp"
#include "object_bonus.hpp"
#include "object_malus.hpp"
#include "object_teleportation.hpp"
#include "tiles.hpp"
#include "player.hpp"
#include "npc.hpp"

    class Physic
    {
        public:
            Physic();
            ~Physic();
            void setPointerValue(Player * player, Map* map);
            void setWidthHeight(int width, int height);
            void deleteMessage();
            void displayMessage(sf::RenderWindow &window, float deltaTime, PositionItem position);
            int calculCollision(sf::RenderWindow &window, Player * player, Map* map, sf::View* view, float deltaTime, int actionCurrent);
            void calculPositionPlayer(sf::RenderWindow &window, Player * player, float deltaTime);
            void calculPositionNpc(sf::RenderWindow &window, Map* map, float deltaTime);
            void calculPositionBulletBullet(sf::RenderWindow &window, Player * player, float deltaTime);
            void calculPositionBulletFlame(sf::RenderWindow &window, Player * player, float deltaTime);
            void calculPositionBulletGrenade(sf::RenderWindow &window, Player * player, float deltaTime);
            void calculPositionBulletMine(sf::RenderWindow &window, Player * player, float deltaTime);
            void calculPositionBulletSword(sf::RenderWindow &window, Player * player, float deltaTime);

            void calculCollisionPlayerNpc(Player * player, Map* map, float deltaTime);
            void calculCollisionPlayerNpcAttack(Player * player, Map* map, float deltaTime);
            void calculCollisionPlayerBulletGrenade(Player * player, Map* map, float deltaTime);
            void calculCollisionPlayerBulletMine(Player * player, Map* map, float deltaTime);
            void calculCollisionPlayerObjectBonus(Player * player, Map* map);
            void calculCollisionPlayerObjectCard(Player * player, Map* map);
            int  calculCollisionPlayerObjectDoor(Player * player, Map* map, int actionCurrent, float deltaTime);
            void calculCollisionPlayerObjectMalus(Player * player, Map* map);
            void calculCollisionPlayerObjectWeapon(Player * player, Map* map);
            void calculCollisionPlayerObjectTeleportation(Player * player, Map* map);
            void calculCollisionPlayerTilesObjectFloor(Player * player, Map* map);
            void calculCollisionPlayerTilesWall(Player * player, Map* map);
            void calculCollisionNpcBulletBullet(Player * player, Map* map, float deltaTime);
            void calculCollisionNpcBulletFlame(Player * player, Map* map, float deltaTime);
            void calculCollisionNpcBulletGrenade(Player * player, Map* map, float deltaTime);
            void calculCollisionNpcBulletMine(Player * player, Map* map, float deltaTime);
            void calculCollisionNpcBulletSword(Player * player, Map* map, float deltaTime);
            void calculCollisionNpcObjectDoor(Player * player, Map* map);
            void calculCollisionNpcTilesObjectFloor(Player * player, Map* map);
            void calculCollisionNpcTilesWall(Player * player, Map* map);

            void calculCollisionBulletBulletTilesObjectFloor(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletBulletTilesWall(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletBulletObjectDoor(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletFlameTilesObjectWall(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletFlameTilesObjectFloor(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletFlameTilesWall(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletGrenadeTilesObjectWall(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletGrenadeTilesObjectFloor(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletGrenadeTilesWall(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletGrenadeObjectDoor(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletMineTilesObjectWall(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletMineTilesObjectFloor(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletMineTilesWall(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletSwordTilesObjectWall(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletSwordTilesObjectFloor(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletSwordTilesWall(Player * player, Map* map, float deltaTime);
            void calculCollisionBulletSwordObjectDoor(Player * player, Map* map, float deltaTime);
            void calculOpenDoors(Player * player, Map* map);

            void updatePositionPlayer(Player * player);
            void updatePositionNpc(Map* map);
            void updatePositionBulletBullet(Player * player);
            void updatePositionBulletFlame(Player * player);
            void updatePositionBulletGrenade(Player * player);
            void updatePositionBulletMine(Player * player);
            void updatePositionBulletSword(Player * player);

            float distance(const PositionItem p1, const PositionItem p2);
            int lowDistance(const PositionItem p1);
            std::string int2Str(int x);

        private:
            SoundManager m_sound;
            PositionItem m_positionPlayer;
            PositionItem m_positionNpc;
            PositionItem m_positionOther;
            PositionItem m_positionBullet1;
            PositionItem m_positionBullet2;
            PositionItem m_positionBullet3;
            PositionItem m_positionCollision[4];

            std::list<Npc> * m_npc;
            std::list<Bullet_bullet> * m_bullet_bullet;
            std::list<Bullet_flame> * m_bullet_flame;
            std::list<Bullet_grenade> * m_bullet_grenade;
            std::list<Bullet_mine> * m_bullet_mine;
            std::list<Bullet_sword> * m_bullet_sword;

            std::list<Object_Bonus> * m_object_bonus;
            std::list<Object_Card> * m_object_card;
            std::list<Object_Card> * m_object_card_player;
            std::list<Object_Door> * m_object_door;
            std::list<Object_Malus> * m_object_malus;
            std::list<Object_Weapon> * m_object_weapon;
            std::list<Object_Teleportation> * m_object_teleportation;

            std::map<std::pair<int, int>, Tiles> * m_tilesWall;
            std::list<Tiles> * m_tilesObjectFloor;
            std::list<Tiles> * m_tilesObjectWall;

            std::list<int> * m_weaponTileBreak;

            Gui_message m_guiMessage;

            int m_timeLastCreateMessageErrorWinChangeLevel;
            int m_executionTime;
    };

#endif // PHYSIC_HPP_INCLUDED
