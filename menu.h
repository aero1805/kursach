#include <SFML/Graphics.hpp>

using namespace sf;

class Menu
{
public:
	String File1, File2;
	int menuNum;
	float x1, y1, x2, y2;
	Texture textureNewGame, textureExit;
	Sprite spriteNew, spriteExit;
	Menu(String, String, float, float, float, float);
	int click(RenderWindow&);
	~Menu() {};
};

Menu::Menu(String F1, String F2, float X1, float Y1, float X2, float Y2)
{
	x1 = X1; x2 = X2; y1 = Y1; y2 = Y2;
	menuNum = 0;
	File1 = F1; File2 = F2;
	textureNewGame.loadFromFile("images/" + F1);
	textureExit.loadFromFile("images/" + F2);
	spriteNew.setTexture(textureNewGame); 
	spriteExit.setTexture(textureExit);
	spriteNew.setPosition(X1, Y1);
	spriteNew.setColor(Color::White);
	spriteExit.setPosition(X2, Y2);
	spriteExit.setColor(Color::White);
}

int Menu::click(RenderWindow& window)
{
	spriteExit.setColor(Color::White);
	spriteNew.setColor(Color::White);
	
	if (IntRect(x1, y1, 200, 40).contains(Mouse::getPosition(window))) { spriteNew.setColor(Color::Blue), menuNum = 1; }
	else
		if (IntRect(x2, y2, 200, 40).contains(Mouse::getPosition(window))) { spriteExit.setColor(Color::Blue), menuNum = 2; }
		else menuNum = 0;

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (menuNum == 1) { return 1; }
		if (menuNum == 2) { window.close(); }
	}
}
