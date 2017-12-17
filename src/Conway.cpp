#include <iostream>
#include "Conway.h"
#include "Random.h"

Conway::Conway(int height, int width, int pixPerCell) {
    Random rdm;
    for (int i=0; i<width/pixPerCell; i++) {
        std::vector<bool> row;
        for (int j=0; j<height/pixPerCell; j++) {
            row.push_back(rdm.getBool());
        }
        world.push_back(row);
    }
}

Conway::~Conway() { }

void Conway::print() {
    int n = world.size(); int m = world.size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            std::cerr << world[i][j];
        }
        std::cerr << std::endl;
    }
}

int Conway::getNeighbors(int x, int y) {
    int n = world.size(); int m = world.size();
    int c = 0;
    for (int i=-1; i<2; i++) {
        if (x+i<0 || x+i>=n) continue;
        for (int j=-1; j<2; j++) {
            if (y+j<0 || y+j>=m || (i==0 && j==0)) continue;
            if (world[x+i][y+j]) c++;
        }
    }
    return c;
}

void Conway::update() {
    int n = world.size(); int m = world.size();
    std::vector<std::vector<bool>> worldcpy = world;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            int nbNeighbors = getNeighbors(i, j);
            if (world[i][j]) {
                if (nbNeighbors != 2 && nbNeighbors != 3) worldcpy[i][j] = false;
            } else {
                if (nbNeighbors == 3) worldcpy[i][j] = true;
            }
        }
    }
    world = worldcpy;
}

bool Conway::getCell(int x, int y) {
    return world[x][y];
}
