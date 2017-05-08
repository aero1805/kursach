#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Header.h"
using namespace sf;

Settings settings;
Hole hole1("hole.png", 650, 370, settings.getM(0)), hole2("hole.png", 500, 600, settings.getM(1)), hole3("hole.png", 800, 150, settings.getM(2));

bool startGame()
{
	RenderWindow window(VideoMode(1366, 768), "Game", Style::Fullscreen);
	window.setVerticalSyncEnabled(true);//������������ ������������� ������ � ���������
	bool isMove = true;
	bool isFall = false;
	bool onMenu = false;
	bool isMenu = false;
	bool isSettings = false;
	isLose = 0;
	isWin = false;
	Clock clock, musicclock;
	Arrow arrow("arrow2.png", 20, 400);
	Ship ship("ship.png", 0, 390);
	Menu menu;
	//���
	Image imconvas;
	imconvas.loadFromFile("images/stars.jpg");
	Texture txconvas;
	txconvas.loadFromImage(imconvas);
	Sprite spconvas;
	spconvas.setTexture(txconvas);
	spconvas.setPosition(0, 0);
	//����� ������
	Image imline;
	imline.loadFromFile("images/line.png");
	Texture txline;
	txline.loadFromImage(imline);
	Sprite spline;
	spline.setTexture(txline);
	spline.setTextureRect(IntRect(0, 0, 25, 577));
	spline.setScale(1, 1.33);
	spline.setPosition(1341, 0);
	//���� �� ����
	Music music;
	music.openFromFile("sounds/Muse.ogg");
	music.play();

	float musictime = 0;
	while (window.isOpen())
	{
		Event event;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 15000;
		musictime = musicclock.getElapsedTime().asSeconds();
		if (musictime > 143) { music.play(); musictime = 0; musicclock.restart(); }

		if (Keyboard::isKeyPressed(Keyboard::Tab)) //����� ���� �� ������� tab
		{
			isMenu = !isMenu;
		}
		
		//��������� ���� ������ ���
		hole1.setM(settings.getM(0));
		hole2.setM(settings.getM(1));
		hole3.setM(settings.getM(2));
		
		//���� ��������� �������
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if(isMove) moveship(ship, arrow, time);

			if (isMove && !isMenu) arrow.move(window, ship);
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					if(!onMenu && !isMenu) isMove = false;
				}
			if (isSettings)
			{
				if (hole1.getM() != 0) hole1.changePosition(window);
				if (hole2.getM() != 0) hole2.changePosition(window);
				if (hole3.getM() != 0) hole3.changePosition(window);
			}
		}

		//����� � ��������� ����
		if (isMenu || isFall || isWin)
		{
			switch (menu.click(window, settings))
			{
			case 1: return true;
			case 2: { menu.setisExit(true); break; }
			case 3: { isMenu = !isMenu;  menu.setonMenu(false); break; };
			case 4: { isSettings = true; break; }
			}
		}

		//�������������� ������� � ������ ���
		if (!isFall && !isWin)
		{
			hole2.come(time, ship);//������ ���� �����������, ���� ������� ��� �� ����
			hole1.come(time, ship);//--//--
			hole3.come(time, ship);
		}
		hole1.destroy(window, ship, &isFall);//���������� �������, ���� �������� ������
		hole2.destroy(window, ship, &isFall);//--//--
		hole3.destroy(window, ship, &isFall);//--//--
		if (!isMove && !isFall && !isWin) ship.go(time, hole1, hole2, hole3, &isFall, &isWin);//��������������� ������� �������� �������
		if (isMove || isFall || isWin) ship.soundpouse();

		//��������� �����
		window.clear();
		window.draw(spconvas);//���
		if (hole1.getM() != 0 && !hole1.getisSelected()) window.draw(hole1.getSprite());//������ ���� 1 ���� �� �������
		if (hole2.getM() != 0 && !hole2.getisSelected()) window.draw(hole2.getSprite());//������ ���� 2 ���� �� �������	
		if (hole3.getM() != 0 && !hole3.getisSelected()) window.draw(hole3.getSprite());//������ ���� 3 ���� �� �������

		if (hole1.getM() != 0 && hole1.getisSelected()) window.draw(hole1.getSpriteSelected());//������ ���� 1 ���� �������
		if (hole2.getM() != 0 && hole2.getisSelected()) window.draw(hole2.getSpriteSelected());//������ ���� 2 ���� �������	
		if (hole3.getM() != 0 && hole3.getisSelected()) window.draw(hole3.getSpriteSelected());//������ ���� 3 ���� �������

		if(!isFall && !isWin) window.draw(ship.getSprite()); //�������, ���� �� �� ����/������
		window.draw(spline); //����� ������
		window.draw(arrow.getSprite());//������� �����������

		//����
		if (isMenu || isFall || isWin) 
		{
			menu.click(window, settings);
			if(isSettings) settings.show(window, &isSettings, &isMenu, &menu.getonMenu()); //���� ������ �� ���������
		}
		

		if (!isMove && !isFall) ship.go(time, hole1, hole2, hole3, &isFall, &isWin);

		if (isFall) 
		//���� ���������
		{
			Blink blink(ship.getX() - 100, ship.getY() - 100); 
			if(isLose == 1) window.draw(blink.getSprite()); //���� ���� ���� � ����
			Font font;
			font.loadFromFile("spacefont.ttf");
			Text text("", font, 40);
			text.setPosition(90, 285);
			//��� �� ����� � ������ ������� ��������� 
			if (isLose == 1)
			{
				text.setString(L"    ��� ������� ������\n�� ���������� �������");
				window.draw(text);
			}
			if (isLose == 2)
			{
				text.setString(L"  ��� ������� �������\n  � ��������� �������");
				window.draw(text);
			}

		}
		//���� �������� 
		if (isWin)
		{
			Font font;
			font.loadFromFile("spacefont.ttf");
			Text text("", font, 40);
			text.setPosition(90, 285);
			text.setString(L"     Congratulations!");
			window.draw(text);
		}

		if (menu.getisExit()) menu.confirm(window);//������������� ������
		window.display();
	}
}

//���������� ������� �����������
void gameRunning()
{
	if (startGame()) { gameRunning(); }
}

int main()
{
	gameRunning();
	return 0;
}