#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
	float x;
	float y;
	float szerokosc;
	float wysokosc;
	float predkosc;
	sf::RectangleShape shape;

public:
	Paletka(float startX, float startY, float w, float h, float v) {
		x = startX;
		y = startY;
		szerokosc = w;
		wysokosc = h;
		predkosc = v;

		shape.setSize({ szerokosc, wysokosc });
		shape.setPosition({ x, y });
		shape.setFillColor(sf::Color::White);
		shape.setOrigin({ szerokosc / 2, wysokosc / 2 });
	};

	void moveLeft() {
		x -= predkosc;
		shape.setPosition({ x, y });
	};
	void moveRight() {
		x += predkosc;
		shape.setPosition({ x, y });
	};
	void clampToBounds(float width) {
		if (x - szerokosc / 2 < 0)
			x = szerokosc / 2;
		if (x + szerokosc / 2 > width)
			x = width - szerokosc / 2;
		shape.setPosition({ x, y });
	}

	void draw(sf::RenderTarget& target) {
		target.draw(shape);
	}
	float getX() const { return x; }
	float getY() const { return y; }
	float getSzerokosc() const { return szerokosc; }
	float getWysokosc() const { return wysokosc; }
};


