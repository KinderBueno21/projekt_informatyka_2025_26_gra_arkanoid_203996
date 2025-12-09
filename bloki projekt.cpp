#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Paletka.h"
#include "Pilka.h"
#include "bloki.h"

using namespace std;

const float WIDTH = 1280;
const float HEIGHT = 720;
int punkty = 0;
enum Stan { MENU, WYBOR, GRA, KONIEC, WYNIKI, POMOC };
Stan stan = MENU;
string komunikat = "";
const int poziomeBloki = 15;
const int pionoweBloki = 25;
float odstepBloki = 5.f;
float blokSzerokosc = (WIDTH - odstepBloki * (poziomeBloki - 1)) / poziomeBloki;
float blokWysokosc = (0.6 * HEIGHT - odstepBloki * (pionoweBloki - 1)) / pionoweBloki;
blok bloki[poziomeBloki][pionoweBloki];
int zycie = 2;
void srodek(sf::Text& txt, float y) {
    sf::FloatRect b = txt.getLocalBounds();
    txt.setOrigin({ b.size.x / 2, b.size.y / 2 }); 
    txt.setPosition({ WIDTH / 2, y });
}


void startPoziomu(int trudnosc) {
    punkty = 0;
    float odstep = 5.f;
    float szer = (WIDTH - odstep * (pionoweBloki - 1)) / pionoweBloki;
    float wys = (0.6f * HEIGHT - odstep * (poziomeBloki - 1)) / poziomeBloki;

    for (int i = 0; i < poziomeBloki; i++) {
        for (int j = 0; j < poziomeBloki; j++) {
            int hp = 1;
            
            if (trudnosc == 2) hp = 2;

            bloki[i][j] = blok(i * (blokSzerokosc + odstepBloki), 90 + j * (blokWysokosc + odstepBloki) + blokWysokosc / 2, blokSzerokosc, blokWysokosc, hp);
        }
    }
}


string czytajWyniki() {
    ifstream plik("wyniki.txt");
    string linia, calosc = "";
    int licznik = 1;
    
    while (getline(plik, linia)) {
        calosc += to_string(licznik) + ". Wynik: " + linia + "\n";
        licznik++;
    }
    if (calosc == "") return "Brak wynikow.";
    return calosc;
}


void zapiszWynik(int p) {
    fstream plik("wyniki.txt", std::ios::app); 
    if (plik.is_open()) {
        plik << p << endl;
        plik.close();
    }
}
int main()
{
    sf::Font font("ARIAL.TTF");
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Arkanoid Test");
    window.setFramerateLimit(144);
    Paletka pal(640.f, 690.f, 150.f, 20.f, 3.5f); 
    Pilka pilka(640.f, 540.f, 0.6f, 1.2f, 8.f); 
    int liczbablokow = poziomeBloki * pionoweBloki;

    while (window.isOpen()) {
        
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (event->is<sf::Event::KeyPressed>()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                    stan = MENU;
                }
            }
            if (event->is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                sf::Vector2i mysz = sf::Mouse::getPosition(window);

                if (stan == MENU) {
                    if (mysz.y > 200 && mysz.y < 250) stan = WYBOR;  
                    if (mysz.y > 300 && mysz.y < 350) stan = WYNIKI;  
                    if (mysz.y > 400 && mysz.y < 450) window.close(); 
                    if (mysz.y > 500 && mysz.y < 550) stan = POMOC; 
                }
                else if (stan == WYBOR) {
                    if (mysz.y > 200 && mysz.y < 250) { 
                        startPoziomu(1);
                        pilka = Pilka(640.f, 540.f, 0.6f, 1.2f, 8.f); 
                        pal=Paletka(640.f, 690.f, 150.f, 20.f, 3.5f); 
                        stan = GRA;
                    }
                    if (mysz.y > 300 && mysz.y < 350) { 
                        startPoziomu(2);
                        pilka = Pilka(640.f, 540.f, 0.6f, 1.2f, 8.f); 
                        pal = Paletka(640.f, 690.f, 150.f, 20.f, 3.5f); 
                        stan = GRA;
                    }
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));

        if (stan == MENU) {
            sf::Text t1(font, "GRAJ", 40); srodek(t1, 225);
            sf::Text t2(font, "WYNIKI", 40); srodek(t2, 325);
            sf::Text t3(font, "WYJSCIE", 40); srodek(t3, 425);
            sf::Text t4(font, "POMOC", 40); srodek(t4, 525);
            window.draw(t1); window.draw(t2); window.draw(t3); window.draw(t4);
        }

        else if (stan == WYBOR) {
            sf::Text t1(font, "POZIOM LATWY (1 strzal)", 40); srodek(t1, 225); t1.setFillColor(sf::Color::Green);
            sf::Text t2(font, "POZIOM TRUDNY (2 strzaly)", 40); srodek(t2, 325); t2.setFillColor(sf::Color::Red);
            sf::Text t3(font, "Wcisnij ESC aby wrocic", 20); srodek(t3, 500);
            window.draw(t1); window.draw(t2); window.draw(t3);
        }

        else if (stan == WYNIKI) {
            sf::Text t(font, "OSTATNIE WYNIKI:", 30); srodek(t, 50);
            sf::Text lista(font, czytajWyniki(), 20); srodek(lista, HEIGHT / 2);
            sf::Text esc(font, "ESC - Powrot", 20); esc.setPosition({ 10, HEIGHT - 30 });
            window.draw(t); window.draw(lista); window.draw(esc);
        }

        else if (stan == GRA) {
            // Logika gry 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            pal.moveLeft();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                pal.moveRight(); pal.clampToBounds(WIDTH);

            pilka.move();
            pilka.collideWalls(WIDTH, HEIGHT);
            pilka.collidePaddle(pal);

            bool wygrana = true;
            for (int i = 0; i < poziomeBloki; i++) {
                for (int j = 0; j < pionoweBloki; j++) {
                    if (bloki[i][j].czyAktywny()) wygrana = false;

                    if (pilka.sprawdzKolizjeBloku(bloki[i][j])) {
                        punkty += 10;
                    }
                }
            }

            if (pilka.getY() > HEIGHT || wygrana) {
                zapiszWynik(punkty);
                komunikat = wygrana ? "WYGRANA!" : "PRZEGRANA!";
                komunikat += " Punkty: " + to_string(punkty);
                stan = KONIEC;
            }

            sf::Text pkt(font, "PKT: " + to_string(punkty), 20);
            window.draw(pkt);
            pal.draw(window);
            pilka.draw(window);
            for (int i = 0; i < poziomeBloki; i++)
                for (int j = 0; j < pionoweBloki; j++)  
                    bloki[i][j].draw(window);
        }

        else if (stan == KONIEC) {
            sf::Text t(font, komunikat, 50); srodek(t, HEIGHT / 2);
            sf::Text info(font, "Wcisnij ESC aby wrocic do menu", 30); srodek(info, HEIGHT / 2 + 100);
            window.draw(t); window.draw(info);
        }
      
        else if (stan == POMOC) {
       
            string opis =
                "Sterowanie podczas gry polega na zmienianiu polozenia\n"
                "paletki strzalkami lub przyciskami A i D.\n\n"
                "Poruszanie sie po menu odbywa sie za pomoca myszki\n"
                "oraz przycisku ESCAPE w celu powrotu do poprzedniego ekranu.";
            sf::Text info(font, opis, 30); srodek(info, HEIGHT / 2 );
           window.draw(info);
        }
        window.display();
    }
}
