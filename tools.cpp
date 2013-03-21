#include "tools.hpp"
//implement random functions here


float module(const sf::Vector2f &v){
	return sqrt(v.x*v.x + v.y*v.y);
	}

sf::Vector2f unit(const sf::Vector2f &v){
	float m = sqrt(v.x*v.x + v.y*v.y);
	return sf::Vector2f(v.x/m, v.y/m);
}

float Fa(float d, float k) {
	return (d*d)/k;
}
float Fr(float d, float k) {
	return (k*k)/d;
}

void drawLine(sf::Vector2f a, sf::Vector2f b, sf::RenderWindow & window){
	sf::Vertex vertices[2] = {
		sf::Vertex(a,sf::Color::Black),
		sf::Vertex(b,sf::Color::Black),
	};
	window.draw(vertices,2,sf::Lines);
}

