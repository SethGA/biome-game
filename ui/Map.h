//
// Created by Xellorated on 2024-11-22.
//

#ifndef NEURALNETWORK_H_MAP_H
#define NEURALNETWORK_H_MAP_H

#include "../Organism.h"
#include "../Food.h"
//// MAP CLASS for the main gameplay loop with the interactions between organisms and food
class Map{
private:
    // Private members that hold the positions of every organism and the round number
    int round;
    std::vector<double> playerx;
    std::vector<double> playery;
    std::vector<double> enemy1x;
    std::vector<double> enemy1y;
    std::vector<double> enemy2x;
    std::vector<double> enemy2y;
    std::vector<double> fxs;
    std::vector<double> fys;
public:
    // Default constructor that initializes with the organisms given and food, and the generation number
    Map(std::vector<std::vector<Organism>> orgs, std::vector<Food> foods, int gen);

    // Method that draws the map
    bool drawMap();

    // Method that updates the map for every frame with the new organisms and food positions
    bool updateMap(std::vector<std::vector<Organism>> orgs, std::vector<Food> foods, int gen);
};


#endif //NEURALNETWORK_H_MAP_H
