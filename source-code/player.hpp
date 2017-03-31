#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "include.hpp"
#include "bullet.hpp"
#include "bullet_bullet.hpp"
#include "bullet_flame.hpp"
#include "bullet_grenade.hpp"
#include "bullet_mine.hpp"
#include "bullet_sword.hpp"
#include "anim.hpp"
#include "object.hpp"
#include "object_card.hpp"
#include "object_weapon.hpp"
#include "object_door.hpp"
#include "object_bonus.hpp"
#include "object_malus.hpp"
#include "tiles.hpp"
#include "npc.hpp"

    class Player
    {
        public:
            Player();
            ~Player();
            void calculNewPosition(sf::RenderWindow &window, float deltaTime);
            void updatePosition();
            void display(sf::RenderWindow &window, float deltaTime);
            void displayBulletBullet(sf::RenderWindow &window, float deltaTime);
            void displayBulletFlame(sf::RenderWindow &window, float deltaTime);
            void displayBulletGrenade(sf::RenderWindow &window, float deltaTime);
            void displayBulletMine(sf::RenderWindow &window, float deltaTime);
            void displayBulletSword(sf::RenderWindow &window, float deltaTime);
            void displayInfo(sf::RenderWindow &window, int width, int height);
            void prendreDegat(Npc &npc, float deltaTime);
            void prendreDegatBullet(int degat, float deltaTime, int timeBetweenAttack);
            void shoot();
            void shootBullet();
            void shootMine();
            void shootGrenade();
            void shootFlame();
            void shootSword();
            void changeWeapon(sf::RenderWindow &window);

            void setLife(int life);
            void setLevel(int level);
            void setWin(bool win);
            void setSpeed(int speed);
            void setPosition(PositionItem position);
            void setPositionX(float x);
            void setPositionY(float y);
            void setTeleported(bool teleported, PositionItem positionTo, PositionItem positionTeleporteur, float coeff);
            void addCard(Object_Card objectCard);
            void setWeapon(Object_Weapon objectWeapon, int id);
            void setBulletBullets(std::list<Bullet_bullet> bullet_bullet);
            void setBulletMines(std::list<Bullet_mine> bullet_mine);
            void setBulletGrenades(std::list<Bullet_grenade> bullet_grenade);
            void setBulletFlames(std::list<Bullet_flame> bullet_flame);
            void setBulletSwords(std::list<Bullet_sword> bullet_sword);
            void setMunitionsWeapon(int weapon, int munitions);
            int getLife();
            int getLevel();
            bool getWin();
            int getSpeed();
            PositionItem getPosition();
            PositionItem getNewPosition();
            std::list<Object_Card> * getCards();
            Object_Weapon * getWeapon();
            Object_Weapon * getWeaponId(int id);
            std::list<Bullet_bullet> * getBulletBullets();
            std::list<Bullet_mine> * getBulletMines();
            std::list<Bullet_grenade> * getBulletGrenades();
            std::list<Bullet_flame> * getBulletFlames();
            std::list<Bullet_sword> * getBulletSwords();
            bool getTeleported();
            std::string int2Str(int x);
            float distance(const PositionItem p1, const PositionItem p2);
            void deleteContentPlayer();

        private:
            int m_life;
            int m_level;
            bool m_win;
            int m_speed;
            int m_armeActive;
            int m_lastChangeArme;
            long m_executionTime;
            long m_lastAttackTime;
            bool m_teleported; //sert a savoir si le joueur est en train de se faire teleporter ou non
            float m_coeffTeleported;
            int m_gameplay;

            sf::Sprite * m_sprite;
            sf::Sprite m_spriteLife;
            sf::Sprite m_spriteWeapon;
            sf::Font m_font;
            sf::String m_textLife;
            sf::String m_textWeapon;
            Anim m_animPlayer;

            std::list<Object_Card> m_objectsCard;
            std::list<Bullet_bullet> m_bulletBullet;
            std::list<Bullet_flame> m_bulletFlame;
            std::list<Bullet_grenade> m_bulletGrenade;
            std::list<Bullet_mine> m_bulletMine;
            std::list<Bullet_sword> m_bulletSword;

            Object_Weapon * m_objectWeapon; // pointeur vers l'arme en cours d'utilisation, permet d'économiser de la mémoire et de faire les changements sur l'arme en temps réel
            Object_Weapon m_objectWeapons[NUMBER_WEAPON_PLAYER];
            PositionItem m_positionPlayer; //position affichee
            PositionItem m_positionNewPlayer; //on calcul la nouvelle position, on la met en "cache"
            PositionItem m_positionTeleportationToPlayer; //on calcul la nouvelle position, on la met en "cache"
            PositionItem m_positionTeleportationPlayer; //permet d'eviter les cas de calcul a l'infini
            PositionItem position; //sert a calculer orientation perso avec souris
            PositionItem position2;
            float coefDirecteurPosition;

            Bullet_bullet bulletBullet;
            Bullet_flame bulletFlame;
            Bullet_grenade bulletGrenade;
            Bullet_mine bulletMine;
            Bullet_sword bulletSword;

            SoundManager m_sound;
    };

#endif // PLAYER_HPP_INCLUDED
