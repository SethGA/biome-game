#ifndef STATS_H
#define STATS_H
#include <vector>
#include <iostream>
#include "Settings.h"
#include "BiomeHelper.h"

// STATS CLASS that contains all of the implemented stats
class Stats {
    friend class Organism;
    friend class UpgradeWindow;
protected:
    double smell;
    double speed;
    double accel;
    double stamina;
    double fertility;
    double camo;

    int smellUpgrades = 0;
    int speedUpgrades = 0;
    int accelUpgrades = 0;
    int staminaUpgrades = 0;
    int fertilityUpgrades = 0;
    int camoUpgrades = 0;

    // Total number of upgrades
    int numUpgrades = 0;

public:
    // Default constructor
    Stats();

    // Copy constructor
    Stats(const std::vector<double> &stats);

    // Method to update the stats given new ones
    void updateStats(const std::vector<double> &upd);\

    // Setting random stats
    void randomStats(double min, double max);

    // Method that returns a range based on the organisms smell
    double smellFactor(double dist);

    // Methods for upgrading individual stats
    void updateSmell(std::vector<double> &upd);

    void updateSpeed(std::vector<double> &upd);

    void updateAccel(std::vector<double> &upd);

    void updateStamina(std::vector<double> &upd);

    void updateFertility(std::vector<double> &upd);

    void updateCamo(std::vector<double> &upd);

};



#endif //STATS_H
