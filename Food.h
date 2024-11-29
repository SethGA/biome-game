//
// Created by Kevin Gao on 2024-11-20.
//

#ifndef FOOD_H
#define FOOD_H
//// FOOD CLASS for the pellets on the map that give eneryg to prey
class Food {
public:
    double x;                // x-coord
    double y;                // y-coord
    int energy;              // energy level

    // Default Constructor
    Food();

    // Method that randomly respawns the food pellet anywhere on the map
    void respawn();

    // Method that just shows the public member values
    void display();
};



#endif //FOOD_H
