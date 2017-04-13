/*
PHYLLOTAXIS 
Created by Mateusz Szczepañski (7szczepanski) 2017 - 04 - 13
*/

#include <SFML/Graphics.hpp>
#include <math.h>
#include <random>
#include <time.h>
//#include <iostream> // - for debugging 

using namespace std;
using namespace sf;

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
	Dot(float x, float y, int siz, Color col) {
		pos.x = x;
		pos.y = y;
		size = siz;
		color = col;
	}
	void setup() {
		dot.setRadius(size);
		dot.setFillColor(color);
		dot.setPosition(pos);
	}
	void show(RenderWindow &target) {
		target.draw(dot);
	}
};





int main()
{
	srand(time(NULL));
	int n{ 0 }, c{ 6 };
	float a, r, x, y;
	constexpr int width{ 800 }, height{ 800 };

	sf::RenderWindow window(sf::VideoMode(width, height), "Phylotaxis");
	sf::RectangleShape background(sf::Vector2f(width,height));
	background.setFillColor(sf::Color(51,51,51));


	vector<Dot> phyllotaxis;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		a = n*136.7;
		r = c*sqrt(n);
		x = r * cos(a) + width / 2;
		y = r * sin(a) + height / 2;
		int randshitcolor = []()->int {return unirand(1, 360); }();
		Dot dot(x, y, 5, (setColor(randshitcolor, 5, 127)));
		dot.setup();
		phyllotaxis.push_back(dot);
		n += 2;


		window.clear();
		window.draw(background);
/*--------------------------------------------------------------| DRAW BELOW |----------------------------------------------------------------------------*/

		for (int i = 0; i < phyllotaxis.size(); i++) {
			phyllotaxis[i].show(window);
		}
		window.display();
	}

	return 0;
}