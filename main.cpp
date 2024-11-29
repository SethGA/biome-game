#include "Biome.h"
Settings settings;

// MAIN
int main() {
    // Creating all the food pellets
    std::vector<Food> foods;
    foods.reserve(settings.foodNum);
    for (int i = 0; i < settings.foodNum; ++i) {
        foods.emplace_back();
    }

    // Creating all the organisms friendly + enemy
    std::vector<Organism> player;
    for (int p = 0; p < settings.playerPopSize; ++p) {
        std::string name = "gen[x]-org[" + std::to_string(p) + "]";
        player.emplace_back(name, false);
    }
    std::vector<Organism> enemy1;
    for (int p = 0; p < settings.popSize; ++p) {
        std::string name = "gen[x]-org[" + std::to_string(p) + "]";
        enemy1.emplace_back(name, true, "HARD");
    }

    // Creating simulation object
    Simulation sim(player, enemy1, foods);

    // Simulation loop
    while(sim.simulate()){
    }

    return 0;
}