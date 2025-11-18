#ifdef _WIN32
#include <windows.h>

// Provide WinMain that forwards to main() so MinGW's linker is satisfied.
// Use C++ linkage for main to avoid calling it with the wrong ABI.
int main();

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return main();
}
#endif
