#pragma once

#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <math.h>
#include "menu.h"

int isLose;
bool isWin;
class Hole;
class Ship;
void lose(int, bool*);

class Vector
{
	float x, y;
public:
	Vector() { x = 0; y = 0; };
	Vector(float, float);
	~Vector() {};
	Vector(const Vector&);
	Vector& operator * (float);
	float mod();
	float getX() { return x; }
	float getY() { return y; }
	void setX(float X) { x = X; }
	void setY(float Y) { y = Y; }

};

Vector::Vector(float a, float b)
{
	x = a; y = b;
}
Vector::Vector(const Vector& a)
{
	x = a.x;
	y = a.y;
}
Vector& Vector::operator*(float a)
{
	Vector b(x*a, y*a);
	return b;
}
float Vector::mod()
{
	return sqrt(x*x + y*y);
}

class Blink
{
	Image image;
	Texture texture;
	Sprite sprite;
	int x, y;
public:
	Blink();
	Blink(float, float);
	~Blink() {};
	int getX() { return x; }
	int getY() { return y; }
	void setX(int X) { x = X; }
	void setY(int Y) { y = Y; }
	Sprite& getSprite() { return sprite; }
};
Blink::Blink()
{
	x = 0; y = 0;
	image.loadFromFile("images/blink.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setScale(0.5, 0.5);
}
Blink::Blink(float X, float Y)
{
	x = X; y = Y;
	image.loadFromFile("images/blink.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	sprite.setScale(0.5, 0.5);
}

class Arrow
{
	int x, y;
	float size;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
public:
	Arrow(String, float, float);
	~Arrow() {};
	void move(RenderWindow&, Ship&);

	float getSize() { return size; }
	int getX() { return x; }
	int getY() { return y; }
	Sprite& getSprite() { return sprite; }
	void setSize(float s) { size = s; }
	void setPosition(float X, float Y) { x = X, y = Y; }
};

Arrow::Arrow(String F, float X, float Y)
{
	x = X;
	y = Y;
	File = F;
	size = 0.05;
	image.loadFromFile("images/" + F);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(size, size);
	sprite.setPosition(x, y);
}

class Ship
{
	Vector *v;
	int x, y;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	SoundBuffer bufferMove, bufferDisappear,bufferFinish, bufferDestroy;
	Sound soundMove, soundDisappear, soundFinish, soundDestroy;

public:
	Ship(String, float, float);
	~Ship() { delete v; };
	void go(float, Hole&, Hole&, Hole&, bool*, bool*);
	void disappear(bool*);
	void finish(bool*);
	void soundpouse();

	Vector getSpeed() { return *v; }
	Vector& setSpeed() { return *v; }
	int getX() { return x; }
	int getY() { return y; }
	Sprite& getSprite() { return sprite; }
	Sound& SoundMove() { return soundMove; }
	Sound& SoundDisappear() { return soundDisappear; }
	Sound& SoundFinish() { return soundFinish; }
	Sound& SoundDestroy() { return soundDestroy; }

	void setX(int X) { x = X; }
	void setY(int Y) { y = Y; }

};

Ship::Ship(String F, float X, float Y)
{
	v = new Vector;
	x = X;
	y = Y;
	file = F;
	image.loadFromFile("images/" + F);
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(0.03, 0.02);
	sprite.setPosition(x, y);

	bufferMove.loadFromFile("sounds/move.ogg");
	soundMove.setBuffer(bufferMove);

	bufferDisappear.loadFromFile("sounds/disap.ogg");
	soundDisappear.setBuffer(bufferDisappear);

	bufferFinish.loadFromFile("sounds/finish.ogg");
	soundFinish.setBuffer(bufferFinish);

	bufferDestroy.loadFromFile("sounds/destroy.ogg");
	soundDestroy.setBuffer(bufferDestroy);
}
void Ship::disappear(bool* isFall)
{
	if ((y < 0 || y > 768) && x < 1340 && !isWin) { soundDisappear.play() ; lose(2, isFall); }
}
void Ship::finish(bool* isWin)
{
	if (x >= 1341)
	{
		soundFinish.play();
		*isWin = true;
	}
}
void Ship::soundpouse()
{
	soundMove.pause();
}

class Hole
{
	bool isSelected;
	Vector *v;
	float  r;
	int x, y;
	float m;
	String file;
	Image image;
	Texture texture;
	Sprite sprite, spriteSelected;
public: 
	Hole(String, float, float, double);
	~Hole() { delete v; };
	void come(float time, Ship& ship);
	void destroy(RenderWindow&, Ship&, bool*);
	void changePosition(RenderWindow&);

	bool getisSelected() { return isSelected; }
	Vector getSpeed() { return *v; }
	float getR() { return r; }
	int getX() { return x; }
	int getY() { return y; }
	float getM() { return m; }
	Sprite& getSprite() { return sprite; }
	Sprite& getSpriteSelected() { return spriteSelected; }

	void setisSelected(bool is) { isSelected = is; }
	Vector& setSpeed() { return *v; }
	void setR(float R) { r = R; }
	void setX(int X) { x = X; }
	void setY(int Y) { y = Y; }
	void setM(float M) { m = M; }
};

Hole::Hole(String F, float X, float Y, double M)
{
	isSelected = false;
	file = F;
	x = X;
	y = Y;
	m = M;
	v = new Vector;

	image.loadFromFile("images/" + F);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	spriteSelected.setTexture(texture);
	spriteSelected.setPosition(x, y);

}
void Hole::come(float time, Ship& ship)
{
	r = sqrt(pow((ship.getX() - (x + 70)), 2) + pow((ship.getY() - (y + 70)), 2));
	v->setX((m * 100)*((x + 70) - ship.getX()) / pow(r, 3));
	v->setY((m * 100)*((y + 70) - ship.getY()) / pow(r, 3));
}
void Hole::destroy(RenderWindow& window, Ship& ship, bool* isFall)
{
	if (m != 0)
		if (IntRect(x + 5, y + 5, 140, 140).contains(ship.getX(), ship.getY()))
		{
			if (!*isFall) ship.SoundDestroy().play();
			ship.setSpeed().setX(0);
			ship.setSpeed().setY(0);
			v->setX(0);
			v->setY(0);
			lose(1, isFall);
		}
}
void Hole::changePosition(RenderWindow& window)
{
	if(IntRect(x, y, 150, 150).contains(Mouse::getPosition(window)))
		if(Mouse::isButtonPressed(Mouse::Right))
		{
			spriteSelected.setColor(Color(0, 0, 255, 128));
			isSelected = true;
		}

	if (isSelected)
		if(Mouse::isButtonPressed(Mouse::Left))
	{
			x = Mouse::getPosition(window).x - 75;
			y = Mouse::getPosition(window).y - 75;
			sprite.setPosition(x, y);
			spriteSelected.setPosition(x, y);
		isSelected = false;
	}
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
	size = fmin(k, 0.5);
	sprite.setScale(size, size);
	ship.setSpeed().setX(10 * size*cos((rotation + 45)*3.14159265 / 180));
	ship.setSpeed().setY(10 * size*sin((rotation + 45)*3.14159265 / 180));
}

void Ship::go(float time, Hole& hole1, Hole& hole2, Hole& hole3, bool* isFall, bool* isWin)
{
	x += (v->getX() + hole1.getSpeed().getX()*time + hole2.getSpeed().getX()*time + hole3.getSpeed().getX()*time)*time;
	y += (v->getY() + hole1.getSpeed().getY()*time + hole2.getSpeed().getY()*time + hole3.getSpeed().getY()*time)*time;

	v->setX( v->getX() + hole1.getSpeed().getX() + hole2.getSpeed().getX() + hole3.getSpeed().getX());
	v->setY( v->getY() + hole1.getSpeed().getY() + hole2.getSpeed().getY() + hole3.getSpeed().getY());
	soundMove.play();

	sprite.setPosition(x, y);
	disappear(isFall);
	finish(isWin);
}

void moveship(Ship& ship, Arrow& arrow, float time)
{
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		ship.setY(fmax(ship.getY() - 5 * time, 0));
		arrow.setPosition(20, fmax(arrow.getY() - 5 * time, 0));
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		ship.setY(fmin(ship.getY() + 5 * time, 740));
		arrow.setPosition(20, fmin(arrow.getY() + 5 * time, 740));
	}
	ship.getSprite().setPosition(ship.getX(), ship.getY());
	arrow.getSprite().setPosition(arrow.getX(), arrow.getY());
}

void lose(int k, bool* isFall)
{
	if (k == 1)
	{
		isLose = 1;
	}
	if (k == 2)
	{
		isLose = 2;
	}
	*isFall = true;
}
