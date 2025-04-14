#include "export.hh"
#include "brush/BrushColor.hh"
#include <GLFW/glfw3.h>

#ifndef KATANA_HH_
#define KATANA_HH_

enum KatanaAppCodes
{
    STOP,
    START,
    PAUSE
};

struct KatanaWindowSizes 
{
    int width;
    int height;
};

class KATANA_EXPORT KatanaWindow
{
private:
    KatanaAppCodes signal = KatanaAppCodes::PAUSE;

public:
    KatanaWindow(char* appTitle, KatanaWindowSizes sizes);
    int SetRenderCallback(KatanaAppCodes (*renderLoop)(KatanaWindow kWindow));
    void SetBackgroundColor(BrushColor brush);
    void Terminate();

    GLFWwindow* window;
    KatanaWindowSizes KWSizes;
};

#endif // KATANA_HH_