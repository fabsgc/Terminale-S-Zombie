#ifndef SOUND_HPP
#define SOUND_HPP
#include <SFML/Audio.hpp>
#define NB_MUSIC 23
#include "include.hpp"

    class SoundManager
    {
        public :
            SoundManager();
            void playSound(int numero, float volume, bool loop, PositionItem position, float minDistance = 512, float attenuation = 1, bool relative = false);
            void pauseSound(int numero);
            void stopSound(int numero);
            ~SoundManager();

        private :
    };

#endif // SOUND_HPP_INCLUDED
