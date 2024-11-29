//
// Created by Kevin Gao on 2024-11-24.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include <raylib.h>
#include <vector>


//// BUTTON CLASS meant for drawing and placing buttons
class Button {
private:
    // Private members
    double width;
    double height;
    double x; // button position
    double y;
    std::string name;
    Color nameColor;
    std::vector<double> namePos; // text position, idk why i did it like this
    int fontsize;
    Color color;
public:
    // Default constructor that needs all button specifications
    Button(double w, double h, double xp, double yp, std::string_view text, Color textColor, double xt, double yt, Color col, int font);

    // Method used to darw the button
    void drawButton();

    // Function that checks if the user has clicked the button
    bool isClicked();

    // Function used to change the color of a button
    void setColor(Color col);

    // Function used to change the text of a button
    void setText(std::string_view text, double xt, double yt);
};



#endif //BUTTON_H
