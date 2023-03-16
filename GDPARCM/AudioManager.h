#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>


class AudioManager
{
public:
    static AudioManager* getInstance();
    void loadAllAudio();
    sf::Sound* getAudio(std::string key);

    void play(std::string key);
    void setVolume(std::string key, int volume);

    void deleteAllAudio();

private:
    AudioManager() {};
    AudioManager(AudioManager const&) {};
    AudioManager& operator=(AudioManager const&) {};
    static AudioManager* sharedInstance;

private:
    void loadAudio(std::string key, std::string path);
    std::unordered_map<std::string, sf::Sound*> AudioMap;
};
