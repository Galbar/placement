#include "GridScene.hpp"
#include "Game.hpp"
#include <list>

using namespace std;

GridScene::GridScene(Game &parent, Graph g) : Scene(parent), g(g), grid(GRIDY, vector<list<int> > (GRIDY, list<int> ())) {
	//grid = vector<vector<list<int> > > (GRIDY, vector<list<int> > (GRIDY, list<int> ()));
}

GridScene::~GridScene() {
}

void GridScene::printMatrix() {
	cout << "----------------------" << endl;
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[0].size(); ++j) {
			if (grid[i][j].empty()) cout << "_";
			else {
				for (list<int>::const_iterator it = grid[i][j].begin(); it != grid[i][j].end(); ++it) {
					cout << *it;
				}
			}
			cout << ",";
		}
		cout << endl;
	}
	cout << "----------------------" << endl;


}

void GridScene::debug() {
	for (int i = 0; i < GRIDY; ++i)
	{
		for (int j = 0; j < GRIDX; ++j)
		{
			for (list<int>::const_iterator it = grid[i][j].begin(); it != grid[i][j].end(); ++it) {
				cout << "At " << j << "," << i << "  : " << *it << endl;
			}
		}
	}
}

bool GridScene::init() {
	//cout << "GridScene start!" << endl;
	for (int i = 0; i < g.getVertexCount(); ++i) {
		g[i].updateGrid();
		grid[g[i].grid.x][g[i].grid.y].push_back(i);
	}

	t = 30;
	k = sqrt((SCRWIDTH*SCRHEIGHT)/g.getVertexCount());
	gridSizeX = SCRWIDTH/GRIDX;
	gridSizeY = SCRHEIGHT/GRIDY;

	//cout << "* Init was succesful asdfasdfa" << std::endl;
	return true;
}

void GridScene::update(float deltaTime){
	float dt = t * 0.02;
	int ordre = g.getVertexCount();
	float m;

	//atraction
	for (int i = 0; i < ordre; ++i) {
		g[i].disp = sf::Vector2f(0,0);
		for (int j = 0; j < g.getDegree(i); ++j) {
			sf::Vector2f dif = g[i].pos - g[ g.getConnections(i)[j] ].pos;
			m = module(dif);
			if (m == 0) m = 0.01;
			g[i].disp = g[i].disp - unit(dif)*Fa(m, k);

		}
	}
	//new repulsion
	for (int i = 0; i < ordre; ++i) {
		int x = g[i].grid.x;
		int y = g[i].grid.y;
		//cout << "pos of " << i << ": " << x << "," << y << endl;
		//cout << "alt.    : " << g[i].gridPos.x << "," << g[i].gridPos.y << endl;
		for (list<int>::const_iterator it = grid[x][y].begin(); it != grid[x][y].end(); ++it) {
			if (i != *it) {
				sf::Vector2f dif = g[i].pos - g[*it].pos;
				m = module(dif);
				if (m == 0) m = 0.01;
				g[i].disp = g[i].disp + unit(dif)*Fr(m, k);

			}
		}
	}


/*
  //WALLS
	for (int i = 0; i < ordre; ++i) {
		sf::Vector2f dif;

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
*/

	for (int i = 0; i < ordre; ++i) {
		m = module(g[i].disp);
		if (m == 0) m = 1;

		sf::Vector2f add;

		if (m < dt) add = g[i].disp;
		else add = unit(g[i].disp)*dt;

		//cout << "add: " << add.x << "  addy : " << add.y << endl;

		//cout << "stage 1 completed" << endl;
		list<int> &lp = grid[g[i].grid.x][g[i].grid.y];
		//cout << "Pos before of " <<  i<< ": " << g[i].pos.x << " |  " << g[i].pos.y << endl;
		g[i].pos = g[i].pos + add;

		//cout << "Pos after of " << i << ": " << g[i].pos.x << " |  " << g[i].pos.y << endl;
		g[i].updateGrid();
		//cout << "grid x: " << g[i].grid.x << "  and grid y: " << g[i].grid.y << endl;
		if (grid[g[i].grid.x][g[i].grid.y] != lp and !grid[g[i].grid.x][g[i].grid.y].empty()){
			g[i].pos = g[i].pos - add;
			g[i].updateGrid();
		}

		else {
			lp.remove(i);
			grid[g[i].grid.x][g[i].grid.y].push_back(i);
		}
	}
//	k *= 0.995;

}

void GridScene::draw() {
	//cout << "drawing!" << endl;


//	float x, y;
	int ordre = g.getVertexCount();

	//dibuixar

	//recorrem cada node
	float stepX = SCRWIDTH /float(GRIDX);
	float stepY = SCRHEIGHT/float(GRIDY);

	sf::Color(100,100,100,255);
	for (float i = 0; i < SCRWIDTH; i += stepX) {
		drawLine(sf::Vector2f(i, 0), sf::Vector2f(i, SCRHEIGHT), parent.getWindow());
	}
	for (float i = 0; i < SCRHEIGHT; i += stepY) {
		drawLine(sf::Vector2f(0, i), sf::Vector2f(SCRWIDTH, i), parent.getWindow());
	}

/////////////////////////
	//DRAW AS MATRIX
	/*
	for (int i = 0; i < ordre; ++i) {
		for (int j = 0; j < g.getDegree(i); ++j) {
			drawLine(
						sf::Vector2f(gridSizeX/2 + g[i].gridPos[0]*gridSizeX, gridSizeY/2 + g[i].gridPos[1]*gridSizeY),
						sf::Vector2f(gridSizeX/2 + g.nodes[g[i].adjacents[j]].gridPos[0]*gridSizeX, gridSizeY/2 + g.nodes[g[i].adjacents[j]].gridPos[1]*gridSizeY),
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
		circle.setPosition(sf::Vector2f(gridSizeX/2 + g[i].gridPos[0]*gridSizeX, gridSizeY/2 + g[i].gridPos[1]*gridSizeY)  - sf::Vector2f(RADIUS, RADIUS));
		parent.getWindow().draw(circle);
	}


*/
//////////////////////////////////

	//edges
	for (int i = 0; i < ordre; ++i) {
		for (int j = 0; j < g.getDegree(i); ++j) {
			drawLine(
				sf::Vector2f(g[i].grid.x*gridSizeX + gridSizeX/2,g[i].grid.y*gridSizeY + gridSizeX/2),
				sf::Vector2f(g[ g.getConnections(i)[j] ].grid.x*gridSizeX + gridSizeX/2,g[ g.getConnections(i)[j] ].grid.y*gridSizeY + gridSizeX/2),
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
		circle.setPosition(sf::Vector2f(g[i].grid.x*gridSizeX + gridSizeX/2 - RADIUS,g[i].grid.y*gridSizeY + gridSizeX/2 - RADIUS));
		parent.getWindow().draw(circle);

	}

	//cout << "end draw" << endl;
}

void GridScene::onKeyPressed(float deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		parent.onClose();
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		printMatrix();
}

void GridScene::onMouseButtonPressed(float deltaTime) {

}

void GridScene::onClose() {
	std::cout << "* Closing scene \"GridScene\"" << std::endl;
}

bool GridScene::loadResources() {
	return true;
}
