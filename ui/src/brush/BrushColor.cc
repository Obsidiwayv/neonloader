#include "brush/BrushColor.hh"
#include <string>

void BrushColor::SetBrushColor() {
    glClearColor(this->color1, this->color2, this->color3, 1.0);
}

BrushFromHex::BrushFromHex(char hex)
    : hexCode{hex} 
{
    std::string hexString{hex};
    int red = int(hexString.at(0) + hexString.at(1));
    int green = int(hexString.at(2) + hexString.at(3));
    int blue = int(hexString.at(4) + hexString.at(5));
    this->color1 = float(red);
    this->color2 = float(green);
    this->color3 = float(blue);
}