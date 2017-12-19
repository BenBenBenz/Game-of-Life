#include <iostream>
#include <fstream>
#include "Game.h"

const int WIDTH = 500;
const int HEIGHT = WIDTH;
const int PIXPERCELL = 5;
const int WORLDSIZE = WIDTH/PIXPERCELL;

Game::Game(int TPS)
: m_window ({WIDTH,HEIGHT}, "Game Name"), m_TPS (TPS), m_playing (false), m_map ({WIDTH, HEIGHT, PIXPERCELL}) {
    m_window.setFramerateLimit(m_TPS);    // Frame limiter
    m_view.setCenter(WIDTH/2, HEIGHT/2);
    m_view.setSize(WIDTH+2, HEIGHT+2);
}

Game::~Game() { }

void Game::Run() {
    const sf::Time timePerTick = sf::seconds(1.0/m_TPS);

    int simSpeed = 5; // in number of frames
    int counter = 0;

    while (m_window.isOpen()) {

        eventHandler();
        m_window.clear(sf::Color::White);

        m_view.setViewport(sf::FloatRect(0, 0, 1, 1));
        m_window.setView(m_view);

        for (int i=0; i<WORLDSIZE; i++) {
            for (int j=0; j<WORLDSIZE; j++) {
                if (m_map.getCell(i, j)) {
                    sf::RectangleShape square(sf::Vector2f(PIXPERCELL, PIXPERCELL));
                    square.setPosition(i*PIXPERCELL, j*PIXPERCELL);
                    square.setFillColor(sf::Color(0, 0, 0));
                    m_window.draw(square);
                }
            }
        }

        m_window.display();

        if (++counter%simSpeed==0  && m_playing) {
            m_map.update();
            counter=0;
        }
    }

}

void Game::eventHandler() {
    sf::Event event;
    while (m_window.pollEvent(event)) {       // Event handeler
        if (event.type == sf::Event::Closed)
            m_window.close();
        else if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            m_window.setView(sf::View(visibleArea));
        }

        if (event.type == sf::Event::KeyPressed) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (m_playing) m_playing = false;
                else m_playing = true;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                m_window.close();
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
                m_map = Conway(HEIGHT, WIDTH, PIXPERCELL);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) {
                readTemplate("presets/1.txt");
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) {
                readTemplate("presets/2.txt");
            }
        }

        if (event.type == sf::Event::MouseWheelMoved) {
            m_view.zoom(1-event.mouseWheel.delta*0.05);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                std::cerr << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
                int indx = int(event.mouseButton.x/PIXPERCELL);
                int indy = int(event.mouseButton.y/PIXPERCELL);
                std::cerr << indx << " " << indy << std::endl;
                if (m_map.getCell(indx,indy)) m_map.setCell(indx,indy, false);
                else m_map.setCell(indx,indy, true);
            }
        }
    }
}

void Game::readTemplate(std::string name) {
    std::ifstream infile(name);

    for(int i = 0; i < WORLDSIZE; i++) {
        for(int j = 0; j < WORLDSIZE; j++) {
            char tmp;
            infile.get(tmp);
            if (tmp!='1' && tmp!='0') {
                j--;
                continue;
            }
            m_map.setCell(j, i, tmp=='1');
            std::cerr << tmp;
        }
        std::cerr << std::endl;
    }
    infile.close();
    std::cerr << "File " << name << " loaded" << std::endl;
}























