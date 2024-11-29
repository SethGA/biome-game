//
// Created by Kevin Gao on 2024-11-20.
//

#ifndef BIOMEHELPER_H
#define BIOMEHELPER_H
#include <vector>
#include <random>
#include <raylib.h>
#include <iostream>

// RNG
static std::random_device rd;   // seed
static std::mt19937 gen(rd());  // Mersenne Twister RNG

namespace BiomeHelper {
    double dist(double x1, double y1, double x2, double y2);

    // Random number generator (double)
    double randomDouble(double min, double max);

    // Random number generator (int)
    int randomInt(int min, int max);

    // Weight matrix initializer
    std::vector<std::vector<double>> initializeWeights(int hnodes, int inodes);

    // Matrix-scalar multiplier: multiplies every elem
    std::vector<std::vector<double>> matrixScalarMultiply(const std::vector<std::vector<double>>& matrix, double scalar);

    // Matrix multiplier
    std::vector<double> matMul(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vec);

    // Element-wise adder for two matrices
    std::vector<std::vector<double>> elementWiseAdd(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b);

    // Activation function
    std::vector<double> af(const std::vector<double>& vec);

    // Radians to degrees
    double radians(double degrees);

    // Convert positions to window coords
    double map_to_window_coords(float const coordinate);
};



#endif //BIOMEHELPER_H
