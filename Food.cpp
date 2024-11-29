//
// Created by Kevin Gao on 2024-11-20.
//

#include "Food.h"
#include "Settings.h"
#include "BiomeHelper.h"

// Default constructor that just respawns a pellet
Food::Food() {
    respawn();  // (re)-init position & energy
}

// Respawn method
void Food::respawn() {
    // Randomly generates a position on the map
    x = BiomeHelper::randomDouble(settings.xMin, settings.xMax);
    y = BiomeHelper::randomDouble(settings.yMin, settings.yMax);

    // Sets the energy level it gives
    energy = BiomeHelper::randomInt(1, 10);
    //// TO DO: make this random and scale the radius
}

void Food::display() {
    std::cout << "Food Position: (" << x << ", " << y << ")\n";
    std::cout << "Food Energy: " << energy << "\n";
}