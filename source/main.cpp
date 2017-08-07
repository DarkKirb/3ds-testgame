#include <stdio.h>
#include <3ds.h>
#include <Python.h>
uint32_t __stacksize__ = 0x100000;

int main() {
    gfxInitDefault();
    consoleInit(GFX_BOTTOM, NULL);
    if(romfsInit()<0)
        return -1;
    printf("Starting python\n");
    Py_FrozenFlag=1;
    Py_NoSiteFlag=1;
    Py_DebugFlag=1;
    Py_Initialize();
    PyRun_SimpleString("print('Started Python3.7')");
    FILE *pyinit=fopen("romfs:/init.py","rb");
    PyRun_SimpleFile(pyinit, "romfs:/init.py");
    PyRun_SimpleString("import tick");

    while(aptMainLoop()) {
        hidScanInput();
        if(hidKeysDown() & KEY_START) {
            break;
        }
        gfxFlushBuffers();
        PyRun_SimpleString("tick.advance_frame()");
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    Py_Finalize();
    gfxExit();
    return 0;
}
