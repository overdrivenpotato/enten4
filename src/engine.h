#ifndef ENGINE_H
#define ENGINE_H

// Libraries
#include <vector>

// Local headers
//#include "system.h"
typedef int System;

class Engine {
public:
    Engine();

    void update(float delta);
    void mainLoop();
    void addSystem(System* system);
private:
    std::vector<System*> systems;
};

#endif // ENGINE_H
