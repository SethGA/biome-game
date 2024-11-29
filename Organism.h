#ifndef ORGANISM_H
#define ORGANISM_H
#include "NeuralNetwork.h"
#include "Food.h"
#include "Stats.h"
#include <raylib.h>
#include <iostream>
#include <string>
#include <vector>

//// ORGANISM CLASS that contains all the functionality for those little moving blips
class Organism {
private:
// Private members that consist of each organisms stats and NN
    NeuralNetwork nn;
    Stats stats;
public:
    bool isPredator;         // Determining if the organism is a predator or prey
    bool dead;               // bool value to determine if an organism died
    double x;                // x-coord
    double y;                // y-coord
    int r;                   // orientation   [0, 360]
    double v;                // velocity      [0, vMax]
    double dv;               // dv
    double dFood;            // distance to nearest food
    double rFood;            // orientation to nearest food
    double dOrg;             // distance to nearest prey
    double rOrg;             // orientation to nearest prey
    double health;           // Attribute that determines how long the organism goes without food
    int fitness;             // fitness (food count)
    double dvNN;
    double drNN;
    std::vector<double> angleRange; // used for the smell mechanic and debugging
    std::string name;        // name of the organism

    // player only
    int currentTimeAlive;    // allows for predator-based fitness function
    double fitnessScore;      // FIXME: confusing name
    double rPred;
    double dPred;
    int currency;

    // Default constructor
    Organism(std::string name_, bool isPredator_);

    // Constructor with a given neural network
    Organism(std::string name_,bool isPredator_, NeuralNetwork n);

    // Constructor that randomizes stats based on difficulty
    Organism(std::string name_, bool isPredator_, std::string difficulty);

    // Neural network
    void think();

    // Update heading
    void update_r();

    // Update velocity
    void update_v();
    // Update position
    void update_pos();

    // Calculate the heading to food for prey
    double calc_heading(const Food& food);

    // Calculate the heading to prey for predators
    double calc_heading(Organism& org);

    // Method that calls all the update methods
    void update();

    // Method to respawn an organism
    void respawn();

    // Get wih
    std::vector<std::vector<double>> getWih() const;

    // Get who
    std::vector<std::vector<double>> getWho() const;

    // Get stats
    void display() const;

    // Bug testing thing
    void drawRedZone();

    // Return an array of the organisms stats
    std::vector<double> getStats();
};



#endif //ORGANISM_H
