//
// Created by Kevin Gao on 2024-11-24.
//

#include "Button.h"

// Default constructor for a button
Button::Button(double w, double h, double xp, double yp, std::string_view text, Color textColor, double xt, double yt, Color col, int font) : width(w), height(h), x(xp), y(yp), name(text), nameColor(textColor), namePos({xt, yt}), color(col), fontsize(font){}

// Drawing the button
void Button::drawButton() {
    // Creating a rectangle with the specifications
    DrawRectangle(x, y, width, height, color);

    // Putting the text on top
    DrawText(name.c_str(), namePos[0], namePos[1], fontsize, nameColor);
}

// Checking for button click
bool Button::isClicked() {
    // Seeing if left clicks is pressed
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // Getting the position of the mouse
        Vector2 mousePosition = GetMousePosition();

        // Seeing if it lies within the button range, returning true if so.
        if (mousePosition.x >= x && mousePosition.x <= x + width &&
            mousePosition.y >= y && mousePosition.y <= y + height) {
            return true;
            }
    }

    return false;
};

// Setting button color
void Button::setColor(Color col) {
    color = col;
}

// Setting button text
void Button::setText(std::string_view text, double xt, double yt) {
    name = text;
    namePos = {xt, yt};
}