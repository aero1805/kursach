#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "menu.h"
/*#include "Arrow.h"
#include "Ship.h"*/
using namespace sf;

class Hole;
class Ship;

//Класс ветор
class Vector
{
public:
	float x, y;
	Vector() { x = 0; y = 0; };
	Vector(float, float);
	~Vector() {};
	Vector(const Vector&);
	Vector& operator + (Vector&);
	Vector& operator - (Vector&);
	void operator = (Vector&);
	Vector& operator * (float);
};

Vector::Vector(float a, float b)
{
	x = a; y = b;
}
Vector& Vector::operator+(Vector& a)
{
	Vector b(x + a.x, y + a.y);
	return b;
}
Vector& Vector::operator-(Vector& a)
{
	Vector b(x - a.x, y - a.y);
	return b;
}
void Vector::operator = (Vector& a)
{
	x = a.x;
	y = a.y;
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

//Класс блик
class Blink
{
public:
	Image image;
	Texture texture;
	Sprite sprite;
	float x, y;
	Blink();
	Blink(float, float);
	~Blink() {};
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



//Класс стрелочка
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

//Класс корабль
class Ship
{
public:
	//float dx, dy;
	Vector *v;
	int x, y;
	//int click, dir;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Ship(String, float, float);
	~Ship() { delete v; };
	void go(float, Hole&);
};

Ship::Ship(String F, float X, float Y)
{
	v = new Vector;
	x = X;
	y = Y;
	File = F;
	image.loadFromFile("images/" + F);
	image.createMaskFromColor(Color(255, 255, 255));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(0.03, 0.02);
}


//Класс черной дыры
class Hole
{
	//friend Ship;
public:
	Vector *v;
	float  r;
	int x, y;
	double m;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Hole(String, float, float, double);
	~Hole() { delete v; };
	void come(float time, Ship& ship);
	void destroy(RenderWindow&, Ship&, bool*);
};

Hole::Hole(String F, float X, float Y, double M)
{
	File = F;
	x = X;
	y = Y;
	m = M;
	r = 0;
	v = new Vector;

	image.loadFromFile("images/" + F);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}
void Hole::come(float time, Ship& ship)
{
	r = sqrt(pow((ship.x - x), 2) + pow((ship.y - y), 2));
	v->x = m*(x - ship.x) / pow(r, 3);
	v->y = m*(y - ship.y) / pow(r, 3);
}
void Hole::destroy(RenderWindow& window, Ship& ship, bool* isFall)
{
	if (IntRect(x, y, 140, 140).contains(ship.x, ship.y))
	{ ship.v->x = 0; 
	ship.v->y = 0;
	v->x = 0;
	v->y = 0;
	*isFall = true;
	}
}

//Метод движения стрелочки
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
	ship.v->x = 10 * size*cos(atan2(Y, X));
	ship.v->y = 10 * size*sin(atan2(Y, X));
}

//Метод движения корабля
void Ship::go(float time, Hole& hole)
{
	Vector c(v->x + hole.v->x*time, v->y + hole.v->y*time);
	x += c.x*time;
	y += c.y*time;
	hole.v->x = 0;
	hole.v->y = 0;
	sprite.setPosition(x, y);
}

//Функция начала игры (почти что main)
bool startGame()
{
	RenderWindow window(sf::VideoMode(1000, 1000), "Kursach", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);//Вертикальная синхронизация кадров с монитором
	bool isMove = true;
	bool isFall = false;
	bool onMenu = false;
	Clock clock;
	Arrow arrow("arrow.png", 15, 15);
	Ship ship("ship.png", 0, 0);
	Hole hole1("hole.png", 200, 500, 10000);
	Menu menu("111.png", "333.png", 1000, 30, 1000, 90);

	Image imconvas;
	imconvas.loadFromFile("images/stars.jpg");
	Texture txconvas;
	txconvas.loadFromImage(imconvas);
	Sprite spconvas;
	spconvas.setTexture(txconvas);
	spconvas.setPosition(0, 0);

	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Event event;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 5000;
		onMenu = menu.menuNum;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();


			if (isMove) arrow.move(window, ship);
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{
					if(!onMenu) isMove = false;
				}
		}
		menu.click(window);

		if (menu.click(window) == 1) return true;
		if(!isFall) hole1.come(time, ship);
		hole1.destroy(window, ship, &isFall);
		if (!isMove) ship.go(time, hole1);

		window.clear();
		window.draw(spconvas);
		window.draw(hole1.sprite);
		if(!isFall) window.draw(ship.sprite);
		window.draw(arrow.sprite);
		window.draw(menu.spriteNew);
		window.draw(menu.spriteExit);
		if (isFall)
		{
			Blink blink(ship.x, ship.y);
			window.draw(blink.sprite);
		}
		window.display();
	}
}

//Рекурсивня функция перезапуска
void gameRunning()
{
	if (startGame()) { gameRunning(); }
}






int main()
{
	gameRunning();
	return 0;
}