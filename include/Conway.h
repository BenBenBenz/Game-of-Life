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

        bool getCell(int x, int j);

    private:
        std::vector<std::vector<bool>> world;
};

#endif // CONWAY_H
