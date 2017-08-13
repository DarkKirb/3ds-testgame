#include <stdio.h>
#include <3ds.h>
#include <Python.h>
#include <citro3d.h>
#include <renderer.hpp>
#include <globals.hpp>
#include <string>
#include <stdio.h>
#include <png.hpp>
bool running=true;
uint32_t __stacksize__ = 0x100000;

int main() {
    gfxInitDefault();
    gfxSet3D(false);
    consoleInit(GFX_BOTTOM, NULL);
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    romfsInit();
    Thread rendererThread = threadCreate((void(*)(void*))(&::rendererThread),0, 65536, 0x20, -1, false);
    PNG *pngs[17];
    char buf[32];
    for(int i=0;i<17;i++) {
        snprintf((char*)(&buf), 32, "romfs:/pics/loading/frame%02i.png", i);
        pngs[i] = new PNG(buf);
    }
    renderers++;
    renderers->push_back([pngs](unsigned char * vram) -> void {
                static int anim_frame=0;
                static bool direction = false;
                char buf[32];
                pngs[anim_frame]->copyImage(vram);
                if(!direction)
                    anim_frame++;
                else
                    anim_frame--;

                if(anim_frame > 16) {
                    anim_frame=16;
                    direction=true;
                }
                if(anim_frame < 0) {
                    anim_frame=0;
                    direction=false;
                }
            });
    renderers--;


    printf("Starting python\n");
    Py_FrozenFlag=1;
    Py_NoSiteFlag=1;
    Py_DebugFlag=1;
    Py_Initialize();
    PyRun_SimpleString("print('Started Python3.7')");
    FILE *pyinit=fopen("romfs:/init.py","rb");
    PyRun_SimpleFile(pyinit, "romfs:/init.py");
    PyRun_SimpleString("import tick");

    renderers++;
    renderers->clear();
    renderers--;
    for(int i=0;i<17;i++) {
        delete pngs[i];
    }

    while(aptMainLoop()) {
        hidScanInput();
        if(hidKeysDown() & KEY_START) {
            break;
        }
        PyRun_SimpleString("tick.advance_frame()");
    }
    running=false;
    Py_Finalize();
    gfxExit();
    return 0;
}
