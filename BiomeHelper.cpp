//
// Created by Kevin Gao on 2024-11-20.
//

#include "BiomeHelper.h"

// NAMESPACE that contains static methods for the files to use
namespace BiomeHelper {

    // Calculates the Euclidian distance between two points
    double dist(double x1, double y1, double x2, double y2) {
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    // Random number generator (double)
    double randomDouble(double min, double max) {
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }


    // Random number generator (int)
    int randomInt(int min, int max) {
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    // Matrix-scalar multiplier: multiplies every elem
    std::vector<std::vector<double>> matrixScalarMultiply(const std::vector<std::vector<double>>& matrix, double scalar) {
        std::vector<std::vector<double>> result = matrix;

        for (std::vector<double>& row : result) {
            for (double& value : row) {
                value *= scalar;
            }
        }

        return result;
    }

    // Matrix multiplier
    std::vector<double> matMul(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vec) {
        if (matrix.empty()) {
            throw std::invalid_argument("Matrix must not be empty.");
        }

        if (matrix[0].size() != vec.size() && vec.size() != 1) {
            std::cout << "Matrix[0] size: " << matrix[0].size() << "\n";
            std::cout << "Vec size: " << vec.size() << "\n";

            throw std::invalid_argument("Matrix dimensions and vector size are incompatible for multiplication.");
        }

        std::vector<double> result(matrix.size(), 0.0);

        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                result[i] += matrix[i][j] * vec[j];
            }
        }

        return result;
    }

    // Element-wise adder for two matrices
    std::vector<std::vector<double>> elementWiseAdd(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
        if (a.size() != b.size()) {
            throw std::invalid_argument("Matrices must have the same number of rows for element-wise addition.");
        }
        std::vector<std::vector<double>> result = a;

        for (size_t i = 0; i < a.size(); ++i) {
            if (a[i].size() != b[i].size()) {
                throw std::invalid_argument("Matrices must have the same number of columns for element-wise addition.");
            }
            for (size_t j = 0; j < a[i].size(); ++j) {
                result[i][j] += b[i][j];
            }
        }

        return result;
    }


    // Radians to degrees
    double radians(double degrees) {
        return degrees * (M_PI / 180.0);
    }

    // Mapping any given coordinates to the window
    double map_to_window_coords(float const coordinate) {
        // Get the screen width dynamically
        int screenWidth = GetMonitorWidth(0);

        // Map the coordinate to the screen width
        return ((coordinate + 2) / 4.0f) * screenWidth/2;
    };
}

