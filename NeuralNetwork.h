#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <vector>

//// NEURALNETWORK CLASS contains the NN along with all of its corresponding weights and functions
class NeuralNetwork {
private:
    // Private members that contains the input, output, and hidden nodes
    std::vector<std::vector<double>> wih;
    std::vector<std::vector<double>> who;
    int inNodes;           // number of input nodes
    int hidNodes;          // number of hidden nodes
    int outNodes;      // number of output nodes

public:
    // Default constructor that initializes the NN with specificed number of nodes
    NeuralNetwork(int in, int hid, int out);

    // Constructor that initializes the NN with given weights
    NeuralNetwork(std::vector<std::vector<double>> wi, std::vector<std::vector<double>> wh);

    //Method that creates random weights depending on the number of nodes given
    std::vector<std::vector<double>> initializeWeights(int hnodes, int inodes);

    // Method for activation function
    std::vector<double> af(const std::vector<double>& vec);

    // Methods that return copies of the input and output weights
    [[nodiscard]] const std::vector<std::vector<double>>& getwih() const;
    [[nodiscard]] const std::vector<std::vector<double>>& getwho() const;

    // Method that causes the Nn to think with given inputs.
    std::vector<double> think(std::vector<double> inputs);
};



#endif //NEURALNETWORK_H
