#define RAYLIB_CPP_SUPPORT
#include "raylib.h"
#include "TitleScreen.h"

void displayTitleScreen() {

    // Colors and fonts
    Color bgColor = DARKGREEN;
    Color textColor = RAYWHITE;

    int titleFontSize = 60;
    const char* titleText = "Biome";
    int textWidth = MeasureText(titleText, titleFontSize); // Calculate text width for centering

    int subtitleFontSize = 20;
    const char* subtitleText = "Press ENTER to start";
    int subtitleWidth = MeasureText(subtitleText, subtitleFontSize);

    // Animation variables
    float circleRadius = 10.0f;
    bool growing = true;

    // Title screen loop
    while (!WindowShouldClose()) {
        // Handle user input to start the simulation
        if (IsKeyPressed(KEY_ENTER)) {
            break; // Exit the title screen loop
        }

        // Animation logic for the background effect
        if (growing) {
            circleRadius += 0.05f;
            if (circleRadius > 30.0f) growing = false;
        } else {
            circleRadius -= 0.05f;
            if (circleRadius < 10.0f) growing = true;
        }

        // Drawing the title screen
        BeginDrawing();
        ClearBackground(bgColor);

        // Draw the animated background (pulsating circles)
        for (int i = 0; i < 5; i++) {
            DrawCircle(GetMonitorWidth(0)/2, GetMonitorHeight(0)/2, circleRadius + i * 50, Fade(LIGHTGRAY, 0.2f)); // Fade for transparency
        }

        // Draw the title text (centered)
        DrawText(titleText, (GetMonitorWidth(0) - textWidth) / 2, GetMonitorHeight(0)  / 3, titleFontSize, textColor);

        // Draw the subtitle (centered)
        DrawText(subtitleText, (GetMonitorWidth(0) - subtitleWidth) / 2, GetMonitorHeight(0) * 3 / 5, subtitleFontSize, RAYWHITE);

        EndDrawing();
    }
}
