#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>


class Random
{
    public:
        Random();
        virtual ~Random();

        int getInt(int min, int max) {
            return rand()%(max+min+1) + min;
        }

        bool getBool() {
            return rand()%2;
        }
};

#endif // RANDOM_H
