
#define BGFX_CONFIG_DEBUG 1
#include <iostream>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#include <bimg/bimg.h>
#include <string>

#if BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3native.h>

#include "util/FileUtil.h"

#include <bgfx/embedded_shader.h>
#include <stdint.h>
#include <bx/math.h>
#include "MyCallback.h"
#include "mapgen.h"
#include "util.h"
#include "renderable.h"
#include "Entity00.h"
#include "Entity01.h"
#include "Entity02.h"
#include "Views.h"

namespace mg
{
    static void glfw_errorCallback(int error, const char *description)
    {
        // fprintf(stderr, "GLFW error %d: %s\n", error, description);
        std::cout << "GLFW error:" << description << std::endl;
    }

    int _main(int argc, char **argv)
    {
        std::cout << std::filesystem::current_path() << std::endl;
        glfwSwapInterval(1); // Enable vsync
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        GLFWwindow *window = glfwCreateWindow(WNDW_WIDTH, WNDW_HEIGHT, "Hello.bgfx", nullptr, nullptr);

        bgfx::Init bgfxInit;
        bgfxInit.type = bgfx::RendererType::OpenGL;
        bgfxInit.platformData.nwh = glfwGetWin32Window(window);
        bgfxInit.resolution.width = WNDW_WIDTH;
        bgfxInit.resolution.height = WNDW_HEIGHT;
        bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
        bgfxInit.debug = true;
        MyCallback callback;
        bgfxInit.callback = &callback;
        bgfx::init(bgfxInit);

        // bgfx::setViewRect(0, 0, 0, WNDW_WIDTH, WNDW_HEIGHT);
        
        Views views;
        views.init();

        
        bgfx::setDebug(BGFX_DEBUG_TEXT       //
                       | BGFX_DEBUG_STATS    //
                       | BGFX_DEBUG_PROFILER //
                                                            | BGFX_DEBUG_WIREFRAME //
        );
        // bgfx::touch(v0);

        ListRenderable list;
        // list.list.push_back(new Entity00());
        list.list.push_back(new Entity01());
        list.list.push_back(new Entity02());

        list.init();

        // main loop
        while (!glfwWindowShouldClose(window))
        {
            views.update();
            glfwPollEvents();
            list.submit();

            bgfx::frame();
            glfwWaitEventsTimeout(0.01); // 16ms ≈ 60Hz
        } // end while

        list.destroy();
        // entity01.destroy();
        bgfx::shutdown();
        glfwTerminate();
        LogUtil::log("Done.");
        return 0;
    }
};

int main(int argc, char **argv)
{
    return mg::_main(argc, argv);
}