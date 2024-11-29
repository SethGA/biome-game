#ifndef TEST_CODE_SIMULATION_H
#define TEST_CODE_SIMULATION_H
#include <vector>
#include <algorithm>
#include "Organism.h"
#include "ui/GUI.h"
#include "BiomeHelper.h"

//// SIMULATION CLASS: contains all of the organisms, GUI, and functions needed to simulate the loop.
class Simulation {
public:
    // Members
    std::vector<Organism> player;
    std::vector<Organism> enemy1;
    std::vector<Organism> enemy2;
    std::vector<Food> foods;
    GUI ui;
    int gen;

    // Constructor for object that contains all of the organisms, and the food.
    Simulation(std::vector<Organism> play, std::vector<Organism> bots1, std::vector<Food> food);

    // Simulation function that updates all NN's and pathings, loops until the end of the round, and then evolves. Will return true if the player lost and exited.
    bool simulate();

    // Function that takes organisms and evolves + randomly mutates the weights in the NN, returning a new population
    std::vector<Organism> evolve(std::vector<Organism>& organisms);

};


#endif //TEST_CODE_SIMULATION_H
