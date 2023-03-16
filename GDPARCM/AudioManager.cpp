#include <iostream>
#include <cstddef>
#include <SFML/Audio.hpp>
#include "AudioManager.h"

AudioManager* AudioManager::sharedInstance = NULL;

AudioManager* AudioManager::getInstance() {
	//initialize only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new AudioManager();
	}
	return sharedInstance;
}

void AudioManager::loadAllAudio() {
	//BGM LOADING
	loadAudio("Battle", "Media/Audio/TOCS_AtrociousRaidSAV.ogg");
	AudioManager::getInstance()->getAudio("Battle")->setLoop(true);


	loadAudio("Intro", "Media/Audio/TrailsInTheSkyIntro.ogg");

	//SFX LOADING
	//loadAudio("collide", "Media/Sounds/SFX/collide.ogg");
}

void AudioManager::loadAudio(std::string key, std::string path) {
	sf::SoundBuffer* Audio = new sf::SoundBuffer();
	Audio->loadFromFile(path);
	sf::Sound* sound = new sf::Sound();
	sound->setBuffer(*Audio);
	AudioMap[key] = sound;
}

sf::Sound* AudioManager::getAudio(std::string key) {
	if (AudioMap[key] != NULL) {
		return AudioMap[key];
	}
	else {
		std::cout << "No Audio found for " << key;
		return NULL;
	}
}

void AudioManager::play(std::string key)
{
	AudioManager::getInstance()->getAudio(key)->play();
	AudioManager::getInstance()->setVolume(key, 50);
}

void AudioManager::setVolume(std::string key, int volume)
{
	AudioManager::getInstance()->getAudio(key)->setVolume(volume);
}

void AudioManager::deleteAllAudio()
{
	this->AudioMap.clear();
}
