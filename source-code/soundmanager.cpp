#include "soundmanager.hpp"

    sf::Sound m_playedSound[NB_MUSIC];
    sf::SoundBuffer m_sounds[NB_MUSIC];

    /**
	 * constructeur
	 * @access public
	 * @return void
    */
    SoundManager::SoundManager()
    {
        m_sounds[0].LoadFromFile("sounds/ping.wav");
        m_playedSound[0].SetBuffer(m_sounds[0]);

        m_sounds[1].LoadFromFile("sounds/bullet.wav");
        m_playedSound[1].SetBuffer(m_sounds[1]);

        m_sounds[2].LoadFromFile("sounds/walk.wav");
        m_playedSound[2].SetBuffer(m_sounds[2]);

        m_sounds[3].LoadFromFile("sounds/bullet_submachine.wav");
        m_playedSound[3].SetBuffer(m_sounds[3]);

        m_sounds[4].LoadFromFile("sounds/bullet_rocket.wav");
        m_playedSound[4].SetBuffer(m_sounds[4]);

        m_sounds[5].LoadFromFile("sounds/bullet_mine.wav");
        m_playedSound[5].SetBuffer(m_sounds[5]);

        m_sounds[6].LoadFromFile("sounds/bullet_grenade_launch.wav");
        m_playedSound[6].SetBuffer(m_sounds[6]);

        m_sounds[7].LoadFromFile("sounds/bullet_flame.wav");
        m_playedSound[7].SetBuffer(m_sounds[7]);

        m_sounds[8].LoadFromFile("sounds/bullet_sword.wav");
        m_playedSound[8].SetBuffer(m_sounds[8]);

        m_sounds[9].LoadFromFile("sounds/player_hurt.wav");
        m_playedSound[9].SetBuffer(m_sounds[9]);

        m_sounds[10].LoadFromFile("sounds/door_open.wav");
        m_playedSound[10].SetBuffer(m_sounds[10]);

        m_sounds[12].LoadFromFile("sounds/bullet_grenade.wav");
        m_playedSound[12].SetBuffer(m_sounds[12]);

        m_sounds[13].LoadFromFile("sounds/zombie_hit.wav");
        m_playedSound[13].SetBuffer(m_sounds[13]);

        m_sounds[14].LoadFromFile("sounds/tile_break.wav");
        m_playedSound[14].SetBuffer(m_sounds[14]);

        m_sounds[15].LoadFromFile("sounds/bullet_ricochet.wav");
        m_playedSound[15].SetBuffer(m_sounds[15]);

        m_sounds[16].LoadFromFile("sounds/ping2.wav");
        m_playedSound[16].SetBuffer(m_sounds[16]);

        m_sounds[17].LoadFromFile("sounds/zombie_hurt.wav");
        m_playedSound[17].SetBuffer(m_sounds[17]);

        m_sounds[18].LoadFromFile("sounds/game_over.wav");
        m_playedSound[18].SetBuffer(m_sounds[18]);

        m_sounds[19].LoadFromFile("sounds/zombie_dead.wav");
        m_playedSound[19].SetBuffer(m_sounds[19]);

        m_sounds[20].LoadFromFile("sounds/bullet_sword_clash.wav");
        m_playedSound[20].SetBuffer(m_sounds[20]);

        m_sounds[21].LoadFromFile("sounds/grenade_mine_exploded.wav");
        m_playedSound[21].SetBuffer(m_sounds[21]);

        m_sounds[22].LoadFromFile("sounds/bullet_gun4.wav");
        m_playedSound[22].SetBuffer(m_sounds[22]);
    }

    /**
	 * Joue un son. note : la même instance de la classe ne peut jouer le même son que une fois simultanément
	 * @param int numero : nu
	 mero du son
	 * @param float volume : volume entre 0 et 100
	 * @param bool loop : le son sera répété ou non (true ou false)
	 * @access public
	 * @return void
    */
    void SoundManager::playSound(int numero, float volume, bool loop, PositionItem position, float minDistance, float attenuation, bool relative)
    {
        m_playedSound[numero-1].SetLoop(loop);
        m_playedSound[numero-1].SetVolume(volume);
        m_playedSound[numero-1].SetPosition(position.x, position.y, 0.f);
        m_playedSound[numero-1].SetAttenuation(attenuation);
        m_playedSound[numero-1].SetMinDistance(minDistance);

        if(relative == true)
        {
            m_playedSound[numero-1].SetRelativeToListener(true);
            m_playedSound[numero-1].SetPosition(0.f, 0.f, 0.f);
            m_playedSound[numero-1].SetAttenuation(0.f);
            m_playedSound[numero-1].SetMinDistance(2048);
        }

        if(m_playedSound[numero-1].GetStatus() != sf::Sound::Playing)
        {
            m_playedSound[numero-1].Play();
            std::cout << "[INFORMATION] : [SoundManager::playSound] : lancement de : \"" << numero-1 << "\", repetition : " << loop << ", volume : " << volume << std::endl;
        }
    }

    /**
	 * Met le son en pause
	 * @param int numero : numero du son
	 * @access public
	 * @return void
    */
    void SoundManager::pauseSound(int numero)
    {
        if(m_playedSound[numero-1].GetStatus() == sf::Sound::Playing)
        {
            m_playedSound[numero-1].Pause();
            std::cout << "[INFORMATION] : [SoundManager::playSound] : pause de : \"" << numero-1 << std::endl;
        }
    }

    /**
	 * Arrête le son
	 * @param int numero : numero du son
	 * @access public
	 * @return void
    */
    void SoundManager::stopSound(int numero)
    {
        if(m_playedSound[numero-1].GetStatus() == sf::Sound::Playing)
        {
            m_playedSound[numero-1].Stop();
            std::cout << "[INFORMATION] : [SoundManager::playSound] : arret de : \"" << numero-1 << std::endl;
        }
    }

    SoundManager::~SoundManager()
    {

    }
