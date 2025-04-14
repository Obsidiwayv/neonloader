#ifndef BRUSHCOLOR_HH_
#define BRUSHCOLOR_HH_

#include "GLFW/glfw3.h"
#include "export.hh"
#include <string>

class KATANA_EXPORT BrushColor
{
public:
    void SetBrushColor();

    float color1;
    float color2;
    float color3;
};

class KATANA_EXPORT BrushFromHex : public BrushColor
{
public:
    BrushFromHex(int hex);
};

#endif // BRUSHCOLOR_HH_