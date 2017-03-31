#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "include.hpp"

    class Bullet
    {
        public:
            Bullet();
            void updatePosition();
            void setId(const int id);
            void setSpeed(const int speed);
            void setPosition(const PositionItem position);
            void setExploded(const bool exploded);
            void setTileBreak(std::list<int> * weaponTileBreak);
            void setDegat(int degat);
            int getId() const;
            int getSpeed() const;
            PositionItem getPosition() const;
            PositionItem getNewPosition() const;
            std::list<int> * getTileBreak();
            int getDegat();
            bool getExploded();
            ~Bullet();

        protected:
            int m_id; //permet de savoir depuis quelle arme la balle a ete tiree
            int m_speed;
            long m_executionTime;
            bool m_exploded;
            int m_degat;
            PositionItem m_positionBullet;
            PositionItem m_positionNewBullet; //on calcul la nouvelle position, on la met en "cache"
            std::list<int> * m_weaponTileBreak; //pointeur vers le tableau de l'arme qui a tire contenant les tiles cassables
    };

#endif // BULLET_H_INCLUDED
