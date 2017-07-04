#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include "Logger.h"
#include "../Resources.h"

class SoundManager
{
public:
	static void loadSound(const std::string& name, const std::string& path); //Loads buffer and sound into maps
	static sf::Sound& getSoundRef(const std::string& key); //Returns the sound for a key
	static void setSoundVolume(float vol); //Sets the volume for all sounds
	static void playSound(const std::string& key); 
	static void stopSound(const std::string& key);

	static void loadMusic(const std::string& name, const std::string& path); //Loads Music pointer into map
	static sf::Music& getMusicRef(const std::string& key); //Returns music for a key
	static void setMusicVolume(float vol); //Sets volume of all music
	static void playMusic(const std::string& key, bool loop);
	static void pauseMusic(const std::string& key);
	static void stopMusic(const std::string& key);

	static void clearBuffers(); //Clears all buffers

private:
	static std::map<std::string, sf::SoundBuffer> buffers;
	static std::map<std::string, sf::Sound> sounds;
	static std::map<std::string, sf::Music*> songs;

};