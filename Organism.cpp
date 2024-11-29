#include "Organism.h"
#include "BiomeHelper.h"
/*
    ORGANISM CLASS
*/

// Constructor
Organism::Organism(std::string name_,bool isPredator_): nn(settings.inNodes, settings.hidNodes,  settings.outNodes), name(name_), isPredator(isPredator_), stats(settings.defaultStats), angleRange({0, 0}){

    // Initialize position
    x = BiomeHelper::randomDouble(settings.xMin, settings.xMax);
    y = BiomeHelper::randomDouble(settings.yMin, settings.yMax);

    // Initialize orientation (r), velocity (v), and delta velocity (dv)
    r = BiomeHelper::randomInt(0, 360);
    v = BiomeHelper::randomDouble(0, settings.vMax);
    dv = BiomeHelper::randomDouble(-settings.dvMax, settings.dvMax);

    // Set attributes
    dFood = 100.0;
    rFood = 0;
    fitness = 0;
    dead = 0;
    health = stats.stamina*100;
    currentTimeAlive = 0;
}

// Same constructor but with a given neural network
Organism::Organism(std::string name_,bool isPredator_, NeuralNetwork n): nn(n), name(name_), isPredator(isPredator_), stats(settings.defaultStats), angleRange({0, 0}){

    // Initialize position
    x = BiomeHelper::randomDouble(settings.xMin, settings.xMax);
    y = BiomeHelper::randomDouble(settings.yMin, settings.yMax);

    // Initialize orientation (r), velocity (v), and delta velocity (dv)
    r = BiomeHelper::randomInt(0, 360);
    v = BiomeHelper::randomDouble(0, settings.vMax);
    dv = BiomeHelper::randomDouble(-settings.dvMax, settings.dvMax);

    // Set attributes
    dFood = 100.0;
    rFood = 0;
    fitness = 0;
    dead = 0;
    health = stats.stamina*50;
}

// Constructor for like the enemy bots at the beginning of a game
Organism::Organism(std::string name_, bool isPredator_, std::string difficulty): nn(settings.inNodes, settings.hidNodes,  settings.outNodes), name(name_), isPredator(isPredator_), stats(settings.defaultStats), angleRange({0, 0}){

    // Initialize position
    x = BiomeHelper::randomDouble(settings.xMin, settings.xMax);
    y = BiomeHelper::randomDouble(settings.yMin, settings.yMax);

    // Initialize orientation (r), velocity (v), and delta velocity (dv)
    r = BiomeHelper::randomInt(0, 360);
    v = BiomeHelper::randomDouble(0, settings.vMax);
    dv = BiomeHelper::randomDouble(-settings.dvMax, settings.dvMax);

    // Set attributes
    dFood = 100.0;
    rFood = 0;
    fitness = 0;
    dead = 0;

    // Randomize stat levels based on the inputted difficulty
    if(difficulty == "EASY"){
        stats.randomStats(1, 4);
    }

    else if(difficulty == "MEDIUM"){
        stats.randomStats(4, 7);
    }

    else if(difficulty == "HARD"){
        stats.randomStats(7, 10);
    }

    health = stats.stamina*50;
}

// Neural network for an organism
void Organism::think() {
    std::vector<double> out;

    // Checking the inputs depending on if predator or prey
    if(isPredator){
        out = nn.think({rOrg, 0.0}); // this multiplies inputs by a factor of 1
    }
    else {
        out = nn.think({rFood, rPred});
    }

    // Setting the NN outputs for velocity and heading
    dvNN = double(out[0]);  // (accel=1, deccel=-1)
    drNN = double(out[1]);  // (left=1, right=-1)
}

// Update heading
void Organism::update_r() {
    r += drNN * settings.drMax * settings.dt;
    r = (r + 360) % 360;
}

// Update velocity
void Organism::update_v() {
    v += dvNN * settings.dt * stats.accel/100;

    // Can't have negative velocity
    if (v < 0) {
        v = 0;
    }

    // SPEED caps out the max velocity
    if (v > stats.speed) {
        v = stats.speed;
    }
}

// Update position
void Organism::update_pos() {
    // Just converting the heading into rectangular coordinates, adding to the current position
    double dx = v * std::cos(BiomeHelper::radians(r)) * settings.dt;
    double dy = v * std::sin(BiomeHelper::radians(r)) * settings.dt;
    x += dx;
    y += dy;

    if (settings.locked == true) { // TODO: more elegant way?
        if (x > settings.xMax) {
            x = settings.xMax;
            r += 180;
        }
        if (x < settings.xMin) {
            x = settings.xMin;
            r += 180;
        }
        if (y > settings.yMax) {
            y = settings.yMax;
            r += 180;
        }
        if (y < settings.yMin) {
            y = settings.yMin;
            r += 180;
        }
    }
}

// Get wih (weights: input-hidden)
std::vector<std::vector<double>> Organism::getWih() const {
    return nn.getwih();
}

// Get who (weights: hidden-output)
std::vector<std::vector<double>> Organism::getWho() const {
    return nn.getwho();
}

void Organism::display() const {
    std::cout << "Organism: " << name << "\n";
    std::cout << "Position: (" << x << ", " << y << ")\n";
    std::cout << "Orientation: " << r << "\n";
    std::cout << "Velocity: " << v << ", Delta velocity: " << dv << "\n";
    std::cout << "Distance to food: " << dFood << ", Orientation to food: " << rFood << "\n";
    std::cout << "Fitness: " << fitness << "\n";

    std::cout << "WIH:" << "\n";
    for (int i = 0; i < settings.hidNodes; ++i) {
        for (int j = 0; j < settings.inNodes; ++j) {
            std::cout << nn.getwih()[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "WOH:" << "\n";
    for (int i = 0; i < settings.hidNodes; ++i) {
        for (int j = 0; j < settings.inNodes; ++j) {
            std::cout << nn.getwho()[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Calculating the heading to food
double Organism::calc_heading(const Food& food) {
    // Taking distance between the organism and food
    double dx = food.x - x;
    double dy = food.y - y;
    double dist = BiomeHelper::dist(food.x, food.y, x, y);

    // Store angle range (adjusted with the smell factor)
    double maxRand = stats.smellFactor(dist);  // Random deviation scaled by distance
    double rand = BiomeHelper::randomDouble(0, maxRand)*(180.0 / M_PI);

    // Calculate the angle to the prey (theta)
    double theta = atan2(dy, dx) * (180.0 / M_PI) - r;
    angleRange[0] = theta - maxRand*(180.0 / M_PI);
    angleRange[1] = theta + maxRand*(180.0 / M_PI);

    int sign = (BiomeHelper::randomInt(0, 1) == 0) ? -1 : 1;
    theta += sign * rand;

    if (std::abs(theta) > 180) {
        theta += 360;
    }

    return theta / 180.0;
}


// Updated calc_heading to integrate smellFactor for random angle adjustments
double Organism::calc_heading(Organism& org) {
    // Calculate the distance between predator and prey
    double dx = org.x - x;
    double dy = org.y - y;
    double dist = BiomeHelper::dist(org.x, org.y, x, y);

    if(dist - org.stats.camo * 3/10 <= 0){
        return rOrg;
    }
    // Store angle range (adjusted with the smell factor)
    double maxRand = stats.smellFactor(dist);  // Random deviation scaled by distance
    double rand = BiomeHelper::randomDouble(0, maxRand)*(180.0 / M_PI);

    // Calculate the angle to the prey (theta)
    double theta = atan2(dy, dx) * (180.0 / M_PI) - r;
    angleRange[0] = theta - maxRand*(180.0 / M_PI);
    angleRange[1] = theta + maxRand*(180.0 / M_PI);

    int sign = (BiomeHelper::randomInt(0, 1) == 0) ? -1 : 1;
    theta += sign * rand;


    // Normalize the angle to the range [-180, 180] degrees
    if (std::abs(theta) > 180) {
        theta += 360;
    }

    return theta / 180.0;  // Normalize the angle to [-1, 1] range for the neural network
}

// Method that updates everything
void Organism::update(){
    // Update heading, velocity, and position
    update_r();
    update_v();
    update_pos();
    // Check if the health is greater than the stamina
    if(health > stats.stamina*100){
        health = stats.stamina*100;
    }
    // Decrementing the health, sort of "hunger"
    health -= settings.dt;

    // Checking if the health is less than 0, if so killing the organism.
    if(health <= 0){
        if(!dead) {
            dead = true;
            settings.playerPopSize--;
        }
    }
}

// Respawn method, just flips the bool.
void Organism::respawn(){
    dead = false;
}

void Organism::drawRedZone(){
    // Map organism's position to window coordinates
    float xp = BiomeHelper::map_to_window_coords(x);
    float yp = BiomeHelper::map_to_window_coords(y);
    float height = BiomeHelper::map_to_window_coords(rOrg) - BiomeHelper::map_to_window_coords(0); // Height of the triangle is dFood

    // Calculate angles for the triangle based on the real heading and angle range
    double angleOffsetMin = angleRange[0];
    double angleOffsetMax = angleRange[1];

    float baseAngle = BiomeHelper::radians(rOrg); // Heading towards the food pellet

    // Calculate the two outer points of the triangle based on angle offsets
    float xMin = xp + height * std::cos(baseAngle + angleOffsetMin);
    float yMin = yp + height * std::sin(baseAngle + angleOffsetMin);
    float xMax = xp + height * std::cos(baseAngle + angleOffsetMax);
    float yMax = yp + height * std::sin(baseAngle + angleOffsetMax);

    // Draw the isosceles triangle
    DrawTriangle({xp, yp}, {xMin, yMin}, {xMax, yMax}, RED);
}

std::vector<double> Organism::getStats(){
    return {stats.smell, stats.speed, stats.accel, stats.stamina, stats.fertility, stats.camo};
}