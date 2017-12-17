#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Conway.h"


class Game
{
    public:
        Game(int TPS);
        virtual ~Game();

        void Run();

    private:
        void eventHandler();
        void readTemplate(std::string name);

        sf::RenderWindow m_window;
        int m_TPS;

        bool m_playing;
        sf::View m_view;

        Conway m_map;
};

#endif // GAME_H
