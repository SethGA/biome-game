#include "Map.h"
#include "../BiomeHelper.h"

// Default constructor
Map::Map(std::vector<std::vector<Organism>> orgs, std::vector<Food> foods, int gen) : round(gen) {
    // Populate the vectors with the positions of the organisms
    for (const auto& org : orgs[0]) {  // player organisms
        playerx.push_back(BiomeHelper::map_to_window_coords(org.x));
        playery.push_back(BiomeHelper::map_to_window_coords(org.y));
    }
    for (const auto& org : orgs[1]) {  // enemy1 organisms
        enemy1x.push_back(BiomeHelper::map_to_window_coords(org.x));
        enemy1y.push_back(BiomeHelper::map_to_window_coords(org.y));
    }

    // Populate the vectors with the positions of the food
    for (const auto& food : foods) {
        fxs.push_back(BiomeHelper::map_to_window_coords(food.x));
        fys.push_back(BiomeHelper::map_to_window_coords(food.y));
    }
}

// Drawing map method
bool Map::drawMap() {
    // Draw background rectangle
    DrawRectangle(0, 0, 2*GetMonitorWidth(0) / 3, 2*GetMonitorHeight(0) / 3, WHITE);

    // Draw food as circles
    for (size_t i = 0; i < fxs.size(); i++) {
        DrawCircle(fxs[i], fys[i], 3, GREEN);
    }

    // Draw player organisms
    for (size_t i = 0; i < playerx.size(); i++) {
        DrawCircle(playerx[i], playery[i], 5, BLUE);
    }

    // Draw enemy1 organisms
    for (size_t i = 0; i < enemy1x.size(); i++) {
        DrawCircle(enemy1x[i], enemy1y[i], 5, RED);
    }

    // Draw enemy2 organisms
    for (size_t i = 0; i < enemy2x.size(); i++) {
        DrawCircle(enemy2x[i], enemy2y[i], 5, YELLOW);
    }

    // Draw the round information
    DrawText(("ROUND: " + std::to_string(round)).c_str(), 5, 5, 20, BLACK);
    return true;
}

// Updating the map
bool Map::updateMap(std::vector<std::vector<Organism>> orgs, std::vector<Food> foods, int gen) {

    // Clear old position vectors of organisms and foods
    playerx.clear();
    playery.clear();
    enemy1x.clear();
    enemy1y.clear();
    enemy2x.clear();
    enemy2y.clear();
    fxs.clear();
    fys.clear();

    // Populate the vectors again with updated positions
    for (const auto& org : orgs[0]) {  // player organisms
        if(!org.dead) {
            playerx.push_back(BiomeHelper::map_to_window_coords(org.x));
            playery.push_back(BiomeHelper::map_to_window_coords(org.y));
        }
    }
    for (auto& org : orgs[1]) {  // enemy1 organisms
        if(!org.dead) {
            enemy1x.push_back(BiomeHelper::map_to_window_coords(org.x));
            enemy1y.push_back(BiomeHelper::map_to_window_coords(org.y));
        }
    }
    for (const auto& org : orgs[2]) {  // enemy2 organisms
        if(!org.dead) {
        enemy2x.push_back(BiomeHelper::map_to_window_coords(org.x));
        enemy2y.push_back(BiomeHelper::map_to_window_coords(org.y));
        }
    }

    // Add updated food positions
    for (const auto& food : foods) {
        fxs.push_back(BiomeHelper::map_to_window_coords(food.x));
        fys.push_back(BiomeHelper::map_to_window_coords(food.y));
    }

    // Update the round number
    round = gen;

    // Redraw the updated map
    drawMap();

    return true;
}