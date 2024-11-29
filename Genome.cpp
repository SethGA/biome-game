#include "Genome.h"
#include "raylib.h"
#include <vector>
#include <string>
#include <cmath>

// Constructor for DNAComponent
DNAComponent::DNAComponent(Vector2 pos, float length, float radius, double scale)
    : position(pos), strandLength(length), strandRadius(radius), scalingFactor(scale), animationOffset(0.0f) {
    strandColors.resize(scale/20, LIGHTGRAY); // Initialize all strands with a default color
}

void DNAComponent::AddStat(const std::string& name, float value, Color color) {
    float buttonWidth = scalingFactor/16;
    float buttonHeight = scalingFactor/64;
    float buttonX = position.x + stats.size() * (buttonWidth + scalingFactor/192);
    float buttonY = position.y + strandRadius + scalingFactor/64;

    stats.emplace_back(name, value, color, Rectangle{buttonX, buttonY, buttonWidth, buttonHeight});
}

void DNAComponent::Update(float deltaTime) {
    animationOffset += deltaTime * 2.0f;
    if (animationOffset > 2 * PI) {
        animationOffset -= 2 * PI;
    }
}

void DNAComponent::HandleClick(Vector2 mousePosition) {
    for (const auto& stat : stats) {
        if (CheckCollisionPointRec(mousePosition, stat.button) && nextStrandIndex < strandColors.size()) { //also check currency isnt 0
            strandColors[nextStrandIndex++] = stat.color; // Assign color and increment index
            //decrement currency by one
            //+1 to the stat that was pressed
            break;

        }
    }
}

void DNAComponent::Draw() const {
    float step = strandLength / (scalingFactor/96);
    float angleOffset = 0.0f;
    float lineThickness = scalingFactor/384;

    for (int i = 0; i < 20; ++i) {
        float x = position.x + i * step;
        float y1 = position.y + strandRadius * sin(animationOffset + angleOffset) - GetMonitorHeight(0)/90;
        float y2 = position.y - strandRadius * sin(animationOffset + angleOffset) - GetMonitorHeight(0)/90;

        DrawLineEx(Vector2{x, y1}, Vector2{x, y2},lineThickness, strandColors[i]); // Draw strand segment

        // Optional: Increase circle size for stats
        float circleRadius = scalingFactor/274.285714286; // Increased size for the circle
        for (const auto& stat : stats) {
            float statOffset = strandRadius * stat.value;
            DrawCircle(x, y1 + statOffset * cos(animationOffset + angleOffset), circleRadius, stat.color);
            DrawCircle(x, y2 - statOffset * cos(animationOffset + angleOffset), circleRadius, stat.color);
        }

        angleOffset += PI / 10.0f;
    }

    // Draw buttons and stat names
    for (const auto& stat : stats) {
        DrawRectangleRec(stat.button, stat.color); // Draw button
        DrawText(stat.name.c_str(), stat.button.x + stat.button.width/2 - MeasureText(stat.name.c_str(), scalingFactor/120)/2, stat.button.y + scalingFactor/384, scalingFactor/120, WHITE); // Draw text
    }
}
