#ifndef ASSETS_H
#define ASSETS_H
#include <SFML/Graphics.hpp>
#include "Components.h"


class Assets
{
public:
	std::map<std::string, sf::Texture*> m_textures;
	std::map<std::string, Animation*> m_animations;
	std::map<std::string, sf::Font*> m_fonts;

public:
	void addTexture(const std::string& name, const std::string& path, float width, float height);
	void addAnimation(const std::string& name, Animation* animation);
	void addFont(const std::string& name, const std::string& path);
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
		std::cout << name << "\n";
		if (m_animations.find(name) == m_animations.end())
		{
			std::cout << "animation not found.\n";
			exit(-5);
		}
		return m_animations[name];
	}
	sf::Font* getFont(const std::string& name)
	{
		if (m_fonts.find(name) == m_fonts.end())
		{
			std::cout << "fontnot found.\n";
			exit(-5);
		}
		return m_fonts[name];
	}
	~Assets()
	{
		for (auto& e : m_textures)
		{
			delete e.second;
		}
		for (auto& e : m_animations)
		{
			delete e.second;
		}
		for (auto& e : m_fonts)
		{
			delete e.second;
		}
	}
};

#endif

