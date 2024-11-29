#include "GUI.h"

// Default constructor for GUI, initializes the map and upgrade window as well
GUI::GUI(double width, double height, const std::vector<std::vector<Organism>>& orgs, const std::vector<Food>& foods): window_size(width, height), organisms(orgs), foods(foods), window(settings.defaultStats), map(orgs, foods, 0), isPaused(true), dna(Vector2{25, static_cast<float>(height)}, static_cast<float>(width - 50), 50, height), showTitleScreen(true){
    // Initializing the window, starting raylib drawing
    InitWindow(window_size[0], window_size[1], "Biome");
    ToggleFullscreen();
    window_size = {static_cast<double>(GetMonitorWidth(0)), static_cast<double>(GetMonitorHeight(0))};
    dna = DNAComponent(Vector2{static_cast<float>(window_size[1]/76.8), static_cast<float>(window_size[1]/1.2)}, static_cast<float>(2.05*window_size[0]), window_size[1]/12, window_size[1]*3);
    
    // A LOT OF MAGIC NUMBERS HERE, but I just added the buttons in terms of monitor resolution so that it scales with all resolutions.
    Button play(window_size[0]/16, window_size[1]/27, (2*window_size[0]/3)-window_size[0]/16, 0, "PLAY", BLACK, window_size[0]/32 + (2*window_size[0]/3) - window_size[0]/16 - MeasureText("PLAY", window_size[1]/36)/2, window_size[1]/192, LIGHTGRAY, window_size[1]/36);
    Button quit(window_size[0]/16, window_size[1]/27, (2*window_size[0]/3)-window_size[0]/16, 2*window_size[1]/3-window_size[1]/27, "QUIT", BLACK, window_size[0]/32 + (2*window_size[0]/3) - window_size[0]/16 - MeasureText("QUIT", window_size[1]/36)/2, 2*window_size[1]/3-window_size[1]/31, LIGHTGRAY, window_size[1]/36);
    Button menu(window_size[0]/4, window_size[1]/10, window_size[0]/2-window_size[0]/8, window_size[1]/2,
                "MAIN MENU", WHITE, window_size[0]/2 - MeasureText("MAIN MENU", window_size[1]/19)/2, window_size[1]/2 + window_size[0]/50, LIGHTGRAY, window_size[1]/19);
    Button exit(window_size[0]/4, window_size[1]/10, window_size[0]/2-window_size[0]/8, 2*window_size[1]/3,
                "EXIT", WHITE,  window_size[0]/2 - MeasureText("EXIT", window_size[1]/13.5)/2, 2*window_size[1]/3 + window_size[0]/96, LIGHTGRAY, window_size[1]/13.5);

    // Putting all the buttons into the class member
    buttons.push_back(play);
    buttons.push_back(menu);
    buttons.push_back(exit);
    buttons.push_back(quit);

    dna.AddStat("Smell", 0.5f, GREEN);
    dna.AddStat("Speed", 0.5f, RED);
    dna.AddStat("Acceleration", 0.7f, BLUE);
    dna.AddStat("Stamina", 1.0f, ORANGE);
    dna.AddStat("Fertility", 0.9f, PURPLE);
    dna.AddStat("Camo", 0.9f, DARKGREEN);

    // Checking if the GUI can be started
    if(!start()){
        std::cout<<"Failed to start" << std::endl;
    }

};

// Starting the GUI
bool GUI::start(){
    // Checking if the window successfully initialized
    if(!IsWindowReady()){
        return false;
    }

    // Making sure window is properly setup
    ClearBackground(BLACK);
    SetWindowSize(window_size[0], window_size[1]);
    
    //start the game up with the tile screen, 
    while(showTitleScreen){
        displayTitleScreen();
        showTitleScreen = false;
    }



    // Drawing the map with the main gameplay loop
    map.drawMap();

    // Drawing the update window and previously mentioned button
    window.drawWindow();
    buttons[0].drawButton();
    dna.Draw();
    
    EndDrawing();

    return true;
}

// Method that updates the GUI as it loops
void GUI::update(const std::vector<std::vector<Organism>>& orgs, const std::vector<Food>& food, int gen){
    // Begin raylib drawing
    BeginDrawing();
    ClearBackground(BLACK);

    organisms = orgs;
    foods = food;

    // Updating the map with new organisms and food positions, updating upgrade window
    map.updateMap(organisms, foods, gen);
    dna.Update(GetFrameTime());
    window.drawWindow();
    dna.Draw();
    buttons[3].drawButton();


    // Checking if the game is paused (in between round), drawing the play button if so.
    if(buttons[0].isClicked() && isPaused){
        isPaused = 0;
    }

    else if(isPaused){
        buttons[0].drawButton();
    }

    // If QUIT is clicked, closes window;
    if(buttons[3].isClicked()){
        CloseWindow();
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        dna.HandleClick(GetMousePosition());
    }

    EndDrawing();
};

// Method that is called whenever the player loses the game
bool GUI::lost(){
    // Drawing the "YOU LOST" screen with the exit and main menu buttons
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("YOU LOST", window_size[0]/2 - MeasureText("YOU LOST", window_size[1]/12)/2, window_size[1]/3, window_size[1]/12, WHITE);
    buttons[1].drawButton();
    buttons[2].drawButton();
    EndDrawing();

    // If exit is clicked, returns true;
    if(buttons[2].isClicked()){
        return true;
    }

    return false;

}