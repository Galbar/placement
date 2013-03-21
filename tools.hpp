#ifndef TOOLS_H
#define TOOLS_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>


extern int SCRWIDTH;
extern int SCRHEIGHT;
extern int RADIUS;
extern int GRIDX;
extern int GRIDY;

#define WINDOW_TITLE "Graph Placement"
#define CONTEXT_SETTINGS_OPENGL sf::ContextSettings(32,32,0,2,0)

float module(const sf::Vector2f &v);
sf::Vector2f unit(const sf::Vector2f &v);

float Fa(float d, float k);
float Fr(float d, float k);

void drawLine(sf::Vector2f a, sf::Vector2f b, sf::RenderWindow& window);
#endif
