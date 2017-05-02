#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "menu.h"
/*#include "Arrow.h"
#include "Ship.h"*/
using namespace sf;

Settings settings;
int isLose;
bool isWin;
class Hole;
class Ship;
void lose(int, bool*);
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
	float mod();
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
float Vector::mod()
{
	return sqrt(x*x + y*y);
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
	void go(float, Hole&, Hole&, Hole&, bool*, bool*);
	void disappear(bool*);
	void finish(bool*);
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
void Ship::disappear(bool* isFall)
{
	if ((y < 0 || y > 768) && x < 1340) lose(2, isFall);
}
void Ship::finish(bool* isWin)
{
	if (x >= 1341)
	{
		*isWin = true;
	}
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
	v = new Vector;

	image.loadFromFile("images/" + F);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}
void Hole::come(float time, Ship& ship)
{
	r = sqrt(pow((ship.x - (x + 70)), 2) + pow((ship.y - (y + 70)), 2));
	v->x = (m * 100)*((x + 70) - ship.x) / pow(r, 3);
	v->y = (m * 100)*((y + 70) - ship.y) / pow(r, 3);
}
void Hole::destroy(RenderWindow& window, Ship& ship, bool* isFall)
{
	if (m != 0)
	if (IntRect(x, y, 140, 140).contains(ship.x, ship.y))
	{ ship.v->x = 0; 
	ship.v->y = 0;
	v->x = 0;
	v->y = 0;
	lose(1, isFall);
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
	size = fmin(k, 0.5);
	sprite.setScale(size, size);
	ship.v->x = 10 * size*cos((rotation + 45)*3.14159265 / 180);
	ship.v->y = 10 * size*sin((rotation + 45)*3.14159265 / 180);
}

//Метод движения корабля
void Ship::go(float time, Hole& hole1, Hole& hole2, Hole& hole3, bool* isFall, bool* isWin)
{
	//Vector c(v->x + hole1.v->x + hole2.v->x + hole3.v->x, v->y + hole1.v->y + hole2.v->y + hole3.v->y);
	x += (v->x + hole1.v->x*time + hole2.v->x*time + hole3.v->x*time)*time;
	y += (v->y + hole1.v->y*time + hole2.v->y*time + hole3.v->y*time)*time;

	v->x = v->x + hole1.v->x + hole2.v->x + hole3.v->x;
	v->y = v->y + hole1.v->y + hole2.v->y + hole3.v->y;

	sprite.setPosition(x, y);
	disappear(isFall);
	if(!*isFall) finish(isWin);
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
	bool cont = false;
	bool isSettings = false;
	isLose = 0;
	isWin = false;
	Clock clock;
	Arrow arrow("arrow2.png", 20, 400);
	Ship ship("ship.png", 0, 390);
	Hole hole1("hole.png", 600, 50, settings.m[0]), hole2("hole.png", 500, 600, settings.m[1]), hole3("hole.png", 800, 150, settings.m[2]);
	Menu menu;
	

	//фон
	Image imconvas;
	imconvas.loadFromFile("images/stars.jpg");
	Texture txconvas;
	txconvas.loadFromImage(imconvas);
	Sprite spconvas;
	spconvas.setTexture(txconvas);
	spconvas.setPosition(0, 0);

	//линия финиша
	Image imline;
	imline.loadFromFile("images/line.png");
	Texture txline;
	txline.loadFromImage(imline);
	Sprite spline;
	spline.setTexture(txline);
	spline.setTextureRect(IntRect(0, 0, 25, 577));
	spline.setScale(1, 1.33);
	spline.setPosition(1341, 0);



	while (window.isOpen())
	{
		Vector2i pixelPos = Mouse::getPosition(window);
		Event event;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 10000;

		if (Keyboard::isKeyPressed(Keyboard::Tab))
		{
			isMenu = !isMenu;
		}
		
		hole1.m = settings.m[0];
		hole2.m = settings.m[1];
		hole3.m = settings.m[2];
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if(isMove) moveship(ship, arrow, time);

			if(!cont) onMenu = menu.onMenu;
			cont = false;
			if (isMove) arrow.move(window, ship);
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					if(!onMenu) isMove = false;
				}
		}

		//Обработка меню
		if (isMenu || isFall || isWin)
		{
			if (menu.click(window, settings) == 1) return true;
			if (menu.click(window, settings) == 3) { isMenu = !isMenu; cont = true; menu.onMenu = false; };
			if (menu.click(window, settings) == 5) { isSettings = true; }
		}

		//Взаимодействие корабля и черных дыр
		if (!isFall) hole2.come(time, ship);//черная дыра притягивает, если корабль еще не упал
		if (!isFall) hole1.come(time, ship);//--//--
		if (!isFall) hole3.come(time, ship);
		hole1.destroy(window, ship, &isFall);//разрушение корабля, если подлетит близко
		hole2.destroy(window, ship, &isFall);//--//--
		hole3.destroy(window, ship, &isFall);//--//--
		if (!isMove && !isFall) ship.go(time, hole1, hole2, hole3, &isFall, &isWin);//непосредственно функция движения корабля

		/////////////////////////////////////////////////////

		//Рисование всего
		window.clear();
		window.draw(spconvas);//фон
		if (hole1.m != 0) window.draw(hole1.sprite);//черная дыра 1
		if (hole2.m != 0) window.draw(hole2.sprite);//черная дыра 2
		if (hole3.m != 0) window.draw(hole3.sprite);//черная дыра 3
		if(!isFall && !isWin) window.draw(ship.sprite); //корабль, если он не упал/пропал
		window.draw(spline); //линия финиша
		window.draw(arrow.sprite);//стрелка направления

		//меню
		if (isMenu || isFall || isWin) 
		{
			menu.click(window, settings);
			if(isSettings) settings.show(window, &isSettings, &isMenu, &cont); //если нажали на настройки
		}
		

		if (isFall) 
		//если проиграли
		{
			Blink blink(ship.x, ship.y); 
			if(isLose == 1) window.draw(blink.sprite); //блик если упал в дыру
			Font font;
			font.loadFromFile("spacefont.ttf");
			Text text("", font, 40);
			text.setPosition(90, 285);
			//сбщ на экран в разных случаях проигрыша 
			if (isLose == 1)
			{
				text.setString(L"    Ваш корабль пропал\nза горизонтом событий");
				isLose = 1;
				window.draw(text);
			}
			if (isLose == 2)
			{
				text.setString(L"  Ваш корабль скрылся\n  в просторах космоса");
				isLose = 2;
				window.draw(text);
			}

		}

		//если выиграли 
		if (isWin)
		{
			Font font;
			font.loadFromFile("spacefont.ttf");
			Text text("", font, 40);
			text.setPosition(90, 285);
			text.setString(L"     Congratulations!");
			window.draw(text);
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