#ifndef MYSCENE_H
#define MYSCENE_H

#include "Scene.hpp"
#include "Graph.hpp"
#include "tools.hpp"
#include <list>

class myScene : public Scene {
	public:
		myScene(Game &parent);
		~myScene();
		bool init(); //should call loadResources()
		void update(float deltaTime); //called by parent on parent.update()
		void draw(); //called by parent on parent.draw()
		void onKeyPressed(float deltaTime); //called by parent on parent.update()
		void onMouseButtonPressed(float deltaTime); //called by parent on parent.update()
		void onClose(); //close scene-wide stuff

		void debug();

	private:
		bool loadResources(); //load stuff with parent.resources
		Graph g;
		float k;
		float t;

};

#endif // MYSCENE_H
