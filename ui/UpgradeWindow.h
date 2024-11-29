//
// Created by Kevin Gao on 2024-11-24.
//

#ifndef UPGRADEWINDOW_H
#define UPGRADEWINDOW_H
#include "../Stats.h"
#include <raylib.h>

//// UPGRADEWINDOW CLASS that contains the player organisms current statistics
class UpgradeWindow {
private:
    Stats stats;
public:
    // Default constructor
    UpgradeWindow(Stats stat);

    // Method to draw the window
    bool drawWindow();

    // Method to update the window
    bool updateWindow(const Stats &stat);
};



#endif //UPGRADEWINDOW_H
