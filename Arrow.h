#include <SFML/Graphics.hpp>
#include <math.h>
#include "Ship.h"

using namespace sf;
class Ship;
class Arrow
{
public:
	float x, y, size;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;

	Arrow(String, float, float);
	~Arrow() {};
	void move(RenderWindow&, Ship&);
};

Arrow::Arrow(String F, float X, float Y)
{
	x = X;
	y = Y;
	File = F;
	size = 0.05;
	image.loadFromFile("images/" + F);
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(size, size);
	sprite.setPosition(x, y);
}


void Arrow::move(RenderWindow& window, Ship& ship)
{
	float X = 0, Y = 0;
	Vector2i pixelPos = Mouse::getPosition(window);;
	X = pixelPos.x - sprite.getPosition().x;
	Y = pixelPos.y - sprite.getPosition().y;
	float rotation = (atan2(Y, X)) * 180 / 3.14159265 - 45;
	sprite.setRotation(rotation);
	float k = sqrt(pow(X, 2) + pow(Y, 2)) / 1000;
	size = k;
	sprite.setScale(size, size);
	ship.a->x = 50 * size*cos(atan2(Y, X));
	ship.a->y = 50 * size*sin(atan2(Y, X));
}
