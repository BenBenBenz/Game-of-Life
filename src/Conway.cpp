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
        m_world.push_back(row);
    }
}

Conway::~Conway() { }

void Conway::print() {
    int n = m_world.size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            std::cerr << m_world[i][j];
        }
        std::cerr << std::endl;
    }
}

int Conway::getNeighbors(int x, int y) {
    int n = m_world.size();
    int c = 0;
    for (int i=-1; i<2; i++) {
        if (x+i<0 || x+i>=n) continue;
        for (int j=-1; j<2; j++) {
            if (y+j<0 || y+j>=n || (i==0 && j==0)) continue;
            if (m_world[x+i][y+j]) c++;
        }
    }
    return c;
}

void Conway::setCell(int x, int y, bool value) {
    m_world[x][y] = value;
}

void Conway::update() {
    int n = m_world.size();
    std::vector<std::vector<bool>> worldcpy = m_world;

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            int nbNeighbors = getNeighbors(i, j);
            if (m_world[i][j]) {
                if (nbNeighbors != 2 && nbNeighbors != 3) worldcpy[i][j] = false;
            } else {
                if (nbNeighbors == 3) worldcpy[i][j] = true;
            }
        }
    }
    m_world = worldcpy;
}

bool Conway::getCell(int x, int y) {
    return m_world[x][y];
}

void Conway::setWorld(std::vector<std::vector<bool>> world) {
    m_world = world;
}
