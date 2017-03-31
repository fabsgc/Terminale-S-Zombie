#include "musicmanager.hpp"

    sf::Music MusicManager::m_playedMusic;

    /**
	 * Joue une musique. note : la même instance de la classe ne peut jouer plusieurs musiques simultanément
	 * @param std::string name : chemin vers la musique
	 * @param float volume : volume entre 0 et 100
	 * @param bool loop : le son sera répété ou non (true ou false)
	 * @access public
	 * @return void
    */
    void MusicManager::playMusic(std::string name, float volume, bool loop)
    {
        m_playedMusic.OpenFromFile(name);
        m_playedMusic.SetLoop(loop);
        m_playedMusic.SetVolume(volume);

        if(m_playedMusic.GetStatus() != sf::Sound::Playing)
        {
            m_playedMusic.Play();
            std::cout << "[INFORMATION] : [MusicManager::playMusic] lancement de : \"" << name << "\", repetition : " << loop << ", volume : " << volume << std::endl;
        }
    }
