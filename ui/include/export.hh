#ifndef EXPORT_HH_
#define EXPORT_HH_

#pragma comment(lib, "OpenGL32.Lib")
#pragma comment(lib, "ui/libs/glfw3_mt.lib")
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")

#define KATANA_EXPORT __declspec(dllexport)

#endif // EXPORT_HH_