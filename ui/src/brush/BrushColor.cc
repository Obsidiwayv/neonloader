#include "brush/BrushColor.hh"
#include <iostream>

void BrushColor::SetBrushColor() {
    glClearColor(this->color1, this->color2, this->color3, 1.0);
}

BrushFromHex::BrushFromHex(int hex)
{
    this->color1 = ((hex >> 16) & 0xFF) / 255.0;
    this->color2 = ((hex >> 8) & 0xFF) / 255.0;
    this->color3 = ((hex) & 0xFF) / 255.0;
}