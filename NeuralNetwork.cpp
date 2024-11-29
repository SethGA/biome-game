#include "NeuralNetwork.h"
#include "BiomeHelper.h"
#include "Settings.h"

// Default constructor
NeuralNetwork::NeuralNetwork(int in, int hid, int out):inNodes(in), hidNodes(hid), outNodes(out), wih(initializeWeights(hid, in)), who(initializeWeights(out, hid)){
}
// Copy constructor
NeuralNetwork::NeuralNetwork(std::vector<std::vector<double>> wi, std::vector<std::vector<double>> wh):wih(wi), who(wh), inNodes(wi[0].size()), hidNodes(settings.hidNodes), outNodes(wh[0].size()){}

// Initialize the weights
std::vector<std::vector<double>> NeuralNetwork::initializeWeights(int hnodes, int inodes) {
    // Create the matrix of weights
    std::vector<std::vector<double>> mat(hnodes, std::vector<double>(inodes));

    // Randomly generate a number in the activation function range for each array index
    for (int i = 0; i < hnodes; ++i) {
        for (int j = 0; j < inodes; ++j) {
            mat[i][j] = BiomeHelper::randomDouble(-1, 1);
        }
    }

    return mat;
}

// Activation function
std::vector<double> NeuralNetwork::af(const std::vector<double>& vec) {
    // Creating a vector
    std::vector<double> result(vec.size());

    // Applying the activation function tanh to each vector element
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = std::tanh(vec[i]);
    }

    return result;
}

// RETURNING COPIES OF WEIGHTS FUNCTIONS
const std::vector<std::vector<double>>& NeuralNetwork::getwih() const{
    return wih;
}

const std::vector<std::vector<double>>& NeuralNetwork::getwho() const{
    return who;
}

// NN thinking function
std::vector<double> NeuralNetwork::think(std::vector<double> inputs) {
    // Multiplying the input nodes with the inputs, getting the activation output
    std::vector<double> h1 = BiomeHelper::matMul(NeuralNetwork::getwih(), inputs);
    h1 = af(h1);

    // Multiplying the output nodes with the inputs, getting the activation output
    std::vector<double> out = BiomeHelper::matMul(NeuralNetwork::getwho(), h1);
    out = af(out);

    return out;
}