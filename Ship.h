#include <SFML/Graphics.hpp>
#include <math.h>
#include "Vector.h"

using namespace sf;

class Hole;
class Ship
{
public:
	float dx, dy;
	Vector *a;
	int x, y;
	int click, dir;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Ship(String, float, float);
	~Ship() { delete a; };
	void go(float, Hole&);
};

Ship::Ship(String F, float X, float Y)
{
	a = new Vector;
	dx = 0; dy = 0; click = 0, dir = 0;
	x = X;
	y = Y;
	File = F;
	image.loadFromFile("images/" + F);
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(0.03, 0.02);
}


class Hole
{
	//friend Ship;
public:
	Vector *a;
	float  r;
	int x, y;
	double m, g;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;

	Hole(String, float, float, double);
	~Hole() { delete a; };
	void setHole();
	void come(float time, Ship& ship);
};

Hole::Hole(String F, float X, float Y, double M)
{
	File = F;
	x = X;
	y = Y;
	m = M;
	r = 0;
	a = new Vector;

	image.loadFromFile("images/" + F);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}
void Hole::setHole()
{
	sprite.setPosition(x, y);
}
void Hole::come(float time, Ship& ship)
{
	r = sqrt(pow((ship.x - x), 2) + pow((ship.y - y), 2));
	a->x = (x - ship.x) / r;
	a->y = (y - ship.y) / r;
}

void Ship::go(float time, Hole& hole)
{
	Vector c(a->x + hole.a->x, a->y + hole.a->y);
	x += c.x*time;
	y += c.y*time;
	hole.a->x = 0;
	hole.a->y = 0;
	sprite.setPosition(x, y);
}

