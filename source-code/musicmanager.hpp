#ifndef MUSICMANAGER_HPP_INCLUDED
#define MUSICMANAGER_HPP_INCLUDED
#include <SFML/Audio.hpp>

#include "include.hpp"

    class MusicManager
    {
        public :
            static void playMusic(std::string name, float volume, bool loop);

        private :
            static sf::Music m_playedMusic;
    };

#endif // MUSICMANAGER_HPP_INCLUDED
