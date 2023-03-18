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

	loadAudio("MainMenu", "Media/Audio/TrailsMainMenu.ogg");
	AudioManager::getInstance()->getAudio("MainMenu")->setLoop(true);

	//SFX LOADING
	loadAudio("Select", "Media/Audio/SFX/Select.wav");
	loadAudio("Hover", "Media/Audio/SFX/Hover.wav");
	loadAudio("SCraft", "Media/Audio/SFX/SCraft.ogg");
	loadAudio("SCraftReady", "Media/Audio/SFX/SCraftReady.wav");

	//ESTELLE AUDIO
	loadAudio("EstelleS1", "Media/Audio/SFX/Estelle/EstelleStandby1.ogg");
	loadAudio("EstelleS2", "Media/Audio/SFX/Estelle/EstelleStandby2.ogg");
	loadAudio("EstelleD1", "Media/Audio/SFX/Estelle/EstelleDamage1.ogg");
	loadAudio("EstelleD2", "Media/Audio/SFX/Estelle/EstelleDamage2.ogg");
	loadAudio("EstelleA1", "Media/Audio/SFX/Estelle/EstelleAttack1.ogg");
	loadAudio("EstelleA2", "Media/Audio/SFX/Estelle/EstelleAttack2.ogg");
	loadAudio("EstelleA3", "Media/Audio/SFX/Estelle/EstelleAttack3.ogg");
	loadAudio("BluntHit", "Media/Audio/SFX/BluntHit.ogg");


	//JOSHUA AUDIO
	loadAudio("JoshuaS1", "Media/Audio/SFX/Joshua/JoshuaStandby1.ogg");
	loadAudio("JoshuaS2", "Media/Audio/SFX/Joshua/JoshuaStandby2.ogg");
	loadAudio("JoshuaD1", "Media/Audio/SFX/Joshua/JoshuaDamage1.ogg");
	loadAudio("JoshuaD2", "Media/Audio/SFX/Joshua/JoshuaDamage2.ogg");
	loadAudio("JoshuaD3", "Media/Audio/SFX/Joshua/JoshuaDamage3.ogg");
	loadAudio("JoshuaD4", "Media/Audio/SFX/Joshua/JoshuaDamage4.ogg");
	loadAudio("JoshuaA1", "Media/Audio/SFX/Joshua/JoshuaAttack1.ogg");
	loadAudio("JoshuaA2", "Media/Audio/SFX/Joshua/JoshuaAttack2.ogg");
	loadAudio("JoshuaA3", "Media/Audio/SFX/Joshua/JoshuaAttack3.ogg");
	loadAudio("Slash", "Media/Audio/SFX/Slash.ogg");


	//ENEMY AUDIO
	loadAudio("EnemyD1", "Media/Audio/SFX/Enemy/EnemyDamage1.ogg");
	loadAudio("EnemyS1", "Media/Audio/SFX/Enemy/EnemyStandby1.ogg");
	loadAudio("MetalPunch", "Media/Audio/SFX/MetalPunch.ogg");
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
	AudioManager::getInstance()->setVolume(key, 10);
	AudioManager::getInstance()->getAudio(key)->play();
}

void AudioManager::setVolume(std::string key, int volume)
{
	AudioManager::getInstance()->getAudio(key)->setVolume(volume);
}

void AudioManager::deleteAllAudio()
{
	this->AudioMap.clear();
}
