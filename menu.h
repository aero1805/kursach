#include <SFML/Graphics.hpp>

using namespace sf;

class Menu
{
public:
	Image image;
	Texture texture;
	Sprite sprite;
	int menuNum;
	float x1, y1, x2, y2, x3, y3;
	Font font;
	Text txt1, txt2, txt3, txt4;
	Menu(float, float, float, float, float, float);
	int click(RenderWindow&);
	~Menu() {};
};

Menu::Menu(float X1, float Y1, float X2, float Y2, float X3, float Y3)
{
	x1 = X1; y1 = Y1;  x2 = X2; y2 = Y2, x3 = X3, y3 = Y3;
	menuNum = 0;
	font.loadFromFile("spacefont.ttf");

	txt1 = Text("", font, 35);
	txt1.setString(L"Новая игра");
	txt1.setPosition(x1, y1);

	txt2 = Text("", font, 35);
	txt2.setString(L"Выход");
	txt2.setPosition(x2, y2);
	
	txt3 = Text("", font, 35);
	txt3.setString(L"Продолжить");
	txt3.setPosition(x3, y3);

	txt4 = Text("", font, 50);
	txt4.setString(L"Меню");
	txt4.setStyle(Text::Bold | Text::Underlined);
	txt4.setPosition(1120, 20);

	image.loadFromFile("images/menu.jpg");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(300, 0, 400, 860));
	sprite.setPosition(1050, 0);
}

int Menu::click(RenderWindow& window)
{
	txt1.setFillColor(Color(255, 255, 255));
	txt2.setFillColor(Color(255, 255, 255));
	txt3.setFillColor(Color(255, 255, 255));
	
	if (IntRect(x1, y1, 440, 35).contains(Mouse::getPosition(window))) { txt1.setFillColor(Color(0, 0, 255)), menuNum = 1; }
	else
		if (IntRect(x2, y2, 240, 35).contains(Mouse::getPosition(window))) { txt2.setFillColor(Color(0, 0, 255)), menuNum = 2; }
		else 
			if (IntRect(x3, y3, 440, 35).contains(Mouse::getPosition(window))) { txt3.setFillColor(Color(0, 0, 255)), menuNum = 3; }
			else 
				if (IntRect(1050, 0, 416, 768).contains(Mouse::getPosition(window))) menuNum = 111;
				else menuNum = 0;

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		switch (menuNum)
		{
		case 1: { return 1; break; }
		case 2: { window.close(); break; }
		case 3: { return 3; break; }
		}
	}

}
