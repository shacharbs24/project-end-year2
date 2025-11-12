#include "Managers/AudioManager.h"
#include <stdexcept>
#include <utility>

AudioManager& AudioManager::getInstance()
{
    static AudioManager instance;
    return instance;
}

sf::Music& AudioManager::getMusic(const std::string& id)
{
    if (auto it = m_tracks.find(id); it != m_tracks.end())
        return *it->second;

    auto music = std::make_unique<sf::Music>();
    const std::string file = id + ".ogg";

    if (!music->openFromFile(file))
        throw std::runtime_error("AudioManager::getMusic – cannot open: " + file);

    music->setVolume(m_isMuted ? 0.f : m_masterVolume);

    auto& ref = *music;
    m_tracks.emplace(id, std::move(music));
    return ref;
}

void AudioManager::playMusic(const std::string& id, bool loop)
{
    if (m_currentTrackId == id) 
        return;

    stopMusic(); 

    sf::Music& track = getMusic(id);
    track.setLoop(loop);
    track.play();

    m_currentTrack = &track;
    m_currentTrackId = id;
}

void AudioManager::stopMusic()
{
    if (m_currentTrack)
    {
        m_currentTrack->stop();
        m_currentTrack = nullptr;
        m_currentTrackId.clear();
    }
}

sf::Sound& AudioManager::acquireSound()
{
    for (auto& s : m_liveSounds)
        if (s.getStatus() == sf::Sound::Stopped)
            return s;

    m_liveSounds.emplace_back();
    return m_liveSounds.back();
}

void AudioManager::playFx(const std::string& id, float volume)
{
 
    BufferPtr buffer;
    if (auto it = m_buffers.find(id); it != m_buffers.end())
        buffer = it->second;
    else
    {
        buffer = std::make_shared<sf::SoundBuffer>();
        const std::string file = id + ".ogg";

        if (!buffer->loadFromFile(file))
            throw std::runtime_error("AudioManager::playFx – cannot load: " + file);

        m_buffers.emplace(id, buffer);
    }

    sf::Sound& sound = acquireSound();
    sound.setBuffer(*buffer);
    sound.setVolume(m_isMuted ? 0.f : volume);
    sound.play();
}

void AudioManager::toggleMute()
{
    m_isMuted = !m_isMuted;
    const float vol = m_isMuted ? 0.f : m_masterVolume;

    if (m_currentTrack)
        m_currentTrack->setVolume(vol);

    for (auto& s : m_liveSounds)
        s.setVolume(vol);

    sf::Listener::setGlobalVolume(vol);
}
