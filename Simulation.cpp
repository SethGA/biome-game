#include "Simulation.h"
#include <iostream>

// Fitness structure used for evolution
struct playerFitness {
    int BEST = 0;             // best fitness value for a gen
    int WORST = 0;            // worst fitness value for a gen
    int SUM = 0;              // total fitness value
    int COUNT = 0;            // # of organisms
    double AVG = 0;           // sum / count
};

struct botFitness {
    int BEST = 0;             // best fitness value for a gen
    int WORST = 0;            // worst fitness value for a gen
    int SUM = 0;              // total fitness value
    int COUNT = 0;            // # of organisms
    double AVG = 0;           // sum / count
};

playerFitness pfit;
botFitness bfit;

// Default constructor that initializes all simulation memeber, so all organisms and food.
Simulation::Simulation(std::vector<Organism> play, std::vector<Organism> bots1, std::vector<Food> food): player(play), enemy1(bots1), foods(food), ui(GUI(1920, 1080, {play, bots1}, food)), gen(1){}

bool Simulation::simulate() {
    // Calculating how long it has been
    int total_time_steps = static_cast<int>(settings.genTime / settings.dt);
    int playerOrgs = settings.playerPopSize;

    // Cycle through each time step
    for (int t_step = 0; t_step < total_time_steps; ++t_step) {
        // Updating the ui with the new organisms and foods
        if (settings.plot == true && !WindowShouldClose()) {
            ui.update({player, enemy1, enemy2}, foods, gen);
        }

        //Checking if the pause button was clciked
        if (ui.isPaused) {
            t_step--;
            continue;
        }

        if (playerOrgs <= 0) {
            break;
        }

        // Checking to see if any organism has eaten food
        for (auto &food: foods) {
            for (auto &org: player) {
                if (!org.dead) {
                    // Calc the distance between org to each food
                    double food_org_dist = BiomeHelper::dist(org.x, org.y, food.x, food.y);

                    // If close enough, update fitness and health, respawn the pellet;
                    if (food_org_dist <= 0.075) {
                        org.fitness += food.energy;
                        org.health += food.energy;
                        food.respawn();
                    }

                    // Reset distance and heading to nearest food source
                    org.dFood = 100;
                    org.rFood = 0;
                }
            }
        }

        // Checking to see if any predator has eaten an organism
        for (auto &org: player) {
            for (auto &pred: enemy1) {
                if (!org.dead && !pred.dead) {
                    double org_pred_dist = BiomeHelper::dist(pred.x, pred.y, org.x, org.y);

                    // Update fitness function, kill organism
                    if (org_pred_dist <= 0.075) {
                        bool IMPLEMENT_HEALTH = false; // FIXME
                        if (IMPLEMENT_HEALTH) {
                            org.health -= 1; //add multipliers for both defence and attack stats
                            org.dv *= 5; 

                            if(org.health <= 0){
                            pred.fitness += 1;
                            org.dead = true;
                            settings.playerPopSize--;
                            }
                        } else {
                            pred.fitness += 1;
                            org.dead = true;
                            org.currentTimeAlive = t_step;
                            playerOrgs -= 1;
                        }
                    } 
                    // else if (org_pred_dist <= 0.5 - pred.getStats()[5]*0.5/10) {
                    //     org.r = pred.r;
                    // }
                }

                // Reset distance and heading
                pred.dOrg = 100;
                pred.rOrg = 0;
            }
        }

        // Calculate heading to nearest predator
        for (auto& pred : enemy1) {
            for (auto& org : player) {
                double org_pred_dist = BiomeHelper::dist(pred.x, pred.y, org.x, org.y);

                // Determine if this is the closest predator
                if (org_pred_dist < org.dPred) {
                    org.dPred = org_pred_dist;
                    org.rPred = org.calc_heading(pred);
                }
            }
        }

        // Calculate heading to nearest food source
        for (auto &food: foods) {
            for (auto &org: player) {
                if (!org.dead) {
                    double food_org_dist = BiomeHelper::dist(org.x, org.y, food.x, food.y);

                    // Determine if this is the closest food source
                    if (food_org_dist < org.dFood) {
                        org.dFood = food_org_dist;
                        org.rFood = org.calc_heading(food);
                    }
                }
            }
        }

        // Calculate heading to the nearest prey
        for (auto& org : player) {
            for (auto& pred : enemy1) {
                if (!org.dead && !pred.dead) {
                    double org_pred_dist = BiomeHelper::dist(pred.x, pred.y, org.x, org.y);

                    int camoValue = rand() % 101;

                    // Determine if this is the closest prey;
                    if (org_pred_dist < pred.dOrg && camoValue > settings.camo) {
                        pred.dOrg = org_pred_dist;
                        pred.rOrg = pred.calc_heading(org);
                    }
                }
            }
        }

        // RUN NEURAL NETWORKS FOR PLAYER AND ENEMIES
        for (auto& org: player) {
            org.think();
            org.update();
        }
        for (auto& pred: enemy1) {
            pred.think();
            pred.update(); // TEST: DO NOT UPDATE
        }

        // Checking if the simulation is endless
        if (settings.persist == true && gen == settings.gens - 1 && t_step == total_time_steps - 1) {
            t_step = 0;
        }
        // Checking if the player lost the round, exiting if so.
        if(settings.playerPopSize <= 0){
            while(!ui.lost()){
            }
            CloseWindow();
            return false;
        }
        // Exiting out of loop if the window is supposed to close.
        if (WindowShouldClose()) {
            break;
        }
    }

    // Adding currency to the players count to upgrade
    for(auto& org : player) {
        org.currency += org.fitness;
        org.dead = false; // and make all orgs alive!
        org.fitnessScore = org.fitness; // * org.currentTimeAlive * 0.1;

        /*
            note: on second thought, currentTimeAlive is a bad optimization target for the network.
            by prioritizing food, the networks learn automatically that staying alive for longer is better.
            we don't need to incentivize them to stay alive with a separate reward.
        */

        std::cout << "Fitness Score " << org.fitnessScore << std::endl;
        std::cout << " " << std::endl;
    }


    // Checking if the player lost the round, exiting if so.
    if(settings.playerPopSize == 0){
        while(!ui.lost()){
        }
        CloseWindow();
        return false;
    }
    // Pausing the game, evolving the enemies, updating round number.
    ui.isPaused = true;
    // FIXME: testing
    enemy1 = evolve(enemy1);

    // FIXME: player evolution needs to factor in time survived
    player = evolve(player);

    std::cout << "ENEMY SIZE: " << enemy1.size() << std::endl;
    std::cout << "PLAYER SIZE: " << player.size() << std::endl;

    for(auto& org : player) {
        org.fitness = 0;
    }

    for(auto& pred : enemy1) {
        pred.fitness = 0;
    }

    for (int i = 0; i < 5; ++i) {
        pfit.BEST = 0;
        pfit.WORST = 0;
        pfit.SUM = 0;
        pfit.COUNT = 0;
        pfit.AVG = 0;

        bfit.BEST = 0;
        bfit.WORST = 0;
        bfit.SUM = 0;
        bfit.COUNT = 0;
        bfit.AVG = 0;
    }

    gen++;
    return true;
}

// Main evolution function that takes organisms and creates a new more fit population
std::vector<Organism> Simulation::evolve(std::vector<Organism>& organisms){

    // Get stats from current generation, storing it in the struct.
    // TEMP FIX
    bool predFlag = false;
    Organism& firstOrganism = organisms.front();
    predFlag = firstOrganism.isPredator;

    int elitism_num = 0;
    int new_orgs = 0;

    if (predFlag) {
        elitism_num = static_cast<int>(std::floor(settings.elitism * settings.popSize));
        new_orgs = settings.popSize - elitism_num;

        for (const auto& org : organisms) {
            if (org.fitness > bfit.BEST or bfit.BEST == 0) {
                bfit.BEST = org.fitness;
            }
            if (org.fitness < bfit.WORST or bfit.WORST == 0) {
                bfit.WORST = org.fitness;
            }
            bfit.SUM += org.fitness;
            bfit.COUNT++;
        }
        bfit.AVG = bfit.SUM / bfit.COUNT;
    } else { // player
        elitism_num = static_cast<int>(std::floor(settings.elitism * settings.playerPopSize));
        new_orgs = settings.playerPopSize - elitism_num;

        for (const auto& org : organisms) {
            if (org.fitnessScore > pfit.BEST or pfit.BEST == 0) {
                pfit.BEST = org.fitnessScore;
            }
            if (org.fitnessScore < pfit.WORST or pfit.WORST == 0) {
                pfit.WORST = org.fitnessScore;
            }
            pfit.SUM += org.fitnessScore;
            pfit.COUNT++;
        }
        pfit.AVG = pfit.SUM / pfit.COUNT;
    }

    // Elitism (keep best performing organisms), sorting is based on the fitness of two adjacent organisms
    std::vector<Organism> sorted_organisms = organisms;

    if (predFlag) {
        std::sort(sorted_organisms.begin(), sorted_organisms.end(), [](const Organism& a, const Organism& b) {
            return a.fitness > b.fitness;
        });
    }
    else {
        std::sort(sorted_organisms.begin(), sorted_organisms.end(), [](const Organism& a, const Organism& b) {
            return a.fitnessScore > b.fitnessScore;
        });
    }

    // Create the new population with the weighted inputs and outputs
    std::vector<Organism> new_population;
    for (int i = 0; i < elitism_num; ++i) {
        new_population.push_back(Organism(sorted_organisms[i].name, sorted_organisms[i].isPredator, NeuralNetwork(sorted_organisms[i].getWih(),sorted_organisms[i].getWho())));
    }

    // Generate new organisms by crossing over two random ones in the sorted organism.
    for (int w = 0; w < new_orgs; ++w) {
        // Creating the indexes for two random organisms
        int idx1 = BiomeHelper::randomInt(0, elitism_num - 1);
        int idx2;
        do {
            idx2 = BiomeHelper::randomInt(0, elitism_num - 1);
        } while (idx1 == idx2);

        // SEtting the organisms
        Organism org_1 = sorted_organisms[idx1];
        Organism org_2 = sorted_organisms[idx2];

        // Crossover
        double crossover_weight = BiomeHelper::randomDouble(0.0, 1.0);

        // Make the new weighted inputs and outputs by multiplying with crossover
        std::vector<std::vector<double>> wih_new = (BiomeHelper::matrixScalarMultiply(org_1.getWih(), crossover_weight));
        wih_new = BiomeHelper::elementWiseAdd(wih_new, BiomeHelper::matrixScalarMultiply(org_2.getWih(), (1 - crossover_weight)));
        std::vector<std::vector<double>> who_new = (BiomeHelper::matrixScalarMultiply(org_1.getWho(), crossover_weight));
        who_new = BiomeHelper::elementWiseAdd(who_new, BiomeHelper::matrixScalarMultiply(org_2.getWho(), (1 - crossover_weight)));

        // Mutation algorithm
        double mutate = BiomeHelper::randomDouble(0.0, 1.0);
        if (mutate <= settings.mutate) {
            // Pick which weight matrix to mutate, 0 means input and 1 means output
            int mat_pick = BiomeHelper::randomInt(0, 1);
            double mutator = BiomeHelper::randomDouble(0.9, 1.1);

            // Mutate: WIH weights
            if (mat_pick == 0) {
                // Pick a random weight to mutate
                int index_row = BiomeHelper::randomInt(0, settings.hidNodes - 1);

                // Mutate that whole row
                for (double& val : wih_new[index_row]) {
                    val *= mutator;
                    val = std::clamp(val, -1.0, 1.0); // Make sure it's still in range for our activation function bounded on [-1, 1]
                }
            }

            // Mutate: WHO weights
            if (mat_pick == 1) {
                // Pick a random output weight to mutate
                int index_row = BiomeHelper::randomInt(0, settings.outNodes - 1);
                int index_col = BiomeHelper::randomInt(0, settings.hidNodes - 1);

                // Mutate one specific weight
                double val = who_new[index_row][index_col] * mutator;
                who_new[index_row][index_col] = std::clamp(val, -1.0, 1.0); // Make sure it's still in range for our activation function bounded on [-1, 1]
            }
        }

        // Put in the new population
        std::string name = "gen[" + std::to_string(gen) + "]-org[" + std::to_string(w) + "]";
        new_population.emplace_back(name, sorted_organisms[0].isPredator, NeuralNetwork(wih_new, who_new));
    }

    // Return evolved population
    return new_population;
}