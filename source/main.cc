#include "katana.hh"

KatanaAppCodes RenderLoop(KatanaWindow kWindow) {
    BrushFromHex bgColor(0x100d16);
    kWindow.SetBackgroundColor(bgColor);
    return KatanaAppCodes::START;
}

int WinMain() {
    KatanaWindowSizes sizes {600, 300};
    KatanaWindow window{(char*)"NeonLoader", sizes};
    window.SetRenderCallback(RenderLoop);
    return 0;
}