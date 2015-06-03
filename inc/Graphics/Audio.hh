/*
 * File:   Sound.hh
 * Author: buchse_a
 *
 * Created on June 3, 2015, 3:08 PM
 */

#ifndef SOUND_HH
#define	SOUND_HH

#include <SFML/Audio.hpp>
#include <map>
#include <list>
#include "Core/Thread.hh"
#include "Core/ThreadPool.hpp"

namespace Audio
{

	class Sound : public Thread::Task
	{
	public:
		Sound(sf::Sound* sound, bool loop);
		virtual ~Sound();

		virtual void	execute();
		void				stop();

	private:
		sf::Sound*	_sound;
		bool			_loop;
	};

	class Music : public Thread::Task
	{
	public:
		Music(sf::Music* music, bool loop);
		virtual ~Music();

		virtual void	execute();
		void				stop();

	private:
		sf::Music*	_music;
		bool			_loop;
	};

	class Manager
	{
	public:
		Manager(size_t channels);
		~Manager();

		void	playMusic(std::string const &, bool loop);
		void	playSound(std::string const &, bool loop);
		void	stopMusic(std::string const &);
		void	stopSound(std::string const &);

	private:
		::ThreadPool<PThread>							_threads;

		std::map<std::string, sf::SoundBuffer*>	_buffers;
		std::list<sf::Sound*>							_sounds;
		std::map<std::string, sf::Music*>			_musics;
	};

}

#endif	/* SOUND_HH */
