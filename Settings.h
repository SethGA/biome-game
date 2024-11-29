#pragma
#include <vector>

//// STARTING SETTINGS TO TINKER FOR THE SIMULATION
struct Settings {

    // EVOLUTION SETTINGS
    int popSize = 10;        // number of bot organisms
    int playerPopSize = 20;  // numker of player organisms
    int foodNum = 100;       // number of food particles
    int gens = 50;            // number of generations
    double elitism = 0.20;    // elitism (selection bias)
    double mutate = 0.10;     // mutation rate

    // SIMULATION SETTINGS
    int genTime = 60;       // generation length      (seconds)
    double dt = 0.02;         // simulation time step   (dt)
    int drMax = 720;         // max rotational speed   (degrees per second)
    double vMax = 0.25;       // max velocity           (units per second)
    double dvMax = 0.25;     // max acceleration (+/-) (units per second^2)

    double xMin = -1.98;      // arena western border
    double xMax = 3.3;       // arena eastern border
    double yMin = -1.98;      // arena southern border
    double yMax = 2.22;       // arena northern border

    bool plot = true;         // plot environment?
    bool locked = true;     // lock movement to bounds?
    bool persist = true;     // keep running sim after final gen?
    bool showPath = false;   // show pathing of each bot?
    bool isPaused = false;   // Add a variable to track pause state

    // NEURAL NET SETTINGS
    int inNodes = 2;           // number of input nodes
    int hidNodes = 5;           // number of hidden nodes
    int outNodes = 2;           // number of output nodes

    // BASE STATS
    double smell = 0.5;
    double speed = 1;
    double accel = 0.25;
    double stamina = 10;
    double fertility = 1;
    double camo = 1;

    std::vector<double> defaultStats = {smell, speed, accel, stamina, fertility, camo};
};

extern Settings settings;