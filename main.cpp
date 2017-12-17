#include <iostream>
#include <SFML/Graphics.hpp>
#include "Conway.h"

const int WIDTH = 1000;
const int HEIGHT = 1000;
const int PIXPERCELL = 1;
const int WORLDSIZE = WIDTH/PIXPERCELL;

using namespace std;

void renderingThread(sf::RenderWindow* window);

int main() {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);    // Frame limiter
    window.setActive(false);        // deactivate its OpenGL context

    // launch the rendering thread
    sf::Thread thread(&renderingThread, &window);
    thread.launch();

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {       // Event handeler
            if (event.type == sf::Event::Closed)
                window.close();
             else if (event.type == sf::Event::LostFocus)
                cerr << "Paused" << endl;
                //myGame.pause();

            else if (event.type == sf::Event::GainedFocus)
                cerr << "Resumed" << endl;
                //myGame.resume();

            if (event.type == sf::Event::KeyPressed) {
                cerr << "Key Pressed" << endl;
            }

            if (event.type == sf::Event::MouseWheelMoved) {
                std::cout << "Wheel movement: " << event.mouseWheel.delta << std::endl;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "The right button was pressed" << std::endl;
                } else {
                    std::cout << "The left button was pressed" << std::endl;
                }
            }
            /*if (event.type == sf::Event::MouseMoved) {
                std::cout << "Mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "Mouse y: " << event.mouseMove.y << std::endl;
            }*/
        }

    }
    //sf::sleep(sf::seconds(1.0/10)-clock.restart());

    return 0;
}


void renderingThread(sf::RenderWindow* window) {
    Conway game(WIDTH, HEIGHT, PIXPERCELL);

    int simSpeed = 10; // in number of frames
    int counter = 0;
    cerr << "Initialised" << endl;

    while (window->isOpen()) {  // the rendering loop
        window->clear(sf::Color::White);

    cerr << "Initialised" << endl;
        for (int i=0; i<WORLDSIZE; i++) {
            for (int j=0; j<WORLDSIZE; j++) {
                if (game.getCell(i, j)) {
                    sf::RectangleShape square(sf::Vector2f(10, 10));
                    square.setPosition(i*10, j*10);
                    square.setFillColor(sf::Color(0, 0, 0));
                    window->draw(square);
                }
            }
        }
    cerr << "Initialised" << endl;

        window->display();

        // LOGIC
        if (++counter==simSpeed) {
            game.update();
            counter=0;
        }
    }
}
