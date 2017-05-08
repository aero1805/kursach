#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

class Settings
{
	int amount;
	float m[3];
public:
	Settings();
	Settings(int, int[]);
	Settings& operator ++();
	Settings& operator--();
	Settings& plusm(int);
	Settings& minusm(int);
	~Settings() {};
	void show(RenderWindow&, bool*, bool*, bool*);
	void change(RenderWindow&, bool*, bool*, bool*);
	int getAmount() { return amount; }
	int getM(int i) { return m[i]; }
	void setAmount(int am) { amount = am; }
	void setM(int i, float M) { m[i] = M; }
};

Settings::Settings()
{
	amount = 1;
	m[0] = 100;
	m[1] = 0; m[2] = 0;
}
Settings::Settings(int am, int M[])
{
	amount = am;
	for (int i = 0; i < am; i++)
		m[i] = M[i];
	for (int i = am; i < 3; i++)
		m[i] = 0;
}
Settings& Settings::operator++()
{
	if (amount < 3) amount++;
	return *this;
}
Settings& Settings::operator--()
{
	if (amount > 1) amount--;
	return *this;
}
Settings& Settings::plusm(int i)
{
	if (m[i] < 200) m[i] += 10;
	return *this;
}
Settings& Settings::minusm(int i)
{
	if (m[i] >= 20) m[i] -= 10;
	return *this;
}
void Settings::show(RenderWindow& window, bool* isSettings, bool* isMenu, bool* onMenu)
{
	
	for (int i = amount; i < 3; i++)
		m[i] = 0;

	Font font;
	font.loadFromFile("spacefont.ttf");
	Text txt0("", font, 35);
	txt0.setString(L"���������");
	txt0.setStyle(Text::Bold | Text::Underlined);
	txt0.setPosition(1055, 300);


	Text txt1("", font, 20);
	txt1.setString(L"����������\n������ ���");
	txt1.setPosition(1055, 360);

	//���������� ���
	std::ostringstream am;
	am << amount;
	Text txtAmount("", font, 20);
	txtAmount.setString(am.str());
	txtAmount.setPosition(1275, 372);

	//+ ����
	Image implus;
	implus.loadFromFile("images/+.png");
	Texture txplus;
	txplus.loadFromImage(implus);
	Sprite spplus;
	spplus.setTexture(txplus);
	spplus.setTextureRect(IntRect(70, 70, 370, 330));
	spplus.setScale(0.054, 0.06);
	spplus.setPosition(1290, 375);

	//- ����
	Image imminus;
	imminus.loadFromFile("images/-.png");
	Texture txminus;
	txminus.loadFromImage(imminus);
	Sprite spminus;
	spminus.setTexture(txminus);
	spminus.setTextureRect(IntRect(70, 70, 370, 330));
	spminus.setScale(0.054, 0.06);
	spminus.setPosition(1245, 375);

	/////////////��������� ����////////////////

	//��� ������ ����
	Text txt11("", font, 20);
	txt11.setString(L"����� 1");
	txt11.setPosition(1055, 410);

	Text txtm1("", font, 20);
	std::ostringstream m1;
	m1 << m[0];
	txtm1.setString(m1.str());
	txtm1.setPosition(1235, 410);

	//- ����� ������
	Sprite spminus1;
	spminus1.setTexture(txminus);
	spminus1.setTextureRect(IntRect(70, 70, 370, 330));
	spminus1.setScale(0.054, 0.06);
	spminus1.setPosition(1205, 410);

	//+ ����� ������
	Sprite spplus1;
	spplus1.setTexture(txplus);
	spplus1.setTextureRect(IntRect(70, 70, 370, 330));
	spplus1.setScale(0.054, 0.06);
	spplus1.setPosition(1305, 410);


	//��� ������ ����
	Text txt12("", font, 20);
	txt12.setString(L"����� 2");
	txt12.setPosition(1055, 430);

	Text txtm2("", font, 20);
	std::ostringstream m2;
	m2 << m[1];
	txtm2.setString(m2.str());
	txtm2.setPosition(1235, 430);

	//- ����� ������
	Sprite spminus2;
	spminus2.setTexture(txminus);
	spminus2.setTextureRect(IntRect(70, 70, 370, 330));
	spminus2.setScale(0.054, 0.06);
	spminus2.setPosition(1205, 430);

	//+ ����� ������
	Sprite spplus2;
	spplus2.setTexture(txplus);
	spplus2.setTextureRect(IntRect(70, 70, 370, 330));
	spplus2.setScale(0.054, 0.06);
	spplus2.setPosition(1305, 430);

	//��� �������
	Text txt13("", font, 20);
	txt13.setString(L"����� 3");
	txt13.setPosition(1055, 450);

	Text txtm3("", font, 20);
	std::ostringstream m3;
	m3 << m[2];
	txtm3.setString(m3.str());
	txtm3.setPosition(1235, 450);

	//- ����� �������
	Sprite spminus3;
	spminus3.setTexture(txminus);
	spminus3.setTextureRect(IntRect(70, 70, 370, 330));
	spminus3.setScale(0.054, 0.06);
	spminus3.setPosition(1205, 450);

	//+ ����� �������
	Sprite spplus3;
	spplus3.setTexture(txplus);
	spplus3.setTextureRect(IntRect(70, 70, 370, 330));
	spplus3.setScale(0.054, 0.06);
	spplus3.setPosition(1305, 450);

	//��//
	Text OK("", font, 50);
	OK.setString("OK");
	OK.setStyle(Text::Bold | Text::Underlined);
	OK.setPosition(1060, 500);
	OK.setFillColor(Color(255, 255, 255));

	if (IntRect(1060, 490, 100, 70).contains(Mouse::getPosition(window)))
	{
		OK.setFillColor(Color(0, 0, 255));
	}

	change(window, isSettings, isMenu, onMenu);
	//���������//
	window.draw(txt0);
	//��������� ����������
	window.draw(txt1);
	window.draw(txtAmount);
	window.draw(spplus);
	window.draw(spminus);

	//��������� ������ ����
	window.draw(txt11);
	window.draw(spminus1);
	window.draw(txtm1);
	window.draw(spplus1);

	//��������� ������ ����
	if (amount > 1)
	{
		window.draw(txt12);
		window.draw(spminus2);
		window.draw(txtm2);
		window.draw(spplus2);
	}

	//��������� ������� ����
	if (amount > 2)
	{
		window.draw(txt13);
		window.draw(spminus3);
		window.draw(txtm3);	
		window.draw(spplus3);
	}

	window.draw(OK);	
}

void Settings::change(RenderWindow& window, bool* isSettings, bool* isMenu, bool* onMenu)
{
	if (IntRect(1245, 375, 20, 20).contains(Mouse::getPosition(window)))
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			--*this;
		}

	if (IntRect(1290, 375, 20, 20).contains(Mouse::getPosition(window)))
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			++*this;
		}

	if (IntRect(1205, 410, 20, 20).contains(Mouse::getPosition(window)))
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			minusm(0);
		}

	if (IntRect(1305, 410, 20, 20).contains(Mouse::getPosition(window)))
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			plusm(0);
		}

	if (amount > 1)
	{
		if (IntRect(1205, 430, 20, 20).contains(Mouse::getPosition(window)))
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				minusm(1);
			}

		if (IntRect(1305, 430, 20, 20).contains(Mouse::getPosition(window)))
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				plusm(1);
			}
	}

	if (amount > 2)
	{
		if (IntRect(1205, 450, 20, 20).contains(Mouse::getPosition(window)))
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				minusm(2);
			}

		if (IntRect(1305, 450, 20, 20).contains(Mouse::getPosition(window)))
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				plusm(2);
			}
	}
	if (IntRect(1060, 490, 100, 70).contains(Mouse::getPosition(window)))
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			*isSettings = false; *isMenu = false; *onMenu = false;
		}
}