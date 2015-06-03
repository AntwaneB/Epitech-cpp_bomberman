/*
 * File:   Sound.cpp
 * Author: buchse_a
 *
 * Created on June 3, 2015, 3:08 PM
 */

#include <SFML/Audio/Sound.hpp>
#include <iostream>
#include "Graphics/Audio.hh"
#include "Exception.hpp"
#include "Core/ThreadPool.hpp"

Audio::Sound::Sound(sf::Sound* sound, bool loop)
	: _sound(sound), _loop(loop)
{
}

Audio::Sound::~Sound()
{
}

void
Audio::Sound::execute()
{
	_sound->setVolume(20);
	_sound->setLoop(_loop);
	_sound->play();
	delete this;
}

Audio::Music::Music(sf::Music* music, bool loop)
	: _music(music), _loop(loop)
{
}

Audio::Music::~Music()
{
}

void
Audio::Music::execute()
{
	_music->setVolume(100);
	_music->setLoop(_loop);
	_music->play();
	delete this;
}

Audio::Manager::Manager(size_t channels)
	: _threads(channels)
{
}

Audio::Manager::~Manager()
{
	for (auto it = _buffers.begin(); it != _buffers.end(); ++it)
		delete it->second;
	for (auto it = _sounds.begin(); it != _sounds.end(); ++it)
		delete *it;
	for (auto it = _musics.begin(); it != _musics.end(); ++it)
		delete it->second;
}

void
Audio::Manager::playMusic(const std::string& path, bool loop)
{
	auto music = _musics.find(path);

	if (music == _musics.end())
	{
		_musics[path] = new sf::Music;
		if (!_musics[path]->openFromFile(path))
			throw AssetException(path + ": couldn't load file.");
	}
	_threads.pushTask(new Audio::Music(_musics[path], loop));
	_threads.runTasks();
}

void
Audio::Manager::playSound(const std::string& path, bool loop)
{
	auto buffer = _buffers.find(path);

	if (buffer == _buffers.end())
	{
		_buffers[path] = new sf::SoundBuffer;
		if (!_buffers[path]->loadFromFile(path))
			throw AssetException(path + ": couldn't load file.");
	}
	sf::Sound* sound = new sf::Sound;
	sound->setBuffer(*(_buffers[path]));
	_threads.pushTask(new Audio::Sound(sound, loop));
	_threads.runTasks();
}
