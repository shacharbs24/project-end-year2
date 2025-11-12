#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <deque>
#include <memory>
#include <string>

class AudioManager
{
public:
    static AudioManager& getInstance();

    sf::Music& getMusic(const std::string& id);
    void playMusic(const std::string& id, bool loop = true);
    void playFx(const std::string& id, float volume = 100.f);

    void toggleMute();
    bool isMuted() const { return m_isMuted; }
    void setMasterVolume(float vol) { m_masterVolume = vol; }

private:
    AudioManager() = default;
    ~AudioManager() = default;

    AudioManager(const AudioManager&) = delete;
    AudioManager& operator=(const AudioManager&) = delete;
    AudioManager(AudioManager&&) = delete;
    AudioManager& operator=(AudioManager&&) = delete;

    using TrackPtr = std::unique_ptr<sf::Music>;
    using BufferPtr = std::shared_ptr<sf::SoundBuffer>;

    std::unordered_map<std::string, TrackPtr> m_tracks; 
    sf::Music* m_currentTrack = nullptr; 
    std::string m_currentTrackId;  

    std::unordered_map<std::string, BufferPtr> m_buffers;
    std::deque<sf::Sound> m_liveSounds; 

    float m_masterVolume = 30.f;
    bool m_isMuted = false;

    void stopMusic(); 
    sf::Sound& acquireSound();
};
