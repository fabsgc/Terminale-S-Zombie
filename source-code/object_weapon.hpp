#ifndef OBJECT_WEAPON_HPP_INCLUDED
#define OBJECT_WEAPON_HPP_INCLUDED

#include "object.hpp"

    class Object_Weapon : public Object
    {
        public:
            Object_Weapon();
            ~Object_Weapon();
            void display(sf::RenderWindow &window);
            void setSprite(int id);
            void setSpriteBullet(int id);
            void setDegat(int degat);
            void setCadence(int cadence);
            void setLastUse(long lastUse);
            void setMunitions(int munitions);
            void setSound (int sound);
            void setSpeed (int speed);
            void setName (std::string name);
            void addWeaponTileBreak(int id);
            int getSpriteBullet();
            int getDegat();
            int getCadence();
            int getLastUse();
            int getMunitions();
            int getSound();
            int getSpeed();
            std::string getName();
            std::list<int> * getWeaponTileBreak();

        private:
            int m_degat;
            int m_cadence;
            long m_lastUse;
            int m_munitions;
            int m_sound;
            int m_speed;
            int m_spriteBullet;
            std::string m_name;
            std::list<int> m_weaponTileBreak;
    };

#endif // OBJECT_WEAPON_HPP_INCLUDED
