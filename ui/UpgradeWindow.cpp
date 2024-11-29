//
// Created by Kevin Gao on 2024-11-24.
//

#include "UpgradeWindow.h"

// Default constructor
UpgradeWindow::UpgradeWindow(Stats stat) : stats(stat){}

// Drawing the upgrade window
bool UpgradeWindow::drawWindow() {
    // Setting the position based on monitor scaling
    double x = 2*GetMonitorWidth(0)/3;
    double y = 0;
    double fontsize = GetMonitorHeight(0)/30;
    double scale = fontsize;

    // Drawing the rectangle
    DrawRectangle(x, y, GetMonitorWidth(0)/3, 2*GetMonitorHeight(0)/3, GRAY);
    DrawRectangle(x, GetMonitorWidth(0)/35, GetMonitorWidth(0)/3, 2, BLACK);
    // Drawing all the text boxes, positions are scaled by resolution
    x += GetMonitorHeight(0)/108;
    DrawText("ORGANISM STATS", x, y+GetMonitorWidth(0)/260, fontsize, WHITE);
    y += GetMonitorWidth(0)/260;
    DrawText(("Speed = " + std::to_string(static_cast<int>(stats.speed))).c_str(), x, y+2*scale, fontsize, WHITE);
    DrawText(("Acceleration = " + std::to_string(static_cast<int>(stats.accel))).c_str(), x, y+5*scale, fontsize, WHITE);
    DrawText(("Stamina = " + std::to_string(static_cast<int>(stats.stamina))).c_str(), x, y+8*scale, fontsize, WHITE);
    DrawText(("Smell = " + std::to_string(static_cast<int>(stats.smell))).c_str(), x, y+11*scale, fontsize, WHITE);
    DrawText(("Fertility = " + std::to_string(static_cast<int>(stats.fertility))).c_str(), x, y+14*scale, fontsize, WHITE);
    DrawText(("Camo = " + std::to_string(static_cast<int>(stats.fertility))).c_str(), x, y+17*scale, fontsize, WHITE);
    return true;
}

// Updating the window
bool UpgradeWindow::updateWindow(const Stats &stat) {
    // Updating the stats member then calling draw window
    stats = stat;
    drawWindow();
    return true;
}
