/*
PHYLLOTAXIS
Created by Mateusz Szczepañski (7szczepanski) 2017 - 04 - 13
*/

#include <SFML/Graphics.hpp>
#include <math.h>
#include <random>
#include <time.h>
#include <iostream>

using namespace std;
using namespace sf;

constexpr int width{ 200 }, height{ 200 };

float Umap(float value, float istart, float istop, float ostart, float ostop) {
	return ostart + (ostop - ostart)*((value - istart) / (istop - istart));
}

double unirand(float start, float end) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(start, end);
	return dist(mt);
}


sf::Color setColor(int hue, float sat, float val) {

	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val*(1.f - sat);
	float q = val*(1.f - sat*f);
	float t = val*(1.f - sat*(1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}



class Dot {
	Vector2f pos;
	Color color;
	int size;


public:
	CircleShape dot;
	int lifespan;
	bool alive = true;
	Dot(float x, float y, int siz) {
		pos.x = x;
		pos.y = y;
		size = siz;
		lifespan = 855;
	}
	void setup() {
		dot.setRadius(size);
		dot.setPosition(pos);

	}
	void update() {
		color = setColor(Umap(lifespan, 855, 1, 1, 360), 5, 127);
		dot.setFillColor(color);
		lifespan--;
	}
	void show(RenderWindow &target) {
		target.draw(dot);

	}
	void checkLife() {
		if (lifespan <= 0 || pos.x > width + 1 || pos.x<0 || pos.y>height || pos.y < 0) alive = false;
	}
};





int main()
{
	srand(time(NULL));
	int n{ 0 }, c{ 4 };
	float a, r, x, y;


	sf::RenderWindow window(sf::VideoMode(width, height), "Phylotaxis");
	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setFillColor(sf::Color(51, 51, 51));


	vector<Dot> phyllotaxis;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		a = n*137.5;
		r = c*sqrt(n);
		x = r * cos(a) + width / 2;
		y = r * sin(a) + height / 2;
		int randshittycolor = []()->int {return unirand(1, 360); }();
		Dot dot(x, y, 2);
		dot.setup();
		phyllotaxis.push_back(dot);
		
		n++;


		window.clear();
		window.draw(background);
		/*--------------------------------------------------------------| DRAW BELOW |----------------------------------------------------------------------------*/

		for (int i = phyllotaxis.size() - 1; i >= 0; i--) {
			phyllotaxis[i].update();
			phyllotaxis[i].checkLife();
			phyllotaxis[i].show(window);


			if (phyllotaxis[i].alive == false) { phyllotaxis.erase(phyllotaxis.begin() + i); }

		}
		window.display();
	}

	return 0;
}