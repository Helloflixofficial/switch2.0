#include <windows.h>
#include <dbghelp.h>
#include <iostream>
#include <vector>

#pragma comment(lib, "dbghelp.lib")

int main() {
    HANDLE process = GetCurrentProcess();
    SymInitialize(process, "build\\bin", FALSE);
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);

    DWORD64 base = SymLoadModuleEx(process, NULL, "build\\bin\\fritchii.exe", NULL, 0x140000000, 0, NULL, 0);
    std::cout << "Loaded base: " << std::hex << base << std::dec << std::endl;

    std::vector<DWORD64> offsets = {
        0xec0a25, 0xddd49d, 0xddcac9, 0xdd9210, 0xdd9825,
        0xd9bf58, 0xda10d7, 0xda47b1, 0xd9cba8, 0xe2e81b,
        0xe31105, 0xe2f066
    };

    char buffer[sizeof(SYMBOL_INFO) + 256];
    PSYMBOL_INFO symbol = (PSYMBOL_INFO)buffer;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = 255;

    IMAGEHLP_LINE64 line;
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    for (DWORD64 off : offsets) {
        DWORD64 addr = base + off;
        DWORD64 displacement = 0;
        DWORD line_disp = 0;
        std::cout << "+0x" << std::hex << off << ": ";
        if (SymFromAddr(process, addr, &displacement, symbol)) {
            std::cout << symbol->Name << " ";
        } else {
            std::cout << "??? ";
        }
        if (SymGetLineFromAddr64(process, addr, &line_disp, &line)) {
            std::cout << "(" << line.FileName << ":" << line.LineNumber << ")";
        }
        std::cout << std::endl;
    }
    return 0;
}
