#include "SoundManager.h"

std::map<std::string, sf::SoundBuffer> SoundManager::buffers;
std::map<std::string, sf::Sound> SoundManager::sounds;
std::map<std::string, sf::Music*> SoundManager::songs;

void SoundManager::loadSound(const std::string& name, const std::string& path)
{
	sf::SoundBuffer buf;
	buf.loadFromFile(AUDIO_DIRECTORY + path);
	buffers[name] = buf;
	sf::Sound sound;
	sound.setBuffer(buffers[name]);
	sounds[name] = sound;
	return;
}

sf::Sound& SoundManager::getSoundRef(const std::string& key)
{
	return sounds.at(key);
}

void SoundManager::setSoundVolume(float vol)
{
	std::map<std::string, sf::Sound>::iterator it;
	for (it = sounds.begin(); it != sounds.end(); it++)
	{
		it->second.setVolume(vol);
	}
}

void SoundManager::playSound(const std::string& key)
{
	sounds[key].play();
}

void SoundManager::stopSound(const std::string& key)
{
	sounds[key].stop();
}

void SoundManager::loadMusic(const std::string& name, const std::string& path)
{
	songs[name] = new sf::Music;
	sf::Music* m = songs[name];
	m->openFromFile(AUDIO_DIRECTORY + path);
}

sf::Music& SoundManager::getMusicRef(const std::string& key)
{
	return *songs.at(key);
}

void SoundManager::setMusicVolume(float vol)
{
	std::map<std::string, sf::Music*>::iterator it;
	for (it = songs.begin(); it != songs.end(); it++)
	{
		it->second->setVolume(vol);
	}
}

void SoundManager::playMusic(const std::string& key, bool loop)
{
	songs[key]->setLoop(loop);
	songs[key]->play();
}

void SoundManager::pauseMusic(const std::string& key)
{
	songs[key]->pause();
}

void SoundManager::stopMusic(const std::string& key)
{
	songs[key]->stop();
}

void SoundManager::clearBuffers()
{
	buffers.clear();
	sounds.clear();
}