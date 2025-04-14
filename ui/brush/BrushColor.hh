#ifndef BRUSHCOLOR_HH_
#define BRUSHCOLOR_HH_

#include "GLFW/glfw3.h"
#include "export.hh"

char ReplaceHex() {}

class KATANA_EXPORT BrushColor
{
public:
    void SetBrushColor();

    float color1;
    float color2;
    float color3;
};

class BrushFromHex : BrushColor
{
private:
    char hexCode;
public:
    BrushFromHex(char hex);
};

#endif // BRUSHCOLOR_HH_