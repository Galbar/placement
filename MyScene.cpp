#include "MyScene.hpp"
#include "Game.hpp"
#include "GridScene.hpp"
#include <list>
using namespace std;

myScene::myScene(Game &parent) : Scene(parent) {
}

myScene::~myScene() {
}


void myScene::debug() {
}

bool myScene::init() {
	//read graphf from input.
	cin >> g;
	//set random position
	for (int i = 0; i < g.getVertexCount(); ++i) {
		g[i].pos = sf::Vector2f(float((rand()%SCRWIDTH)),float((rand()%SCRHEIGHT)));
		cout << "Pos x: " << g[i].pos.x << "  y: " << g[i].pos.y << endl;
	}

	t = 30;
	k = sqrt((SCRWIDTH*SCRHEIGHT)/g.getVertexCount());

	cout << "* Init correctly" << std::endl;
	return true;
}

void myScene::update(float deltaTime){

	float dt = t*0.2;
	int ordre = g.getVertexCount();


	//atraction
	for (int i = 0; i < ordre; ++i) {
		//cout << "posx: " << g[i].pos.x << "  y: " << g[i].pos.y << endl;

		g[i].disp = sf::Vector2f(0,0);

		for (int j = 0; j < g.getDegree(i); ++j) {
			sf::Vector2f dif = g[i].pos - g[ g.getConnections(i)[j] ].pos;
			float m = module(dif);
			//cout << "module of " << i << " and " << g.getConnections(i)[j] << "  " << m << endl;
			if (m != 0) {
				g[i].disp = g[i].disp - unit(dif)*Fa(m, k);
			}
		}
	}

	//new repulsion
	for (int i = 0; i < ordre; ++i) {
		for (int j = 0; j < ordre; ++j) {
			if (i != j) {
				sf::Vector2f dif = g[i].pos - g[j].pos;
				float m = module(dif);
				if (m != 0) {
					g[i].disp = g[i].disp + unit(dif)*Fr(m,k);
				}
			}
		}
	}

	/*
	for (int i = 0; i < g.nodes; ++i) {
		g.disp[i] = Vec(0,0);
		for (int j = 0; j < g.nodes; ++j) {
			if (i != j) {
				Vec dif = g.pos[i] - g.pos[j];
				float m = dif.module();
				if (m != 0) {
					g.disp[i] = g.disp[i] + dif.unit()*Fr(m);
				}
			}
		}
	}
	//atraction
	for (int i = 0; i < g.nodes; ++i) {
		for (int j = g.ind[i]; j < g.ind[i+1]; ++j) {
			Vec dif = g.pos[i] - g.pos[g.adj[j]];
			float m = dif.module();
			if (m != 0) {
				g.disp[i] = g.disp[i] - dif.unit()*Fa(m);
			}
		}
	}
	*/


  //WALLS
	for (int i = 0; i < ordre; ++i) {
		sf::Vector2f dif;
		float m;

		//left
		dif = g[i].pos - sf::Vector2f(0, g[i].pos.y);
		m = module(dif);
		g[i].disp = g[i].disp + unit(dif)*Fr(m, k);

		//right
		dif = g[i].pos - sf::Vector2f(SCRWIDTH, g[i].pos.y);
		m = module(dif);
		g[i].disp = g[i].disp + unit(dif)*Fr(m, k);

		//up
		dif = g[i].pos - sf::Vector2f(g[i].pos.x, 0);
		m = module(dif);
		g[i].disp = g[i].disp + unit(dif)*Fr(m, k);

		//down
		dif = g[i].pos - sf::Vector2f(g[i].pos.x, SCRHEIGHT);
		m = module(dif);
		g[i].disp = g[i].disp + unit(dif)*Fr(m, k);
	}


	for (int i = 0; i < ordre; ++i) {
		float m = module(g[i].disp);
		if (m == 0) m = 1;


		if ( m < dt) {
			g[i].pos = g[i].pos + g[i].disp;
		}
		else {
			g[i].pos = g[i].pos + unit(g[i].disp)*dt;
		}

		//g[i].pos = sf::Vector2f(min(float(SCRWIDTH - RADIUS), max(float(RADIUS), g[i].pos.x)), min(float(SCRHEIGHT - RADIUS), max(float(RADIUS), g[i].pos.y)));

	}

	t *= 0.99;
	//lul
	if (t < 0.02) parent.setScene(new GridScene(parent, g));
}

void myScene::draw() {


//	float x, y;
	int ordre = g.getVertexCount();

	//edges
	for (int i = 0; i < ordre; ++i) {
		for (int j = 0; j < g.getDegree(i); ++j) {
			drawLine(
				g[i].pos,
				g[ g.getConnections(i)[j] ].pos,
				parent.getWindow()
			);
		}
	}


	//nodes
	for (int i = 0; i < ordre; ++i) {
		sf::CircleShape circle;
		circle.setFillColor(sf::Color(255, 0, 0, 255));
		circle.setRadius(RADIUS);
		circle.setPointCount(12);
		circle.setPosition(g[i].pos - sf::Vector2f(RADIUS, RADIUS));
		parent.getWindow().draw(circle);

	}


}

void myScene::onKeyPressed(float deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		parent.onClose();
}

void myScene::onMouseButtonPressed(float deltaTime) {

}

void myScene::onClose() {
	std::cout << "* Closing scene \"Myscene\"" << std::endl;
}

bool myScene::loadResources() {
	return true;
}
