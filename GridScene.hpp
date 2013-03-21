#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include "Scene.hpp"
#include "Graph.hpp"
#include "tools.hpp"
#include <vector>
#include <list>


class GridScene : public Scene {
	public:
		GridScene(Game &parent, Graph g);
		~GridScene();
		bool init();
		void update(float deltaTime); //called by parent on parent.update()
		void draw(); //called by parent on parent.draw()
		void onKeyPressed(float deltaTime); //called by parent on parent.update()
		void onMouseButtonPressed(float deltaTime); //called by parent on parent.update()
		void onClose(); //close scene-wide stuff
		void gridList(sf::Vector2i pos);
		void debug();
		void printMatrix();
		int calcDist();

	private:
		bool loadResources();
		Graph g;
		float k;
		float t;
		float gridSizeX, gridSizeY;
		int gridX, gridY;
		std::vector <std::vector <int> > M;
		std::vector <std::vector <std::list<int> > > grid;
};

#endif // GRIDSCENE_H
