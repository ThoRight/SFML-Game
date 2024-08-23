#include "Assets.h"
#include <iostream>


void Assets::addTexture(const std::string& name, const std::string& path, float width, float height)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(path, sf::IntRect(0, 0, width, height)))
	{
		exit(0);
	}
	texture->setSmooth(true);
	m_textures[name] = texture;

}
void Assets::addAnimation(const std::string& name, Animation* animation)
{
	
	m_animations[name] = animation;
}
void Assets::addFont(const std::string& name, const std::string& path)
{
	sf::Font* f = new sf::Font();
	if (!f->loadFromFile(path))
	{
		exit(-8);
	}
	m_fonts[name] = f;
	
}
void Assets::addSound(const std::string& name, const std::string& path)
{
	sf::SoundBuffer* s = new sf::SoundBuffer();
	if (!s->loadFromFile(path))
	{
		exit(-9);
	}
	m_sounds[name] = s;
}