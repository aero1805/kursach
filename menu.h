#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"

using namespace sf;

class Menu
{
public:
	bool onMenu;
	Image image;
	Texture texture;
	Sprite sprite;
	int menuNum;
	Font font;
	Text txt1, txt2, txt3, txt4, txt5;
	Menu();
	int click(RenderWindow&, Settings& settings);
	~Menu() {};
};

Menu::Menu()
{
	onMenu = false;

	menuNum = 0;
	font.loadFromFile("spacefont.ttf");

	txt1 = Text("", font, 35);
	txt1.setString(L"Новая игра");
	txt1.setPosition(1075, 160);

	txt2 = Text("", font, 35);
	txt2.setString(L"Выход");
	txt2.setPosition(1205, 240);
	
	txt3 = Text("", font, 35);
	txt3.setString(L"Продолжить");
	txt3.setPosition(1055, 120);

	txt4 = Text("", font, 50);
	txt4.setString(L"Меню");
	txt4.setStyle(Text::Bold | Text::Underlined);
	txt4.setPosition(1120, 20);

	txt5 = Text("", font, 35);
	txt5.setString(L"Настройки");
	txt5.setPosition(1090, 200);


	image.loadFromFile("images/menu.jpg");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(300, 0, 400, 860));
	sprite.setPosition(1050, 0);
}

int Menu::click(RenderWindow& window, Settings& settings)
{
	txt1.setFillColor(Color(255, 255, 255));
	txt2.setFillColor(Color(255, 255, 255));
	txt3.setFillColor(Color(255, 255, 255));
	txt5.setFillColor(Color(255, 255, 255));
	
	if (IntRect(1075, 160, 440, 35).contains(Mouse::getPosition(window))) { txt1.setFillColor(Color(0, 0, 255)), menuNum = 1; onMenu = true; }
    else
		if (IntRect(1205, 240, 240, 35).contains(Mouse::getPosition(window))) { txt2.setFillColor(Color(0, 0, 255)), menuNum = 2; onMenu = true; }
		else
			if (IntRect(1055, 120, 440, 35).contains(Mouse::getPosition(window))) { txt3.setFillColor(Color(0, 0, 255)), menuNum = 3; onMenu = true;}
			else
				if (IntRect(1090, 200, 440, 35).contains(Mouse::getPosition(window))) { txt5.setFillColor(Color(0, 0, 255)), menuNum = 5; onMenu = true; }
				else
				if (IntRect(1050, 0, 416, 768).contains(Mouse::getPosition(window))) onMenu = true;
				else
				{
					menuNum = 0;
					onMenu = false;
				}

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		switch (menuNum)
		{
		case 1: { return 1; break; }
		case 2: { window.close(); break; }
		case 3: {return 3; break; }
		case 5: {return 5; break; }
		}
	}
	window.draw(sprite);
	window.draw(txt4);
	window.draw(txt1);
	window.draw(txt2);
	window.draw(txt3);
	window.draw(txt5);
}
