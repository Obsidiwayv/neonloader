#include "katana.hh"

#pragma comment(lib, "bin/katana64.lib")

KatanaAppCodes RenderLoop() {
    return KatanaAppCodes::START;
}

int WinMain() {
    KatanaWindowSizes sizes {600, 300};
    KatanaWindow window{(char*)"NeonLoader", sizes};
    window.SetRenderCallback(RenderLoop);
    return 0;
}