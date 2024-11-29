//
// Created by Kevin Gao on 2024-11-24.
//

#ifndef GENOME_H
#define GENOME_H

#include "ui/Button.h"

#include "raylib.h"
#include <vector>
#include <string>

struct DNAStat {
    std::string name; // Name of the stat (e.g., "Strength")
    float value;      // Value of the stat (range: 0.0 to 1.0)
    Color color;      // Color associated with the stat
    Rectangle button;

    // Constructor for convenience
    DNAStat(const std::string& statName, float statValue, Color statColor, Rectangle btn)
        : name(statName), value(statValue), color(statColor), button(btn) {}
};

class DNAComponent {
private:
    std::vector<DNAStat> stats;   // Collection of stats to display
    std::vector<Color> strandColors;
    Vector2 position;             // Top-left position of the DNA strand
    float strandLength;           // Total length of the DNA strand
    float strandRadius;           // Radius of the DNA helix
    float animationOffset;        // Offset for animation (angle in radians)
    double scalingFactor;
    int nextStrandIndex = 0;

public:
    // Constructor
    DNAComponent(Vector2 pos, float length, float radius, double scale);

    // Adds a stat to the strand
    void AddStat(const std::string& name, float value, Color color);

    // Updates animation offset
    void Update(float deltaTime);

    // Renders the DNA strand and stats
    void Draw() const;

    void HandleClick(Vector2 mousePosition);
};

#endif // DNA_COMPONENT_H
