#ifndef ASSETS_H
#define ASSETS_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Components.h"


class Assets
{
public:
	std::map<std::string, sf::Texture*> m_textures;
	std::map<std::string, Animation*> m_animations;
	std::map<std::string, sf::Font*> m_fonts;
	std::map<std::string, sf::SoundBuffer*> m_sounds;

public:
	void addTexture(const std::string& name, const std::string& path, float width, float height);
	void addAnimation(const std::string& name, Animation* animation);
	void addFont(const std::string& name, const std::string& path);
	void addSound(const std::string& name, const std::string& path);
	sf::Texture* getTexture(const std::string& name)
	{
		if (m_textures.find(name) == m_textures.end())
		{
			std::cout << "texture not found.\n";
			return nullptr;
		}
		return m_textures[name];
	}
	Animation* getAnimation(const std::string& name)
	{
		if (m_animations.find(name) == m_animations.end())
		{
			std::cout << "\n" << name << ": " << "Animation it not found.\n";
			exit(-5);
		}
		return m_animations[name];
	}
	sf::Font* getFont(const std::string& name)
	{
		if (m_fonts.find(name) == m_fonts.end())
		{
			std::cout << "\n" << name << ": " << "Font is not found.\n";
			exit(-5);
		}
		return m_fonts[name];
	}
	sf::SoundBuffer* getSound(const std::string& name)
	{
		if (m_sounds.find(name) == m_sounds.end())
		{
			std::cout << "\n" << name << ": " << "Sound is not found.\n";
			exit(-5);
		}
		std::cout << "Work";
		return m_sounds[name];
	}
	~Assets()
	{
		for (auto& e : m_textures)
		{
			if (e.second != nullptr)
			{
				delete e.second;
				e.second = nullptr;
			}
		}
		for (auto& e : m_animations)
		{
			if (e.second != nullptr)
			{
				delete e.second;
				e.second = nullptr;
			}
		}
		for (auto& e : m_fonts)
		{
			if (e.second != nullptr)
			{
				delete e.second;
				e.second = nullptr;
			}
		}
		for (auto& e : m_sounds)
		{
			if (e.second != nullptr)
			{
				delete e.second;
				e.second = nullptr;
			}
		}
	}
};

#endif

