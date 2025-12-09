#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class blok {
private:
	float x;
	float y;
	float szerokosc;
	float wysokosc;
	bool aktywny;
	int hp;
	int maxhp;
	sf::RectangleShape shape;
public:
	blok() {
		aktywny = false;
		hp = 0;
	}
	blok(float startX, float startY, float w, float h,int zycie) {

		x = startX;
		y = startY;
		szerokosc = w;
		wysokosc = h;
		aktywny = true;
		shape.setFillColor(sf::Color::Blue);
		shape.setSize({ szerokosc, wysokosc });
		shape.setPosition({ x, y });
		hp = zycie;
		maxhp = zycie;
		kolor();
	}
	void kolor() {
		if (hp == 1) shape.setFillColor(sf::Color::Blue);
		if (hp == 2) shape.setFillColor(sf::Color::Red); 
		
	}
	
	void draw(sf::RenderTarget& target) {
		if (aktywny)
			target.draw(shape);
	}
	float getX() const { return x; }
	float getY() const { return y; }
	float getSzerokosc() const { return szerokosc; }
	float getWysokosc() const { return wysokosc; }
	int getmaxhp() const { return maxhp; }

	sf::FloatRect getBounds() const {
		return shape.getGlobalBounds();
	}
	void usun() {
		aktywny = false;
	}
	void uderz() {
		if (hp > 0) {
			hp--;
			if (hp == 1) {
				shape.setFillColor(sf::Color::Blue);
			}
			if (hp <= 0) {
				aktywny = false;
			}
		}
	}
	bool czyAktywny() const {
		return aktywny;
	}
};

