#include "engine.h"
#include <iostream>

Engine::Engine() :
systems(5)
{

}

void Engine::addSystem(System *system) {
    systems.push_back(system);
}
