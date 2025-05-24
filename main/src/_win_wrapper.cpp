#ifdef _WIN32
#include <windows.h>

// Declare your standard main
extern "C" int main(int argc, char** argv);

// Helper function to convert command line to argc/argv
static void CommandLineToArgs(int& argc, char**& argv) {
    LPWSTR* szArglist;
    int nArgs;

    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    if (szArglist == NULL) {
        argc = 0;
        argv = nullptr;
        return;
    }

    // Allocate argv
    argv = new char*[nArgs];
    for (int i = 0; i < nArgs; ++i) {
        int len = WideCharToMultiByte(CP_UTF8, 0, szArglist[i], -1, nullptr, 0, nullptr, nullptr);
        argv[i] = new char[len];
        WideCharToMultiByte(CP_UTF8, 0, szArglist[i], -1, argv[i], len, nullptr, nullptr);
    }
    argc = nArgs;

    // No need to free szArglist - handled by system
}

static void FreeArgs(int argc, char** argv) {
    for (int i = 0; i < argc; ++i) {
        delete[] argv[i];
    }
    delete[] argv;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc = 0;
    char** argv = nullptr;

    CommandLineToArgs(argc, argv);

    int result = main(argc, argv);

    FreeArgs(argc, argv);

    return result;
}
#endif
