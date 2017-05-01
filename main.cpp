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
	void go(float, Hole&, Hole&);
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
	sprite.setPosition(x, y);
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
	r = sqrt(pow((ship.x - (x + 70)), 2) + pow((ship.y - (y + 70)), 2));
	v->x = m*((x + 70) - ship.x) / pow(r, 3);
	v->y = m*((y + 70) - ship.y) / pow(r, 3);
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

//Метод движения стрелочки (задания начальной скорости корабля)
void Arrow::move(RenderWindow& window, Ship& ship)
{
	float X = 0, Y = 0;
	Vector2i pixelPos = Mouse::getPosition(window);;
	X = pixelPos.x - sprite.getPosition().x;
	Y = pixelPos.y - sprite.getPosition().y;
	float rotation = (atan2(Y, X)) * 180 / 3.14159265 - 45;
	sprite.setRotation(rotation);
	float k = sqrt(pow(X, 2) + pow(Y, 2)) / 1000;
	size = fmin(k, 0.2);
	sprite.setScale(size, size);
	ship.v->x = 10 * size*cos((rotation + 45)*3.14159265 / 180);
	ship.v->y = 10 * size*sin((rotation + 45)*3.14159265 / 180);
}

//Метод движения корабля
void Ship::go(float time, Hole& hole1, Hole& hole2)
{
	Vector c(v->x + hole1.v->x*time + hole2.v->x*time, v->y + hole1.v->y*time + hole2.v->y*time);
	x += c.x*time;
	y += c.y*time;
	hole1.v->x = 0;
	hole1.v->y = 0;
	hole2.v->x = 0;
	hole2.v->y = 0;
	sprite.setPosition(x, y);
}

//функция движения корабля вверх-вниз на старте игры
void moveship(Ship& ship, Arrow& arrow, float time)
{
	if(Keyboard::isKeyPressed(Keyboard::Up))
		{
			ship.y = fmax(ship.y-5 * time, 0);
			arrow.y = fmax(arrow.y - 5 * time, 0);
		}

	if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			ship.y = fmin(ship.y + 5 * time, 740);
			arrow.y = fmin(arrow.y + 5 * time, 740);
		}
	ship.sprite.setPosition(ship.x, ship.y);
	arrow.sprite.setPosition(ship.x + 20, ship.y + 10);
}
/////////////////////////////////////////////////
void lose(RenderWindow& window)
{
	Font font;
	font.loadFromFile("spacefont.ttf");
	Text text("", font, 40);
	text.setString(L"    Ваш корабль пропал\nза горизонтом событий");
	text.setPosition(90, 285);
	
	window.draw(text);
}
/////////////////////////////////////////////////
//Функция начала игры (почти что main)
bool startGame()
{
	RenderWindow window(VideoMode(1366, 768), "Kursach", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);//Вертикальная синхронизация кадров с монитором
	bool isMove = true;
	bool isFall = false;
	bool onMenu = false;
	bool isMenu = false;
	Clock clock;
	Arrow arrow("arrow.png", 20, 400);
	Ship ship("ship.png", 0, 390);
	Hole hole1("hole.png", 400, 100, 10000), hole2("hole.png", 700, 500, 10000);
	Menu menu(1075, 160, 1205, 200, 1055, 120);

	//фон
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

		if (Keyboard::isKeyPressed(Keyboard::Tab))
		{
			isMenu = !isMenu;
		}
		

		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if(isMove) moveship(ship, arrow, time);

			onMenu = menu.menuNum;
			if (isMove) arrow.move(window, ship);
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{
					if(!onMenu) isMove = false;
				}
		}

		//Обработка меню
		if (isMenu || isFall)
		{
			if (menu.click(window) == 1) return true;
			if (menu.click(window) == 3) isMenu = !isMenu;
		}

		//Взаимодействие корабля и черных дыр
		if (!isFall) hole2.come(time, ship);//черная дыра притягивает, если корабль еще не упал
		if (!isFall) hole1.come(time, ship);//--//--
		hole1.destroy(window, ship, &isFall);//разрушение корабля, если подлетит близко
		hole2.destroy(window, ship, &isFall);//--//--
		if (!isMove) ship.go(time, hole1, hole2);//непосредственно функция движения корабля

		//Рисование всего
		window.clear();
		window.draw(spconvas);
		window.draw(hole1.sprite);
		window.draw(hole2.sprite);
		if(!isFall) window.draw(ship.sprite);
		window.draw(arrow.sprite);
		if (isMenu || isFall)
		{
			window.draw(menu.sprite);
			window.draw(menu.txt4);
			window.draw(menu.txt1);
			window.draw(menu.txt2);
			window.draw(menu.txt3);
		}
		if (isFall)
		{
			Blink blink(ship.x, ship.y);
			window.draw(blink.sprite);
			lose(window);
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