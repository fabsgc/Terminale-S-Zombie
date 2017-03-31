#ifndef ANIM_HPP_INCLUDED
#define ANIM_HPP_INCLUDED

#include "include.hpp"

    class Anim
    {
        public:
            Anim();
            ~Anim();
            void setSprite(const sf::Image * image);
            void setSpriteChangeTime(const int spriteChangeTime);
            void setSpriteNumber(const int spriteNumber);
            void setSpriteWidth(const int spriteWidth);
            void setSpriteHeight(const int spriteHeight);
            void setSpriteCenterX(const int spriteCenterX);
            void setSpriteCenterY(const int spriteCenterY);
            void animPlay(const int spriteDeltaTime);
            void animStop(const int spriteDeltaTime);
            int getCurrentSprite() const;
            sf::Sprite * getSprite(const int positionX, const int positionY);

        private:
            sf::Sprite m_spriteAnim;

            int m_spriteChangeTime; //temps entre chaque changement de sprite en millisecondes
            long m_spriteExecutionTime;
            long m_spriteLastExecution;
            int m_spriteNumber; //
            int m_spriteFirstSprite;
            int m_spriteWidth;
            int m_spriteHeight;
            int m_spriteCenterX;
            int m_spriteCenterY;
            int m_spriteCurrentSprite;
            bool m_animPlay;
    };

#endif // ANIM_HPP_INCLUDED
