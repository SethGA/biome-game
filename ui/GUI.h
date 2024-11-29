#ifndef NEURALNETWORK_H_GUI_H
#define NEURALNETWORK_H_GUI_H
#include "../Organism.h"
#include "../Food.h"
#include "Map.h"
#include "Button.h"
#include "UpgradeWindow.h"
#include "TitleScreen.h"
#include "../Genome.h"
#include <vector>
#include <random>
#include <iostream>

//// GUI CLASS that contains all the elements on the UI, including buttons, the map, and upgrade window
class GUI {
private:
    // Private members
    std::vector<double> window_size;
    Map map;
    UpgradeWindow window;
    std::vector<Button> buttons;
    std::vector<std::vector<Organism>> organisms;
    std::vector<Food> foods;
    DNAComponent dna;
    bool showTitleScreen;
public:
    // Public members
    bool isPaused; // checking if the game is paused (between rounds)

    // Constructor that specifies the window size, initializes the map and buttons using the given organisms and foods
    GUI(double width, double height, const std::vector<std::vector<Organism>>& orgs, const std::vector<Food>& foods);

    //Functions that start the GUI and update it throughout the gameplay loop
    bool start(); // returns false if the GUI could not start
    void update(const std::vector<std::vector<Organism>>& orgs, const std::vector<Food>& foods, int gen);

    // Function that is called if the player loses, displays a blank screen and returns true if the player clicks any button.
    bool lost();
};


#endif //NEURALNETWORK_H_GUI_H
