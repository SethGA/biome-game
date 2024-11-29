//
// Created by Kevin Gao on 2024-11-24.
//

#include "Stats.h"
#include <math.h>

// Default constructor, initializes based on the default stats in settings.h
Stats::Stats(): smell(settings.smell), speed(settings.speed), accel(settings.accel), stamina(settings.stamina), fertility(settings.fertility), camo(settings.camo){
};

// Copy constructor
Stats::Stats(const std::vector<double> &stats): smell(stats[0]), speed(stats[1]), accel(stats[2]), stamina(stats[3]), fertility(stats[4]), camo(stats[5]) {
};

// Updating the stats
void Stats::updateStats(const std::vector<double> &upd) {

    // Can't give stats that don't contain all information
    if(upd.size() != 6) {
        std::cout << "Invalid stats update" << std::endl;
        return;
    }

    // Painstakingly updating each one individually
    smell = upd[0];
    speed = upd[1];
    accel = upd[2];
    stamina = upd[3];
    fertility = upd[4];
    camo = upd[5];

};

// Method that returns random stats
void Stats::randomStats(double min, double max) {
    // Painstakingly randomizing each one individually
    smell = BiomeHelper::randomDouble(min, max);
    speed = BiomeHelper::randomDouble(min, max);
    accel = BiomeHelper::randomDouble(min, max);
    stamina = BiomeHelper::randomDouble(min, max);
    fertility = BiomeHelper::randomDouble(min, max);
    camo = BiomeHelper::randomDouble(min, max);

};

// Updated smellFactor to scale between 0 and smell, then apply exponential decay
double Stats::smellFactor(double dist) {
    // Making it so that the maximum it can output is 3 degrees when smell is 0
    double MaxAngle = 3;

    // Restrict the range
    double randFactor = MaxAngle - smell * MaxAngle/10;

    if(randFactor <= 0){
        return 0;
    }

    // Apply an exponential scaling to the random number based on distance
    // Closer distances will result in smaller randomness, further distances will allow more randomness
    double decay = std::exp(dist-3);

    // Scale the random factor by the decay, so that closer organisms result in smaller randomness
    double scaledFactor = randFactor * decay;

    // Just incase the organism is really far away and smell is really low
    if(scaledFactor > MaxAngle){
        scaledFactor = MaxAngle;
    }

    // Return the scaled randomness, which will be between 0 and the smell value
    return scaledFactor;  // The value here will represent a random deviation in radians
}

void Stats::updateSmell(std::vector<double> &upd){
    if(smellUpgrades < 7 && numUpgrades < 20){ 
        // 7 is arbitrary, but the idea is maxing out how many times you can upgrade a single stat
        // 20 is also arbitrary, set at 20 since there are 20 lines on Thomas's genome
        // do upgrade stuff here, change the smell with some kind of multiplier value
        upd[0] = smell;
        smellUpgrades++;
        numUpgrades++;
    } 
}

void Stats::updateSpeed(std::vector<double> &upd) {
    if(speedUpgrades < 7 && numUpgrades < 20){ 
        speed *= 1.5; // 1.5 is an arbitrary multiplier, will figure out good multiplier by testing
        upd[1] = speed;
        speedUpgrades++;
        numUpgrades++;
    } 
}

void Stats::updateAccel(std::vector<double> &upd) {
    if(accelUpgrades < 7 && numUpgrades < 20){ 
        accel *= 1.5; // 1.5 is an arbitrary multiplier, will figure out good multiplier by testing
        upd[2] = accel;
        accelUpgrades++;
        numUpgrades++;
    } 
}

void Stats::updateStamina(std::vector<double> &upd) {
    if(staminaUpgrades < 7 && numUpgrades < 20){ 
        stamina *= 1.5; // 1.5 is an arbitrary multiplier, will figure out good multiplier by testing
        upd[3] = stamina;
        staminaUpgrades++;
        numUpgrades++;
    } 
}

void Stats::updateFertility(std::vector<double> &upd) {
    if(fertilityUpgrades < 7 && numUpgrades < 20){ 
        fertility+=2; 
        upd[4] = fertility;
        fertilityUpgrades++;
        numUpgrades++;
    } 
}

void Stats::updateCamo(std::vector<double> &upd) {
    if(camoUpgrades < 7 && numUpgrades < 20){ 
        camo += 2; 
        upd[5] = camo;
        camoUpgrades++;
        numUpgrades++;
    } 
}
