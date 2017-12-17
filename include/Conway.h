#ifndef CONWAY_H
#define CONWAY_H
#include <vector>

class Conway
{
    public:
        Conway();
        Conway(int height, int width, int pixPerCell);
        virtual ~Conway();

        void print();
        void update();
        int getNeighbors(int x, int y);

        bool getCell(int x, int y);
        void setCell(int x, int y, bool value);
        void setWorld(std::vector<std::vector<bool>> world);

    private:
        std::vector<std::vector<bool>> m_world;
};

#endif // CONWAY_H
