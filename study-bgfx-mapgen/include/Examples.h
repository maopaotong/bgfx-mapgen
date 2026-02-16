
#pragma once
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
#include "Entity00.h"
#include "Entity01.h"
#include "Entity02.h"
#include "Views.h"
#include "fg/util/Injector.h"
#include "mapgen.h"

namespace mg
{
    using AllRenderables = RenderableTuple<Entity02>;
    using AllViews = ViewTuple<View0, View1>;
    //using AllViews = ViewTuple<View0>;

    struct Example
    {

        static void glfw_errorCallback(int error, const char *description)
        {
            // fprintf(stderr, "GLFW error %d: %s\n", error, description);
            std::cout << "GLFW error:" << description << std::endl;
        }

        AllViews &views;
        AllRenderables &list;

        INJECT(Example(AllViews &views, AllRenderables &list)) : list(list), views(views)
        {
        }

        int run()
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

            views.init();

            bgfx::setDebug(BGFX_DEBUG_TEXT       //
                           | BGFX_DEBUG_STATS    //
                           | BGFX_DEBUG_PROFILER //
                                                 //  | BGFX_DEBUG_WIREFRAME //
            );
            // bgfx::touch(v0);

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
};